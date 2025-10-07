#include <iostream>
#include <string>
using namespace std;

// Ini struktur Node buat stack (tumpukan)
struct Node {
    char data;
    Node* next;
};

// Fungsi push & pop dari soal 1 (biar ga ngetik ulang)
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

// Fungsi buat cek bracket seimbang
bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (stackTop == nullptr) return false; // Ada tutup, tapi ga ada buka
            char topChar = pop(stackTop);
            // Cek pasangannya
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                return false; // Nggak cocok pasangannya
            }
        }
    }
    // Stack harus kosong, kalo ga berarti masih ada buka yang ga ditutup
    return (stackTop == nullptr);
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;
    // Expected output: Seimbang
    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}

// Komentar anak SMA:
// Cek bracket seimbang itu gampang kalo pake stack. Setiap nemu buka, masukin ke stack. Nemu tutup, cek yang paling atas stack pasangannya. Kalo ga cocok, berarti ga seimbang. Abis itu stack harus kosong, baru deh bener.