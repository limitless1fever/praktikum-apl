#include<iostream>
using namespace std;

int main(){
    string nama;
    string password;
    string nama_benar = "Pirlo";
    string password_benar = "008";
    int percobaan = 0;
    bool login = false;

    while(percobaan < 3){
        cout<<"Masukkan Nama : ";
        cin>> nama;
        cout<<"Masukkan Password : ";
        cin>> password;

        if(nama == nama_benar && password == password_benar){
            login = true;
            break;
        } else {
            percobaan = percobaan + 1;
            cout<<"Login Gagal Nama atau Password Salah."<< endl;
        }
    }

    if(login == false){
        cout<<"Login Gagal 3 Kali Program Berhenti."<< endl;
        return 0;
    }

    cout<<"Login Berhasil."<< endl;
    cout<<endl;

    int pilihan;
    int nilai_waktu;
    int jam, menit, detik;

    do {
        cout<<"========================================"<<endl;
        cout<<"           MENU KONVERSI WAKTU          "<<endl;
        cout<<"========================================"<<endl;
        cout<<"1. Konversi Jam -> Menit dan Detik"<<endl;
        cout<<"2. Konversi Menit -> Jam dan Detik"<<endl;
        cout<<"3. Konversi Detik -> Jam dan Menit"<<endl;
        cout<<"4. Keluar"<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<"Pilih menu (1-4): ";
        cin>> pilihan;
        cout<<endl;

        if(pilihan == 1){
            cout<<"Masukkan nilai Jam: ";
            cin>> nilai_waktu;
            menit = nilai_waktu * 60;
            detik = nilai_waktu * 3600;
            cout<<endl;
            cout<<"========================================"<<endl;
            cout<<"  "<< nilai_waktu <<" Jam               "<<endl;
            cout<<"  = "<< menit <<" menit                 "<<endl;
            cout<<"  = "<< detik <<" detik                 "<<endl;
            cout<<"========================================"<<endl;
        } 
        else if(pilihan == 2){
            cout<<"Masukkan nilai Menit: ";
            cin>> nilai_waktu;
            jam = nilai_waktu / 60;
            detik = nilai_waktu * 60;
            cout<<endl;
            cout<<"========================================"<<endl;
            cout<<"  "<< nilai_waktu <<" Menit             "<<endl;
            cout<<"  = "<< jam <<" jam                     "<<endl;
            cout<<"  = "<< detik <<" detik                 "<<endl;
            cout<<"========================================"<<endl;
        } 
        else if(pilihan == 3){
            cout<<"Masukkan nilai Detik: ";
            cin>> nilai_waktu;
            jam = nilai_waktu / 3600;
            menit = nilai_waktu / 60;
            cout<<endl;
            cout<<"========================================"<<endl;
            cout<<"  "<< nilai_waktu <<" Detik             "<<endl;
            cout<<"  = "<< jam <<" jam                     "<<endl;
            cout<<"  = "<< menit <<" menit                 "<<endl;
            cout<<"========================================"<<endl;
        } 
        else if(pilihan == 4){
            cout<<"Keluar dari program."<< endl;
        } 
        else {
            cout<<"Pilihan tidak valid."<< endl;
        }

        cout<<endl;
    } while(pilihan != 4);

    return 0;
}