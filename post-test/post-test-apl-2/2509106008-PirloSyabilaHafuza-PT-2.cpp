#include <iostream>
#include <string>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

struct AlamatGudang {
    string gedung;
    string lantai;
    string rak;
};

struct ItemInventaris {
    string kodeBarang;
    string namaBarang;
    string kategori;
    int jumlah;
    int harga;
    AlamatGudang alamat;
    bool tersedia;
};

int main() {

    const int MAKS_BARANG = 100;
    ItemInventaris dataBarang[MAKS_BARANG];
    int jumlahBarang = 0;

    dataBarang[0].kodeBarang = "EL001";
    dataBarang[0].namaBarang = "Laptop Asus";
    dataBarang[0].kategori = "Komputer";
    dataBarang[0].jumlah = 10;
    dataBarang[0].harga = 5000000;
    dataBarang[0].alamat.gedung = "Gudang A";
    dataBarang[0].alamat.lantai = "1";
    dataBarang[0].alamat.rak = "01";
    dataBarang[0].tersedia = (dataBarang[0].jumlah > 0);

    dataBarang[1].kodeBarang = "EL002";
    dataBarang[1].namaBarang = "Mouse Logitech";
    dataBarang[1].kategori = "Aksesoris";
    dataBarang[1].jumlah = 50;
    dataBarang[1].harga = 150000;
    dataBarang[1].alamat.gedung = "Gudang A";
    dataBarang[1].alamat.lantai = "1";
    dataBarang[1].alamat.rak = "02";
    dataBarang[1].tersedia = (dataBarang[1].jumlah > 0);

    dataBarang[2].kodeBarang = "EL003";
    dataBarang[2].namaBarang = "Monitor LG";
    dataBarang[2].kategori = "Komputer";
    dataBarang[2].jumlah = 0;
    dataBarang[2].harga = 2000000;
    dataBarang[2].alamat.gedung = "Gudang B";
    dataBarang[2].alamat.lantai = "2";
    dataBarang[2].alamat.rak = "05";
    dataBarang[2].tersedia = (dataBarang[2].jumlah > 0);

    jumlahBarang = 3;
    bool programAktif = true;

    while (programAktif) {

        bool sudahLogin = false;
        int menuAwal;

        while (!sudahLogin && programAktif) {

            system("cls");

            cout << "\n==================================================";
            cout << "\n   SISTEM MANAJEMEN INVENTARIS GUDANG ELEKTRONIK   ";
            cout << "\n==================================================";
            cout << "\n1. Login";
            cout << "\n2. Keluar Program";
            cout << "\n\nPilihan: ";

            cin >> menuAwal;
            cin.ignore();

            if (menuAwal == 1) {

                string inputNama, inputPass;
                int percobaan = 0;

                while (percobaan < 3) {

                    cout << "\n--- Login (Percobaan " << percobaan + 1 << "/3) ---";
                    cout << "\nUsername: ";
                    cin >> inputNama;

                    cout << "Password: ";
                    cin >> inputPass;

                    if (inputNama == "Pirlo" && inputPass == "008") {

                        sudahLogin = true;

                        cout << "\nLogin Berhasil!";
                        cout << "\nSelamat datang." << endl;
                        
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.ignore();
                        cin.get(); 
                        break;
                    }
                    else {

                        cout << "Username atau Password salah!" << endl;
                        percobaan++;

                        if (percobaan >= 3) {
                            cout << "\nGagal login 3 kali. Program berhenti.";
                            cout << "\nTekan Enter untuk keluar...";
                            cin.ignore();
                            cin.get();
                            return 0;
                        }
                        
                        cout << "Tekan Enter untuk mencoba lagi...";
                        cin.ignore();
                        cin.get();
                    }
                }
            }
            else if (menuAwal == 2) {

                cout << "\nTerima kasih telah menggunakan program ini.";
                programAktif = false;
            }
            else {
                cout << "\nPilihan tidak valid!";
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
            }
        }

        while (sudahLogin) {

            int menuUtama;

            system("cls");

            cout << "\n==================================================";
            cout << "\n   MENU UTAMA INVENTARIS GUDANG ELEKTRONIK         ";
            cout << "\n==================================================";

            cout << "\n1. Tambah Barang";
            cout << "\n2. Lihat Barang";
            cout << "\n3. Ubah Barang";
            cout << "\n4. Hapus Barang";
            cout << "\n5. Logout";

            cout << "\n\nPilihan: ";

            cin >> menuUtama;
            cin.ignore();

            if (menuUtama == 1) {

                if (jumlahBarang >= MAKS_BARANG) {

                    cout << "\nKapasitas gudang penuh!";
                    cout << "\nTekan Enter untuk melanjutkan...";
                    cin.get();
                }
                else {

                    cout << "\n--- Tambah Barang ---";

                    cout << "\nKode Barang: ";
                    cin >> dataBarang[jumlahBarang].kodeBarang;

                    bool kodeSama = false;

                    for (int i = 0; i < jumlahBarang; i++) {
                        if (dataBarang[i].kodeBarang == dataBarang[jumlahBarang].kodeBarang) {
                            kodeSama = true;
                            break;
                        }
                    }

                    if (kodeSama) {
                        cout << "Kode barang sudah digunakan!";
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.ignore();
                        cin.get();
                    }
                    else {
                        cin.ignore();

                        cout << "Nama Barang: ";
                        getline(cin, dataBarang[jumlahBarang].namaBarang);

                        cout << "Kategori: ";
                        getline(cin, dataBarang[jumlahBarang].kategori);

                        cout << "Jumlah: ";
                        cin >> dataBarang[jumlahBarang].jumlah;

                        cout << "Harga: ";
                        cin >> dataBarang[jumlahBarang].harga;

                        cin.ignore();

                        cout << "\n--- Lokasi Penyimpanan ---";

                        cout << "\nGedung: ";
                        getline(cin, dataBarang[jumlahBarang].alamat.gedung);

                        cout << "Lantai: ";
                        getline(cin, dataBarang[jumlahBarang].alamat.lantai);

                        cout << "Rak: ";
                        getline(cin, dataBarang[jumlahBarang].alamat.rak);

                        dataBarang[jumlahBarang].tersedia =
                            (dataBarang[jumlahBarang].jumlah > 0);

                        jumlahBarang++;

                        cout << "\nBarang berhasil ditambahkan!";
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.get();
                    }
                }
            }

            else if (menuUtama == 2) {

                Table inventoryTable;
                inventoryTable.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});

                if (jumlahBarang == 0) {
                    inventoryTable.add_row({"", "Belum ada data barang.", "", "", "", "", ""});
                }
                else {
                    for (int i = 0; i < jumlahBarang; i++) {

                        string lokasi =
                            dataBarang[i].alamat.gedung + "-" +
                            dataBarang[i].alamat.lantai + "-" +
                            dataBarang[i].alamat.rak;

                        string status =
                            dataBarang[i].tersedia ? "Tersedia" : "Habis";

                        inventoryTable.add_row({
                            dataBarang[i].kodeBarang,
                            dataBarang[i].namaBarang,
                            dataBarang[i].kategori,
                            to_string(dataBarang[i].jumlah),
                            to_string(dataBarang[i].harga),
                            lokasi,
                            status
                        });
                    }
                }

                cout << "\n=== DAFTAR INVENTARIS GUDANG ===" << endl;
                cout << inventoryTable << endl;
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
            }

            else if (menuUtama == 3) {

                if (jumlahBarang == 0) {
                    cout << "\nBelum ada data barang.";
                    cout << "\nTekan Enter untuk melanjutkan...";
                    cin.get();
                }
                else {

                    string kodeCari;

                    cout << "\nMasukkan kode barang: ";
                    cin >> kodeCari;
                    cin.ignore();

                    int posisiBarang = -1;

                    for (int i = 0; i < jumlahBarang; i++) {

                        if (dataBarang[i].kodeBarang == kodeCari) {
                            posisiBarang = i;
                            break;
                        }
                    }

                    if (posisiBarang != -1) {

                        cout << "\nNama Barang baru: ";
                        getline(cin, dataBarang[posisiBarang].namaBarang);

                        cout << "Kategori baru: ";
                        getline(cin, dataBarang[posisiBarang].kategori);

                        cout << "Jumlah baru: ";
                        cin >> dataBarang[posisiBarang].jumlah;

                        cout << "Harga baru: ";
                        cin >> dataBarang[posisiBarang].harga;

                        cin.ignore();

                        cout << "Gedung baru: ";
                        getline(cin, dataBarang[posisiBarang].alamat.gedung);

                        cout << "Lantai baru: ";
                        getline(cin, dataBarang[posisiBarang].alamat.lantai);

                        cout << "Rak baru: ";
                        getline(cin, dataBarang[posisiBarang].alamat.rak);

                        dataBarang[posisiBarang].tersedia =
                            (dataBarang[posisiBarang].jumlah > 0);

                        cout << "\nData berhasil diubah.";
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.get();
                    }
                    else {
                        cout << "\nBarang tidak ditemukan.";
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.get();
                    }
                }
            }

            else if (menuUtama == 4) {

                if (jumlahBarang == 0) {
                    cout << "\nBelum ada data barang.";
                    cout << "\nTekan Enter untuk melanjutkan...";
                    cin.get();
                }
                else {

                    string kodeHapus;

                    cout << "\nMasukkan kode barang: ";
                    cin >> kodeHapus;
                    cin.ignore();

                    int posisiBarang = -1;

                    for (int i = 0; i < jumlahBarang; i++) {

                        if (dataBarang[i].kodeBarang == kodeHapus) {
                            posisiBarang = i;
                            break;
                        }
                    }

                    if (posisiBarang != -1) {

                        string konfirmasi;
                        cout << "Yakin ingin menghapus? (y/n): ";
                        getline(cin, konfirmasi);

                        if (konfirmasi == "y" || konfirmasi == "Y") {
                            for (int i = posisiBarang; i < jumlahBarang - 1; i++) {
                                dataBarang[i] = dataBarang[i + 1];
                            }
                            jumlahBarang--;

                            cout << "\nBarang berhasil dihapus!";
                        } else {
                            cout << "\nPenghapusan dibatalkan.";
                        }
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.get();
                    }
                    else {
                        cout << "\nBarang tidak ditemukan.";
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.get();
                    }
                }
            }

            else if (menuUtama == 5) {

                cout << "\nLogout berhasil.";
                cout << "\nTekan Enter untuk keluar...";
                cin.get();
                sudahLogin = false;
            }

            else {
                cout << "\nPilihan tidak valid.";
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
            }
        }
    }

    return 0;
}