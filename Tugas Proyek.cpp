#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

// Kelas Motor
class Motor {
private:
    string nama;
    string platNomor;
    double hargaSewa;
    bool tersedia;

public:
    Motor(string nama, string platNomor, double hargaSewa) {
        this->nama = nama;
        this->platNomor = platNomor;
        this->hargaSewa = hargaSewa;
        this->tersedia = true;
    }

    string getNama() { return nama; }
    string getPlatNomor() { return platNomor; }
    double getHargaSewa() { return hargaSewa; }
    bool isTersedia() { return tersedia; }

    void sewa() {
        tersedia = false;
    }

    void kembalikan() {
        tersedia = true;
    }
};

// Struktur untuk mencatat penyewaan
struct RegistrasiPenyewaan {
    string namaPenyewa;
    string motor;
    string platNomor;
    double hargaSewa;
    int jumlahHari;
    double totalBiaya;
};

// Kelas PenyewaanMotor
class PenyewaanMotor {
private:
    vector<Motor> daftarMotor;
    stack<Motor> stackMotorBaru;
    vector<RegistrasiPenyewaan> daftarPenyewaan;

public:
    void tambahMotor(Motor motor) {
        daftarMotor.push_back(motor);
    }

    void tambahMotorKeStack(Motor motor) {
        stackMotorBaru.push(motor);
        cout << "Motor " << motor.getNama() << " telah ditambahkan ke antrian untuk ditambahkan ke daftar.\n";
    }

    void pindahkanMotorDariStack() {
        if (stackMotorBaru.empty()) {
            cout << "Tidak ada motor baru dalam antrian.\n";
            return;
        }
        Motor motor = stackMotorBaru.top();
        stackMotorBaru.pop();
        tambahMotor(motor);
        cout << "Motor " << motor.getNama() << " telah dipindahkan ke daftar penyewaan.\n";
    }

    void tampilkanMotor() {
        if (daftarMotor.empty()) {
            cout << "Tidak ada motor dalam daftar.\n";
            return;
        }

        cout << "Daftar Motor:" << endl;
        for (size_t i = 0; i < daftarMotor.size(); ++i) {
            cout << i + 1 << ". " << daftarMotor[i].getNama()
                 << " (" << daftarMotor[i].getPlatNomor() << ") - Harga Sewa per Hari: Rp"
                 << daftarMotor[i].getHargaSewa() << " - "
                 << (daftarMotor[i].isTersedia() ? "Tersedia" : "Disewa") << endl;
        }
    }

    void hapusMotor(int indeks) {
        if (indeks > 0 && indeks <= daftarMotor.size()) {
            cout << "Motor " << daftarMotor[indeks - 1].getNama() << " telah dihapus dari daftar.\n";
            daftarMotor.erase(daftarMotor.begin() + (indeks - 1));
        } else {
            cout << "Indeks motor tidak valid!\n";
        }
    }

    void sewaMotor(int indeks, const string& namaPenyewa, int jumlahHari) {
        if (indeks > 0 && indeks <= daftarMotor.size()) {
            Motor& motor = daftarMotor[indeks - 1];
            if (motor.isTersedia()) {
                motor.sewa();
                double totalBiaya = motor.getHargaSewa() * jumlahHari;
                daftarPenyewaan.push_back({namaPenyewa, motor.getNama(), motor.getPlatNomor(), motor.getHargaSewa(), jumlahHari, totalBiaya});
                cout << "Motor " << motor.getNama() << " berhasil disewa oleh " << namaPenyewa
                     << " untuk " << jumlahHari << " hari dengan total biaya Rp" << totalBiaya << endl;
            } else {
                cout << "Motor " << motor.getNama() << " sedang tidak tersedia." << endl;
            }
        } else {
            cout << "Indeks motor tidak valid!" << endl;
        }
    }

    void kembalikanMotor(int indeks) {
        if (indeks > 0 && indeks <= daftarMotor.size()) {
            Motor& motor = daftarMotor[indeks - 1];
            if (!motor.isTersedia()) {
                motor.kembalikan();
                cout << "Motor " << motor.getNama() << " berhasil dikembalikan." << endl;
            } else {
                cout << "Motor " << motor.getNama() << " sudah tersedia." << endl;
            }
        } else {
            cout << "Indeks motor tidak valid!" << endl;
        }
    }

    void tampilkanRiwayatPenyewaan() {
        if (daftarPenyewaan.empty()) {
            cout << "Belum ada riwayat penyewaan.\n";
            return;
        }

        cout << "Riwayat Penyewaan:\n";
        for (size_t i = 0; i < daftarPenyewaan.size(); ++i) {
            cout << i + 1 << ". Nama Penyewa: " << daftarPenyewaan[i].namaPenyewa
                 << ", Motor: " << daftarPenyewaan[i].motor
                 << ", Plat Nomor: " << daftarPenyewaan[i].platNomor
                 << ", Harga Sewa per Hari: Rp" << daftarPenyewaan[i].hargaSewa
                 << ", Jumlah Hari: " << daftarPenyewaan[i].jumlahHari
                 << ", Total Biaya: Rp" << daftarPenyewaan[i].totalBiaya << endl;
        }
    }
};

int main() {
    PenyewaanMotor penyewaan;

    // Menambahkan motor ke dalam daftar awal
    penyewaan.tambahMotor(Motor("Honda Beat", "AB1234CD", 50000));
    penyewaan.tambahMotor(Motor("Yamaha Nmax", "AB5678EF", 100000));
    penyewaan.tambahMotor(Motor("Suzuki Address", "AB9101GH", 75000));

    int pilihan, indeks, jumlahHari;
    string namaPenyewa;

    do {
        cout << "\nSistem Penyewaan Motor\n";
        cout << "1. Tampilkan Daftar Motor\n";
        cout << "2. Sewa Motor\n";
        cout << "3. Kembalikan Motor\n";
        cout << "4. Tambah Motor ke Stack\n";
        cout << "5. Pindahkan Motor dari Stack ke Daftar\n";
        cout << "6. Hapus Motor\n";
        cout << "7. Tampilkan Riwayat Penyewaan\n";
        cout << "8. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            penyewaan.tampilkanMotor();
            break;
        case 2:
            cout << "Masukkan indeks motor yang ingin disewa: ";
            cin >> indeks;
            cout << "Masukkan nama penyewa: ";
            cin.ignore();
            getline(cin, namaPenyewa);
            cout << "Masukkan jumlah hari sewa: ";
            cin >> jumlahHari;
            penyewaan.sewaMotor(indeks, namaPenyewa, jumlahHari);
            break;
        case 3:
            cout << "Masukkan indeks motor yang ingin dikembalikan: ";
            cin >> indeks;
            penyewaan.kembalikanMotor(indeks);
            break;
        case 4: {
            string nama, platNomor;
            double hargaSewa;
            cout << "Masukkan nama motor: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan plat nomor motor: ";
            getline(cin, platNomor);
            cout << "Masukkan harga sewa motor: ";
            cin >> hargaSewa;
            penyewaan.tambahMotorKeStack(Motor(nama, platNomor, hargaSewa));
            break;
        }
        case 5:
            penyewaan.pindahkanMotorDariStack();
            break;
        case 6:
            cout << "Masukkan indeks motor yang ingin dihapus: ";
            cin >> indeks;
            penyewaan.hapusMotor(indeks);
            break;
        case 7:
            penyewaan.tampilkanRiwayatPenyewaan();
            break;
        case 8:
            cout << "Terima kasih telah menggunakan sistem penyewaan motor." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 8);

    return 0;
}
 
