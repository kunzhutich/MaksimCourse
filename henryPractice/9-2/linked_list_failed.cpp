#include <iostream>

using namespace std;

// template<typename T>
class forwardLinkedList {
public:
    char _node;
    forwardLinkedList* _next;

    forwardLinkedList() : _node(), _next(nullptr) {}
    forwardLinkedList(char node) : _node(node), _next(nullptr) {}
    forwardLinkedList(char node, forwardLinkedList* next) : _node(node), _next(next) {}

    void print() {
        forwardLinkedList* current = this;
        while (current) {
            cout << current->_node;
            current = current->_next;
        }
        cout << endl;
    }
};

int main() {
    forwardLinkedList* strList = new forwardLinkedList('h');

    strList->_next = new forwardLinkedList('e');
    strList->_next->_next = new forwardLinkedList('l');
    strList->_next->_next->_next = new forwardLinkedList('l');
    strList->_next->_next->_next->_next = new forwardLinkedList('o');

    strList->print();


    forwardLinkedList* reverseList = new forwardLinkedList();
    forwardLinkedList* p_start = strList;
    forwardLinkedList* p_end = strList;

    int count = 0;
    while (p_end->_next != nullptr) {
        cout << "p_end: " << p_end->_node << endl;
        p_end = p_end->_next;
        count++;
    }

    reverseList = p_end;
    cout << reverseList->_node << endl;

    while (count >= 0) {
        if (p_end == strList) {
            reverseList = p_end;
            break;
        }

        cout << "Count = " << count << endl;
        p_start = strList;

        while (p_start->_next != p_end) {
            cout << "p_start: " << p_start->_node << "\t";
            cout << "p_end: " << p_end->_node << endl;
            p_start = p_start->_next;
        }

        p_end = p_start;
        cout << "after p_end = p_start, p_end's node = " << p_end->_node << endl;
        reverseList->_next = p_end;
        cout << "reverseList current node = " << reverseList->_node << endl;
        reverseList = reverseList->_next;

        count--;
    }

    reverseList->print();
}