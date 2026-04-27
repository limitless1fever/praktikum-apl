#include <iostream>
#include <string>
#include <limits>
#include <tabulate/table.hpp>
#include "ErrorHandling.h"

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

bool prosesLogin(int percobaan) {
    try {
        if (percobaan >= 3) {
            throw LoginGagalException(0);
        }

        string inputNama, inputPass;
        cout << "\n--- Login (Percobaan " << percobaan + 1 << "/3) ---";
        inputNama = inputStringValid("\nUsername: ");
        inputPass = inputStringValid("Password: ");

        if (inputNama == "Pirlo" && inputPass == "008") {
            cout << "\nLogin Berhasil! Selamat datang." << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore(); 
            cin.get();
            return true;
        } else {
            throw LoginGagalException(3 - (percobaan + 1));
        }
    }
    catch (const LoginGagalException& e) {
        cout << "\n" << e.what() << endl;
        if (percobaan >= 2) {
            cout << "\nGagal login 3 kali. Program berhenti.";
            return false;
        }
        cout << "Tekan Enter untuk mencoba lagi...";
        cin.ignore(); 
        cin.get();
        return prosesLogin(percobaan + 1);
    }
    catch (const exception& e) {
        cout << "\nTerjadi kesalahan sistem: " << e.what() << endl;
        return false;
    }
}

int cariIndex(ItemInventaris data[], int indexSaatIni, int jumlah, string kode) {
    if (indexSaatIni >= jumlah) return -1;
    if (data[indexSaatIni].kodeBarang == kode) return indexSaatIni;
    return cariIndex(data, indexSaatIni + 1, jumlah, kode);
}

