#include <iostream>

class A {
  public: A() = default;
    virtual ~A() {}

    protected: int b;
    private:   int c;
  public:    
    int a;
    //virtual
    int sub(int x, int y) {
        return x + y + 10;
    }
};

class B : public A {
public: B() {}
      ~B() {}
      int add(int x) {
          int y = x + a;
          y += b;
      }

      virtual int sub(int zssfsd, int w) {
          return zssfsd - w;
      }
      int x = 0;
      int v() {}
};


int add (int a, int b) {
    return a + b;
}

int main()
{
    try {
        A* a = new A();
        int res = a->sub(3, 5);
        B* b = new B();
        A* ap = b;
        res = b->sub(2, 4);
        res = ap->sub(2, 4);
        B* badP = (B*)a;
        B * x = dynamic_cast<B*>(a);
        int sss = badP->x;
        res = add(2, 5);
        std::cout << "Hello World Henry!" << res << "\r\n";
        res = 1 / 0;
        delete a;
        delete ap;
        //delete ap; // bug;;;
    }
    catch (...) {

    }
}
