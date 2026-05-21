#include <iostream>
#include <fstream>
using namespace std;

struct buku
{
    string judul, pengarang;
    int stock, id;
};

int jumlahid=0;

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

void admin4(){
    int pilih;
    do{
      
        cout << endl << "=== MENU MODIFIKASI BUKU ===" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Hapus Buku" << endl;
        cout << "3. kembali" << endl;
        cin >> pilih;
        switch (pilih) {
        case 1:
        {
            buku bbaru;
            bool sudahAda;

            do {
                sudahAda = false;
                cout << "=== Tambah Buku ===" << endl;
                cout << "Masukan ID Buku: ";
                cin >> bbaru.id;

                ifstream fileCek("buku.txt");
                
                if (fileCek.is_open()) {
                    string tempId, tempJudul, tempPengarang, tempStock;
    
                    while (getline(fileCek, tempId, '|') && 
                           getline(fileCek, tempJudul, '|') && 
                           getline(fileCek, tempPengarang, '|') && 
                           getline(fileCek, tempStock)) {
                        
                        if (stoi(tempId) == bbaru.id) {
                            sudahAda = true;
                            break;
                        }
                    }
                    fileCek.close();
                }

                if (sudahAda) {
                    cout << "[Peringatan] ID Buku " << bbaru.id << " sudah ada! Silakan gunakan ID lain." << endl;
                }
            }while(sudahAda);
            cin.ignore();
            cout << "Masukan Judul buku     : ";
            getline(cin, bbaru.judul);
            cout << "Masukan Pengarang buku : ";
            getline(cin, bbaru.pengarang);
            cout << "Jumlah buku            : ";
            cin >> bbaru.stock;

            ofstream filebaru("buku.txt", ios::app);
            filebaru << bbaru.id << "|" << bbaru.judul << "|" << bbaru.pengarang << "|" << bbaru.stock << endl;
            filebaru.close(); 
            jumlahid++;
            cout << "[Info] Buku berhasil ditambahkan!" << endl;
            break;
        }
       case 2:
        {
            int idHapus;
            bool ditemukan = false;

            cout << "=== Hapus Buku ===" << endl;
            cout << "Masukkan ID Buku yang ingin dihapus: ";
            cin >> idHapus;

            ifstream fileMasuk("buku.txt");
            ofstream fileTemp("temp.txt");

            string tempId, tempJudul, tempPengarang, tempStock;

            while (getline(fileMasuk, tempId, '|') &&
                getline(fileMasuk, tempJudul, '|') &&
                getline(fileMasuk, tempPengarang, '|') &&
                getline(fileMasuk, tempStock)) {

                if (stoi(tempId) == idHapus) {
                    ditemukan = true;
                    cout << "[Info] Buku dengan ID " << idHapus << " berhasil dihapus." << endl;
                } else {
                    fileTemp << tempId << "|"
                            << tempJudul << "|"
                            << tempPengarang << "|"
                            << tempStock << endl;
                }
            }

            fileMasuk.close();
            fileTemp.close();

            remove("buku.txt");
            rename("temp.txt", "buku.txt");

            if (!ditemukan) {
                cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
            }

            break;
        }
        default:
            break;
        }
    }while(pilih!=3);
}


void tampilkanMenuadmin() {
    int menu;
    do {
        cout << endl << "=== MENU ADMIN ===" << endl;
        cout << "1. Cari Buku" << endl;
        cout << "2. Tampilkan Daftar Buku" << endl;
        cout << "3. Daftar Peminjam" << endl;
        cout << "4. Modifikasi Buku" << endl;
        cout << "5. Keluar menu admin" << endl;
        cout << "Pilih Menu (1-4): ";
            cin >> menu;
        
        switch (menu) {
            case 1:
                cout << "[Info] Fitur Tambah Buku akan dibuat di sini." << endl;
                break;
            case 2:
                cout << "[Info] Fitur Tampilkan Buku akan dibuat di sini." << endl;
                break;
            case 3:
                cout << "[Info] Fitur Pinjam Buku akan dibuat di sini." << endl;
                break;
            case 4:
                admin4();
                break;
            case 5:
                cout << "Keluar dari program ADMIN!!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    } while(menu!=5); 
}

void tampilkanMenu() {
    cout << endl << "=== MENU UTAMA PERPUSTAKAAN ===" << endl;
    cout << "1. cari buku" << endl;
    cout << "2. Tampilkan Daftar Buku" << endl;
    cout << "3. Pinjam Buku" << endl;
    cout << "4. login admin" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu (1-4): ";
}

void caribuku(){

}

int main() {
    
    int pilihan;
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                cout << "[Info] Fitur Tambah Buku akan dibuat di sini." << endl;
                break;
            case 2:
                cout << "[Info] Fitur Tampilkan Buku akan dibuat di sini." << endl;
                break;
            case 3:
                cout << "[Info] Fitur Pinjam Buku akan dibuat di sini." << endl;
                break;
            case 4:
                if (!login()) {
                    cout << "Login gagal! Username atau password salah." << endl;
                } else {
                    cout << endl << "Login sukses! Selamat datang di sistem." << endl;
                    tampilkanMenuadmin();
                };
                break;
            case 5:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    } while (pilihan != 5);
    
    return 0;
}
