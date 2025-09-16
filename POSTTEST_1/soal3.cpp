#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    const int n = 4;
    Mahasiswa mhs[n];

    cout << "Masukkan data 4 mahasiswa:\n";
    for (int i = 0; i < n; i++) {
        cout << "Mahasiswa " << i + 1 << endl;
        cout << "Nama : "; cin >> mhs[i].nama;
        cout << "NIM  : "; cin >> mhs[i].nim;
        cout << "IPK  : "; cin >> mhs[i].ipk;
    }

    // Urutkan berdasarkan IPK ascending
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mhs[i].ipk > mhs[j].ipk) {
                Mahasiswa temp = mhs[i];
                mhs[i] = mhs[j];
                mhs[j] = temp;
            }
        }
    }

    cout << "\nData mahasiswa setelah diurutkan (IPK ascending):\n";
    for (int i = 0; i < n; i++) {
        cout << "Nama : " << mhs[i].nama << endl;
        cout << "NIM  : " << mhs[i].nim << endl;
        cout << "IPK  : " << mhs[i].ipk << endl << endl;
    }

    return 0;
}