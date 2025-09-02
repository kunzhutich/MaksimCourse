
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

class IShape;

typedef shared_ptr<IShape> IShapePtr;
typedef weak_ptr<IShape> IShapeWPtr;

class IHasName {
public:
    virtual string name() = 0;
};

class IHasParent {
public:
    virtual IShapePtr getParent() = 0;
    virtual void setParent(IShapePtr) = 0;
};

class IShape : public IHasName, public IHasParent {
public:
    virtual void draw() = 0;
    virtual double calSquare() = 0;
    virtual double calPerimeter() = 0;
    virtual IShapePtr makeDeepCopy(int x, int y) = 0;
};

class Point : IHasParent {
    IShapeWPtr _parent;
    int _x;
    int _y;
public:
    Point(IShapePtr parent, int x=0, int y=0) : _parent(parent), _x(x), _y(y) {}
    int getX() { return _x; }
    int getY() { return _y; }
    // int setY(int v) { return _y = v; }

    Point(int x, int y) {
        _x = x;
        _y = y;
    }

    virtual IShapePtr getParent() override { return _parent.lock(); }
    virtual void setParent(IShapePtr parent) override { _parent = parent; }

    virtual IShapePtr makeDeepCopy(int x, int y) = 0;

};

class Rectangle : public Point, public IShape {
public:
    int _w;
    int _h;
    Rectangle(int w, int h, int x = 1, int y=1) : Point(nullptr, x, y), _w(w), _h(h) {}

    Rectangle(IShapePtr parent, int w, int h, int x = 1, int y = 2)
        : Point(parent, x, y), _w(w), _h(h) {}


    Rectangle& operator=(const Rectangle& from) {
        if (this == &from) return *this;
        *this = from;
        _w = from._w;
        _h = from._h;
        return *this;
    }

    virtual string name() override { return "Rectangle"; }
    virtual void draw() override {
        cout << "Drawing " << name() << " with sides " << _w << " and " << _h;
        cout << " at coordinate (" << getX() << ", " << getY() << ")" << endl; 
    }
    virtual double calSquare() override { return _w * _h; }
    virtual double calPerimeter() override { return 2 * (_w + _h); }
    virtual IShapePtr getParent() override { return Point::getParent(); }
    virtual void setParent(IShapePtr parent) override { Point::setParent(parent); }
    virtual IShapePtr makeDeepCopy(int x, int y) override {
        auto p = make_shared<Rectangle>(Point::getParent(), x, y);
        p->_w = _w;
        p->_h = _h;
        return p;
    }
};

struct Circle : public Point, public IShape {
public:
    int _r;

    Circle(int r, int x = 0, int y = 0)
        : Point(x, y), _r(r) {
    }

    Circle(IShapePtr parent, int r, int x = 0, int y = 0)
        : Point(parent, x, y), _r(r) {}

    virtual string name() override { return "Circle"; }
    virtual void draw() override {
        cout << "Drawing " << name() << " with radius " << _r;
        cout << " at coordinate (" << getX() << ", " << getY() << ")" << endl; 
    }
    virtual double calSquare() override { return 3.14158 * _r * _r; }
    virtual double calPerimeter() override { return 2 * 3.14158 * _r; }
    virtual IShapePtr getParent() override { return Point::getParent(); }
    virtual void setParent(IShapePtr parent) override { Point::setParent(parent); }

    virtual IShapePtr makeDeepCopy(int x, int y) override {
        auto p = make_shared<Circle>(Point::getParent(), x, y);
        p->_r = _r;
        return p;
    }

};

class Triangle : public Point, public IShape {
public:
    int side;

    Triangle(IShapePtr parent, int s, int x = 5, int y = 6) : Point(parent, x, y), side(s) {}
    Triangle(int s, int x = 5, int y = 6) : Point(x, y), side(s) {}

    virtual string name() override { return "Triangle"; }

    int getSide()      { return side; }
    void setSide(int s) { side = s; }
    
    virtual void draw() override {
        cout << "Drawing equilateral " << name() << " with sides " << side;
        cout << " at coordinate (" << getX() << ", " << getY() << ")" << endl; 
    }

