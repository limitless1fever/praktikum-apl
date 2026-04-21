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

bool prosesLogin(int percobaan) { // Fungsi Rekursif
    if (percobaan >= 3) {
        cout << "\nGagal login 3 kali. Program berhenti.";
        return false;
    }

    string inputNama, inputPass;
    cout << "\n--- Login (Percobaan " << percobaan + 1 << "/3) ---";
    cout << "\nUsername: ";
    cin >> inputNama;
    cout << "Password: ";
    cin >> inputPass;

    if (inputNama == "Pirlo" && inputPass == "008") {
        cout << "\nLogin Berhasil! Selamat datang." << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(); 
        cin.get();
        return true;
    } else {
        cout << "Username atau Password salah!" << endl;
        cout << "Tekan Enter untuk mencoba lagi...";
        cin.ignore(); 
        cin.get();
        return prosesLogin(percobaan + 1);
    }
}

int cariIndex(ItemInventaris data[], int indexSaatIni, int jumlah, string kode) { // Fungsi Rekursif
    if (indexSaatIni >= jumlah) {
        return -1;
    }
    if (data[indexSaatIni].kodeBarang == kode) {
        return indexSaatIni;
    }
    return cariIndex(data, indexSaatIni + 1, jumlah, kode);
}

void tambahBarang(ItemInventaris data[], int &jumlah, int maks) { // Prosedur
    cout << "\n==================================================";
    cout << "\n   TAMBAH BARANG";
    cout << "\n==================================================";

    if (jumlah >= maks) {
        cout << "\nKapasitas gudang penuh!";
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    cout << "\nKode Barang: ";
    cin >> data[jumlah].kodeBarang;

    if (cariIndex(data, 0, jumlah, data[jumlah].kodeBarang) != -1) {
        cout << "Kode barang sudah digunakan!";
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore(); 
        cin.get();
        return;
    }

    cin.ignore();
    cout << "Nama Barang: ";
    getline(cin, data[jumlah].namaBarang);
    cout << "Kategori: ";
    getline(cin, data[jumlah].kategori);
    cout << "Jumlah: ";
    cin >> data[jumlah].jumlah;
    cout << "Harga: ";
    cin >> data[jumlah].harga;
    cin.ignore();

    cout << "\n--- Lokasi Penyimpanan ---";
    cout << "\nGedung: ";
    getline(cin, data[jumlah].alamat.gedung);
    cout << "Lantai: ";
    getline(cin, data[jumlah].alamat.lantai);
    cout << "Rak: ";
    getline(cin, data[jumlah].alamat.rak);

    data[jumlah].tersedia = (data[jumlah].jumlah > 0);
    jumlah++;

    cout << "\nBarang berhasil ditambahkan!";
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void lihatBarang(ItemInventaris data[], int jumlah) { // Prosedur
    cout << "\n==================================================";
    cout << "\n   DAFTAR INVENTARIS GUDANG";
    cout << "\n==================================================";
    cout << "\n";

    if (jumlah == 0) {
        cout << "\nBelum ada data barang.";
    } else {
        Table table;
        
        table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
        
        for (size_t i = 0; i < table[0].size(); ++i) {
            table[0][i].format()
                .font_align(FontAlign::center)
                .font_style({FontStyle::bold}); 
        }

        for (int i = 0; i < jumlah; i++) {
            string lokasi = data[i].alamat.gedung + "-" +
                            data[i].alamat.lantai + "-" +
                            data[i].alamat.rak;
            string status = data[i].tersedia ? "Tersedia" : "Habis";
            
            table.add_row({
                data[i].kodeBarang,
                data[i].namaBarang,
                data[i].kategori,
                to_string(data[i].jumlah),
                "Rp " + to_string(data[i].harga),
                lokasi,
                status
            });
        }

        cout << table << endl;
    }

    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void ubahBarang(ItemInventaris data[], int jumlah) { // Prosedur
    cout << "\n==================================================";
    cout << "\n   UBAH BARANG";
    cout << "\n==================================================";

    if (jumlah == 0) {
        cout << "\nBelum ada data barang.";
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    string kodeCari;
    cout << "\nMasukkan kode barang: ";
    cin >> kodeCari;
    cin.ignore();

    int posisiBarang = cariIndex(data, 0, jumlah, kodeCari);

    if (posisiBarang != -1) {
        cout << "\nNama Barang baru: ";
        getline(cin, data[posisiBarang].namaBarang);
        cout << "Kategori baru: ";
        getline(cin, data[posisiBarang].kategori);
        cout << "Jumlah baru: ";
        cin >> data[posisiBarang].jumlah;
        cout << "Harga baru: ";
        cin >> data[posisiBarang].harga;
        cin.ignore();
        cout << "Gedung baru: ";
        getline(cin, data[posisiBarang].alamat.gedung);
        cout << "Lantai baru: ";
        getline(cin, data[posisiBarang].alamat.lantai);
        cout << "Rak baru: ";
        getline(cin, data[posisiBarang].alamat.rak);

        data[posisiBarang].tersedia = (data[posisiBarang].jumlah > 0);

        cout << "\nData berhasil diubah.";
    } else {
        cout << "\nBarang tidak ditemukan.";
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void hapusBarang(ItemInventaris* data, int* jumlah) { // Prosedur menggunakan * = Dereference Operator
    cout << "\n==================================================";
    cout << "\n   HAPUS BARANG";
    cout << "\n==================================================";

    if (*jumlah == 0) {  // * = Dereference Operator
        cout << "\nBelum ada data barang.";
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    string kodeHapus;
    cout << "\nMasukkan kode barang: ";
    cin >> kodeHapus;
    cin.ignore();

    int posisiBarang = cariIndex(data, 0, *jumlah, kodeHapus);

    if (posisiBarang != -1) {
        string konfirmasi;
        cout << "Yakin ingin menghapus? (y/n): ";
        getline(cin, konfirmasi);

        if (konfirmasi == "y" || konfirmasi == "Y") {
            for (int i = posisiBarang; i < *jumlah - 1; i++) {
                data[i] = data[i + 1];
            }
            (*jumlah)--;  // * = Dereference Operator
            cout << "\nBarang berhasil dihapus!";
        } else {
            cout << "\nPenghapusan dibatalkan.";
        }
    } else {
        cout << "\nBarang tidak ditemukan.";
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void bubbleSortNamaDescending(ItemInventaris data[], int jumlah) { // Fungsi Rekursif Iteratif
    if (jumlah <= 1) return;
    
    bool swapped;
    for (int i = 0; i < jumlah - 1; i++) {
        swapped = false;
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j].namaBarang < data[j + 1].namaBarang) {
                ItemInventaris temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSortHargaAscending(ItemInventaris data[], int jumlah) { // Prosedur
    if (jumlah <= 1) return;
    
    for (int i = 0; i < jumlah - 1; i++) {
        int indeksMin = i;
        for (int j = i + 1; j < jumlah; j++) {
            if (data[j].harga < data[indeksMin].harga) {
                indeksMin = j;
            }
        }
        if (indeksMin != i) {
            ItemInventaris temp = data[i];
            data[i] = data[indeksMin];
            data[indeksMin] = temp;
        }
    }
}

void insertionSortJumlahAscending(ItemInventaris data[], int jumlah) { // Prosedur
    if (jumlah <= 1) return;
    
    for (int i = 1; i < jumlah; i++) {
        ItemInventaris key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j].jumlah > key.jumlah) {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

void tampilkanDataTerurut(ItemInventaris data[], int jumlah, string judul) { // Prosedur
    cout << "\n==================================================";
    cout << "\n   " << judul;
    cout << "\n==================================================";
    cout << "\n";

    if (jumlah == 0) {
        cout << "\nBelum ada data barang.";
    } else {
        Table table;
        
        table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
        
        for (size_t i = 0; i < table[0].size(); ++i) {
            table[0][i].format()
                .font_align(FontAlign::center)
                .font_style({FontStyle::bold}); 
        }

        for (int i = 0; i < jumlah; i++) {
            string lokasi = data[i].alamat.gedung + "-" +
                            data[i].alamat.lantai + "-" +
                            data[i].alamat.rak;
            string status = data[i].tersedia ? "Tersedia" : "Habis";
            
            table.add_row({
                data[i].kodeBarang,
                data[i].namaBarang,
                data[i].kategori,
                to_string(data[i].jumlah),
                "Rp " + to_string(data[i].harga),
                lokasi,
                status
            });
        }

        cout << table << endl;
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void menuSorting(ItemInventaris data[], int jumlah) { // Prosedur
    int pilihan;
    do {
        system("cls");
        cout << "\n==================================================";
        cout << "\n   MENU SORTING INVENTARIS";
        cout << "\n==================================================";

        if (jumlah == 0) {
            cout << "\nBelum ada data barang untuk diurutkan.";
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return;
        }

        cout << "\n1. Urutkan Nama Barang (Z ke A)";
        cout << "\n2. Urutkan Harga (Terkecil ke Terbesar)";
        cout << "\n3. Urutkan Jumlah Stok (Sedikit ke Banyak)";
        cout << "\n4. Kembali ke Menu Utama";
        cout << "\n\nPilihan: ";
        
        int pilihan;
        cin >> pilihan;
        cin.ignore();

        ItemInventaris dataSalinan[100];
        for (int i = 0; i < jumlah; i++) {
            dataSalinan[i] = data[i];
        }

        if (pilihan == 1) {
            bubbleSortNamaDescending(dataSalinan, jumlah);
            tampilkanDataTerurut(dataSalinan, jumlah, "HASIL SORTING: NAMA BARANG (DESCENDING)");
        } else if (pilihan == 2) {
            selectionSortHargaAscending(dataSalinan, jumlah);
            tampilkanDataTerurut(dataSalinan, jumlah, "HASIL SORTING: HARGA (ASCENDING)");
        } else if (pilihan == 3) {
            insertionSortJumlahAscending(dataSalinan, jumlah);
            tampilkanDataTerurut(dataSalinan, jumlah, "HASIL SORTING: JUMLAH STOK (ASCENDING)");
        } else if (pilihan == 4) {
            return;
        } else {
            cout << "\nPilihan tidak valid.";
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
    }while (pilihan != 4);
}

//Searching
int linearSearchNama(ItemInventaris* data, int jumlah, string target) { // Linear Search untuk kata/huruf (namaBarang)
    for (int i = 0; i < jumlah; i++) {
        if ((*(data + i)).namaBarang == target) {
            return i;
        }
    }
    return -1;
}

int binarySearchHarga(ItemInventaris* data, int jumlah, int target) { // Binary Search untuk angka (harga)
    int low = 0, high = jumlah - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int val = (*(data + mid)).harga;
        if (val == target) {
            return mid;
        } else if (val < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void menuPencarian(ItemInventaris data[], int jumlah) { // Prosedur untuk menu searching
    int pilihan;
    do {
        system("cls");
        cout << "\n==================================================";
        cout << "\n   MENU PENCARIAN (SEARCHING)";
        cout << "\n==================================================";
        cout << "\n1. Cari berdasarkan Nama Barang (Linear Search)";
        cout << "\n2. Cari berdasarkan Harga (Binary Search)";
        cout << "\n3. Kembali ke Menu Utama";
        cout << "\n\nPilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string namaCari;
            cout << "\nMasukkan Nama Barang: ";
            getline(cin, namaCari);
            int idx = linearSearchNama(data, jumlah, namaCari);
            if (idx != -1) {
                cout << "\nBarang ditemukan!" << endl;
                Table table;
                table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
                string lokasi = data[idx].alamat.gedung + "-" + data[idx].alamat.lantai + "-" + data[idx].alamat.rak;
                string status = data[idx].tersedia ? "Tersedia" : "Habis";
                table.add_row({
                    data[idx].kodeBarang,
                    data[idx].namaBarang,
                    data[idx].kategori,
                    to_string(data[idx].jumlah),
                    "Rp " + to_string(data[idx].harga),
                    lokasi,
                    status
                });
                cout << table << endl;
            } else {
                cout << "\nNama barang tidak ditemukan dalam database.";
            }
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
        else if (pilihan == 2) {
            int hargaCari;
            cout << "\nMasukkan Harga Barang (Rp): ";
            cin >> hargaCari;
            cin.ignore();
            
            ItemInventaris dataTemp[100];
            for (int i = 0; i < jumlah; i++) {
                dataTemp[i] = data[i];
            }
            selectionSortHargaAscending(dataTemp, jumlah);
            
            int idx = binarySearchHarga(dataTemp, jumlah, hargaCari);
            if (idx != -1) {
                cout << "\nBarang ditemukan dengan harga Rp " << dataTemp[idx].harga << "!" << endl;
                Table table;
                table.add_row({"Kode", "Nama Barang", "Kategori", "Jumlah", "Harga", "Lokasi", "Status"});
                string lokasi = dataTemp[idx].alamat.gedung + "-" + dataTemp[idx].alamat.lantai + "-" + dataTemp[idx].alamat.rak;
                string status = dataTemp[idx].tersedia ? "Tersedia" : "Habis";
                table.add_row({
                    dataTemp[idx].kodeBarang,
                    dataTemp[idx].namaBarang,
                    dataTemp[idx].kategori,
                    to_string(dataTemp[idx].jumlah),
                    "Rp " + to_string(dataTemp[idx].harga),
                    lokasi,
                    status
                });
                cout << table << endl;
            } else {
                cout << "\nHarga tidak ditemukan dalam database.";
            }
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
    } while (pilihan != 3);
}

void tampilkanMenuUtama() { // Prosedur
    cout << "\n1. Tambah Barang";
    cout << "\n2. Lihat Barang";
    cout << "\n3. Ubah Barang";
    cout << "\n4. Hapus Barang";
    cout << "\n5. Sorting Barang";
    cout << "\n6. Cari Barang";
    cout << "\n7. Logout";
    cout << "\n\nPilihan: ";
}

int main() { // Fungsi Utama
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
        int menuAwal;

        while (!sudahLogin && programAktif) {
            system("cls");
            cout << "\n==================================================";
            cout << "\n   SISTEM MANAJEMEN INVENTARIS GUDANG ELEKTRONIK";
            cout << "\n==================================================";
            cout << "\n1. Login";
            cout << "\n2. Keluar Program";
            cout << "\n\nPilihan: ";
            cin >> menuAwal;
            cin.ignore();

            if (menuAwal == 1) {
                sudahLogin = prosesLogin(0);
            } else if (menuAwal == 2) {
                cout << "\nTerima kasih telah menggunakan program ini.";
                programAktif = false;
            } else {
                cout << "\nPilihan tidak valid!";
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
            }
        }

        while (sudahLogin) {
            system("cls");
            cout << "\n==================================================";
            cout << "\n   MENU UTAMA INVENTARIS GUDANG ELEKTRONIK";
            cout << "\n==================================================";
            tampilkanMenuUtama();

            int menuUtama;
            cin >> menuUtama;
            cin.ignore();

            if (menuUtama == 1) {
                tambahBarang(dataBarang, jumlahBarang, MAKS_BARANG);
            } else if (menuUtama == 2) {
                lihatBarang(dataBarang, jumlahBarang);
            } else if (menuUtama == 3) {
                ubahBarang(dataBarang, jumlahBarang);
            } else if (menuUtama == 4) {
                hapusBarang(dataBarang, &jumlahBarang);  // memanggil denggan & = Address-of Operator
            } else if (menuUtama == 5) {
                menuSorting(dataBarang, jumlahBarang);
            } else if (menuUtama == 6) {
                menuPencarian(dataBarang, jumlahBarang);
            } else if (menuUtama == 7) {
                cout << "\nLogout berhasil.";
                cout << "\nTekan Enter untuk keluar...";
                cin.get();
                sudahLogin = false;
            } else {
                cout << "\nPilihan tidak valid.";
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
            }
        }
    }

    return 0;
}