// Fungsi untuk menghapus buku
void hapusBuku(struct Buku *buku, int *jumlahBuku) {
    unsigned int id;
    printf("Masukkan ID buku yang ingin dihapus: ");
    scanf("%u", &id);

    int indeks = cariIDBuku(buku, *jumlahBuku, id);
    if (indeks != -1) {
        // Menggeser elemen array untuk menghapus buku
        for (int i = indeks; i < *jumlahBuku - 1; i++) {
            buku[i] = buku[i + 1];
        }
        (*jumlahBuku)--;
        printf("Buku dengan ID %u telah dihapus.\n", id);
    } else {
        printf("Buku dengan ID %u tidak ditemukan.\n", id);
    }
}