    virtual double calSquare() override { return sqrt(3) * side * side / 4; }

    virtual double calPerimeter() override { return 3 * side; }

    virtual IShapePtr getParent() override { return Point::getParent(); }
    virtual void setParent(IShapePtr parent) override { Point::setParent(parent); }

    virtual IShapePtr makeDeepCopy(int x, int y) override {
        auto p = make_shared<Triangle>(Point::getParent(), x, y);
        p->side = this->side;
        return p;
    }
};

class Picture : public Point, public IShape {
    vector<shared_ptr<IShape>> _shapes;
    string _name;
    
    static vector<shared_ptr<IShape>> make_deep_copy(const vector<shared_ptr<IShape>> & from) {
        vector<shared_ptr<IShape>> arr;
        for (const auto & it : from) {
            shared_ptr<Point>point = dynamic_pointer_cast<Point>(it);
            auto copyIt = it->makeDeepCopy(point->getX(), point->getY());
        }
        return arr;
    }
public:
    Picture(IShapePtr parent, string name = "picture") : Point(parent, 0, 0), _name(name) {
    }
    Picture(IShapePtr parent, string name, int x, int y) : Point(parent, x, y), _name(name) {
    }
    Picture(string name = "picture") : Point(0, 0), _name(name) {
    }

    Picture(const Picture& from) : Point(from), _shapes(make_deep_copy(from._shapes)) {

    }
   
    Picture& operator=(const Picture& from) {
       if (this == &from) return *this;
       Point::operator=(from);
       _shapes = from._shapes;
       return *this;
    }

    virtual string name() override { return _name; }
    
    IShapePtr getChild(int index) {
        if (index < 0) return nullptr;
        if (index >= _shapes.size()) return nullptr;
        return _shapes[index];
    }

    template<typename T>
    shared_ptr<T> getChildT(int index) {
        if (index < 0) return nullptr;
        if (index >= _shapes.size()) return nullptr;
        auto shapePtr = _shapes[index];
        return dynamic_pointer_cast<T>(shapePtr);
    }

    void add(shared_ptr<IShape> shape) {
        _shapes.push_back(shape);
    }

    virtual void draw() override {
        cout << "drawing picture " << name() << endl;
        for (int i = 0; i < _shapes.size(); ++i) {
            shared_ptr<IShape> shape = _shapes[i];
            cout << "Current shape " << shape->name() << ":" << endl;
            shape->draw();
        }
    }

    double calSquare() override {
        double s = 0;
        for (int i = 0; i < _shapes.size(); ++i) {
            shared_ptr<IShape> shape = _shapes[i];
            s += shape->calSquare();
        }
        return s;
    }

    double calPerimeter() override {
        double perimeter = 0;
        for (shared_ptr<IShape> shape : _shapes) {
            perimeter += shape->calPerimeter();
        }
        return perimeter;
    }
    virtual IShapePtr getParent() override { return Point::getParent(); }
    virtual void setParent(IShapePtr parent) override { Point::setParent(parent); }
  
    virtual IShapePtr makeDeepCopy(int x, int y) override {
        auto p = make_shared<Picture>(getParent(), name(), x, y);
        p->_name = this->_name;
        for (const auto & it : _shapes) {
            auto copyIt = it->makeDeepCopy(x, y);
            p->add(copyIt);
        }
        return p;
    }
};

class Spinner : public Point, public IShape {
    Picture picture;
    int _r;
    int _side;
public:
    Spinner(int r, int side, int x = 3, int y = 2) 
    : Point(x, y), picture("spinner"), _r(r), _side(side) {
        picture.add(make_shared<Circle>(_r, 3, 3));
        picture.add(make_shared<Circle>(_r, 1, 1));
        picture.add(make_shared<Circle>(_r, 5, 1));
        picture.add(make_shared<Triangle>(_side, x, y));
    }

