#include <iostream>
using namespace std; 

class A {
    int H = 0;
};

class RefCount {
    int count = 0;

public:
    void incCount() { ++count; }
    void decCount() { --count; }
    int getCount() { return count; }
};

class MySharedPtr {
    A* _ptr;
    RefCount* c_ptr;

public:
    MySharedPtr(A* ptr) : _ptr(ptr), c_ptr(new RefCount()) {
        c_ptr->incCount();
    }
    MySharedPtr(const MySharedPtr& from) : _ptr(from._ptr), c_ptr(from.c_ptr) {
        c_ptr->incCount();
    }
    MySharedPtr& operator=(MySharedPtr& from) {
        if (this == &from) return *this;

        if (c_ptr != nullptr) {
            c_ptr->decCount();
            
            if (c_ptr->getCount() == 0) {
                delete _ptr;
                delete c_ptr;
                _ptr = nullptr;
                c_ptr = nullptr;
            }
        }

        _ptr = from._ptr;
        c_ptr = from.c_ptr;
        c_ptr->incCount();
        return *this;
    }
    ~MySharedPtr() {
        if (c_ptr != nullptr) {
            c_ptr->decCount();

            if (c_ptr->getCount() == 0) {
                delete _ptr;
                delete c_ptr;
                _ptr = nullptr;
                c_ptr = nullptr;
            }
        }
    }

    void getCount() {
        cout << "Current refCount = " << c_ptr->getCount() << endl;
    }
};

int main() {
    MySharedPtr p1(new A());

    {
        MySharedPtr p2 = p1;
        
        {
            MySharedPtr p3 = p2;
            p1.getCount(); 
            p2.getCount(); 
            p3.getCount();
        }

        p1.getCount(); 
        p2.getCount();
    }

    p1.getCount();
}