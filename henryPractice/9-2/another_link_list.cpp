#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class FLL {
    class Node {
    public:
        T _data;
        shared_ptr<Node> _next;

        Node(T data) : _data(data), _next(nullptr) {}
        Node(T data, shared_ptr<Node> next) : _data(data), _next(next) {}
    };
    
    shared_ptr<Node> _head;
    shared_ptr<Node> _tail;

public:
    FLL() : _head(nullptr), _tail(nullptr) {}

    void add(T data) {
        auto node = make_shared<Node>(data);
        
        if(_head == nullptr && _tail == nullptr) {
            _head = node;
            _tail = node;
            return;
        }

        _tail->_next = node;
        _tail = _tail->_next;
    }

    void reverse() {
        auto curr = _head;
        auto oldHead = _head;
        shared_ptr<Node> prev;

        while (curr) {
            auto nxt = curr->_next;
            curr->_next = prev;
            prev = curr;
            curr = nxt;
        }

        _head = prev;
        _tail = oldHead;
    }

    void print() {
        auto current = _head;

        while(current != nullptr) {
            cout << current->_data;
            current = current->_next;
        }
        cout << endl;
    }
};

int main() {
    FLL<int> lst;
    for (int i : {1, 2, 3, 4, 5, 6, 7, 8, 9}){
        lst.add(i);
    }
    lst.print();
    lst.reverse();
    lst.print();

    FLL<char> ch_lst;
    for (char ch : "hello") {
        ch_lst.add(ch);
    }
    ch_lst.print();
    ch_lst.reverse();
    ch_lst.print();
}