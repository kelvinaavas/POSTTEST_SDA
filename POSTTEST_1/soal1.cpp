#include <iostream>
using namespace std;

// Fungsi untuk membalik array dengan pointer
void balikArray(int *arr, int n) {
    int *awal = arr;
    int *akhir = arr + n - 1;
    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;
        awal++;
        akhir--;
    }
}

// Fungsi cek bilangan prima
bool prima(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    const int n = 7;
    int arr[n];

    // Isi array dengan bilangan prima
    int angka = 2, idx = 0;
    while (idx < n) {
        if (prima(angka)) {
            arr[idx] = angka;
            idx++;
        }
        angka++;
    }

    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";

    balikArray(arr, n);

    cout << "\nArray sesudah dibalik: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}