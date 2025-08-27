// SmartPointer.cpp :

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Car;
class FactoryCar;

class NoCopyOrMove {
public: 
    NoCopyOrMove(const NoCopyOrMove &) = delete;
    NoCopyOrMove(const NoCopyOrMove&&) = delete;
    NoCopyOrMove& operator=(Car&& from) = delete;
    NoCopyOrMove& operator=(const Car && from) = delete;
};

class Car {
public:
    static int carCount;
    // static function... Factory class;
    static Car createCar(const char* name) {
        Car car;
        car.setName(name);
        return car;
    }

    static unique_ptr<Car> assemble(const Car& a0, Car& b0) {
        unique_ptr<Car> car = make_unique<Car>();
        car->milledge = a0.milledge + b0.milledge;
        car->price = (a0.price + b0.price) / 2;
        car->setName("AB");
        return car;
    }

    shared_ptr<FactoryCar> madeBy;
    shared_ptr<string> name;
    int price;
    int milledge;
    // Default
    Car() {
        madeBy = nullptr;
        carCount++;
        name = nullptr;
        price = 13000;
        milledge = 0;
    }

    //copy constructor assign operator...
    Car(const Car& from) {
        carCount++;
        madeBy = from.madeBy;
        price = from.price;
        milledge = from.milledge;
        name = from.name;
    }
    Car& operator=(const Car& from) {
        madeBy = from.madeBy;
        price = from.price;
        milledge = from.milledge;
        name = from.name;
        return *this;
    }
    
    // Move symantic...
    Car(const Car&& from) noexcept {
        madeBy = from.madeBy;
        price = from.price;
        milledge = from.milledge;
        name = from.name;
       
    }
    Car& operator=(Car&& from) noexcept {
        price = from.price;
        milledge = from.milledge;
        name = from.name;
        return *this;
    }

    // Destructor
    ~Car() noexcept {
        carCount--;
    }

    bool setName(const char* s) {
        // problem here? what is about if name is pointing to old name?
        name = make_shared<string>(string(s));
        return true;
    }
};



class FactoryCar {
public:
    Car createCar(const char* name) {
        Car car;
        car.setName(name);
        return car;
    }

    Car pickupBestCar(bool bestMilige) {
        Car carA;
        Car carB;
        carA.setName("SSSS");
        carA.setName("ffdfdf");
        carA.milledge = 15;
        carB.milledge = 11;
        if (bestMilige) {
            return carB;
        }
        else {
            return carA;
        }
    }
};

class SmartPointers {
public:
    static int learn() {
        {
            FactoryCar factory;
            Car a = factory.createCar("sss");
            Car x = factory.pickupBestCar(true);
        }
        return 0;
    }
};