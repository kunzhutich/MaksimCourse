#include <iostream>

using namespace std;


class Car {
public:
    string name;
    int price;
    int mileage;
    
    Car() {
        name = "default";
        price = 0;
        mileage = 0;
    }
    
    Car(string n, int p = 1000, int m = 300000) {
        name = n;
        price = p;
        mileage = m;
    }
    
    // Car(string n, int p = 1000, int m = 300000);

    // ~Car(){}

    void change_name(string n) {
        name = n;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Mileage: " << mileage << endl << endl;
    }

private:
    int VIN;

};

// Car::Car(string n, int p, int m) {
//     name = n;
//     price = p;
//     mileage = m;
// }



int main() {
    int rand_size = sizeof(Car);    // is car object on heap?
    cout << rand_size << endl;      // is randsize in stack?
    cout << &rand_size << endl;     // what is this address? is it the address of randsize on stack or Car object in heap?

    Car car1;
    car1.print();

    cout << "Testing alias..." << endl;
    Car& r = car1;
    cout << "Alias car name: " << r.name << endl;
    r.print();
    r.change_name("Nissan");
    cout << "after changing r's name..." << endl;
    cout << "r.name = " << r.name << endl;
    cout << "car1.name = " << car1.name << endl;


    Car car2("Honda", 37000, 20);
    car2.print();

    Car* p2 = &car2;        // is this p2 pointer stored on stack? and it has the address of car2 object in heap right? 
    cout << p2 << endl;     // why when I want to dereference p2, it gives me error?
    
    p2->print();    
    (*p2).print();

    p2->change_name("Honda CRV");
    cout << "after changing p2's name..." << endl;
    cout << "p2->name = " << p2->name << endl;
    cout << "car2.name = " << car2.name << endl << endl;


    Car* car3 = new Car("Toyota Supra", 57500, 0);
    Car copy = *car3;
    copy.change_name("Toyota");
    cout << "after changing copy's name..." << endl;
    cout << "copy.name = " << copy.name << endl;
    cout << "car3.name = " << car3->name << endl;

    delete car3;    // avoid leakage
}