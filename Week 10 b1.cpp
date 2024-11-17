#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Hàm tạo node mới
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

// Hàm thêm node vào cuối danh sách
void append(Node*& head, int value) {
    Node* newNode = createNode(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Hàm in danh sách
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "null" << endl;
}

// Xóa node ở đầu danh sách
void deleteAtHead(Node*& head) {
    if (head == nullptr) {
        cout << "Danh sách rỗng, không thể xóa." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

// Xóa node ở cuối danh sách
void deleteAtTail(Node*& head) {
    if (head == nullptr) {
        cout << "Danh sách rỗng, không thể xóa." << endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Xóa node sau node cho trước
void deleteAfter(Node* prevNode) {
    if (prevNode == nullptr || prevNode->next == nullptr) {
        cout << "Không thể xóa, node không hợp lệ." << endl;
        return;
    }
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    delete temp;
}

int main() {
    Node* head = nullptr;

    // Tạo danh sách liên kết
    append(head, 10);
    append(head, 20);
    append(head, 30);
    append(head, 40);

    cout << "Danh sách ban đầu: ";
    printList(head);

    // Xóa node ở đầu
    deleteAtHead(head);
    cout << "Sau khi xóa node đầu: ";
    printList(head);

    // Xóa node ở cuối
    deleteAtTail(head);
    cout << "Sau khi xóa node cuối: ";
    printList(head);

    // Xóa node sau node cho trước
    deleteAfter(head); // Xóa node sau node đầu
    cout << "Sau khi xóa node sau node đầu: ";
    printList(head);

    return 0;
}
