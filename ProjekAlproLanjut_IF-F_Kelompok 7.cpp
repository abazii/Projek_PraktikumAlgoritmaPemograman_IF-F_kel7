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

void tambahBuku(){
    buku bbaru;
    bool sudahAda;
    string tempId, tempJudul, tempPengarang, tempStock;

    do {
        sudahAda = false;
        cout << "=== Tambah Buku ===" << endl;
        cout << "Masukan ID Buku: ";
        cin >> bbaru.id;

        ifstream fileCek("buku.txt");
                
        if (fileCek.is_open()) {
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
}

void hapusBuku(){
    int idHapus;
    bool ditemukan = false;
    string tempId, tempJudul, tempPengarang, tempStock;

    cout << "=== Hapus Buku ===" << endl;
    cout << "Masukkan ID Buku yang ingin dihapus: ";
    cin >> idHapus;

    ifstream fileMasuk("buku.txt");
    ofstream fileTemp("temp.txt");
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
}

void tampilkanBuku(){

    buku data[100];
    int jumlah = 0;

    ifstream file("buku.txt");

    if (!file.is_open()) {
        cout << "File buku tidak ditemukan!" << endl;
        return;
    }

    string tempId, tempJudul, tempPengarang, tempStock;

    while (getline(file, tempId, '|') &&
           getline(file, tempJudul, '|') &&
           getline(file, tempPengarang, '|') &&
           getline(file, tempStock)) {

        data[jumlah].id = stoi(tempId);
        data[jumlah].judul = tempJudul;
        data[jumlah].pengarang = tempPengarang;
        data[jumlah].stock = stoi(tempStock);

        jumlah++;
    }

    file.close();

    for (int i = 0; i < jumlah - 1; i++) {

        for (int j = 0; j < jumlah - i - 1; j++) {

            if (data[j].id > data[j + 1].id) {

                buku temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    cout << endl;
    cout << "==================================================" << endl;
    cout << "              DAFTAR BUKU PERPUSTAKAAN           " << endl;
    cout << "==================================================" << endl;

    if (jumlah == 0) {
        cout << "Belum ada data buku!" << endl;
    }
    else {

        for (int i = 0; i < jumlah; i++) {

            cout << "ID Buku    : " << data[i].id << endl;
            cout << "Judul      : " << data[i].judul << endl;
            cout << "Pengarang  : " << data[i].pengarang << endl;
            cout << "Stok       : " << data[i].stock << endl;
            cout << "--------------------------------------------------" << endl;
        }
    }
}

void cariBuku(){

    buku data[100];
    int jumlah = 0;
    string tempId, tempJudul, tempPengarang, tempStock;

    ifstream file("buku.txt");

    if (!file.is_open()) {
        cout << "File buku tidak ditemukan!" << endl;
        return;
    }

    while (getline(file, tempId, '|') &&
           getline(file, tempJudul, '|') &&
           getline(file, tempPengarang, '|') &&
           getline(file, tempStock)) {

        data[jumlah].id = stoi(tempId);
        data[jumlah].judul = tempJudul;
        data[jumlah].pengarang = tempPengarang;
        data[jumlah].stock = stoi(tempStock);

        jumlah++;
    }

    file.close();

    cin.ignore();

    string cari;
    bool ditemukan = false;

    cout << "=== CARI BUKU ===" << endl;
    cout << "Masukkan judul buku: ";
    getline(cin, cari);

    cout << endl;

    for (int i = 0; i < jumlah; i++) {

        if (data[i].judul == cari) {

            ditemukan = true;

            cout << "Buku ditemukan!" << endl;
            cout << "-------------------------" << endl;
            cout << "ID Buku    : " << data[i].id << endl;
            cout << "Judul      : " << data[i].judul << endl;
            cout << "Pengarang  : " << data[i].pengarang << endl;
            cout << "Stok       : " << data[i].stock << endl;
            cout << "-------------------------" << endl;
        }
    }

    if (!ditemukan) {
        cout << "Buku tidak ditemukan!" << endl;
    }
}

void daftarPeminjam(){


}

void tampilkanMenuadmin() {
    int menu;
    do {
        cout << endl << "=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Hapus Buku" << endl;
        cout << "3. Edit Buku" << endl;
        cout << "4. Tampilkan Daftar Buku" << endl;
        cout << "5. Cari Buku" << endl;
        cout << "6. Daftar Peminjam" << endl;
        cout << "7. Keluar Menu Admin" << endl;
        cout << "Pilih Menu (1-7): "; cin >> menu;
        
        switch (menu) {
            case 1:
                tambahBuku();
                break;
            case 2:
                hapusBuku();
                break;
            case 3:
                cout << "Edit buku" << endl;
                break;
            case 4:
                tampilkanBuku();
                break;
            case 5:
                cariBuku();
                break;
            case 6:
                
                break;
            case 7:
                cout << "Anda telah keluar dari admin!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    } while(menu!=7); 
}

void tampilkanMenu() {
    cout << endl << "=== MENU UTAMA PERPUSTAKAAN ===" << endl;
    cout << "1. Tampilkan Daftar Buku" << endl;
    cout << "2. Cari Buku" << endl;
    cout << "3. Pinjam Buku" << endl;
    cout << "4. Kembalikan Buku" << endl;
    cout << "5. Login Admin" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu (1-6): ";
}

int main() {
    char konfirm;
    int pilihan;
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanBuku();
                break;
            case 2:
                cout << "Pastikan Anda sudah melihat fitur Tampilkan Buku pada menu 1!" << endl;
                cout << "Konfirmasi apakah sudah melihat fitur 1(y/n) ?"; cin >> konfirm;
                if (konfirm == 'y' || konfirm == 'Y'){
                    cariBuku();
                }
                break;
            case 3:
                cout << " Fitur Pinjam" << endl;
                break;
            case 4:
                cout << " FItur kembali" << endl;
                break;
            case 5:
                if (!login()) {
                    cout << "Login gagal! Username atau password salah." << endl;
                } else {
                    cout << endl << "Login sukses! Selamat datang di sistem." << endl;
                    tampilkanMenuadmin();
                };
                break;
            case 6:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    } while (pilihan != 6);
    
    return 0;
}
