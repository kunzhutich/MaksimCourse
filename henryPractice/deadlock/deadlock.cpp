#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Parent;


class Child : public enable_shared_from_this<Child>{
    mutex cm;
    string _name;
    shared_ptr<Parent> _parent = nullptr;

public:
    Child(shared_ptr<Parent> parent, string name) : _parent(parent), _name(name) {
        // parent->addChild(this);
    }

    shared_ptr<Parent> getParent() {
        lock_guard<mutex> lock_parent(cm);
        return _parent;
    }

    string getName() {
        lock_guard<mutex> lock_parent(cm);
        return _name;
    }

};

class Parent : public enable_shared_from_this<Parent>{
    mutex mp;

    string _name;
    int _age;
    vector<shared_ptr<Child>> _children;

public:
    Parent(string name, int age) : _name(name), _age(age) {}
    vector<shared_ptr<Child>> getChildren() {
        lock_guard<mutex> lock_children(mp);
        return _children;
    }

    shared_ptr<Child> makeChild(string childName) {
        lock_guard<mutex> lock_children(mp);
        shared_ptr<Child> child = make_shared<Child>(shared_from_this(), childName);
        _children.push_back(child);
        return child;
    }

    void addChild(shared_ptr<Child> child) {
        lock_guard<mutex> lock_children(mp);
        _children.push_back(child);
    }

    bool isMyChild(shared_ptr<Child> child) {
        lock_guard<mutex> lock_children(mp);

        for (shared_ptr<Child> ch : _children) {
            if (ch->getParent().get() == this) {
                return true;
            }
        } 
        return false;
    }

    string getName() {
        lock_guard<mutex> lock_children(mp);
        return _name;
    }

    bool hasChildwithName(string name) {
        lock_guard<mutex> lock_children(mp);
        
        for(shared_ptr<Child> ch : _children) {
            if (ch->getName() == name) {
                return true;
            }
        }
        return false;
    }

    bool testParent() {
        string parentName;
        vector<shared_ptr<Child>> kids;

        {
            lock_guard<mutex> lock_children(mp);
            parentName = _name;
            kids = _children;
        }
        
        // for(shared_ptr<Child> ch : _children) { 
        //     if (ch->getParent()->getName() == _name) {
        //         return true;
        //     }
        // }

        for (shared_ptr<Child> ch : _children) {
            auto parent = ch->getParent();
            if (parent != nullptr && parent->getName() == parentName) {
                return true;
            }
        }

        return false;
    }
};


int main() {
    auto p1 = make_shared<Parent>("Mei", 53);
    // auto c1 = make_shared<Child>(p1, "Henry");
    auto c1 = p1->makeChild("Henry");

    bool result = p1->testParent();
    cout << result;

    // p1->getChildren();
    // auto p2 = make_shared<Parent>("Bill Gates", 66);         // WRONG
    // p2->addChild(c1);

    
}
