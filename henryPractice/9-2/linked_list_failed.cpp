#include <iostream>
#include <vector>

using namespace std;


//template<typename T>
class forwardLinkedList {

    class Node;
    Node* _head;
    Node* _tail;
    int _count;

    //template<typename T>
    class Node {
    public:
        char _data;
        Node* _next;
        Node(char data) {
            _data = data;
            _next = nullptr;
        }
    };
public:
    int getCount() { return _count; }
    forwardLinkedList() {
        _head = nullptr;
        _tail = nullptr;
    }
    //forwardLinkedList() : _data('a') , _next(nullptr) {
   // }
    void add (char v) {
        ++_count;
        auto* node = new Node(v);
        if (_tail == nullptr) {
            _head = node;
            _tail = node;
            return;
        }
        _tail->_next = node;
        _tail = node;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = _tail;
        while (curr) {
            Node* nxt = curr->_next; // remember the rest
            curr->_next = prev;      // flip link
            prev = curr;            // advance prev
            curr = nxt;             // advance curr
        }
        auto* tmp = _head;
        _head = _tail;
        _tail = tmp;
    }

    std::vector<char> toVector() {
        std::vector<char> add;
        Node* current = _head;
        while (current != nullptr) {
            add.push_back(current->_data);
            current = current->_next;
        }
        return add;
    }
    void print() {
        Node* current = _head;
        while (current != nullptr) {
            cout << current->_data;
            current = current->_next;
        }
        cout << endl;
    }

};