void tambahBarang(ItemInventaris data[], int &jumlah, int maks) {
    try {
        cout << "\n==================================================";
        cout << "\n   TAMBAH BARANG";
        cout << "\n==================================================";

        if (jumlah >= maks) throw KapasitasPenuhException();

        data[jumlah].kodeBarang = inputStringValid("\nKode Barang: ");

        if (cariIndex(data, 0, jumlah, data[jumlah].kodeBarang) != -1) throw KodeDuplikatException();

        data[jumlah].namaBarang = inputStringValid("Nama Barang: ");
        data[jumlah].kategori = inputStringValid("Kategori: ");
        data[jumlah].jumlah = inputIntValid("Jumlah: ");
        data[jumlah].harga = inputIntValid("Harga: ");

        cout << "\n--- Lokasi Penyimpanan ---";
        data[jumlah].alamat.gedung = inputStringValid("\nGedung: ");
        data[jumlah].alamat.lantai = inputStringValid("Lantai: ");
        data[jumlah].alamat.rak = inputStringValid("Rak: ");

        data[jumlah].tersedia = (data[jumlah].jumlah > 0);
        jumlah++;

        cout << "\nBarang berhasil ditambahkan!";
    }
    catch (const InventarisException& e) { cout << "\n" << e.what(); }
    catch (const exception& e) { cout << "\nTerjadi kesalahan: " << e.what(); }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void lihatBarang(ItemInventaris data[], int jumlah) {
    cout << "\n==================================================";
    cout << "\n   DAFTAR INVENTARIS GUDANG";
    cout << "\n==================================================\n";
    if (jumlah == 0) { cout << "\nBelum ada data barang."; } 
    else {
        Table table;
        table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
        for (size_t i = 0; i < table[0].size(); ++i) table[0][i].format().font_align(FontAlign::center).font_style({FontStyle::bold});
        for (int i = 0; i < jumlah; i++) {
            string lokasi = data[i].alamat.gedung + "-" + data[i].alamat.lantai + "-" + data[i].alamat.rak;
            string status = data[i].tersedia ? "Tersedia" : "Habis";
            table.add_row({data[i].kodeBarang, data[i].namaBarang, data[i].kategori, to_string(data[i].jumlah), "Rp " + to_string(data[i].harga), lokasi, status});
        }
        cout << table << endl;
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void ubahBarang(ItemInventaris data[], int jumlah) {
    try {
        cout << "\n==================================================";
        cout << "\n   UBAH BARANG";
        cout << "\n==================================================";
        if (jumlah == 0) throw BarangTidakDitemukanException();

        string kodeCari = inputStringValid("\nMasukkan kode barang: ");
        int posisiBarang = cariIndex(data, 0, jumlah, kodeCari);
        if (posisiBarang == -1) throw BarangTidakDitemukanException();

        data[posisiBarang].namaBarang = inputStringValid("\nNama Barang baru: ");
        data[posisiBarang].kategori = inputStringValid("Kategori baru: ");
        data[posisiBarang].jumlah = inputIntValid("Jumlah baru: ");
        data[posisiBarang].harga = inputIntValid("Harga baru: ");
        
        data[posisiBarang].alamat.gedung = inputStringValid("Gedung baru: ");
        data[posisiBarang].alamat.lantai = inputStringValid("Lantai baru: ");
        data[posisiBarang].alamat.rak = inputStringValid("Rak baru: ");

        data[posisiBarang].tersedia = (data[posisiBarang].jumlah > 0);
        cout << "\nData berhasil diubah.";
    }
    catch (const InventarisException& e) { cout << "\n" << e.what(); }
    catch (const exception& e) { cout << "\nTerjadi kesalahan: " << e.what(); }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void hapusBarang(ItemInventaris* data, int* jumlah) {
    try {
        cout << "\n==================================================";
        cout << "\n   HAPUS BARANG";
        cout << "\n==================================================";
        if (*jumlah == 0) throw BarangTidakDitemukanException();

        string kodeHapus = inputStringValid("\nMasukkan kode barang: ");
        int posisiBarang = cariIndex(data, 0, *jumlah, kodeHapus);
        if (posisiBarang == -1) throw BarangTidakDitemukanException();

        string konfirmasi = inputStringValid("Yakin ingin menghapus? (y/n): ");
        if (konfirmasi == "y" || konfirmasi == "Y") {
            // Menggunakan pointer arithmetic untuk shifting array
            for (int i = posisiBarang; i < *jumlah - 1; i++) {
                data[i] = data[i + 1];
            }
            (*jumlah)--;
            cout << "\nBarang berhasil dihapus!";
        } else { cout << "\nPenghapusan dibatalkan."; }
    }
    catch (const InventarisException& e) { cout << "\n" << e.what(); }
    catch (const exception& e) { cout << "\nTerjadi kesalahan: " << e.what(); }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void bubbleSortNamaDescending(ItemInventaris data[], int jumlah) {
    if (jumlah <= 1) return;
    bool swapped;
    for (int i = 0; i < jumlah - 1; i++) {
        swapped = false;
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j].namaBarang < data[j + 1].namaBarang) {
                ItemInventaris temp = data[j]; data[j] = data[j + 1]; data[j + 1] = temp; swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSortHargaAscending(ItemInventaris data[], int jumlah) {
    if (jumlah <= 1) return;
    for (int i = 0; i < jumlah - 1; i++) {
        int indeksMin = i;
        for (int j = i + 1; j < jumlah; j++) if (data[j].harga < data[indeksMin].harga) indeksMin = j;
        if (indeksMin != i) { ItemInventaris temp = data[i]; data[i] = data[indeksMin]; data[indeksMin] = temp; }
    }
}

void insertionSortJumlahAscending(ItemInventaris data[], int jumlah) {
    if (jumlah <= 1) return;
    for (int i = 1; i < jumlah; i++) {
        ItemInventaris key = data[i]; int j = i - 1;
        while (j >= 0 && data[j].jumlah > key.jumlah) { data[j + 1] = data[j]; j = j - 1; }
        data[j + 1] = key;
    }
}

void tampilkanDataTerurut(ItemInventaris data[], int jumlah, string judul) {
    cout << "\n==================================================";
    cout << "\n   " << judul;
    cout << "\n==================================================\n";
    if (jumlah == 0) { cout << "\nBelum ada data barang."; } 
    else {
        Table table;
        table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
        for (size_t i = 0; i < table[0].size(); ++i) table[0][i].format().font_align(FontAlign::center).font_style({FontStyle::bold});
        for (int i = 0; i < jumlah; i++) {
            string lokasi = data[i].alamat.gedung + "-" + data[i].alamat.lantai + "-" + data[i].alamat.rak;
            table.add_row({data[i].kodeBarang, data[i].namaBarang, data[i].kategori, to_string(data[i].jumlah), "Rp " + to_string(data[i].harga), lokasi, data[i].tersedia ? "Tersedia" : "Habis"});
        }
        cout << table << endl;
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void menuSorting(ItemInventaris data[], int jumlah) {
    int pilihan;
    do {
        system("cls");
        cout << "\n==================================================";
        cout << "\n   MENU SORTING INVENTARIS";
        cout << "\n==================================================";
        if (jumlah == 0) {
            cout << "\nBelum ada data barang untuk diurutkan.";
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
            return;
        }
        cout << "\n1. Urutkan Nama Barang (Z ke A)";
        cout << "\n2. Urutkan Harga (Terkecil ke Terbesar)";
        cout << "\n3. Urutkan Jumlah Stok (Sedikit ke Banyak)";
        cout << "\n4. Kembali ke Menu Utama";

        pilihan = inputMenuValid("\n\nPilihan: ", 1, 4);

        ItemInventaris dataSalinan[100];
        for (int i = 0; i < jumlah; i++) dataSalinan[i] = data[i];

        try {
            if (pilihan == 1) bubbleSortNamaDescending(dataSalinan, jumlah);
            else if (pilihan == 2) selectionSortHargaAscending(dataSalinan, jumlah);
            else if (pilihan == 3) insertionSortJumlahAscending(dataSalinan, jumlah);
            else if (pilihan == 4) return;
            else throw InputInvalidException("Pilihan menu");

            string judul = (pilihan == 1) ? "HASIL SORTING: NAMA BARANG (DESCENDING)" : 
                        (pilihan == 2) ? "HASIL SORTING: HARGA (ASCENDING)" : "HASIL SORTING: JUMLAH STOK (ASCENDING)";
            tampilkanDataTerurut(dataSalinan, jumlah, judul);
        }
        catch (const exception& e) {
            cout << "\n" << e.what();
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        }
    } while (pilihan != 4);
}

int linearSearchNama(ItemInventaris* data, int jumlah, string target) {
    for (int i = 0; i < jumlah; i++) if ((*(data + i)).namaBarang == target) return i;
    return -1;
}

int binarySearchHarga(ItemInventaris* data, int jumlah, int target) {
    int low = 0, high = jumlah - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int val = (*(data + mid)).harga;
        if (val == target) return mid;
        else if (val < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void menuPencarian(ItemInventaris data[], int jumlah) {
    int pilihan;
    do {
        system("cls");
        cout << "\n==================================================";
        cout << "\n   MENU PENCARIAN (SEARCHING)";
        cout << "\n==================================================";
        cout << "\n1. Cari berdasarkan Nama Barang";
        cout << "\n2. Cari berdasarkan Harga";
        cout << "\n3. Kembali ke Menu Utama";

        pilihan = inputMenuValid("\n\nPilihan: ", 1, 3);

        try {
            if (pilihan == 1) {
                string namaCari = inputStringValid("\nMasukkan Nama Barang: ");
                int idx = linearSearchNama(data, jumlah, namaCari);
                if (idx != -1) {
                    cout << "\nBarang ditemukan!" << endl;
                    Table table; table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
                    string lokasi = data[idx].alamat.gedung + "-" + data[idx].alamat.lantai + "-" + data[idx].alamat.rak;
                    table.add_row({data[idx].kodeBarang, data[idx].namaBarang, data[idx].kategori, to_string(data[idx].jumlah), "Rp " + to_string(data[idx].harga), lokasi, data[idx].tersedia ? "Tersedia" : "Habis"});
                    cout << table << endl;
                } else throw BarangTidakDitemukanException();
            }
            else if (pilihan == 2) {
                int hargaCari = inputIntValid("\nMasukkan Harga Barang (Rp): ");
                ItemInventaris dataTemp[100];
                for (int i = 0; i < jumlah; i++) dataTemp[i] = data[i];
                selectionSortHargaAscending(dataTemp, jumlah);
                int idx = binarySearchHarga(dataTemp, jumlah, hargaCari);
                if (idx != -1) {
                    cout << "\nBarang ditemukan dengan harga Rp " << dataTemp[idx].harga << "!" << endl;
                    Table table; table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
                    string lokasi = dataTemp[idx].alamat.gedung + "-" + dataTemp[idx].alamat.lantai + "-" + dataTemp[idx].alamat.rak;
                    table.add_row({dataTemp[idx].kodeBarang, dataTemp[idx].namaBarang, dataTemp[idx].kategori, to_string(dataTemp[idx].jumlah), "Rp " + to_string(dataTemp[idx].harga), lokasi, dataTemp[idx].tersedia ? "Tersedia" : "Habis"});
                    cout << table << endl;
                } else throw BarangTidakDitemukanException();
            }
            else if (pilihan == 3) return;
            else throw InputInvalidException("Pilihan menu");

            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        }
        catch (const exception& e) {
            cout << "\n" << e.what();
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        }
    } while (pilihan != 3);
}

void tampilkanMenuUtama() {
    cout << "\n1. Tambah Barang";
    cout << "\n2. Lihat Barang";
    cout << "\n3. Ubah Barang";
    cout << "\n4. Hapus Barang";
    cout << "\n5. Sorting Barang";
    cout << "\n6. Cari Barang";
    cout << "\n7. Logout";
}

int main() {
    const int MAKS_BARANG = 100;
    ItemInventaris dataBarang[MAKS_BARANG];
    int jumlahBarang = 0;

    dataBarang[0] = {"EL001", "Laptop Asus", "Komputer", 10, 5000000, {"Gudang A", "1", "01"}, true};
    dataBarang[1] = {"EL002", "Mouse Logitech", "Aksesoris", 50, 150000, {"Gudang A", "1", "02"}, true};
    dataBarang[2] = {"EL003", "Monitor LG", "Komputer", 0, 2000000, {"Gudang B", "2", "05"}, false};
    jumlahBarang = 3;

    bool programAktif = true;

    while (programAktif) {
        bool sudahLogin = false;
        while (!sudahLogin && programAktif) {
            system("cls");
            cout << "\n==================================================";
            cout << "\n   SISTEM MANAJEMEN INVENTARIS GUDANG ELEKTRONIK";
            cout << "\n==================================================";
            cout << "\n1. Login";
            cout << "\n2. Keluar Program";
            
            int menuAwal = inputMenuValid("\n\nPilihan: ", 1, 2);

            if (menuAwal == 1) {
                sudahLogin = prosesLogin(0);
            } else {
                cout << "\nTerima kasih telah menggunakan program ini.";
                programAktif = false;
            }
        }

        while (sudahLogin) {
            system("cls");
            cout << "\n==================================================";
            cout << "\n   MENU UTAMA INVENTARIS GUDANG ELEKTRONIK";
            cout << "\n==================================================";
            tampilkanMenuUtama();

            int menuUtama = inputMenuValid("\n\nPilihan: ", 1, 7);

            if (menuUtama == 1) tambahBarang(dataBarang, jumlahBarang, MAKS_BARANG);
            else if (menuUtama == 2) lihatBarang(dataBarang, jumlahBarang);
            else if (menuUtama == 3) ubahBarang(dataBarang, jumlahBarang);
            else if (menuUtama == 4) hapusBarang(dataBarang, &jumlahBarang);
            else if (menuUtama == 5) menuSorting(dataBarang, jumlahBarang);
            else if (menuUtama == 6) menuPencarian(dataBarang, jumlahBarang);
            else if (menuUtama == 7) {
                cout << "\nLogout berhasil.";
                cout << "\nTekan Enter untuk keluar...";
                cin.ignore(); cin.get();
                sudahLogin = false;
            }
        }
    }
    return 0;
}