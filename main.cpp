#include <iostream>
using namespace std;

// All array versions have a fixed capacity of 5.
const int CAPACITY = 5;

// 1. Stack using an array: last in, first out.
class ArrayStack {
    int data[CAPACITY];
    int count = 0;
public:
    void push(int value) {
        if (count == CAPACITY) { cout << "Stack full\n"; return; }
        data[count++] = value;
        cout << "Pushed " << value << "\n";
    }
    void pop() {
        if (count == 0) { cout << "Stack empty\n"; return; }
        cout << "Popped " << data[--count] << "\n";
    }
};

// 2. Stack using singly linked list.
class LinkedStack {
    struct Node { int value; Node* next; };
    Node* head = nullptr;
public:
    ~LinkedStack() { while (head) { Node* old = head; head = head->next; delete old; } }
    void push(int value) {
        head = new Node{value, head};
        cout << "Pushed " << value << "\n";
    }
    void pop() {
        if (!head) { cout << "Stack empty\n"; return; }
        Node* old = head;
        cout << "Popped " << old->value << "\n";
        head = head->next;
        delete old;
    }
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;
    LinkedStack() = default;
};

// 3. Queue using a circular array: first in, first out.
class ArrayQueue {
    int data[CAPACITY];
    int front = 0, count = 0;
public:
    void enqueue(int value) {
        if (count == CAPACITY) { cout << "Queue full\n"; return; }
        data[(front + count) % CAPACITY] = value;
        ++count;
        cout << "Enqueued " << value << "\n";
    }
    void dequeue() {
        if (count == 0) { cout << "Queue empty\n"; return; }
        cout << "Dequeued " << data[front] << "\n";
        front = (front + 1) % CAPACITY;
        --count;
    }
};

// 4. Queue using singly linked list.
class LinkedQueue {
    struct Node { int value; Node* next; };
    Node* first = nullptr;
    Node* last = nullptr;
public:
    ~LinkedQueue() { while (first) { Node* old = first; first = first->next; delete old; } }
    void enqueue(int value) {
        Node* node = new Node{value, nullptr};
        if (last) last->next = node;
        else first = node;
        last = node;
        cout << "Enqueued " << value << "\n";
    }
    void dequeue() {
        if (!first) { cout << "Queue empty\n"; return; }
        Node* old = first;
        cout << "Dequeued " << old->value << "\n";
        first = first->next;
        if (!first) last = nullptr;
        delete old;
    }
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;
    LinkedQueue() = default;
};

// 5. Deque using a circular array: insert/remove at both ends.
class ArrayDeque {
    int data[CAPACITY];
    int front = 0, count = 0;
public:
    void pushFront(int value) {
        if (count == CAPACITY) { cout << "Deque full\n"; return; }
        front = (front + CAPACITY - 1) % CAPACITY;
        data[front] = value;
        ++count;
        cout << "Added front " << value << "\n";
    }
    void pushBack(int value) {
        if (count == CAPACITY) { cout << "Deque full\n"; return; }
        data[(front + count) % CAPACITY] = value;
        ++count;
        cout << "Added back " << value << "\n";
    }
    void popFront() {
        if (count == 0) { cout << "Deque empty\n"; return; }
        cout << "Removed front " << data[front] << "\n";
        front = (front + 1) % CAPACITY;
        --count;
    }
    void popBack() {
        if (count == 0) { cout << "Deque empty\n"; return; }
        cout << "Removed back " << data[(front + count - 1) % CAPACITY] << "\n";
        --count;
    }
};

