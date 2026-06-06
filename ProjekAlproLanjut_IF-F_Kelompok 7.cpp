#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

struct buku
{
    string judul, pengarang;
	string info[2][2];
    int stock, id;
};

void clear(){
	cin.clear();
	cin.ignore(1000, '\n');
    cout << "input tidak valid!"<<endl;
}

string toLowerCase(string teks) {
    for (int i = 0; i < teks.length(); i++) {
        teks[i] = tolower((unsigned char)teks[i]);
    }
    return teks;
}

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

void asc(buku data[], int jumlah, int parameter){
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (parameter == 1){
                if (data[j].id > data[j + 1].id){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else if (parameter == 2){
                if (toLowerCase(data[j].judul) > toLowerCase(data[j + 1].judul)){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else if (parameter ==3){
                if (data[j].stock > data[j + 1].stock){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else if (parameter == 4){
                int tahun1 = 0;
                int tahun2 = 0;

                try {
                    tahun1 = stoi(data[j].info[1][0]);
                    tahun2 = stoi(data[j + 1].info[1][0]);
                }
                catch (...) {
                    tahun1 = 0;
                    tahun2 = 0;
                }

                if (tahun1 > tahun2){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}

void desc(buku data[], int jumlah, int parameter){
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (parameter == 1){
                if (data[j].id < data[j + 1].id){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else if (parameter == 2){
                if (toLowerCase(data[j].judul) < toLowerCase(data[j + 1].judul)){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else if (parameter ==3){
                if (data[j].stock < data[j + 1].stock){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else if (parameter == 4){
                int tahun1 = 0;
                int tahun2 = 0;

                try {
                    tahun1 = stoi(data[j].info[1][0]);
                    tahun2 = stoi(data[j + 1].info[1][0]);
                }
                catch (...) {
                    tahun1 = 0;
                    tahun2 = 0;
                }

                if (tahun1 < tahun2){
                    buku temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}

void bacaFileBuku(buku data[], int &jumlah) {

    jumlah = 0;

    ifstream file("buku.txt");

    if (!file.is_open()) {
        cout << "File buku tidak ditemukan!" << endl;
        return;
    }

    string tempId, tempJudul, tempPengarang, tempStock;
    string tempKategori, tempRak, tempTahun, tempPenerbit;

    while (getline(file, tempId, '|') &&
           getline(file, tempJudul, '|') &&
           getline(file, tempPengarang, '|') &&
           getline(file, tempStock, '|') &&
           getline(file, tempKategori, '|') &&
           getline(file, tempRak, '|') &&
           getline(file, tempTahun, '|') &&
           getline(file, tempPenerbit)) {

        try {
            data[jumlah].id = stoi(tempId);
            data[jumlah].stock = stoi(tempStock);
        }
        catch (...) {
            cout << "Data rusak dilewati!" << endl;
            continue;
        }
        
        data[jumlah].pengarang = tempPengarang;
        data[jumlah].stock = stoi(tempStock);

        data[jumlah].info[0][0] = tempKategori;
        data[jumlah].info[0][1] = tempRak;
        data[jumlah].info[1][0] = tempTahun;
        data[jumlah].info[1][1] = tempPenerbit;

        jumlah++;
        if (jumlah >= 100) {
            cout << "Kapasitas penuh!";
            break;
        }
    }

    file.close();
}

void tambahBuku(){
    buku bbaru;
    bool sudahAda;
    string tempId, tempJudul, tempPengarang, tempStock;
	string tempKategori, tempRak, tempTahun, tempPenerbit;
	
    do {
        sudahAda = false;
        cout << "=== Tambah Buku ===" << endl;
        while (true){
            cout << "Masukan ID Buku: ";
            cin >> bbaru.id;
            if (cin.fail()){
                clear();
            } else{
                break;
            }
        }

        ifstream fileCek("buku.txt");
                
        if (fileCek.is_open()) {
            while (getline(fileCek, tempId, '|') &&
				getline(fileCek, tempJudul, '|') &&
				getline(fileCek, tempPengarang, '|') &&
				getline(fileCek, tempStock, '|') &&
				getline(fileCek, tempKategori, '|') &&
				getline(fileCek, tempRak, '|') &&
				getline(fileCek, tempTahun, '|') &&
				getline(fileCek, tempPenerbit)) {
                        
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
            cout << "Masukan Judul buku     : ";
            cin.ignore();
            getline(cin, bbaru.judul);
            cout << "Masukan Pengarang buku : ";
            getline(cin, bbaru.pengarang);
			cout << "Masukan kategori buku  : ";
			getline(cin, bbaru.info[0][0]);
			cout << "Masukan rak buku       : ";
			getline(cin, bbaru.info[0][1]);
			cout << "Masukan tahun terbit  : ";
			getline(cin, bbaru.info[1][0]);
			cout << "Masukan penerbit buku : ";
			getline(cin, bbaru.info[1][1]);
            while (true){
                cout << "Jumlah buku            : ";
                cin >> bbaru.stock;
                if (cin.fail() || bbaru.stock < 0){
                    clear();
                } else{
                    break;
                }
            }

            ofstream filebaru("buku.txt", ios::app);
            filebaru << bbaru.id << "|"
					<< bbaru.judul << "|"
					<< bbaru.pengarang << "|"
					<< bbaru.stock << "|"
					<< bbaru.info[0][0] << "|"
					<< bbaru.info[0][1] << "|"
					<< bbaru.info[1][0] << "|"
					<< bbaru.info[1][1] << endl;
            filebaru.close();
            cout << "[Info] Buku berhasil ditambahkan!" << endl;
}

void hapusBuku(){
    int idHapus;
    bool ditemukan = false;
    string tempId, tempJudul, tempPengarang, tempStock;
	string tempKategori, tempRak, tempTahun, tempPenerbit;
	
    cout << "=== Hapus Buku ===" << endl;
    while (true){
        cout << "Masukkan ID Buku yang ingin dihapus: ";
        cin >> idHapus;
        if (cin.fail()) {
            clear();
        } else {
            break;
        }
    }
    ifstream fileMasuk("buku.txt");
    ofstream fileTemp("temp.txt");
        while (getline(fileMasuk, tempId, '|') &&
			getline(fileMasuk, tempJudul, '|') &&
			getline(fileMasuk, tempPengarang, '|') &&
			getline(fileMasuk, tempStock, '|') &&
			getline(fileMasuk, tempKategori, '|') &&
			getline(fileMasuk, tempRak, '|') &&
			getline(fileMasuk, tempTahun, '|') &&
			getline(fileMasuk, tempPenerbit)) {

               if (stoi(tempId) == idHapus) {
                    ditemukan = true;
                    cout << "[Info] Buku dengan ID " << idHapus << " berhasil dihapus." << endl;
                } else {
                    fileTemp << tempId << "|"
							<< tempJudul << "|"
							<< tempPengarang << "|"
							<< tempStock << "|"
							<< tempKategori << "|"
							<< tempRak << "|"
							<< tempTahun << "|"
							<< tempPenerbit << endl;
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
    int jumlah = 0, idBaru;
    bacaFileBuku(data, jumlah);
    
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
    while (true){
        cout << "masukkan id buku : ";
        cin >> idCari;
        if (cin.fail()) {
            clear();
        } else {
            break;
        }
    }
    
    int indeks = cariBukuRekursif(data, 0, jumlah - 1, idCari);
    
    if (indeks == -1) {
        cout << "[Peringatan] ID Buku tidak ditemukan!" << endl;
        return;
    }

    cout << endl << endl;
    while (true) {
        cout << "Masukkan id baru : "; 
        cin >> idBaru;
        if (cin.fail()) {
            clear();
        } else {
            break;
        }
    }

    bool idAda = false;

    for (int i = 0; i < jumlah; i++) {
        if (i != indeks && data[i].id == idBaru) {
            idAda = true;
        }
    }
    if (idAda) {
        cout << "ID sudah digunakan!" << endl;
        return;
    }
    
    data[indeks].id = idBaru;
    cin.ignore();
    cout << "Nama buku baru   : "; getline(cin, data[indeks].judul);
    cout << "Pengarang baru   : "; getline(cin, data[indeks].pengarang);
    while (true) {
        cout << "Stok baru        : "; 
        cin >> data[indeks].stock;
        if (cin.fail() || data[indeks].stock < 0) {
            clear();
        } else {
            break;
        }
    }
    cin.ignore();
	cout << "Kategori baru    : "; getline(cin, data[indeks].info[0][0]);
	cout << "Rak buku baru    : "; getline(cin, data[indeks].info[0][1]);
	cout << "Tahun terbit baru: "; getline(cin, data[indeks].info[1][0]);
	cout << "Penerbit baru    : "; getline(cin, data[indeks].info[1][1]);
    ofstream fileTulis("buku.txt");
    for (int i = 0; i < jumlah; i++) {
        fileTulis << data[i].id << "|"
				  << data[i].judul << "|"
				  << data[i].pengarang << "|"
				  << data[i].stock << "|"
				  << data[i].info[0][0] << "|"
				  << data[i].info[0][1] << "|"
				  << data[i].info[1][0] << "|"
				  << data[i].info[1][1] << endl;
    }
    fileTulis.close();
    cout << "[Info] Buku berhasil diperbarui!" << endl;
}

void tampilkanBuku(){

    buku data[100];
    int sorting, jumlah = 0;
    bacaFileBuku(data, jumlah);

    cout << "PILIH JENIS SORTING\n";
    cout << "1. Sorting by ID Buku\n";
    cout << "2. Sorting by Judul\n";
    cout << "3. Sorting by Stok Buku\n";
    cout << "4. Sorting by Tahun Terbit\n";

    while (true) {
        cout << "Pilih Jenis Sorting : ";
        cin >> sorting;

        if (cin.fail() || sorting < 1 || sorting > 4) {
            clear();
        } else {
            break;
        }
    }

    int urutan;
    while (true) {
        cout << "1. ascending\n";
        cout << "2. descending\n";
        cin >> urutan;

        if (cin.fail() || (urutan != 1 && urutan != 2)) {
            clear();
        } else {
            break;
        }
    }    
    if (urutan == 1){
        asc(data, jumlah, sorting);
    } else {
        desc(data, jumlah, sorting);
    }
	buku *ptr = data;

    cout << endl;
    cout << "==================================================" << endl;
    cout << "              DAFTAR BUKU PERPUSTAKAAN           " << endl;
    cout << "==================================================" << endl;

    if (jumlah == 0) {
        cout << "Belum ada data buku!" << endl;
    }
    else {

        for (int i = 0; i < jumlah; i++) {

            cout << "ID Buku      : " << (ptr + i)->id << endl;
			cout << "Judul        : " << (ptr + i)->judul << endl;
			cout << "Pengarang    : " << (ptr + i)->pengarang << endl;
			cout << "Stok         : " << (ptr + i)->stock << endl;
			cout << "Kategori     : " << (ptr + i)->info[0][0] << endl;
			cout << "Rak Buku     : " << (ptr + i)->info[0][1] << endl;
			cout << "Tahun Terbit : " << (ptr + i)->info[1][0] << endl;
			cout << "Penerbit     : " << (ptr + i)->info[1][1] << endl;
            cout << "--------------------------------------------------" << endl;
        }
    }
}

void tulisbuku (buku data[], int i){
    cout << "Buku ditemukan!" << endl;
    cout << "-------------------------" << endl;
    cout << "ID Buku    : " << data[i].id << endl;
    cout << "Judul      : " << data[i].judul << endl;
    cout << "Pengarang  : " << data[i].pengarang << endl;
    cout << "Stok       : " << data[i].stock << endl;
	cout << "Kategori   : " << data[i].info[0][0] << endl;
	cout << "Rak Buku   : " << data[i].info[0][1] << endl;
	cout << "Tahun Terbit : " << data[i].info[1][0] << endl;
	cout << "Penerbit     : " << data[i].info[1][1] << endl;
    cout << "-------------------------" << endl;
}

void cariBuku(){

    buku data[100];
    int jumlah = 0;

    bacaFileBuku(data, jumlah);

    string cari;
    bool ditemukan = false;
    int pil;

    cout << "=== CARI BUKU ===" << endl;
    cout << "1. Berdasar ID Buku" << endl;
    cout << "2. Berdasar Judul Buku" << endl;
    cout << "3. Berdasar Kategori Buku" << endl;
    cout << "4. Berdasar Rak Buku" << endl;
    cout << "5. Keluar" << endl;
    while (true) {
        cout << "pilihan : ";
        cin >> pil;
        if (cin.fail() || pil < 1 || pil > 5) {
            clear();
        } else {
            break;
        }
    }
    cin.ignore();

    if (pil==1){
        int cari;
        while (true) {
            cout << "Masukan ID Buku : ";
            cin >> cari;
            if (cin.fail()) {
                clear();
            } else {
                break;
            }
        }
        for (int i = 0; i < jumlah; i++) {
            if (data[i].id == cari) {
                ditemukan = true;
            tulisbuku (data, i);
            }
        }
    } else if (pil==2){
        string cari;
        cin.clear();
        cout << "Masukan Judul Buku : ";
        getline(cin, cari);
        for (int i = 0; i < jumlah; i++) {
            if (toLowerCase(data[i].judul) == toLowerCase(cari)) {
                ditemukan = true;
            tulisbuku (data, i);
            }
        }
    } else if (pil==3){
        string cari;
        cin.clear();
        cout << "Masukan Kategori Buku : ";
        getline(cin, cari);
        for (int i = 0; i < jumlah; i++) {
            if (toLowerCase(data[i].info[0][0]) == toLowerCase(cari)) {
                ditemukan = true;
            tulisbuku (data, i);
            }
        }
    }else if (pil==4){
        string cari;
        cin.clear();
        cout << "Masukan rak buku : ";
        getline(cin, cari);
        for (int i = 0; i < jumlah; i++) {
            if (toLowerCase(data[i].info[0][1]) == toLowerCase(cari)) {
                ditemukan = true;
            tulisbuku (data, i);
            }
        }
    } else if (pil==5){
        return;
    } else {
        cout << "pilihan tidak valid";
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
    bacaFileBuku(data, jumlah);

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

    while (true) {
        cout << "Masukkan ID Buku yang ingin dipinjam : ";
        cin >> idCari;

        if (cin.fail()) {
            clear();
        } else {
            break;
        }
    }

    int indeks = cariBukuRekursif(data, 0, jumlah - 1, idCari);

    if (indeks == -1) {
        cout << "[Peringatan] Buku dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }

    if (data[indeks].stock <= 0) {
        cout << "[Peringatan] Stok buku habis!" << endl;
        return;
    }

    cin.ignore(1000, '\n');
    cout << "Masukkan Nama Anda: ";
    getline(cin, namaPeminjam);

    ifstream cekPeminjam("peminjam.txt");
    if (!cekPeminjam.is_open()){
        ofstream buatFile("peminjam.txt");
        buatFile.close();

        cekPeminjam.open("peminjam.txt");
    }
    string tempNama, tempId, tempJudul;

    while (getline(cekPeminjam, tempNama, '|') &&
           getline(cekPeminjam, tempId, '|') &&
           getline(cekPeminjam, tempJudul)) {

        if (toLowerCase(tempNama) == toLowerCase(namaPeminjam)) {

            cout << "[Peringatan] "
                 << namaPeminjam
                 << " masih memiliki buku yang dipinjam!" << endl;

            cekPeminjam.close();
            return;
        }
    }

    cekPeminjam.close();
    data[indeks].stock--;

    ofstream fileTulis("buku.txt");

    for (int i = 0; i < jumlah; i++) {
        fileTulis << data[i].id << "|"
                  << data[i].judul << "|"
                  << data[i].pengarang << "|"
                  << data[i].stock << "|"
                  << data[i].info[0][0] << "|"
                  << data[i].info[0][1] << "|"
                  << data[i].info[1][0] << "|"
                  << data[i].info[1][1] << endl;
    }

    fileTulis.close();

    ofstream filePinjam("peminjam.txt", ios::app);

    filePinjam << namaPeminjam << "|"
               << data[indeks].id << "|"
               << data[indeks].judul << endl;

    filePinjam.close();

    ofstream histori("histori.txt", ios::app);
    
    if (!histori.is_open()) {
        cout << "File histori gagal dibuka!" << endl;
        return;
    }

    histori << namaPeminjam << "|"
            << data[indeks].id << "|"
            << data[indeks].judul << "|"
            << "Dipinjam" << endl;

    histori.close();

    cout << "[Sukses] Buku berhasil dipinjam!" << endl;
}

void kembalikanBuku() {
    string namaCari;
    int idCari;

    cout << "=== KEMBALIKAN BUKU ===" << endl;

    cin.ignore(1000, '\n');

    cout << "Masukkan Nama Anda: ";
    getline(cin, namaCari);

    while (true) {
        cout << "Masukkan ID Buku yang dikembalikan: ";
        cin >> idCari;
        if (cin.fail()) {
            clear();
        } else {
            break;
        }
    }

    ifstream filePinjam("peminjam.txt");
    ofstream fileTemp("temp_pinjam.txt");

    if (!filePinjam.is_open()) {
        cout << "File peminjam gagal dibuka!" << endl;
        return;
    }

    string tempNama, judulBuku, tempIdBuku, tempJudul;
    bool ditemukan = false;

    while (getline(filePinjam, tempNama, '|') &&
           getline(filePinjam, tempIdBuku, '|') &&
           getline(filePinjam, tempJudul)) {
        if (toLowerCase(tempNama) == toLowerCase(namaCari)
            && stoi(tempIdBuku) == idCari
            && !ditemukan) {
            ditemukan = true;
            judulBuku = tempJudul;
        } else {
            fileTemp << tempNama << "|"
                     << tempIdBuku << "|"
                     << tempJudul << endl;
        }
    }

    filePinjam.close();
    fileTemp.close();

    if (remove("peminjam.txt") != 0) {
        cout << "Gagal menghapus file lama!" << endl;
    }

    if (rename("temp_pinjam.txt", "peminjam.txt") != 0) {
        cout << "Gagal rename file!" << endl;
    }
    if (!ditemukan) {
        cout << "[Gagal] Data peminjaman tidak ditemukan!" << endl;
        return;
    }

    buku data[100];
    int jumlah = 0;

    bacaFileBuku(data, jumlah);

    for (int i = 0; i < jumlah; i++) {

        if (data[i].id == idCari) {
            data[i].stock++;
        }
    }

    ofstream fileTulis("buku.txt");

    for (int i = 0; i < jumlah; i++) {

        fileTulis << data[i].id << "|"
                  << data[i].judul << "|"
                  << data[i].pengarang << "|"
                  << data[i].stock << "|"
                  << data[i].info[0][0] << "|"
                  << data[i].info[0][1] << "|"
                  << data[i].info[1][0] << "|"
                  << data[i].info[1][1] << endl;
    }

    fileTulis.close();
    ofstream histori("histori.txt", ios::app);

    histori << namaCari << "|"
            << idCari << "|"
            << judulBuku << "|"
            << "Dikembalikan" << endl;

    histori.close();

    cout << "[Sukses] Buku berhasil dikembalikan!" << endl;
}

void historiPeminjaman() {
    ifstream file("histori.txt");

    if (!file.is_open()) {
        cout << "Belum ada histori peminjaman!" << endl;
        return;
    }

    string nama, idBuku, judul, status;

    cout << endl;
    cout << "==================================================" << endl;
    cout << "               HISTORI PEMINJAMAN                " << endl;
    cout << "==================================================" << endl;

    bool adaData = false;

    while (getline(file, nama, '|') &&
           getline(file, idBuku, '|') &&
           getline(file, judul, '|') &&
           getline(file, status)) {

        adaData = true;

        cout << "Nama Peminjam : " << nama << endl;
        cout << "ID Buku       : " << idBuku << endl;
        cout << "Judul Buku    : " << judul << endl;
        cout << "Status        : " << status << endl;
        cout << "--------------------------------------------------" << endl;
    }

    if (!adaData) {
        cout << "Belum ada histori peminjaman!" << endl;
    }

    file.close();
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
        cout << "7. Histori Peminjaman" << endl;
        cout << "8. Keluar Menu Admin" << endl;
        while (true) {
            cout << "Pilih Menu (1-8): "; 
            cin >> menu;
            if (cin.fail()) {
                clear();
            } else {
                break;
            }
        }
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
                historiPeminjaman();
                break;
            case 8:
                cout << "Anda telah keluar dari admin!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    } while(menu != 8); 
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
       while (true) {
            tampilkanMenu();
            cin >> pilihan;
            if (cin.fail()) {
                clear();
            } else {
                break;
            }
        }
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
