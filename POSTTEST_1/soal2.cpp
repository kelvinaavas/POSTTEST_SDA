#include <iostream>
using namespace std;

int main() {
    const int n = 3;
    int matriks[n][n];

    // Input matriks
    cout << "Masukkan elemen matriks 3x3:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matriks[i][j];
        }
    }

    int jumlah = 0;
    for (int i = 0; i < n; i++) {
        if ((i + 1) % 2 == 0) { // baris genap (baris ke-2 dst)
            for (int j = 0; j < n; j++) {
                jumlah += matriks[i][j];
            }
        }
    }

    cout << "\nMatriks:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Jumlah elemen baris genap = " << jumlah << endl;
    return 0;
}