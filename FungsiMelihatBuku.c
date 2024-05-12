void SimpanDataBukuYangsedangdipinjam(struct Buku *buku, int jumlahBuku) {
    FILE *file = fopen("pinjaman.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahBuku; i++) {
            fprintf(file, "%u;%s;%s;%u;%u;%u;%d\n", buku[i].idBuku, buku[i].judul, buku[i].penulis, buku[i].jumlahHalaman, buku[i].tahunTerbit, buku[i].jumlahBukuTersedia, buku[i].dipinjam);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data buku.\n");
    }
}

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

printf("Lihat Buku yang sudah di pinjem di file pinjaman.txt");
SimpanDataBukuYangsedangdipinjam(buku, jumlahBuku);
lihatyangsedangdipinjem(buku, &jumlahBuku);
