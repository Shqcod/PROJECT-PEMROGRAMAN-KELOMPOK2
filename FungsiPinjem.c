//Fungsi pinjem
void pinjem(struct Buku *buku, unsigned int jumlahBuku, unsigned int id) {
    if (id >= 0 && id < jumlahBuku) {
        if (buku[id].jumlahBukuTersedia > 0 && !buku[id].dipinjam){
            buku[id].jumlahBukuTersedia--;
            buku[id].dipinjam = 1;
            printf("Buku dengan ID %u telah berhasil dipinjem.\n", buku[id].idBuku);
        } else if (buku[id].dipinjam) {
            printf("Buku dengan ID %u sudah dipinjem sebelumnya.\n", buku[id].idBuku);
        } else {
            printf("Maaf, buku dengan ID %u tidak tersedia untuk dipinjam saat ini.\n", buku[id].idBuku);
        }
    } else {
        printf("ID buku tidak valid.\n");   
    }
} 

// Panggil 
    unsigned int id;
    printf("masukan ID buku yang ingin dipinjem")
    scanf("%u", &id);
    pinjem(buku, jumlahBuku, id);