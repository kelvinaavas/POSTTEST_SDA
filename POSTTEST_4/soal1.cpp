#include <iostream>
#include <string>
using namespace std;

// Ini struktur Node buat stack (tumpukan)
struct Node {
    char data;
    Node* next;
};

// Fungsi buat masukin data ke stack (Push)
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

// Fungsi buat ngeluarin data dari stack (Pop)
char pop(Node*& top) {
    if (top == nullptr) return '\0'; // Stack kosong
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

// Fungsi buat balik string pake stack
string reverseString(string s) {
    Node* stackTop = nullptr;
    string reversed = "";

    // Masukin semua karakter ke stack
    for (char c : s) {
        push(stackTop, c);
    }
    // Ambil lagi satu-satu dari stack, jadi kebalik
    while (stackTop != nullptr) {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // Output: ataD rukurts
    return 0;
}

// Komentar anak SMA:
// Di sini kita pake stack yang manual pake linked list buat ngebalik string. Jadi hurufnya dimasukin ke tumpukan, terus diambil satu-satu dari atas, jadinya urutannya kebalik. Stack itu LIFO cuy, jadi yang terakhir masuk, yang pertama keluar.