// 6. Deque using doubly linked list.
class LinkedDeque {
    struct Node { int value; Node* prev; Node* next; };
    Node* first = nullptr;
    Node* last = nullptr;
public:
    ~LinkedDeque() { while (first) { Node* old = first; first = first->next; delete old; } }
    void pushFront(int value) {
        Node* node = new Node{value, nullptr, first};
        if (first) first->prev = node;
        else last = node;
        first = node;
        cout << "Added front " << value << "\n";
    }
    void pushBack(int value) {
        Node* node = new Node{value, last, nullptr};
        if (last) last->next = node;
        else first = node;
        last = node;
        cout << "Added back " << value << "\n";
    }
    void popFront() {
        if (!first) { cout << "Deque empty\n"; return; }
        Node* old = first;
        cout << "Removed front " << old->value << "\n";
        first = first->next;
        if (first) first->prev = nullptr;
        else last = nullptr;
        delete old;
    }
    void popBack() {
        if (!last) { cout << "Deque empty\n"; return; }
        Node* old = last;
        cout << "Removed back " << old->value << "\n";
        last = last->prev;
        if (last) last->next = nullptr;
        else first = nullptr;
        delete old;
    }
    LinkedDeque(const LinkedDeque&) = delete;
    LinkedDeque& operator=(const LinkedDeque&) = delete;
    LinkedDeque() = default;
};
//7. For each structure, demonstrate insertion and removal operations, empty handling, and a sequence of at least 10 operations
template <typename Stack>
void testStack(const char* name) {
    cout << "\n=== " << name << " ===\n";
    Stack s;
    s.pop();       // 1: empty test
    s.push(10);    // 2
    s.push(20);    // 3
    s.push(30);    // 4
    s.pop();       // 5
    s.push(40);    // 6
    s.pop();       // 7
    s.pop();       // 8
    s.pop();       // 9
    s.pop();       // 10: empty test
    s.push(50);    // 11
    s.pop();       // 12
}

template <typename Queue>
void testQueue(const char* name) {
    cout << "\n=== " << name << " ===\n";
    Queue q;
    q.dequeue();     // 1: empty test
    q.enqueue(10);   // 2
    q.enqueue(20);   // 3
    q.enqueue(30);   // 4
    q.dequeue();     // 5
    q.enqueue(40);   // 6
    q.dequeue();     // 7
    q.dequeue();     // 8
    q.dequeue();     // 9
    q.dequeue();     // 10: empty test
    q.enqueue(50);   // 11
    q.dequeue();     // 12
}

template <typename Deque>
void testDeque(const char* name) {
    cout << "\n=== " << name << " ===\n";
    Deque d;
    d.popFront();     // 1: empty test
    d.pushBack(10);   // 2
    d.pushFront(20);  // 3
    d.pushBack(30);   // 4
    d.popBack();      // 5
    d.pushFront(40);  // 6
    d.popFront();     // 7
    d.popBack();      // 8
    d.popFront();     // 9
    d.popBack();      // 10: empty test
    d.pushBack(50);   // 11
    d.popFront();     // 12
}

int main() {
    testStack<ArrayStack>("Array Stack");
    testStack<LinkedStack>("Linked Stack");
    testQueue<ArrayQueue>("Array Queue");
    testQueue<LinkedQueue>("Linked Queue");
    testDeque<ArrayDeque>("Array Deque");
    testDeque<LinkedDeque>("Linked Deque");

    //

    cout << "\n=== Array Stack Full Test ===\n";
    ArrayStack fullStack;

    fullStack.push(10);
    fullStack.push(20);
    fullStack.push(30);
    fullStack.push(40);
    fullStack.push(50);
    fullStack.push(60);


    cout << "\n=== Array Queue Full Test ===\n";
    ArrayQueue fullQueue;

    fullQueue.enqueue(10);
    fullQueue.enqueue(20);
    fullQueue.enqueue(30);
    fullQueue.enqueue(40);
    fullQueue.enqueue(50);
    fullQueue.enqueue(60);


    cout << "\n=== Array Deque Full Test ===\n";
    ArrayDeque fullDeque;

    fullDeque.pushBack(10);
    fullDeque.pushBack(20);
    fullDeque.pushFront(30);
    fullDeque.pushFront(40);
    fullDeque.pushBack(50);
    fullDeque.pushFront(60);
    fullDeque.pushBack(70);
    return 0;
}
