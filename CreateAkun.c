//Fungsi Create akun
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

//panggil fungsi 
createAkun(akun, &jumlahAkun);


//nambah Fungsi dalam While 
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
