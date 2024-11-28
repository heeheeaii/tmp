#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <functional>
#include <typeinfo>
#include <stdexcept>
#include <memory>

template<typename ReturnType, typename... Args>
struct FunctionWrapper {
    std::function<ReturnType(Args...)> func;
};

class AnyFunctionWrapper {
public:
    AnyFunctionWrapper()
    {
    }

    template<typename T>
    AnyFunctionWrapper(T funcWrapper) : content(new Model<T>(std::move(funcWrapper)))
    {}

    template<typename T>
    T &get()
    {
        if (typeid(T) != content->type()) {
            throw std::runtime_error("Incorrect type access");
        }
        return static_cast<Model <T> *>(content.get())->data;
    }

private:
    struct Concept {
        virtual ~Concept() = default;

        virtual const std::type_info &type() const = 0;
    };

    template<typename T>
    struct Model : Concept {
        Model(T data) : data(std::move(data))
        {}

        const std::type_info &type() const override
        { return typeid(T); }

        T data;
    };

    std::unique_ptr<Concept> content;
};

std::map<std::string, AnyFunctionWrapper> registeredFunctions;

template<typename ReturnType, typename... Args>
void registerFunction(const std::string &name, ReturnType (*func)(Args...))
{
    registeredFunctions[name] = AnyFunctionWrapper(FunctionWrapper<ReturnType, Args...>{func});
}

template<typename ReturnType, typename... Args>
auto callFunction(const std::string &name, Args &&... args) -> ReturnType
{
    auto it = registeredFunctions.find(name);
    if (it != registeredFunctions.end()) {
        try {
            using WrapperType = FunctionWrapper<ReturnType, Args...>;
            WrapperType &funcWrapper = it->second.get<WrapperType>();
            return funcWrapper.func(std::forward<Args>(args)...);
        } catch (const std::runtime_error &) {
            throw std::runtime_error("Function signature mismatch for: " + name);
        }
    } else {
        throw std::runtime_error("Function not found: " + name);
    }
}

int myIntFunction(int a, double b, char c)
{
    std::cout << "myIntFunction called with: " << a << ", " << b << ", " << c << std::endl;
    return a + static_cast<int>(b) + static_cast<int>(c);
}

std::tuple<int, double, char> myTupleFunction(int a, double b, char c)
{
    std::cout << "myTupleFunction called with: " << a << ", " << b << ", " << c << std::endl;
    return std::make_tuple(a * 2, b * 2, c + 1);
}

double myDoubleFunction(double a, int b)
{
    std::cout << "myDoubleFunction called with: " << a << ", " << b << std::endl;
    return a / b;
}

std::string myStringFunction()
{
    std::cout << "myStringFunction called" << std::endl;
    return "Hello from myStringFunction";
}

int main3()
{
    registerFunction("myIntFunction", myIntFunction);
    registerFunction("myTupleFunction", myTupleFunction);
    registerFunction("myDoubleFunction", myDoubleFunction);
    registerFunction("myStringFunction", myStringFunction);

    std::cout << registeredFunctions.size() << std::endl;
    for (auto &itm: registeredFunctions) {
        std::cout << itm.first << std::endl;
    }

    int intResult = callFunction<int>("myIntFunction", 1, 2.5, 'a');
    std::cout << "intResult: " << intResult << std::endl;

    auto tupleResult = callFunction<std::tuple<int, double, char>>("myTupleFunction", 1, 2.5, 'a');
    std::cout << "tupleResult: (" << std::get<0>(tupleResult) << ", " << std::get<1>(tupleResult) << ", "
              << std::get<2>(tupleResult) << ")" << std::endl;

    auto doubleResult = callFunction<double>("myDoubleFunction", 3.14, 10);
    std::cout << "doubleResult: " << doubleResult << std::endl;

    auto stringResult = callFunction<std::string>("myStringFunction");
    std::cout << "stringResult: " << stringResult << std::endl;

    return 0;
}
