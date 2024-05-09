
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struct untuk data buku
struct dataBuku {
    unsigned int idBuku;
    char judul[100];
    char penulis[50];
    unsigned int jumlahHalaman;
    unsigned int tahunTerbit;
    unsigned int jumlahBukuTersedia;
    int dipinjam; // Menandakan status buku sedang dipinjam atau tidak
    
} buku ;
void pinjam(void){}

int main(){
    pinjam();
    return 0;
}

  void pinjam(void){}

int pinjamBuku(int userId) {
  
  // 1. Memuat data buku dari file
  struct dataBuku* buku = loadBukuData();
  int jumlahBuku = getJumlahBuku(); 

  // 2. Menampilkan daftar buku yang tersedia
  printf("\nDaftar Buku yang Tersedia:\n");
  for (int i = 0; i < jumlahBuku; i++) {
    if (buku[i].jumlahBukuTersedia> 0) {
      printf("  - ID: %d, Judul: %s\n", buku[i].idBuku, buku[i].judul);
    }
  }

  // 3. Mendapatkan ID buku dari pengguna
  int pinjamID;
  printf("\nMasukkan ID buku yang ingin dipinjam: ");
  scanf("%d", &pinjamID);

  // 4. Memeriksa ketersediaan buku
  int ditemukan = 0;
  for (int i = 0; i < jumlahBuku; i++) {
    if (buku[i].idBuku == pinjamID && buku[i].jumlahBukuTersedia > 0) {
      ditemukan = 1;
      buku[i].jumlahBukuTersedia--;
      break;
    }
  }

  // 5. Menangani ketersediaan buku
  if (ditemukan) {
    // Mencatat data peminjaman (panggil fungsi untuk menulis ke peminjaman.txt)
    printf("\nBuku berhasil dipinjam!\n");
    LihatPeminjaman(userId, pinjamID); // Asumsikan fungsi ini ada
  } else {
    printf("\nMaaf, buku tidak tersedia atau jumlah stok tidak mencukupi.\n");
  }

  // 6. Membebaskan memori yang dialokasikan untuk buku (jika berlaku)
  free(buku);
  return 0;
}

void LihatPeminjaman(int userId, int bukuId) {
  // Membuka peminjaman.txt untuk menambahkan data
  FILE* pinjamFile = fopen("pinjaman.txt", "a");
  if (pinjamFile == NULL) {
    printf("Gagal membuka file pinjaman.txt\n");
    return;
  }

  
  char tanggalPinjam[20]; 
  

  // Menulis data ke file (userId, bukuId, tanggalPinjam)
  fprintf(pinjamFile, "%d %d %s\n", userId, bukuId, tanggalPinjam);

  fclose(pinjamFile);
  printf("Data peminjaman berhasil dicatat.\n");
