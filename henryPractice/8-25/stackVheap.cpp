#include <iostream>

using namespace std;

class Simple {
public:
    int x;

};

class Stack {
public:
    Simple simple;
};

class Heap {
public:
    Simple *simple;

    Heap(int x) {
        simple = new Simple;
        this->simple->x = x;
    }
};

int main() {
    // Simple simpleA;
    // Simple simpleB;
    // simpleA.x = 4;
    // simpleB.x = 0;

    // cout << "INITIAL... " << endl;
    // cout << "simpleA.x = " << simpleA.x << endl;
    // cout << "simpleB.x = " << simpleB.x << endl;

    // simpleB = simpleA;

    // cout << "B = A... " << endl;
    // cout << "simpleA.x = " << simpleA.x << endl;
    // cout << "simpleB.x = " << simpleB.x << endl;

    // simpleB.x = 20;
    // cout << "Changing B..." << endl;
    // cout << "simpleA.x = " << simpleA.x << endl;
    // cout << "simpleB.x = " << simpleB.x << endl;



    // Stack stackA;
    // Stack stackB;
    // stackA.simple.x = 4;
    // stackB.simple.x = 0;

    // cout << "INITIAL... " << endl;
    // cout << "stackA.simple.x = " << stackA.simple.x << endl;
    // cout << "stackB.simple.x = " << stackB.simple.x << endl;

    // stackB = stackA;

    // cout << "B = A... " << endl;
    // cout << "stackA.simple.x = " << stackA.simple.x << endl;
    // cout << "stackB.simple.x = " << stackB.simple.x << endl;

    // stackB.simple.x = 20;
    // cout << "Changing B..." << endl;
    // cout << "stackA.simple.x = " << stackA.simple.x << endl;
    // cout << "stackB.simple.x = " << stackB.simple.x << endl;



    Heap heapA(4);
    Heap heapB(0);

    cout << "INITIAL... " << endl;
    cout << "heapA.simple->x = " << heapA.simple->x << endl;
    cout << "heapB.simple->x = " << heapB.simple->x << endl;

    heapB = heapA;  // this is wrong because now there is memory leakage in heap due to heapB's object lost ref count and is just existing in heap

    cout << "B = A... " << endl;
    cout << "heapA.simple->x = " << heapA.simple->x << endl;
    cout << "heapB.simple->x = " << heapB.simple->x << endl;

    heapB.simple->x = 20;
    cout << "Changing B..." << endl;
    cout << "heapA.simple->x = " << heapA.simple->x << endl;
    cout << "heapB.simple->x = " << heapB.simple->x << endl;
}