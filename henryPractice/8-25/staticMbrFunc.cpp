#include <iostream>

using namespace std;

class Rectangle {
private:
    static int count;

public: 
    int length;
    int width;

    Rectangle() {
        length = 2;
        width = 4;
        count++;
    }

    Rectangle(int l, int w) {
        length = l;
        width = w;
        count++;
    }

    ~Rectangle() {
        count--;
    }

    int returnArea() {
        return length * width;
        // return this->length * this->width;
    }

    static int getCount() {
        return count;
    }

};

int Rectangle::count = 0;


int main() {
    Rectangle rec1;
    int area1 = rec1.returnArea();
    cout << "area1: " << area1 << endl;
    cout << Rectangle::getCount() << endl << endl;

    Rectangle rec2(5, 6);
    int area2 = rec2.returnArea();
    cout << "area2: " << area2 << endl;
    cout << Rectangle::getCount() << endl << endl;

    Rectangle* rec3 = new Rectangle(3, 3);
    int area3 = rec3->returnArea();
    cout << "area3: " << area3 << endl;
    cout << Rectangle::getCount() << endl << endl;

    Rectangle& rec4 = *(new Rectangle(4, 3));   // *(new ...) is almost always a mistake bc we still have to delete the allocated memory, but reference doesnt give ownership semantics
                                                // technically we can do "delete &rec4;" but its not good practice bc we cant tell at the call site whether rec4 actually refers to heap or stack memory
    int area4 = rec4.returnArea();
    cout << "area4: " << area4 << endl;
    // cout << "rec4 is " << &rec4 << endl;
    cout << Rectangle::getCount() << endl << endl;


    delete rec3;
}