
#include <iostream>
#include <vector>

using namespace std;

class IShap {
public:
    virtual void draw() = 0;
    virtual double calSquare() = 0;
};

class IHasName {
public:
    virtual string name() = 0;
};


class Point {
    int _x;
    int _y;
public:
    int getX() { return _x; }
    int getY() { return _y; }
    int setY(int v) {_y = v; }

    Point(int x, int y) {
        _x = x;
        _y = y;
    }

};
class Rectangle : public Point, public IShap, public IHasName {
public:
    int _w;
    int _h;
    Rectangle(int w, int h) : Point(1,2) {
        _w = w;
        _h = h;
    }
    virtual string name() override { return "Rectangle"; }
    virtual void draw() override {
        cout << "draw rectangle:" << _w << _h << endl;
    }
    virtual double calSquare() { return _w * _h; };
};

struct Circle : public Point, public IShap, public IHasName {
public:
    int _r;
    Circle(int r) : Point(0,0) {
        _r = r;
    }
    virtual string name() override { return "Circle"; }
    virtual void draw() override {
        cout << "draw " << name() << _r << endl;
    }
    virtual double calSquare() { return 3.14158 * _r * _r; };
};

class Picture : public Point, public IShap {
    vector<IShap*> _shapes;
public:
    Picture() : Point(0,0) {}
    void add(IShap * shape) {
        _shapes.push_back(shape);
    }
    virtual void draw() override {
        cout << "drawing picture " << endl;
        for (int i = 0; i < _shapes.size(); ++i) {
            IShap* shape = _shapes[i];
            cout << shape << "drawing " << dynamic_cast<IHasName*>(shape)->name();
            shape->draw();
        }
    }

    double calSquare() {
        double s = 0;
        for (int i = 0; i < _shapes.size(); ++i) {
            IShap* shape = _shapes[i];
            s += shape->calSquare();
        }
        return s;
    }
    double calPerimeter() {
        return 0.0;
    }

    
};

