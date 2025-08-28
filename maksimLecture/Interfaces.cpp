
#include <iostream>
#include <memory>
#include <vector>

using namespace std;


class IHasName {
public:
    virtual string name() = 0;
};

class IShape : public IHasName {
public:
    virtual void draw() = 0;
    virtual double calSquare() = 0;
    virtual double calPerimeter() = 0;
};



class Point {
    int _x;
    int _y;
public:
    int getX() { return _x; }
    int getY() { return _y; }
    int setY(int v) { return _y = v; }

    Point(int x, int y) {
        _x = x;
        _y = y;
    }

};
class Rectangle : public Point, public IShape {
public:
    int _w;
    int _h;
    Rectangle(int w, int h) : Point(1,2) {
        _w = w;
        _h = h;
    }
    virtual string name() override { return "Rectangle"; }
    virtual void draw() override {
        cout << " draw " << name() << ": " << _w << _h << endl;
    }
    virtual double calSquare() { return _w * _h; }
    virtual double calPerimeter() { return 2 * (_w + _h); }
};

struct Circle : public Point, public IShape  {
public:
    int _r;
    Circle(int r) : Point(0,0) {
        _r = r;
    }
    virtual string name() override { return "Circle"; }
    virtual void draw() override {
        cout << " draw " << name() << ": " << _r << endl;
    }
    virtual double calSquare() { return 3.14158 * _r * _r; }
    virtual double calPerimeter() { return 2 * 3.14158 * _r; }
};

class Picture : public Point, public IShape {
    vector<shared_ptr<IShape>> _shapes;
    string _name;
public:
    Picture(string name = "picture") : Point(0, 0) {
        _name = name;
    }
    void add(shared_ptr<IShape> shape) {
        _shapes.push_back(shape);
    }
    
    virtual string name() override { return _name; }

    virtual void draw() override {
        cout << "drawing picture " << name() << endl;
        for (int i = 0; i < _shapes.size(); ++i) {
            shared_ptr<IShape> shape = _shapes[i];
            cout << "drawing " << shape->name();
            shape->draw();
        }
    }

    double calSquare() {
        double s = 0;
        for (int i = 0; i < _shapes.size(); ++i) {
            shared_ptr<IShape> shape = _shapes[i];
            s += shape->calSquare();
            cout << shape->name() << "'s area is " << s << endl;
        }
        return s;
    }

    double calPerimeter() {
        double perimeter = 0;

        for (shared_ptr<IShape> shape : _shapes) {
            perimeter = shape->calPerimeter();
            cout << shape->name() << "'s perimeter is " << perimeter << endl;
        }

        return perimeter;
    }

    
};


class Interface {
public:
    static void learn() {
        auto picture = make_shared<Picture>(" A ");
        picture->add(make_shared<Rectangle>(10, 2));
        picture->add(make_shared<Rectangle>(13, 5));
        picture->add(make_shared<Circle>(10));
        picture->draw();

        Picture topPicture("Top");
        topPicture.add(picture);
        double s = picture->calSquare();
        double per = picture->calPerimeter();
    }
};
