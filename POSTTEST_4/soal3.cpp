#include <iostream>
#include <string>
using namespace std;

// Node buat queue (antrian)
struct Node {
    string document;
    Node* next;
};

// Fungsi masukin dokumen ke antrian (enqueue)
void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};
    if (front == nullptr) {
        front = rear = newNode; // Kalo antrian kosong
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Fungsi ngeluarin dokumen dari antrian (dequeue)
string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return ""; // Queue kosong
    Node* temp = front;
    string doc = temp->document;
    front = front->next;
    if (front == nullptr) rear = nullptr; // Kalo udah abis, rear juga null
    delete temp;
    return doc;
}

// Fungsi proses semua dokumen di antrian
void processAllDocuments(Node*& front, Node*& rear) {
    while (front != nullptr) {
        string doc = dequeue(front, rear);
        cout << "Memproses: " << doc << endl;
    }
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}

// Komentar anak SMA:
// Ini antrian printer pake queue manual. Jadi yang pertama masuk, diproses duluan. Kalo masuk, rear maju. Kalo keluar, front maju. Simple, urutannya ga bakal ketukar.