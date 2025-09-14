#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class A {
    int A = 0;
};

class B {
    int B = 0;
};

template <typename T>
class ControlBlock {        // control block
    mutex countMutex;

    T* _ptr;
    int count = 1;

public:
    ControlBlock(T* ptr) : _ptr(ptr) {}
    ~ControlBlock() { delete _ptr; }

    void incCount() {
        const lock_guard<mutex> lock(countMutex);
        ++count;
    }
    bool decCount() { 
        bool shouldDelete = false;
        {
            const lock_guard<mutex> lock(countMutex);
            --count;

            if (count == 0) shouldDelete = true;
        }
        if (shouldDelete) delete this;

        return shouldDelete;
    }
    int getCount() { 
        const lock_guard<mutex> lock(countMutex);
        return count;
    }
    // mutex* getMutex() {     //bad practice but kinda ok in this case
    //     return &countMutex;
    // }
};

template<typename T>
class MySharedPtr {
    ControlBlock<T>* cb;

public:
    MySharedPtr(T* ptr) : cb(new ControlBlock<T>(ptr)) {}
    MySharedPtr(const MySharedPtr& from) : cb(from.cb) {
        if (cb) cb->incCount();
    }
    MySharedPtr& operator=(MySharedPtr& from) {
        if (this == &from) return *this;

        if(cb->decCount()) {
            cb = nullptr;
        }

        cb = from.cb;
        cb->incCount();
        return *this;
    }
    ~MySharedPtr() {
        if(cb->decCount()) {
            delete cb;
            cb = nullptr;
        }
    }
    void getCount() {
        cout << "Current ControlBlock = " << cb->getCount() << endl;
    }
};

int main() {
    MySharedPtr p1(new A());
    {
        MySharedPtr p2 = p1;

        MySharedPtr pB(new B());
        pB.getCount();
        {
            MySharedPtr p3 = p2;
            p1.getCount(); 
            p2.getCount(); 
            p3.getCount();

            // p2 = pB;
            pB.getCount();
        }

        p1.getCount(); 
        p2.getCount();
    }

    p1.getCount();
}