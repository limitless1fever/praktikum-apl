#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <exception>
#include <string>
#include <iostream>
#include <limits>

class InventarisException : public std::exception {
protected: std::string pesan;
public:
    InventarisException(const std::string& msg) : pesan(msg) {}
    const char* what() const noexcept override { return pesan.c_str(); }
    virtual ~InventarisException() noexcept = default;
};

class LoginGagalException : public InventarisException {
public: LoginGagalException(int sisa) : InventarisException("Gagal login! Sisa percobaan: " + std::to_string(sisa)) {} };

class KapasitasPenuhException : public InventarisException {
public: KapasitasPenuhException() : InventarisException("Kapasitas gudang penuh!") {} };

class KodeDuplikatException : public InventarisException {
public: KodeDuplikatException() : InventarisException("Kode barang sudah digunakan!") {} };

class BarangTidakDitemukanException : public InventarisException {
public: BarangTidakDitemukanException() : InventarisException("Barang tidak ditemukan!") {} };

class InputInvalidException : public InventarisException {
public: InputInvalidException(const std::string& field) : InventarisException("Input tidak valid untuk " + field + "!") {} };

// Validasi string tidak boleh kosong
inline std::string inputStringValid(const std::string& prompt) {
    std::string val;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, val);
        if (!val.empty()) return val;
        std::cout << "Input tidak boleh kosong! Coba lagi." << std::endl;
    }
}

// Validasi input angka
inline int inputIntValid(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "Input harus berupa angka! Coba lagi." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Validasi pilihan menu (range min-max)
inline int inputMenuValid(const std::string& prompt, int min, int max) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        if (line.empty()) {
            std::cout << "Input tidak boleh kosong! Masukkan " << min << "-" << max << "." << std::endl;
            continue;
        }
        try {
            size_t pos;
            int val = std::stoi(line, &pos);
            if (pos != line.length()) {
                std::cout << "Hanya masukkan angka! Coba lagi." << std::endl;
                continue;
            }
            if (val >= min && val <= max) return val;
            std::cout << "Pilihan tidak tersedia! Masukkan " << min << "-" << max << "." << std::endl;
        } catch (...) {
            std::cout << "Input harus berupa angka! Coba lagi." << std::endl;
        }
    }
}

#endif