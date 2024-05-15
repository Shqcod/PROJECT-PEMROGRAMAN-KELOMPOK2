#include <stdio.h>
#include <stdlib.h>

typedef struct Buku {
    unsigned int idBuku;
    char judul[256];
    char penulis[256];
    unsigned int halaman;
    unsigned int tahunTerbit;
    unsigned int jumlahBukuTersedia;
} book;

void booksavailable(book data[])
{
    FILE *input_fp;

    char books[1024];

    input_fp = fopen("bookstable.txt", "r");

    if (input_fp == NULL)
    {
        printf("Error! file doesn't exist\n");

        EXIT_FAILURE;
    }

    for (int index = 0; fgets(books, sizeof(books), input_fp) != NULL; index++)
    {
        sscanf(books, "%u \"%[^\"]\" \"%[^\"]\" %u %u %u", &data[index].idBuku, data[index].judul, data[index].penulis, &data[index].halaman, &data[index].tahunTerbit, &data[index].jumlahBukuTersedia);
    }
}
void printRow(book data[], int index) {
    printf("| %-4u | %-30s | %-25s | %-6u | %-8u | %-6u |\n", data[index].idBuku, data[index].judul, data[index].penulis, data[index].halaman, data[index].tahunTerbit, data[index].jumlahBukuTersedia);
}

void printSeparator() {
    printf("+------+--------------------------------+-------------------------+----------+----------+--------+\n");
}

int main() {
    book data[20];

    // Inisialisasi data buku-buku
    // struct Buku daftarBuku[] = {
    //     {111, "Clean Code", "R. C. Martin", 464, 2008, 8},
    //     {112, "Cracking the Coding", "G. L. McDowell", 687, 2015, 6},
    //     {113, "Python Crash Course", "E. Matthes", 44, 2015, 15},
    //     {114, "Computer Networking", "J. F. Kurose, K. W. Ross", 864, 2016, 10},
    //     {115, "Artificial Intelligence", "S. Russell, P. Norvig", 1132, 2020, 12},
    //     {116, "Algorithms Unlocked", "T. H. Cormen", 240, 2013, 18},
    //     {117, "Effective Java", "J. Bloch", 432, 2017, 15},
    //     {118, "Programming Python", "M. Lutz", 1632, 2019, 20},
    //     {119, "Learning SQL", "A. Beaulieu", 338, 2009, 15},
    //     {211, "Hacking", "J. Erickson", 488, 2008, 20},
    //     {211, "Rapid Development", "S. McConnell", 672, 1996, 12},
    //     {212, "Security Engineering", "R. J. Anderson", 1060, 2008, 8},
    //     {213, "Java", "H. Schildt", 12, 2018, 14},
    //     {214, "Programming Pearls", "J. Bentley", 256, 1999, 16},
    //     {215, "Software Engineering", "R. S. Pressman", 992, 2014, 22},
    //     {216, "Computer Security", "W. Stallings, L. Brown", 864, 2018, 25},
    //     {217, "Learning Web Design", "J. N. Robbins", 808, 2018, 25},
    //     {218, "Information Security", "M. Stamp", 648, 2011, 6},
    //     {219, "The Internet of Money", "A. M. Antonopoulos", 150, 2016, 5},
    //     {220, "Blockchain Basics", "D. Drescher", 255, 2017, 12}
    // };

    booksavailable(data);

    // Cetak header tabel
    printSeparator();
    printf("| %-4s | %-30s | %-25s | %-6s | %-8s | %-6s |\n", "ID", "Judul", "Penulis", "Halaman", "Tahun", "Tersedia");
    printSeparator();

    // Cetak data buku
    for(int i = 0; i < 20; i++) 
    {
        printRow(data, i);
        printSeparator();
    }

    return 0;
}
