#include <iostream>
#include <fstream>
using namespace std;

struct buku
{
    string judul, pengarang;
    int stock, id;
};

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

int cariBukuRekursif(buku data[], int awal, int akhir, int idCari) {
    if (awal > akhir) {
        return -1;
    }
    
    int tengah = awal + (akhir - awal) / 2;
    
    if (data[tengah].id == idCari) {
        return tengah;
    }
    if (data[tengah].id > idCari) {
        return cariBukuRekursif(data, awal, tengah - 1, idCari);
    }
    return cariBukuRekursif(data, tengah + 1, akhir, idCari);
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

void editBuku() {
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

    int idCari;
    cout << "=== Edit Buku ===" << endl;
    cout << "masukkan id buku : ";
    cin >> idCari;
    
    int indeks = cariBukuRekursif(data, 0, jumlah - 1, idCari);

    if (indeks == -1) {
        cout << "[Peringatan] ID Buku tidak ditemukan!" << endl;
        return;
    }

    cout << endl << endl;
    cout << "Masukkan id baru : "; cin >> data[indeks].id;
    cin.ignore();
    cout << "Nama buku baru   : "; getline(cin, data[indeks].judul);
    cout << "Pengarang baru   : "; getline(cin, data[indeks].pengarang);
    cout << "Stok baru        : "; cin >> data[indeks].stock;

    ofstream fileTulis("buku.txt");
    for (int i = 0; i < jumlah; i++) {
        fileTulis << data[i].id << "|" << data[i].judul << "|" << data[i].pengarang << "|" << data[i].stock << endl;
    }
    fileTulis.close();
    cout << "[Info] Buku berhasil diperbarui!" << endl;
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
    ifstream file("peminjam.txt");
    if (!file.is_open()) {
        cout << "Belum ada data peminjaman!" << endl;
        return;
    }

    string tempNama, tempIdBuku, tempJudul;
    cout << endl;
    cout << "==================================================" << endl;
    cout << "              DAFTAR PEMINJAM BUKU               " << endl;
    cout << "==================================================" << endl;

    bool adaData = false;
    while (getline(file, tempNama, '|') &&
           getline(file, tempIdBuku, '|') &&
           getline(file, tempJudul)) {
        adaData = true;
        cout << "Nama Peminjam : " << tempNama << endl;
        cout << "ID Buku       : " << tempIdBuku << endl;
        cout << "Judul Buku    : " << tempJudul << endl;
        cout << "--------------------------------------------------" << endl;
    }
    file.close();

    if (!adaData) {
        cout << "Belum ada data peminjaman!" << endl;
    }
}

void pinjamBuku() {
    buku data[100];
    int jumlah = 0;
    ifstream file("buku.txt");
    
    if (!file.is_open()) {
        cout << "File data buku tidak ditemukan!" << endl;
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

    int idCari;
    string namaPeminjam;
    cout << "=== PINJAM BUKU ===" << endl;
    cout << "Masukkan ID Buku yang ingin dipinjam: "; cin >> idCari;

    int indeks = cariBukuRekursif(data, 0, jumlah - 1, idCari);

    if (indeks == -1) {
        cout << "[Peringatan] Buku dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }

    if (data[indeks].stock <= 0) {
        cout << "[Peringatan] Stok buku habis, tidak bisa dipinjam!" << endl;
        return;
    }

    cin.ignore();
    cout << "Masukkan Nama Anda: "; getline(cin, namaPeminjam);

    data[indeks].stock--;

    ofstream fileTulis("buku.txt");
    for (int i = 0; i < jumlah; i++) {
        fileTulis << data[i].id << "|" << data[i].judul << "|" << data[i].pengarang << "|" << data[i].stock << endl;
    }
    fileTulis.close();

    ofstream filePinjam("peminjam.txt", ios::app);
    filePinjam << namaPeminjam << "|" << data[indeks].id << "|" << data[indeks].judul << endl;
    filePinjam.close();

    cout << "[Sukses] Buku berhasil dipinjam oleh " << namaPeminjam << "!" << endl;
}

void kembalikanBuku() {
    string namaCari;
    int idCari;
    cout << "=== KEMBALIKAN BUKU ===" << endl;
    cin.ignore();
    cout << "Masukkan Nama Anda: "; getline(cin, namaCari);
    cout << "Masukkan ID Buku yang dikembalikan: "; cin >> idCari;

    ifstream filePinjam("peminjam.txt");
    ofstream fileTemp("temp_pinjam.txt");
    string tempNama, tempIdBuku, tempJudul;
    bool ditemukan = false;

    if (filePinjam.is_open()) {
        while (getline(filePinjam, tempNama, '|') &&
               getline(filePinjam, tempIdBuku, '|') &&
               getline(filePinjam, tempJudul)) {
            
            if (tempNama == namaCari && stoi(tempIdBuku) == idCari && !ditemukan) {
                ditemukan = true;
            } else {
                fileTemp << tempNama << "|" << tempIdBuku << "|" << tempJudul << endl;
            }
        }
        filePinjam.close();
        fileTemp.close();
        remove("peminjam.txt");
        rename("temp_pinjam.txt", "peminjam.txt");
    }

    if (!ditemukan) {
        cout << "[Gagal] Data peminjaman tidak ditemukan! Periksa kembali Nama atau ID Buku." << endl;
        return;
    }

    buku data[100];
    int jumlah = 0;
    ifstream file("buku.txt");
    string tempId, tempJudulBuku, tempPengarang, tempStock;
    
    while (getline(file, tempId, '|') &&
           getline(file, tempJudulBuku, '|') &&
           getline(file, tempPengarang, '|') &&
           getline(file, tempStock)) {
        data[jumlah].id = stoi(tempId);
        data[jumlah].judul = tempJudulBuku;
        data[jumlah].pengarang = tempPengarang;
        data[jumlah].stock = stoi(tempStock);
        
        if (data[jumlah].id == idCari) {
            data[jumlah].stock++;
        }
        jumlah++;
    }
    file.close();

    ofstream fileTulis("buku.txt");
    for (int i = 0; i < jumlah; i++) {
        fileTulis << data[i].id << "|" << data[i].judul << "|" << data[i].pengarang << "|" << data[i].stock << endl;
    }
    fileTulis.close();

    cout << "[Sukses] Buku berhasil dikembalikan!" << endl;
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
                editBuku();
                break;
            case 4:
                tampilkanBuku();
                break;
            case 5:
                cariBuku();
                break;
            case 6:
                daftarPeminjam();
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
                pinjamBuku();
                break;
            case 4:
                kembalikanBuku();
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
