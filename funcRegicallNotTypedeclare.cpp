#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <functional>
#include <typeinfo>
#include <stdexcept>
#include <memory>

template<typename... Args>
struct FunctionWrapper {
    std::function<unsigned long long(Args...)> func;
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

template<typename... Args>
void registerFunction(const std::string &name, unsigned long long (*func)(Args...))
{
    registeredFunctions[name] = AnyFunctionWrapper(FunctionWrapper<Args...>{func});
}

template<typename... Args>
unsigned long long callFunction(const std::string &name, Args &&... args)
{
    auto it = registeredFunctions.find(name);
    if (it != registeredFunctions.end()) {
        try {
            using WrapperType = FunctionWrapper<Args...>;
            WrapperType &funcWrapper = it->second.get<WrapperType>();
            return funcWrapper.func(std::forward<Args>(args)...);
        } catch (const std::runtime_error &) {
            throw std::runtime_error("Function signature mismatch for: " + name);
        }
    } else {
        throw std::runtime_error("Function not found: " + name);
    }
}

unsigned long long myIntFunction(int a, double b, char c, int &rst)
{
    std::cout << "myIntFunction called with: " << a << ", " << b << ", " << c << std::endl;
    rst = a + static_cast<int>(b) + static_cast<int>(c);
    return 0;
}

unsigned long long myTupleFunction(int a, double b, char c, std::tuple<int, double, char> &rst)
{
    std::cout << "myTupleFunction called with: " << a << ", " << b << ", " << c << std::endl;
    rst = std::make_tuple(a * 2, b * 2, c + 1);
    return 0;
}

unsigned long long myDoubleFunction(double a, int b, double &rst)
{
    std::cout << "myDoubleFunction called with: " << a << ", " << b << std::endl;
    rst = a / b;
    return 0;
}

unsigned long long myStringFunction(std::string &rst)
{
    std::cout << "myStringFunction called" << std::endl;
    rst = "Hello from myStringFunction";
    return 0;
}

int main()
{
    registerFunction("myIntFunction", myIntFunction);
    registerFunction("myTupleFunction", myTupleFunction);
    registerFunction("myDoubleFunction", myDoubleFunction);
    registerFunction("myStringFunction", myStringFunction);

    std::cout << registeredFunctions.size() << std::endl;
    for (auto &itm: registeredFunctions) {
        std::cout << itm.first << std::endl;
    }

    int intResult;
    callFunction("myIntFunction", 1, 2.5, 'a', intResult);
    std::cout << "intResult: " << intResult << std::endl;

    std::tuple<int, double, char> tupleResult;
    callFunction("myTupleFunction", 1, 2.5, 'a', tupleResult);
    std::cout << "tupleResult: (" << std::get<0>(tupleResult) << ", " << std::get<1>(tupleResult) << ", "
              << std::get<2>(tupleResult) << ")" << std::endl;

    double doubleResult;
    callFunction("myDoubleFunction", 3.14, 10, doubleResult);
    std::cout << "doubleResult: " << doubleResult << std::endl;

    std::string stringResult;
    callFunction("myStringFunction", stringResult);
    std::cout << "stringResult: " << stringResult << std::endl;

    return 0;
}
