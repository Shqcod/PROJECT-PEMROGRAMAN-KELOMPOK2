//Fungsi Pinjem buku
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

//Pangil fungsi
// Fungsi peminjaman buku
printf("Masukkan ID buku yang ingin dipinjam: ");
scanf("%u", &idCari);
pinjem(buku, jumlahBuku, idCari);
simpanDataBuku(buku, jumlahBuku); // Simpan data buku setelah dipinjam
