//Fungsi edit buku
void editBuku(struct Buku *buku, unsigned int jumlahBuku, unsigned int id) {
    if (id >= 0 && id < jumlahBuku) {
        // Membuka file "data_buku.txt" untuk membaca dan menulis
        FILE *file = fopen("data_buku.txt", "r+");
        if (file != NULL) {
            // Mencari posisi buku dalam file berdasarkan ID
            int posisi = -1;
            for (int i = 0; i < jumlahBuku; i++) {
                if (buku[i].idBuku == id) {
                    posisi = i;
                    break;
                }
            }
            
            if (posisi != -1) {
                // Posisi buku ditemukan, mengedit informasi buku
                printf("Masukkan judul buku baru: ");
                fgets(buku[posisi].judul, sizeof(buku[posisi].judul), stdin);
                printf("Masukkan penulis buku baru: ");
                fgets(buku[posisi].penulis, sizeof(buku[posisi].penulis), stdin);
                printf("Masukkan jumlah buku tersedia baru: ");
                scanf("%u", &buku[posisi].jumlahBukuTersedia);
                
                // Mengubah posisi pointer file ke posisi buku yang akan diubah
                fseek(file, posisi * sizeof(struct Buku), SEEK_SET);
                
                // Menulis informasi buku yang telah diubah ke file
                fprintf(file, "judul buku: %s", buku[posisi].judul);
                fprintf(file, "penulis: %s", buku[posisi].penulis);
                fprintf(file, "jumlah buku tersedia: %u", buku[posisi].jumlahBukuTersedia);
                
                printf("Buku dengan ID %u telah berhasil diubah.\n", buku[posisi].idBuku);
            } else {
                printf("Buku dengan ID %u tidak ditemukan.\n", id);
            }
            
            fclose(file);
        } else {
            printf("Gagal membuka file data_buku.txt\n");
        }
    } else {
        printf("ID buku tidak valid.\n");
    }
}

//Memanggil fungsi edit buku
printf("Masukan id buku yang mau di edit : \n");
scanf("%u", &idCari);
editBuku(buku, jumlahBuku,idCari);
simpanDataBuku(buku, jumlahBuku);