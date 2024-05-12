
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

//
editBuku(buku, jumlahBuku);
simpanDataBuku(buku, jumlahBuku);
