#ifndef SLL1_H
#define SLL1_H

#include <iostream>
#include "Student.h"
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    bool IsEmpty() const {
        return head == nullptr;
    }

    int Count() const {
        return count;
    }

    void AddAtTheEnd(const T& val) {
        Node<T>* n = new Node<T>{val, nullptr};

        if (head == nullptr) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }

        ++count;
    }

    bool GetByRoll(int roll, T& result) const {
        Node<T>* trav = head;

        // Search by roll: O(n) time, O(1) auxiliary space.
        while (trav != nullptr) {
            if (trav->data.roll == roll) {
                result = trav->data;
                return true;
            }

            trav = trav->next;
        }

        return false;
    }

    bool Search(const T& val) const {
        Node<T>* trav = head;

        // Search: O(n) time, O(1) auxiliary space.
        while (trav != nullptr) {
            if (trav->data == val) {
                return true;
            }

            trav = trav->next;
        }

        return false;
    }

    bool Remove(const T& val) {
        if (head == nullptr) {
            return false;
        }

        if (head->data == val) {
            Node<T>* old = head;
            head = head->next;

            if (head == nullptr) {
                tail = nullptr;
            }

            delete old;
            --count;
            return true;
        }

        Node<T>* prev = head;

        // Removal: O(n) time to find the node and its predecessor.
        while (prev->next != nullptr &&
               !(prev->next->data == val)) {
            prev = prev->next;
        }

        if (prev->next == nullptr) {
            return false;
        }

        Node<T>* old = prev->next;
        prev->next = old->next;

        if (old == tail) {
            tail = prev;
        }

        delete old;
        --count;

        return true;
    }

    void PrintAll() const {
        if (head == nullptr) {
            cout << "No student records found.\n";
            return;
        }

        Node<T>* trav = head;

        // Display all records: O(n) time, O(1) auxiliary space.
        while (trav != nullptr) {
            cout << trav->data << '\n';
            trav = trav->next;
        }
    }

    template <typename Func>
    void ForEach(Func action) const {
        Node<T>* trav = head;

        // Visit all records: O(n) time, O(1) traversal space.
        while (trav != nullptr) {
            action(trav->data);
            trav = trav->next;
        }
    }

    void Clear() {
        Node<T>* trav = head;

        // Delete all nodes: O(n) time, O(1) auxiliary space.
        while (trav != nullptr) {
            Node<T>* nextNode = trav->next;
            delete trav;
            trav = nextNode;
        }

        head = tail = nullptr;
        count = 0;
    }

    ~SinglyLinkedList() {
        Clear();
    }
};

#endif