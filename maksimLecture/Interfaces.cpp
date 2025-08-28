
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

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
    // int setY(int v) { return _y = v; }

    Point(int x, int y) {
        _x = x;
        _y = y;
    }

};

class Rectangle : public Point, public IShape {
public:
    int _w;
    int _h;
    Rectangle(int w, int h, int x = 1, int y = 2) 
        : Point(x, y), _w(w), _h(h) {}

    virtual string name() override { return "Rectangle"; }
    virtual void draw() override {
        cout << "Drawing " << name() << " with sides " << _w << " and " << _h;
        cout << " at coordinate (" << getX() << ", " << getY() << ")" << endl; 
    }
    virtual double calSquare() override { return _w * _h; }
    virtual double calPerimeter() override { return 2 * (_w + _h); }
};

struct Circle : public Point, public IShape {
public:
    int _r;
    Circle(int r, int x = 0, int y = 0) 
        : Point(x, y), _r(r) {}

    virtual string name() override { return "Circle"; }
    virtual void draw() override {
        cout << "Drawing " << name() << " with radius " << _r;
        cout << " at coordinate (" << getX() << ", " << getY() << ")" << endl; 
    }
    virtual double calSquare() override { return 3.14158 * _r * _r; }
    virtual double calPerimeter() override { return 2 * 3.14158 * _r; }
};

class Triangle : public Point, public IShape {
public:
    int side;

    Triangle(int s, int x = 5, int y = 6) : Point(x, y), side(s) {}

    virtual string name() override { return "Triangle"; }
    
    virtual void draw() override {
        cout << "Drawing equilateral " << name() << " with sides " << side;
        cout << " at coordinate (" << getX() << ", " << getY() << ")" << endl; 
    }

    virtual double calSquare() override { return sqrt(3) * side * side / 4; }

    virtual double calPerimeter() override { return 3 * side; }
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
};

class Spinner : public Point, public IShape {
    Picture spinner;
public:
    Spinner(int r, int side, int x = 3, int y = 2) : Point(x, y), spinner("spinner") {
        spinner.add(make_shared<Circle>(r, 3, 3));
        spinner.add(make_shared<Circle>(r, 1, 1));
        spinner.add(make_shared<Circle>(r, 5, 1));
        spinner.add(make_shared<Triangle>(side, x, y));
    }

    virtual string name() override { return "Spinner"; }

    virtual void draw() override {
        cout << "Drawing " << name() << " that has the following: " << endl;
        spinner.draw();
    }

    virtual double calSquare() override {
        return spinner.calSquare();
    }

    virtual double calPerimeter() override {
        return spinner.calPerimeter();
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
};
