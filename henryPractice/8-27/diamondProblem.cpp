#include <iostream>
using namespace std;
    
class A {
public:
    void hello() {                  // adding virtual here wont help 
        cout << "Hello from A" << endl;
    }
};

// class B : public A { };          // these 2 functions wont work due to diamond problem
// class C : public A { };          // class D inherits 2 copies of A, which makes it ambiguous which one to call

class B : virtual public A { };     // this is ok
class C : virtual public A { };     // adding virtual solves the diamond problem

class D : public B, public C {} ;


int main() {
    D d;
    d.hello();
}