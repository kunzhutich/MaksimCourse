#include <iostream>

using namespace std;

struct A {
    virtual void f() { std::cout << "A::f\n"; }
    virtual ~A() = default;

    virtual int sum(int i, int j) {
        return i + j;
    }

    protected:
        int a = 3;

    private:
        int x = 10;
};

struct B : A {
    void f() override { std::cout << "B::f\n"; }

    int sum(int i, int j) override {
        return i + j + 1;
    }

};

int main() {
    B b;
    A& r = b;      // base ref bound to a B
    A* p = &b;     // base ptr to a B
    r.f();         // prints "B::f"
    p->f();        // prints "B::f"

    // cout << p->a << endl;

    cout << p->sum(1, 2) << endl;
}