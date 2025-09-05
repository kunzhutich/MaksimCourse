// #include "Classes.cpp"
// #include "SmartPointers.cpp"
//#include "Interfaces.cpp"
#include "../henryPractice/9-2/linked_list_failed.cpp"

// int Car::carCount = 0;
// int B::countB = 0;
// int A::countA = 0;
// int C::countX = 0;


int learnFLinkList() {
    forwardLinkedList flst;// = new forwardLinkedList();
    // for (char sym : "1") {
    //     flst.add(sym);
    // }

    for (char sym : std::string("1")){
        flst.add(sym);
    }
    
    flst.print();
    flst.reverse();

    flst.print();
    return 0;
};

int test1() {
    forwardLinkedList flst;// = new forwardLinkedList();
    for (char sym : "1234567") {
        flst.add(sym);
    }

    auto arr = flst.toVector();
    //if (arr[0] != '1') error();
    flst.print();
    flst.reverse();

    flst.print();
    return 0;
};

int main() {
    learnFLinkList();
    //Interface::learnDeepCopy();

    //Interface::learnPicture();
    //Interface::learnSpinner();
    //Classes::learn();
    // 
    //SmartPointers::learn();
}