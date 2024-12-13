#include <tuple>
#include <stdexcept>

template<size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
get_element_by_index(size_t index, std::tuple<Tp...>& t, void* result) {}


template<size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
get_element_by_index(size_t index, std::tuple<Tp...>& t, void* result)
{
    if (index == I) {
        *reinterpret_cast<typename std::tuple_element<I, std::tuple<Tp...>>::type*>(result) = std::get<I>(t);
    } else {
        get_element_by_index<I + 1, Tp...>(index, t, result);
    }
}

template<typename... Tp>
void get_element(size_t index, std::tuple<Tp...>& t, void* result) {
    if (index >= sizeof...(Tp)) {
        throw std::out_of_range("Index out of range");
    }
    get_element_by_index(index, t, result);
}



int main() {
    std::tuple<int, std::string, double> t(10, "hello", 3.14);

    size_t index = 1;

    std::string value;
    get_element(index, t, &value);

    int intValue;
    get_element(0,t,&intValue);


    double doubleValue;
    get_element(2,t, &doubleValue);


    return 0;
}
