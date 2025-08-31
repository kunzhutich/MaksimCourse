#include <iostream>

template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};
template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};
template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};


int main() {
    std::cout << Factorial<5>::value << std::endl;

    std::cout << Fibonacci<5>::value << std::endl;
}