#include <iostream>
#include <fstream>
using namespace std;

bool login() {
    string username, password;
    cout << "===  LOGIN SISTEM PERPUSTAKAAN ===" << endl;
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    
    if (username == "admin" && password == "123") {
        return true;
    }
    return false;
}

void tampilkanMenuadmin() {
    int menu;
    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Cari Buku" << endl;
        cout << "2. Tampilkan Daftar Buku" << endl;
        cout << "3. Daftar Peminjam" << endl;
        cout << "4. Modifikasi Buku" << endl;
        cout << "5. Keluar menu admin" << endl;
        cout << "Pilih Menu (1-4): ";
            cin >> menu;
        
        switch (menu) {
            case 1:
                cout << "[Info] Fitur Tambah Buku akan dibuat di sini.\n";
                break;
            case 2:
                cout << "[Info] Fitur Tampilkan Buku akan dibuat di sini.\n";
                break;
            case 3:
                cout << "[Info] Fitur Pinjam Buku akan dibuat di sini.\n";
                break;
            case 4:
                cout << "[Info] Fitur Pinjam Buku akan dibuat di sini.\n";
            case 5:
                cout << "Keluar dari program ADMIN. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while(menu!=5); 
}

void tampilkanMenu() {
    cout << "\n=== MENU UTAMA PERPUSTAKAAN ===" << endl;
    cout << "1. cari buku" << endl;
    cout << "2. Tampilkan Daftar Buku" << endl;
    cout << "3. Pinjam Buku" << endl;
    cout << "4. login admin" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu (1-4): ";
}

int main() {
    
    int pilihan;
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                cout << "[Info] Fitur Tambah Buku akan dibuat di sini.\n";
                break;
            case 2:
                cout << "[Info] Fitur Tampilkan Buku akan dibuat di sini.\n";
                break;
            case 3:
                cout << "[Info] Fitur Pinjam Buku akan dibuat di sini.\n";
                break;
            case 4:
                if (!login()) {
                    cout << "Login gagal! Username atau password salah." << endl;
                } else {
                    cout << "\nLogin sukses! Selamat datang di sistem." << endl;
                    tampilkanMenuadmin();
                };
            case 5:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 5);
    
    return 0;
}
