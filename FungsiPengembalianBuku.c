void pengembalian(struct Buku *buku, unsigned int jumlahBuku, unsigned int id) {
    if (id < jumlahBuku) {
        if (buku[id].pinjem) {
            buku[id].pinjem = 0;
            printf("Buku dengan ID %u telah berhasil dikembalikan.\n", buku[id].idBuku);
        } else {
            printf("Buku dengan ID %u tidak sedang dipinjam.\n", buku[id].idBuku);
        }
    } else {
        printf("ID buku tidak valid.\n");
    }
}

//memanggil fungsi
unsigned int id;
printf("Masukkan ID buku yang ingin dikembalikan: ");
scanf("%u", &id);
pengembalian(buku, jumlahBuku, id);

