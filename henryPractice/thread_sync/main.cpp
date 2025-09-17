#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono_literals;

template<typename T>
class Q {
    mutex m;
    condition_variable not_empty;
    condition_variable not_full;
    deque<T> queue; 
    const size_t _cap;
public:
    Q(size_t cap) : _cap(cap) {}

    void add(T&& x) {
        unique_lock<mutex> lock(m); 
        // while (true) {
        //     cout << "The queue is currently full. Waiting..." << endl;
        //     not_full.wait_for(lock, 20ms);
        //     if (queue.size() < _cap) {
        //         break;
        //     }
        // }

        while (queue.size() >= _cap) {
            cout << "The queue is currently full. Waiting..." << endl;
            not_full.wait(lock);
        }

        try {
            cout << "Added " << x << " to the queue" << endl;
            queue.push_back(move(x));
        } catch (...) {
        }

        lock.unlock();
        not_empty.notify_one();
    }

    T pop() {
        unique_lock<mutex> lock(m);
        // while (true) {
        //     cout << "The queue is currently empty. Waiting..." << endl;
        //     not_empty.wait_for(lock, 50ms);
        //     if (queue.size() > 0) {
        //         break;
        //     }
        // }

        while (queue.empty()) {
            cout << "The queue is currently empty. Waiting..." << endl;
            not_empty.wait(lock);
        }

        T first;

        try{
            first = move(queue.front());
            queue.pop_front();
        } catch (...) {
        }

        lock.unlock();
        not_full.notify_one();

        return move(first);
    }

    bool try_add_for(T&& x, chrono::milliseconds timeout) {
        unique_lock<mutex> lk(m);
        while (queue.size() >= _cap) {
            if (not_full.wait_for(lk, timeout) == cv_status::timeout)
                return false;
        }
        queue.push_back(move(x));

        lk.unlock(); 
        not_empty.notify_one();
        return true;
    }

    bool try_pop_for(T& out, chrono::milliseconds timeout) {
        unique_lock<mutex> lk(m);
        while (queue.empty()) {
            if (not_empty.wait_for(lk, timeout) == cv_status::timeout)
                return false;
        }
        out = move(queue.front());
        queue.pop_front();

        lk.unlock(); 
        not_full.notify_one();
        return true;
    }
};


int main() {
    // Q<string> que(3);

    // thread producer([&]{
    //     for(string v : {"Adam", "Eve", "Henry"}) {
    //         que.add(move(v));
    //         this_thread::sleep_for(10ms);
    //     }
    // });

    // thread consumer([&]{
    //     for (int i = 0; i < 3; ++i) {
    //         string front = que.pop();
    //         cout << front << " was removed from the front" << endl;
    //         this_thread::sleep_for(200ms);
    //     }
    // });

    // producer.join();
    // consumer.join();


    Q<string> q(3);
    string s;
    bool ok1 = q.try_add_for("hello", 200ms);  // add with 200ms cap
    bool ok2 = q.try_pop_for(s, 500ms);        // pop with 500ms cap

    cout << ok1 << endl;
    cout << ok2 << endl;
}