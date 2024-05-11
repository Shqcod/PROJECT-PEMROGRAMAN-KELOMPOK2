#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struct untuk data buku
struct Buku {
    unsigned int idBuku;
    char judul[100];
    char penulis[50];
    unsigned int jumlahHalaman;
    unsigned int tahunTerbit;
    unsigned int jumlahBukuTersedia;
    int dipinjam; // Menandakan status buku sedang dipinjam atau tidak
    
};

// Definisi struct untuk data akun
struct Akun {
    char username[20];
    char password[20];
    int role; // 1 untuk admin, 2 untuk user
};


// Fungsi untuk menampilkan menu admin
void tampilkanMenuAdmin() {
    printf("=== Menu Admin ===\n");
    printf("1. Tambah Buku\n");
    printf("2. Hapus Buku\n");
    printf("3. Edit Buku\n");
    printf("4. Keluar\n");
    printf("Pilih menu: ");
}

// Fungsi untuk menampilkan menu user
void tampilkanMenuUser() {
    printf("=== Menu User ===\n");
    printf("1. Lihat Buku yang Tersedia\n");
    printf("2. Pinjam Buku\n");
    printf("3. Lihat Buku yang Dipinjam\n");
    printf("4. Kembalikan Buku\n");
    printf("5. Keluar\n");
    printf("Pilih menu: ");
}

// Fungsi untuk menambah buku
void tambahBuku(struct Buku *buku, int *jumlahBuku) {
    printf("Masukkan ID Buku: ");
    scanf("%u", &buku[*jumlahBuku].idBuku);

    printf("Masukkan Judul Buku: ");
    scanf(" %[^\n]s", buku[*jumlahBuku].judul);

    printf("Masukkan Nama Penulis: ");
    scanf(" %[^\n]s", buku[*jumlahBuku].penulis);

    printf("Masukkan Jumlah Halaman: ");
    scanf("%u", &buku[*jumlahBuku].jumlahHalaman);

    printf("Masukkan Tahun Terbit: ");
    scanf("%u", &buku[*jumlahBuku].tahunTerbit);

    printf("Masukkan Jumlah Buku Tersedia: ");
    scanf("%u", &buku[*jumlahBuku].jumlahBukuTersedia);

    // Set status dipinjam menjadi 0 saat buku ditambahkan
    buku[*jumlahBuku].dipinjam = 0;

    (*jumlahBuku)++;
}

// Fungsi untuk mencari buku dengan ID
int cariIDBuku(struct Buku *buku, int jumlahBuku, unsigned int id) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (buku[i].idBuku == id) {
            return i;
        }
    }
    return -1; // -1 jika buku tidak ditemukan
}

// Fungsi pinjem
void pinjem(struct Buku *buku, unsigned int jumlahBuku, unsigned int id) {
    if (id >= 0 && id < jumlahBuku) {
        if (buku[id].jumlahBukuTersedia > 0) {
            // Menambahkan lokasi pinjaman ke file "pinjaman.txt"
            FILE *file = fopen("pinjaman.txt", "a");
            if (file != NULL) {
                fprintf(file, "judul buku: %s\n", buku[id].judul);
                fprintf(file, "penerbit: %s\n", buku[id].penulis);
                fprintf(file, "buku dengan ID %u telah berhasil dipinjam.\n", buku[id].idBuku);
                fclose(file);
            } else {
                printf("Gagal membuka file pinjaman.txt\n");
            }
            
            printf("Buku dengan ID %u telah berhasil dipinjam.\n", buku[id].idBuku);
        } else if (buku[id].dipinjam) {
            printf("Buku dengan ID %u sudah dipinjam sebelumnya.\n", buku[id].idBuku);
        } else {
            printf("Maaf, buku dengan ID %u tidak tersedia untuk dipinjam saat ini.\n", buku[id].idBuku);
        }
    } else {
        printf("ID buku tidak valid.\n");   
    }
}

// Fungsi untuk menyimpan data buku ke dalam file
void simpanDataBuku(struct Buku *buku, int jumlahBuku) {
    FILE *file = fopen("data_buku.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahBuku; i++) {
            fprintf(file, "%u;%s;%s;%u;%u;%u;%d\n", buku[i].idBuku, buku[i].judul, buku[i].penulis, buku[i].jumlahHalaman, buku[i].tahunTerbit, buku[i].jumlahBukuTersedia, buku[i].dipinjam);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data buku.\n");
    }
}

