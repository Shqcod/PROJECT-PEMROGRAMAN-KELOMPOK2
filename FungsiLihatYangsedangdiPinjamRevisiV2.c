//Fungsi lihat Buku yang sedang di pinjam
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

//Panggil
printf("Lihat Buku yang sudah di pinjem di file pinjaman.txt\n");
    lihatyangsedangdipinjem(buku, &jumlahBuku);
