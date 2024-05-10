#include "header.h"

void borrow_books(book data[], char *account_id, unsigned int book_id, int size)
{
    FILE *input_fp;

    input_fp = fopen("borrowed_books.txt", "a");

    // if (id >= 0 && id < numof_books)
    // {
    //     if (data[id].available > 0)
    //     {
    //         if (input_fp != NULL)
    //         {
    //             fprintf(input_fp, "Title: %s\n", data[id].title);
    //             fprintf(input_fp, "Author: %s\n", data[id].author);
    //             fprintf(input_fp, "buku dengan ID %u telah berhasil dipinjam.\n", data[id].id);
    //             fclose(input_fp);
    //         }
    //         else
    //         {
    //             printf("Gagal membuka file pinjaman.txt\n");
    //         }

    //         printf("Buku dengan ID %u telah berhasil dipinjam.\n", data[id].id);
    //     }
    //     else if (data[id].available)
    //     {
    //         printf("Buku dengan ID %u sudah dipinjam sebelumnya.\n", data[id].id);
    //     }
    //     else
    //     {
    //         printf("Maaf, buku dengan ID %u tidak tersedia untuk dipinjam saat ini.\n", data[id].id);
    //     }
    // }
    // else
    // {
    //     printf("ID buku tidak valid.\n");
    // }

    for (int index = 0; index < size; index++)
    {
        if ((data[index].id != book_id) || (data[index].available == 0))
        {
            printf("\033[33mBook is not available");

            break;
        }
        else if (data[index].id == book_id && data[index].available > 0)
        {
            --(data[index].available);
        }
    }

    for (int index = 0; index < size; index++)
    {
        fprintf(input_fp, "\"%s\" %u \"%s\" \"%s\" %u %u %u", account_id, data[index].id, data[index].title, data[index].author, data[index].page, data[index].pub_year, data[index].available);
    }
}