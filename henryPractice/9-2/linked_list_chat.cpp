#include <iostream>
#include <string>
using namespace std;

struct Node {
    char val;
    Node* next;
    Node(char v, Node* n=nullptr) : val(v), next(n) {}
};

// ----- helpers -----
Node* make_list_from_string(const string& s) {
    if (s.empty()) return nullptr;
    Node* head = new Node(s[0]);
    Node* tail = head;
    for (size_t i = 1; i < s.size(); ++i) {
        tail->next = new Node(s[i]);
        tail = tail->next;
    }
    return head;
}
void print(const Node* head) {
    for (auto* p = head; p; p = p->next) cout << p->val;
    cout << '\n';
}
void destroy(Node*& head) {
    while (head) { Node* t = head->next; delete head; head = t; }
}

// ===========================================================
// 1) IN-PLACE REVERSAL (reuse nodes) — O(n) time, O(1) space.
//    prev / curr / next classic pattern
// ===========================================================
void reverse_in_place(Node*& head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* nxt = curr->next; // remember the rest
        curr->next = prev;      // flip link
        prev = curr;            // advance prev
        curr = nxt;             // advance curr
    }
    head = prev; // new head
}

// ==================================================================
// 2) BUILD A SEPARATE REVERSED COPY (keep original intact) — O(n) time,
//    O(n) extra space. push_front-style copy
// ==================================================================
Node* reversed_copy_push_front(const Node* head) {
    Node* new_head = nullptr;
    for (auto* p = head; p; p = p->next) {
        new_head = new Node(p->val, new_head); // push_front
    }
    return new_head;
}

// ==================================================================
// 3) “PEEL FROM THE END” (find predecessor each round) — O(n^2) time.
//    Reuses nodes. Each round:
//      - scan to find (prev_of_tail, tail)
//      - detach tail from original (null-terminate remainder)
//      - append tail to result tail (and keep result_tail)
// ==================================================================
void reverse_by_peeling(Node*& head) {
    if (!head || !head->next) return; // empty or single-node: nothing to do

    Node* result_head = nullptr;
    Node* result_tail = nullptr;

    while (head) {
        Node* prev = nullptr;
        Node* tail = head;

        // walk to the last node, keeping its predecessor
        while (tail->next) {
            prev = tail;
            tail = tail->next;
        }

        // detach tail from original list
        if (prev) {
            prev->next = nullptr;
        } else {
            // prev == nullptr means tail == head (single node remains)
            head = nullptr;
        }

        // append detached tail to result
        tail->next = nullptr; // ensure correct termination
        if (!result_head) {
            result_head = tail;
            result_tail = tail;
        } else {
            result_tail->next = tail;
            result_tail = tail;
        }

        // if we detached the last remaining node, head is already set to nullptr above
        if (!head && prev) {
            // nothing: loop will exit
        }
    }

    head = result_head; // new head is the head of the built reversed chain
}

// ----- tiny demos -----
int main() {
    // demo string
    Node* a = make_list_from_string("hello");
    cout << "orig a: "; print(a);

    // 1) in-place
    reverse_in_place(a);
    cout << "in-place reversed a: "; print(a);
    destroy(a);

    // 2) reversed copy (original intact)
    Node* b = make_list_from_string("hello");
    Node* b_rev = reversed_copy_push_front(b);
    cout << "orig b (intact): "; print(b);
    cout << "copy reversed b: "; print(b_rev);
    destroy(b);
    destroy(b_rev);

    // 3) peel-from-end (O(n^2))
    Node* c = make_list_from_string("hello");
    reverse_by_peeling(c);
    cout << "peel reversed c: "; print(c);
    destroy(c);
}
