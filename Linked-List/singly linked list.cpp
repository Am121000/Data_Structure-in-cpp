/// singly linked acts like an efficient dynamic error which offer better memory use
/// it is one of the easiest data structure to learn and master, the concepts are also easy into this aspect
#include<iostream>
using namespace std;
///Firstly we make a class named node for declaring our data structure.
/// you can also use structures and make use of the keyword struct.
///and the reason i do so because I can always use the constructor to directly assign the value rather than making a new function
#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    bool isEmpty() {
        return head == nullptr;
    }
/// insert at head we give a assign a new headnode into the existing list
    void insertAtHead(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }
/// insert at the tail we traverse our list till the end using the while loop and then we add the newnode
    void insertAtTail(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
/// delete at head we first copy our head value to the temp folder and then assign the new head
    void deleteAtHead() {
        if (isEmpty()) {
            std::cout << "Linked list is empty. No nodes to delete." << std::endl;
        } else {
            Node* temp = head;
            head = head->next;
            delete temp;/// temp is stil having the prev head vlaue so we are deleting it.
        }
    }
/// deleting at tail is not very similar to inserting at tail
    void deleteAtTail() {
        if (isEmpty()) {
            std::cout << "Linked list is empty. No nodes to delete." << std::endl;
        } else if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next->next != nullptr) { /// heare the condition checks if the next to next node is the last node.
                current = current->next;
            }
            delete current->next;/// once we are at he 2nd last node we delete the next value of the current pointer
            current->next = nullptr;
        }
    }
/// display function
    void display() {
        if (isEmpty()) {
            std::cout << "Linked list is empty." << std::endl;
        } else {
            Node* current = head;
            while (current != nullptr) {
                std::cout << current->data << " -> ";
                current = current->next;
            }
            std::cout << "NULL" << std::endl;
        }
    }
};

int main() {
    LinkedList linkedList;
    linkedList.insertAtHead(3);
    linkedList.insertAtHead(2);
    linkedList.insertAtHead(1);
    linkedList.insertAtTail(4);
    linkedList.insertAtTail(5);
    linkedList.display();

    linkedList.deleteAtHead();
    linkedList.deleteAtTail();
    linkedList.display();
    return 0;
}