// Fungsi untuk memuat data buku dari file
void bacaDataBuku(struct Buku *buku, int *jumlahBuku) {
    FILE *file = fopen("data_buku.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%u;%[^;];%[^;];%u;%u;%u;%d\n", &buku[*jumlahBuku].idBuku, buku[*jumlahBuku].judul, buku[*jumlahBuku].penulis, &buku[*jumlahBuku].jumlahHalaman, &buku[*jumlahBuku].tahunTerbit, &buku[*jumlahBuku].jumlahBukuTersedia, &buku[*jumlahBuku].dipinjam) == 7) {
            (*jumlahBuku)++;
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk membaca data buku.\n");
    }
}

// Fungsi untuk menyimpan data akun ke dalam file
void simpanDataAkun(struct Akun *akun, int jumlahAkun) {
    FILE *file = fopen("data_akun.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahAkun; i++) {
            fprintf(file, "%s;%s;%d\n", akun[i].username, akun[i].password, akun[i].role);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data akun.\n");
    }
}

// Fungsi untuk memuat data akun dari file
void bacaDataAkun(struct Akun *akun, int *jumlahAkun) {
    FILE *file = fopen("data_akun.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%[^;];%[^;];%d\n", akun[*jumlahAkun].username, akun[*jumlahAkun].password, &akun[*jumlahAkun].role) == 3) {
            (*jumlahAkun)++;
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk membaca data akun.\n");
    }
}
//Fungsi Melihat buku yang sedang di pinjam
void lihatyangsedangdipinjem(struct Buku *buku, unsigned int *jumlahBuku) {
    FILE *file = fopen("pinjaman.txt", "r");
    if (file != NULL) {
        unsigned int idBuku;
        while (fscanf(file, "%u;", &idBuku[jumlahBuku]) == 1) {
            printf("ID Buku: %u\n", idBuku[jumlahBuku]);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file pinjaman.txt\n");
    }
}
// Fungsi Pengembalian Buku
void pengembalian(struct Buku *buku, unsigned int jumlahBuku, unsigned int id) {
    if (id >= 0 && id < jumlahBuku) {
        if (buku[id].dipinjam) {
            buku[id].jumlahBukuTersedia++;
            buku[id].dipinjam = 0;
            printf("Buku dengan ID %u telah berhasil dikembalikan.\n", buku[id].idBuku);
        } else {
            printf("Buku dengan ID %u tidak sedang dipinjam.\n", buku[id].idBuku);
        }
    } else {
        printf("ID buku tidak valid.\n");
        }
}

//Fungsi Edit Buku 
void editBuku(struct Buku *buku, int jumlahBuku) {
    unsigned int id;
    printf("Masukkan ID Buku yang ingin diubah: ");
    scanf("%u", &id);

    if (id >= 0 && id < jumlahBuku) {
        FILE *file = fopen("data_buku.txt", "r+");
        if (file != NULL) {
            int posisi = -1;
            for (int i = 0; i < jumlahBuku; i++) {
                if (buku[i].idBuku == id) {
                    posisi = i;
                    break;
                }
            }

            if (posisi != -1) {
                printf("Masukkan Judul Buku Baru: ");
                scanf(" %[^\n]s", buku[posisi].judul);

                printf("Masukkan Nama Penulis Baru: ");
                scanf(" %[^\n]s", buku[posisi].penulis);

                printf("Masukkan Jumlah Halaman Baru: ");
                scanf("%u", &buku[posisi].jumlahHalaman);

                printf("Masukkan Tahun Terbit Baru: ");
                scanf("%u", &buku[posisi].tahunTerbit);

                printf("Masukkan Jumlah Buku Tersedia Baru: ");
                scanf("%u", &buku[posisi].jumlahBukuTersedia);

                fseek(file, posisi * sizeof(struct Buku), SEEK_SET);
                fprintf(file, "judul buku: %s\n", buku[posisi].judul);
                fprintf(file, "penulis: %s\n", buku[posisi].penulis);
                fprintf(file, "jumlah halaman: %u\n", buku[posisi].jumlahHalaman);
                fprintf(file, "tahun terbit: %u\n", buku[posisi].tahunTerbit);
                fprintf(file, "jumlah buku tersedia: %u\n", buku[posisi].jumlahBukuTersedia);

                printf("Buku dengan ID %u telah berhasil diubah.\n", buku[posisi].idBuku);
            } else {
                printf("Buku dengan ID %u tidak ditemukan.\n", id);
            }

            fclose(file);
        } else {
            printf("Gagal membuka file data_buku.txt.\n");
        }
    } else {
        printf("ID Buku tidak valid.\n");
    }
}

// Fungsi Create akun 
void createAkun(struct Akun *akun, int *jumlahAkun) {
    printf("Masukkan Username: ");
    scanf(" %[^\n]s", akun[*jumlahAkun].username);

    printf("Masukkan Password: ");
    scanf(" %[^\n]s", akun[*jumlahAkun].password);

    printf("Pilih peran (1 - Admin, 2 - User): ");
    scanf("%d", &akun[*jumlahAkun].role);

    (*jumlahAkun)++;

    printf("Akun berhasil dibuat.\n");

    int id = *jumlahAkun - 1;
    if (id >= 0 && id < *jumlahAkun) {
        FILE *file = fopen("data_akun.txt", "a");
        if (file != NULL) {
            fprintf(file, "%s;%s;%d\n", akun[id].username, akun[id].password, akun[id].role);

            fclose(file);
            printf("Data akun berhasil ditulis ke file data_akun.txt.\n");
        } else {
            printf("Gagal membuka file data_akun.txt untuk penulisan.\n");
        }
    } else {
        printf("ID Akun tidak valid.\n");
    }
}


int main() {
    struct Buku buku[100];
    int jumlahBuku = 0;
    struct Akun akun[100];
    int jumlahAkun = 0;
    int status = 0; // 0 untuk belum login, 1 untuk admin, 2 untuk user
    int role; // Untuk menentukan admin atau user
    unsigned int idCari;
    int indeksCari;

    bacaDataBuku(buku, &jumlahBuku);
    bacaDataAkun(akun, &jumlahAkun);
    createAkun(akun, &jumlahAkun);

    while (1) {
    if (!status) {
        char username[20];
        char password[20];

        printf("Masukkan username: ");
        scanf("%s", username);

        printf("Masukkan password: ");
        scanf("%s", password);

        // Memeriksa data akun
        int ditemukan = 0;
        for (int i = 0; i < jumlahAkun; i++) {
            if (strcmp(username, akun[i].username) == 0 && strcmp(password, akun[i].password) == 0) {
                status = 1;
                role = akun[i].role;
                ditemukan = 1;
                break;
            }
        }

        if (!ditemukan) {
            printf("Username atau password salah.\n");
            printf("Apakah Anda ingin membuat akun baru? (1 - Ya, 0 - Tidak): ");
            int opsi;
            scanf("%d", &opsi);

            if (opsi == 1) {
                if (jumlahAkun < 100) {
                    createAkun(&akun[jumlahAkun], &jumlahAkun);
                } else {
                    printf("Batas maksimum akun telah tercapai.\n");
                }
            }
        }
        } else {
            if (role == 1) { // Admin
                int pilihan;
                tampilkanMenuAdmin();
                scanf("%d", &pilihan);
                switch (pilihan) {
                    case 1:
                        tambahBuku(buku, &jumlahBuku);
                        simpanDataBuku(buku, jumlahBuku);
                        break;
                    case 2:
                        // Fungsi untuk menghapus buku
                        break;
                    case 3:
                        editBuku(buku, jumlahBuku);
                        simpanDataBuku(buku, jumlahBuku);
                        break;
                    case 4:
                        status = 0;
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                }
            } else if (role == 2) { // User
                int pilihan;
                tampilkanMenuUser();
                scanf("%d", &pilihan);
                switch (pilihan) {
                    // menu user
                    case 1:
                        // Fungsi lihat buku yang tersedia
                        printf("Daftar Buku Tersedia:\n");
                        for (int i = 0; i < jumlahBuku; i++) {
                            printf("ID: %u, Judul: %s, Penulis: %s, Tersedia: %u\n",
                                   buku[i].idBuku, buku[i].judul, buku[i].penulis, buku[i].jumlahBukuTersedia);
                        }
                        break;
                    case 2:
                        // Fungsi peminjaman buku
                        printf("Masukkan ID buku yang ingin dipinjam: ");
                        scanf("%u", &idCari);
                        pinjem(buku, jumlahBuku, idCari);
                        simpanDataBuku(buku, jumlahBuku); // Simpan data buku setelah dipinjam
                        break;
                    case 3:
                        printf("Lihat Buku yang sudah di pinjem di file pinjaman.txt\n");
                        lihatyangsedangdipinjem(buku, &jumlahBuku);

                        break;
                    case 4: 
                        break;
                    case 5:
                        status = 0;
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                }
            }
        }
    }

    return 0;
}