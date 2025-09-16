#include <iostream>
using namespace std;

// Fungsi tukar pakai reference
void tukar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x, y;
    cout << "Masukkan nilai pertama: ";
    cin >> x;
    cout << "Masukkan nilai kedua  : ";
    cin >> y;

    cout << "Sebelum ditukar: x = " << x << ", y = " << y << endl;

    tukar(x, y);

    cout << "Sesudah ditukar: x = " << x << ", y = " << y << endl;
    return 0;
}