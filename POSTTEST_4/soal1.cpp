#include <iostream>
#include <string>
using namespace std;

// Ini struktur Node buat stack
struct Node {
    char data;
    Node* next;
};

// Fungsi buat masukin data ke stack
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

// Fungsi buat ngeluarin data dari stack
char pop(Node*& top) {
    if (top == nullptr) return '\0';
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

    for (char c : s) {
        push(stackTop, c);
    }

    while (stackTop != nullptr) {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl;
    return 0;
}
