#include <iostream>

using namespace std;

class A {
public:
    static int countA;

    A() :b(0), c(0), a(0) {
        cout << " default ctor: A() countA:" << ++countA << endl;
    }

    A(const A & from) :b(from.a), c(from.b), a(from.c) {
        cout << "copy ctor: A() countA:" << ++countA << endl;
    }

    // it's a good practice to mark destructor as noexcept: destructor must never rise any exception
    virtual ~A() noexcept {
        cout << "destructor ~A() countA:" << --countA << endl;
    }

protected: int b;

private:   int c;

public:    
    int a;
    virtual int sub(int x, int y) {
        cout << " sub(" << x << "," << y << ") " << endl;
        return x + y + 10;
    }
};


class B : public A {
public:
    static int countB;
    int x = 0;
    B():x(0) { 
        // it's better to constrace x inside initialize list insted of here:
        // x = 0;
        cout << " B() countB:" << ++countB << endl;
    }

    // virtual is optional here if the base class function is virtual
    // then all derived functions become the virtual too
    virtual ~B() noexcept { 
        cout << " ~B() countB:" << --countB << endl;        //changed to --
    }
    int add(int x) {
        cout << " ~B() countB:" << ++countB << endl;
        int y = x + a;
        y += b;

        return y;       // added return here
    }

    // virtual is optional here if the base class function is virtual
    // then all derived functions become the virtual too
    // but override is recomended to indicates that we are know that sub is virtual in A
    virtual int sub(int a, int b) override {
        cout << " B::sub(" << a << "," << b << ")" << endl;
        return a - b;
    }
};



class Classes {
public:
    static void learn() {
        try {
            cout << endl << " === learnClasses starts === " << endl;
            A* a = new A();
            int res = a->sub(3, 5);
            B* b = new B();
            A* ap = b;
            res = b->sub(2, 4);
            res = ap->sub(2, 4);
            {
                // using C-cast is not recomended (B*) compiler and no check are done...
                B* pB = (B*)a;
                int sss = pB->x; // will work
            }
            //
            // using dynamic_cast instead... it will not crash and will return nullptr 
            // it the cast cannot be done
            B* x = dynamic_cast<B*>(a);

            delete a;
            delete ap;
            // double deleting can cause seg fault
            //delete ap;
            cout << endl << " === learnClasses is done === " << endl;
        }
        // this cath(...) will handle and hide any exception except segfault
        catch (...) {
        }
    }
};
