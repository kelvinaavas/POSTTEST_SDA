#include <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

static const string NIM_LAST3 = "094";
static const int LAST_DIGIT = 4; 

struct Node {
    string kodePenerbangan;
    string tujuan;
    string status; 
    Node* next;
    Node(const string& kode, const string& tujuan, const string& status)
        : kodePenerbangan(kode), tujuan(tujuan), status(status), next(nullptr) {}
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};

static inline string trim(const string& s) {
    size_t start = 0, end = s.size();
    while (start < end && isspace(static_cast<unsigned char>(s[start]))) start++;
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) end--;
    return s.substr(start, end - start);
}

static inline string toUpper(const string& s) {
    string r = s;
    for (char& c : r) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    return r;
}

void pauseAndClear() {
    cout << "\nTekan Enter untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader() {
    cout << "+------------------------------------------------------------+\n";
    cout << "|               FLIGHT SCHEDULE SYSTEM                       |\n";
    cout << "|            [ NAMA ANDA - NIM ..." << NIM_LAST3 << " ]                      |\n";
    cout << "+------------------------------------------------------------+\n";
}

void printMenu() {
    printHeader();
    cout << "| 1. Tambah Jadwal Penerbangan                               |\n";
    cout << "| 2. Sisipkan Jadwal Penerbangan                             |\n";
    cout << "| 3. Hapus Jadwal Paling Awal                                |\n";
    cout << "| 4. Update Status Penerbangan                               |\n";
    cout << "| 5. Tampilkan Semua Jadwal                                  |\n";
    cout << "| 0. Keluar                                                  |\n";
    cout << "+------------------------------------------------------------+\n";
    cout << "Pilih menu: ";
}

string generateFlightCode(const List& list) {
    
    if (list.size == 0) return string("JT-") + NIM_LAST3;
    return string("JT-") + NIM_LAST3 + "-" + to_string(list.size);
}

size_t getInsertPositionFromNIM() {
    if (LAST_DIGIT == 0) return 2; 
    return static_cast<size_t>(LAST_DIGIT + 1); 
}

string readLineSafe(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return trim(s);
}

void addFront(List& list, Node* node) {
    if (!node) return;
    if (!list.head) {
        list.head = list.tail = node;
    } else {
        node->next = list.head;
        list.head = node;
    }
    list.size++;
}

void addBack(List& list, Node* node) {
    if (!node) return;
    if (!list.head) {
        list.head = list.tail = node;
    } else {
        list.tail->next = node;
        list.tail = node;
    }
    list.size++;
}

void insertAtPosition(List& list, Node* node, size_t pos) {
    if (!node) return;
    if (pos <= 1 || list.size == 0) {
        addFront(list, node);
        return;
    }
    if (pos > list.size) {
        addBack(list, node);
        return;
    }
    
    Node* prev = list.head;
    for (size_t i = 1; i < pos - 1 && prev->next; ++i) {
        prev = prev->next;
    }
    node->next = prev->next;
    prev->next = node;
    if (node->next == nullptr) list.tail = node;
    list.size++;
}

bool deleteFront(List& list) {
    if (!list.head) return false;
    Node* del = list.head;
    list.head = list.head->next;
    if (!list.head) list.tail = nullptr;
    delete del;
    list.size--;
    return true;
}

Node* findByCode(List& list, const string& kode, Node** outPrev = nullptr) {
    Node* prev = nullptr;
    Node* cur = list.head;
    while (cur) {
        if (cur->kodePenerbangan == kode) {
            if (outPrev) *outPrev = prev;
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    if (outPrev) *outPrev = nullptr;
    return nullptr;
}

bool updateStatusByCode(List& list, const string& kode, const string& statusBaru) {
    Node* node = findByCode(list, kode);
    if (!node) return false;
    node->status = statusBaru;
    return true;
}

void showAll(const List& list) {
    cout << "\nDaftar Semua Jadwal (" << list.size << "):\n";
    if (!list.head) {
        cout << "(Kosong)\n";
        return;
    }
    const Node* cur = list.head;
    size_t i = 1;
    while (cur) {
        cout << i << ". Kode: " << cur->kodePenerbangan
             << " | Tujuan: " << cur->tujuan
             << " | Status: " << cur->status << "\n";
        cur = cur->next;
        ++i;
    }
}

void clearAll(List& list) {
    while (list.head) {
        deleteFront(list);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    List list;
    bool running = true;

    while (running) {
        printMenu();
        string choiceLine;
        getline(cin, choiceLine);
        choiceLine = trim(choiceLine);
        if (choiceLine.empty()) continue;
        int choice = -1;
        try {
            choice = stoi(choiceLine);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: {
                
                string tujuan = readLineSafe("Masukkan tujuan: ");
                if (tujuan.empty()) tujuan = "(Tanpa Tujuan)";
                string status = readLineSafe("Masukkan status awal (Tepat Waktu/Terlambat/Naik Pesawat): ");
                if (status.empty()) status = "Tepat Waktu";

                string kode = generateFlightCode(list);
                Node* node = new Node(kode, tujuan, status);
                addBack(list, node);
                cout << "Berhasil menambahkan jadwal dengan kode: " << kode << "\n";
                pauseAndClear();
                break;
            }
            case 2: {
                
                string tujuan = readLineSafe("Masukkan tujuan: ");
                if (tujuan.empty()) tujuan = "(Tanpa Tujuan)";
                string status = readLineSafe("Masukkan status awal (Tepat Waktu/Terlambat/Naik Pesawat): ");
                if (status.empty()) status = "Tepat Waktu";

                string kode = generateFlightCode(list);
                Node* node = new Node(kode, tujuan, status);
                size_t pos = getInsertPositionFromNIM();
                
                insertAtPosition(list, node, pos);
                cout << "Berhasil menyisipkan jadwal pada posisi " << pos
                     << " dengan kode: " << kode << "\n";
                pauseAndClear();
                break;
            }
            case 3: {
                
                if (deleteFront(list)) {
                    cout << "Jadwal paling awal berhasil dihapus.\n";
                } else {
                    cout << "List kosong, tidak ada yang dihapus.\n";
                }
                pauseAndClear();
                break;
            }
            case 4: {
                
                string kode = readLineSafe("Masukkan kode penerbangan yang ingin diupdate: ");
                Node* target = findByCode(list, kode);
                if (!target) {
                    cout << "Kode tidak ditemukan.\n";
                } else {
                    cout << "Data ditemukan: Tujuan=" << target->tujuan
                         << ", Status saat ini=" << target->status << "\n";
                    string statusBaru = readLineSafe("Masukkan status baru: ");
                    if (statusBaru.empty()) {
                        cout << "Status baru kosong, dibatalkan.\n";
                    } else {
                        bool ok = updateStatusByCode(list, kode, statusBaru);
                        cout << (ok ? "Status berhasil diperbarui.\n" : "Gagal memperbarui status.\n");
                    }
                }
                pauseAndClear();
                break;
            }
            case 5: {
                
                showAll(list);
                pauseAndClear();
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default: {
                cout << "Pilihan tidak valid.\n";
                pauseAndClear();
                break;
            }
        }
    }

    clearAll(list);
    cout << "Terima kasih telah menggunakan sistem.\n";
    return 0;
}