    Spinner(IShapePtr parent, int r, int side, int x = 3, int y = 2) 
    : Point(parent, x, y), picture("spinner"), _r(r), _side(side) {
        picture.add(make_shared<Circle>(_r, 3, 3));
        picture.add(make_shared<Circle>(_r, 1, 1));
        picture.add(make_shared<Circle>(_r, 5, 1));
        picture.add(make_shared<Triangle>(_side, x, y));
    }

    shared_ptr<Circle> getCircle_0()   { return picture.getChildT<Circle>(0); }
    shared_ptr<Circle> getCircle_1()   { return picture.getChildT<Circle>(1); }
    shared_ptr<Circle> getCircle_2()   { return picture.getChildT<Circle>(2); }
    shared_ptr<Triangle> getTriangle() { return picture.getChildT<Triangle>(3); }

    virtual string name() override { return "Spinner"; }

    Picture& getPicture() { return picture; }

    virtual void draw() override {
        cout << "Drawing " << name() << " that has the following: " << endl;
        picture.draw();
    }

    virtual double calSquare() override {
        return picture.calSquare();
    }

    virtual double calPerimeter() override {
        return picture.calPerimeter();
    }
    virtual IShapePtr getParent() override { return Point::getParent(); }
    virtual void setParent(IShapePtr parent) override { Point::setParent(parent); }
    virtual IShapePtr makeDeepCopy(int x, int y) override {
        // auto p = make_shared<Spinner>(Spinner::getParent(), x, y);
        auto p = make_shared<Spinner>(Spinner::getParent(), this->_r, this->_side, x, y);
        IShapePtr copy = picture.makeDeepCopy(x, y);
        p->picture = *dynamic_pointer_cast<Picture>(copy);
        return p;
    }
};

class Check {
public:
    static void ifTrue(bool condition, string errmsg) {
        if (!condition) {
            cout << errmsg << endl;
        } else {
            cout << "check passed" << endl;
        }
    }
};

class Interface {
public:
    static void learnPicture() {
        auto picture = make_shared<Picture>(" A ");
        picture->add(make_shared<Rectangle>(10, 2));
        picture->add(make_shared<Rectangle>(13, 5));
        picture->add(make_shared<Circle>(10));
        picture->draw();

        Picture topPicture("Top");
        topPicture.add(picture);
        double s = picture->calSquare();
        cout << "The sum of all squares for picture " << picture->name() << " is " << s << endl;
        double per = picture->calPerimeter();
        cout << "The sum of all perimeters for picture " << picture->name() << " is " << per << endl;
    }

    static void learnSpinner() {
        Spinner spin1(3, 5);
        spin1.draw();
        double spin1_square = spin1.calSquare();
        cout << "The sum of all squares for picture " << spin1.name() << " is " << spin1_square << endl;
        double spin1_per = spin1.calPerimeter();
        cout << "The sum of all perimeters for picture " << spin1.name() << " is " << spin1_per << endl;
    }

    static void learnDeepCopy() {
        int radius = 3;
        int side   = 5;
        Spinner spin1(radius, side);
        shared_ptr<Spinner> copy = dynamic_pointer_cast<Spinner>(spin1.makeDeepCopy(20, 30));
        Check::ifTrue(copy->getX() == 20, " Error copy->getX() != 20");
        Check::ifTrue(copy->getY() == 30, " Error copy->getY() != 30");

        shared_ptr<Circle> circle_0 = copy->getCircle_0();
        shared_ptr<Circle> circle_1 = copy->getCircle_1();
        shared_ptr<Circle> circle_2 = copy->getCircle_2();
        shared_ptr<Triangle> triangle = copy->getTriangle();
        triangle->setSide(100);
        Check::ifTrue(triangle->getSide() == 100, "Error triangle->getSide() == 100");
        cout << "shared_ptr triangle's side = " << triangle->getSide() << endl;
        // validate that we did deap copy for triange:
        Check::ifTrue(spin1.getTriangle()->getSide() != 100, "deap copy for triange fail: spin1.getTriangle()->getSide() != 4");
        cout << "spin1's triangle's side = " << spin1.getTriangle()->getSide() << endl;
    }
};

class Math {
public :
    template <typename T> 
    static T Max(T a, T b) {
        if (a > b) return a;
        return b;
    }

};