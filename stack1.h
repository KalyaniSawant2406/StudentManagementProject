
#ifndef STACK_H
#define STACK_H

#include <stdexcept>
using namespace std;

template <typename T>
struct StackNode {
    T data;
    StackNode<T>* next;
};

template <typename T>
class Stack {
private:
    StackNode<T>* head;
    int count;

public:
    Stack() : head(nullptr), count(0) {}

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    bool IsEmpty() const {
        return head == nullptr;
    }

    int Count() const {
        return count;
    }

    void Push(const T& val) {
        StackNode<T>* n = new StackNode<T>{val, head};
        head = n;
        ++count;
    }

    T Pop() {
        if (head == nullptr) {
            throw runtime_error("Stack is empty");
        }

        StackNode<T>* old = head;
        T value = old->data;

        head = head->next;
        delete old;
        --count;

        return value;
    }

    T Peek() const {
        if (head == nullptr) {
            throw runtime_error("Stack is empty");
        }

        return head->data;
    }

    ~Stack() {
        // Clear stack: O(n) time, O(1) auxiliary space.
        while (head != nullptr) {
            StackNode<T>* old = head;
            head = head->next;
            delete old;
        }

        count = 0;
    }
};

#endif