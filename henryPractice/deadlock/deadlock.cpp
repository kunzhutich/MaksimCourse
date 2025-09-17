#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <memory>
#include <atomic>
using namespace std;

class Parent;


class Child : public enable_shared_from_this<Child>{
    mutex cm;
    string _name;
    weak_ptr<Parent> _parent;
    
public:
    atomic<int> instanceCount{0};
    // static int instanceCount;

    Child(shared_ptr<Parent> parent, string name) : _parent(parent), _name(name) {
        // parent->addChild(this);
        // ++instanceCount;
        instanceCount.fetch_add(1);
    }
    ~Child() {
        // --instanceCount;
        instanceCount.fetch_sub(1);
    }

    shared_ptr<Parent> getParent() {
        lock_guard<mutex> lock_parent(cm);
        if (auto p = _parent.lock()){
            return p;
        } else {
            return nullptr;
        }
    }

    string getName() {
        lock_guard<mutex> lock_parent(cm);
        return _name;
    }

   int getCount() {
        return instanceCount.load();
    }
};

class Parent : public enable_shared_from_this<Parent>{
    mutex mp;

    string _name;
    int _age;
    vector<shared_ptr<Child>> _children;

    
public:
    std::atomic<int> instanceCount{0};
    // static int instanceCount;


    Parent(string name, int age) : _name(name), _age(age) {
        ++instanceCount;
    }
    ~Parent() {
        --instanceCount;
    }
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
        lock_guard<mutex> lock_children(mp);

        for(shared_ptr<Child> ch : _children) {
            auto parent = ch->getParent();
            if (parent != nullptr && parent->_name == _name) {
                return true;
            }
        }

        return false;
    }

    int getCount() {
        return instanceCount;
    }
};

// int Child::instanceCount = 0;
// int Parent::instanceCount = 0;

int main() {
    {
        auto p1 = make_shared<Parent>("Mei", 53);
        auto c1 = p1->makeChild("Henry");

        bool result = p1->testParent();
        cout << result << endl;

        // cout << "Instance Count for parent = " << Parent::getCount() << endl;
        // cout << "Instance Count for child = " << Child::getCount() << endl;
        
        cout << "Instance Count for p1 = " << p1->getCount() << endl;
        cout << "Instance Count for c1 = " << c1->getCount() << endl;

    }

    // cout << "Instance Count for parent = " << Parent::getCount() << endl;
    // cout << "Instance Count for child = " << Child::getCount() << endl;

}
