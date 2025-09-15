#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std;

template<typename T>
class Q {
    mutex m;
    condition_variable not_empty;
    condition_variable not_full;
    deque<T> queue; 
    const size_t _cap;
public:
    Q(size_t cap) : _cap(cap) {}

    void add(T x) {
    unique_lock<mutex> lock(m);
        while (queue.size() >= _cap) {
            cout << "The queue is currently full. Waiting..." << endl;
            not_full.wait(lock);
        }

        queue.push_back(x);
        cout << "Added " << x << " to the queue" << endl;

        lock.unlock();
        not_empty.notify_one();
    }

    T pop() {
    unique_lock<mutex> lock(m);
        while (queue.empty()) {
            cout << "The queue is currently empty. Waiting..." << endl;
            not_empty.wait(lock);
        }

        T first = queue.front();
        queue.pop_front();

        lock.unlock();
        not_full.notify_one();
        return first;
    }
};


int main() {
    Q<int> que(3);

    thread producer([&]{
        for(int v : {10, 20, 30, 40, 50}) {
            que.add(v);
            this_thread::sleep_for(10ms);
        }
    });

    thread consumer([&]{
        for (int i = 0; i < 5; ++i) {
            int front = que.pop();
            cout << front << " was removed from the front" << endl;
            this_thread::sleep_for(200ms);
        }
    });

    producer.join();
    consumer.join();
}