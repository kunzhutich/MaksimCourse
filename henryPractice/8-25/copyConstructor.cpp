#include <iostream>

using namespace std;

class Number {
public:
    int* n;

    Number(int num) {
        n = (int*) malloc(sizeof(int));     // heap is allocating memory in size of int, it returns a pointer to that memory address, n is storing that address
        *n = num;       // dereferencing n to store the actual number in that memory address
    }

    Number(const Number& from) {            //without this --> memory leak 
        n = (int *) malloc(sizeof(int));
        *n = *(from.n);
    }

    ~Number() {
        free(n);
    }

    int getN() {
        return *n;
    }
};

int main() {
    Number num1(3);
    cout << "num1 = " << num1.getN() << endl;

    Number num2 = num1;
    cout << "num2 = " << num2.getN() << endl;

    *(num1.n) = 33;

    cout << "num1 = " << num1.getN() << endl;
    cout << "num2 = " << num2.getN() << endl;

    return 0;
}