#include "Classes.cpp"
#include "SmartPointers.cpp"
#include "Interfaces.cpp"

int Car::carCount = 0;
int B::countB = 0;
int A::countA = 0;
int C::countX = 0;

int main() {
    Picture picture;

    picture.add(new Rectangle(10, 2));
    picture.add(new Rectangle(13, 5));
    picture.add(new Circle(10));
    picture.draw();

    Picture  topPicture;
    topPicture.add(&picture);
    double s = picture.calSquare();
    //Classes::learn();
    // 
    //SmartPointers::learn();
}