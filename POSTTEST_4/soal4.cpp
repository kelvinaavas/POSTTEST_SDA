#include <iostream>
using namespace std;

// Node buat circular doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Fungsi buat insert data biar tetap urut
void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};
    // List kosong
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    // Sisip di awal (data lebih kecil dari head)
    if (data < head_ref->data) {
        Node* tail = head_ref->prev;
        newNode->next = head_ref;
        newNode->prev = tail;
        tail->next = newNode;
        head_ref->prev = newNode;
        head_ref = newNode; // Head pindah ke node baru
        return;
    }
    // Sisip di tengah/akhir
    Node* current = head_ref;
    while (current->next != head_ref && current->next->data < data) {
        current = current->next;
    }
    // Sisip setelah current
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

void printList(Node *head_ref)
{
    if (head_ref == nullptr)
    {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main()
{
    Node *head = nullptr;

    // Test sorted insert
    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    // Expected output: 10 20 30 40
    printList(head);

    return 0;
}

// Komentar anak SMA:
// Ini circular doubly linked list yang urut. Kalo data baru lebih kecil dari head, jadi head. Kalo di tengah/akhir, cari posisi yang bener. Biar urut terus, pointer next & prev harus diatur bener-bener.