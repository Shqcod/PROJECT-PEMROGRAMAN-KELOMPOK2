void kembalikan(struct Buku *buku, unsigned int jumlahBuku, unsigned int id) {
    if (id < jumlahBuku) {
        if (buku[id].dipinjam) {
            buku[id].dipinjam = 0;
            printf("Buku dengan ID %u telah berhasil dikembalikan.\n", buku[id].idBuku);
        } else {
            printf("Buku dengan ID %u tidak sedang dipinjam.\n", buku[id].idBuku);
        }
    } else {
        printf("ID buku tidak valid.\n");
    }
}
