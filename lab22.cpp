#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void delete_pos(int position) {
        if (!head) return;

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            return;
        }

        if (temp == head) {
            pop_front();
        } else if (temp == tail) {
            pop_back();
        } else {
            temp->prev->next = temp->next;
            if (temp->next)
                temp->next->prev = temp->prev;
            delete temp;
        }
    }

    void pop_front() {
        if (!head) return;

        Node* temp = head;
        head = head->next;
        
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) return;

        Node* temp = tail;
        tail = tail->prev;

        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp == head) {
            pop_front();
        } else if (temp == tail) {
            pop_back();
        } else {
            temp->next->prev = temp->next;
            if (temp->next)
                temp->next->prev = temp->prev;
            delete temp;
        }
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    list.delete_pos(0);
    cout << "Delete by position: ";
    list.print();

    list.pop_front();
    cout << "Pop front: ";
    list.print();

    list.pop_back();
    cout << "Pop back: ";
    list.print();

    list.delete_val(15);
    cout << "Delete value: ";
    list.print();

    return 0;
}
