#include <iostream>

template<typename T>
T add(T a, T b) {
    return a + b;
}

template<typename T>
class Box {
    T _value;
public:
    Box(T value) : _value(value) {};
    T getValue() {
        return _value;
    }
};


int main() {
    int x = 4;
    int y = 9;
    std::cout << add(x, y) << std::endl;

    std::string str1 = "Hello ";
    std::string str2 = "World!";
    std::cout << add(str1, str2) << std::endl;


    Box<int> box1(33);
    Box<float> box2(3.3);
    std::cout << "Value of box1: " << box1.getValue() << std::endl;
    std::cout << "Value of box2: " << box2.getValue() << std::endl;
}