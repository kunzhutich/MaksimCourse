#include <iostream>
#include <memory>

using namespace std;

void hello() {
    cout << "Hello, World!" << endl;
}

struct Point {
    int x, y;
};

int main() {
    // POINTER
    // int x = 10;
    // int* p = &x;  // &x = address of x
    // cout << "x = " << x << endl;
    // cout << "p points to address " << p << endl;
    // cout << "*p dereferences to " << *p << endl; // *p = value at that address


    // POINTERS AND ARRAYS
    // int arr[3] = {10, 20, 30};
    // int* arrP = arr;
    // cout << *arrP << endl;
    // cout << *(arrP + 1) << endl;
    // cout << arrP[2] << endl;


    // DYNAMIC MEMORY HEAP
    // int* pointer = new int(42);
    // cout << *pointer << endl;
    // delete pointer;

    // int* arrayP = new int[5];
    // arrayP[0] = 10;
    // arrayP[1] = 20;
    // cout << arrayP[1] << endl;
    // delete[] arrayP;


    // POINTERS TO POINTERS
    // int x = 100;
    // int* p = &x;
    // int** pp = &p;
    // cout << **pp << endl;
    // cout << *pp << endl;
    // cout << pp << endl;
    // cout << &pp << endl;

    // FUNCTION POINTER
    // void (*fp)() = hello;
    // fp();
    // hello();


    // POINTERS AND CLASSES
    // Point* p = new Point{3, 4};
    // cout << p->x << ", " << p->y << endl;
    // delete p;


    // SMART POINTERS
    // unique_ptr --> sole ownership
    // shared_ptr --> shared ownership
    // weak_ptr --> non-owning reference

    // unique_ptr<int> p1 = make_unique<int>(42);
    // cout << *p1 << endl;

    // shared_ptr<int> p2 = make_shared<int>(99);
    // shared_ptr<int> p3 = p2;
    // cout << *p3 << endl;
}