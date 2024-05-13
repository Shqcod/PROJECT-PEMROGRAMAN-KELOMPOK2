// import header.h
#include "header.h"

// books available function
// Fungsi untuk membaca data buku dari file "books.txt" dan menyimpannya dalam array 'data'.
void books_available(book data[])
{
    FILE *input_fp;

    char books[1024];

    input_fp = fopen("books.txt", "r");

    if (input_fp == NULL)
    {
        printf("Error! file doesn't exist\n");

        EXIT_FAILURE;
    }

    for (int index = 0; fgets(books, sizeof(books), input_fp) != NULL; index++)
    {
        sscanf(books, "%u \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %u %u %u", &data[index].id, data[index].title, data[index].author, data[index].publisher, &data[index].page, &data[index].pub_year, &data[index].available);
    }

    fclose(input_fp);
}

// table row function
// Fungsi untuk mencetak satu baris tabel dengan data buku pada indeks tertentu.
void table_row(book data[], int index)
{
    printf("\033[33m");
    printf("| %-5u | %-27s | %-27s | %-25s | %-11u | %-11u | %-11u |\n", data[index].id, data[index].title, data[index].author, data[index].publisher, data[index].page, data[index].pub_year, data[index].available);
    printf("\033[0m");
}

// on loan table row function
// Fungsi untuk mencetak satu baris tabel untuk buku yang sedang dipinjam.
void onloan_table_row(book data[], int index)
{
    printf("\033[33m");
    printf("| %-5u | %-27s | %-27s | %-25s | %-11u | %-11u | %-11u |\n", data[index].id, data[index].title, data[index].author, data[index].publisher, data[index].page, data[index].pub_year, 1);
    printf("\033[0m");
}

// table border function
// Fungsi untuk mencetak garis pembatas tabel.
void table_border(char *enter)
{
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 5, 2, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 28, 2, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 28, 2, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 26, 1, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 14, 0, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 14, 0, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 14, 0, "FALSE");
    printf("\033[1;33m+");

    if (strcmp(enter, "TRUE") == 0)
    {
        printf("\n");
    }
    else if (strcmp(enter, "FALSE") == 0)
    {
        EXIT_SUCCESS;
    }
    else
    {
        EXIT_FAILURE;
    }
}

// user loans function
// Fungsi untuk membaca data peminjaman buku dari file "borrowed.txt" dan menyimpannya dalam array 'onloan'.
void user_loans(user onloan[])
{
    FILE *input_fp;

    char borrowed[512];

    input_fp = fopen("borrowed.txt", "r");

    if (input_fp == NULL)
    {
        printf("\033[33mError! file doesn't exist\n");

        EXIT_FAILURE;
    }

    for (int index = 0; fgets(borrowed, sizeof(borrowed), input_fp) != NULL; index++)
    {
        sscanf(borrowed, "\"%[^\"]\" %u %u", onloan[index].username, &onloan[index].book_id, &onloan[index].numof_book);
    }

    fclose(input_fp);
}

// book status function
// Fungsi untuk mencetak status buku berdasarkan pilihan.
void book_status(char *win_linux, int option)
{
    if (option == 1)
    {
        printf("\033[33mBook have been borrowed!");
        printf("\033[0m");

        timesleep(1, "TRUE", win_linux);
        system_clear(win_linux);
    }
    else if (option == 2)
    {
        printf("\033[33mBook is not available!");
        printf("\033[0m");

        timesleep(1, "TRUE", win_linux);
        system_clear(win_linux);
    }
    else if (option == 3)
    {
        printf("\033[33mBook already available!");
        printf("\033[0m");

        timesleep(1, "TRUE", win_linux);
        system_clear(win_linux);
    }
    else
    {
        EXIT_FAILURE;
    }
}

// print to file (added books) function
// Fungsi untuk menambahkan data buku ke file "books.txt".
void add_books(unsigned int id, char title[], char author[], char publisher[], unsigned int page, unsigned int pub_year, unsigned int quantity, char *win_linux)
{
    FILE *output_fp;

    output_fp = fopen("books.txt", "a");

    fprintf(output_fp, "\n%u \"%s\" \"%s\" \"%s\" %u %u %u", id, title, author, publisher, page, pub_year, quantity);

    timesleep(1, "TRUE", win_linux);

    printf("\033[33mBook successfully added!");
    printf("\033[0m");

    enter(22);
    hyphen("\033[1;33m", 130, 10, "TRUE");

    fclose(output_fp);
}

// print to file (deleted book) function
// Fungsi untuk menghapus data buku dari file "books.txt" berdasarkan ID buku.
void delete_books(book data[], unsigned int book_id, int books_size, char *win_linux)
{
    FILE *output_fp;

    output_fp = fopen("books.txt", "w");

    for (int index = 0; index < books_size; index++)
    {
        if (data[index].id != book_id)
        {
            fprintf(output_fp, "%u \"%s\" \"%s\" \"%s\" %u %u %u", data[index].id, data[index].title, data[index].author, data[index].publisher, data[index].page, data[index].pub_year, data[index].available);

            if (index < (books_size - 1))
            {
                fprintf(output_fp, "\n");
            }
        }
        else
        {
            continue;
        }
    }

    timesleep(1, "TRUE", win_linux);

    printf("\033[33mBook successfully deleted!");
    printf("\033[0m");

    fclose(output_fp);
}

// Modify books function
// Fungsi untuk mengubah data buku dalam array 'data' berdasarkan pilihan.
void modify_books(book data[], unsigned int book_id, int books_size, int option, int numof_trials)
{
    if (option == 1)
    {
        numof_trials = 0;

        char title[128];

        header();

        printf("\033[1;33mModify book title");
        printf("\033[0m");
        enter(1);

        printf("\033[33mNew title: ");
        scanf(" %[^\n]s", title);
        enter(1);
        printf("\033[0m");

        for (int index = 0; index < books_size; index++)
        {
            if (data[index].id == book_id)
            {
                strcpy(data[index].title, title);

                break;
            }
            else
            {
                continue;
            }
        }
    }
    else if (option == 2)
    {
        numof_trials = 0;

        char author[128];

        header();

        printf("\033[1;33mModify author name");
        printf("\033[0m");
        enter(1);

        printf("\033[33mNew author name: ");
        scanf(" %[^\n]s", author);
        enter(1);
        printf("\033[0m");

        for (int index = 0; index < books_size; index++)
        {
            if (data[index].id == book_id)
            {
                strcpy(data[index].author, author);

                break;
            }
            else
            {
                continue;
            }
        }
    }
    else if (option == 3)
    {
        numof_trials = 0;

        char publisher[128];

        header();

        printf("\033[1;33mModify publisher");
        printf("\033[0m");
        enter(1);

        printf("\033[33mNew publisher: ");
        scanf(" %[^\n]s", publisher);
        enter(1);
        printf("\033[0m");

        for (int index = 0; index < books_size; index++)
        {
            if (data[index].id == book_id)
            {
                strcpy(data[index].publisher, publisher);

                break;
            }
            else
            {
                continue;
            }
        }
    }
    else if (option == 4)
    {
        numof_trials = 0;

        unsigned int numof_pages;

        header();

        printf("\033[1;33mModify num. of pages");
        printf("\033[0m");
        enter(1);

        printf("\033[33mNew num. of pages: ");
        scanf("%u", &numof_pages);
        enter(1);
        printf("\033[0m");

        for (int index = 0; index < books_size; index++)
        {
            if (data[index].id == book_id)
            {
                data[index].page = numof_pages;

                break;
            }
            else
            {
                continue;
            }
        }
    }
    else if (option == 5)
    {
        numof_trials = 0;

        unsigned int pub_year;

        header();

        printf("\033[1;33mModify pub. year");
        printf("\033[0m");
        enter(1);

        printf("\033[33mNew pub. year: ");
        scanf("%u", &pub_year);
        enter(1);
        printf("\033[0m");

        for (int index = 0; index < books_size; index++)
        {
            if (data[index].id == book_id)
            {
                data[index].pub_year = pub_year;

                break;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        numof_trials = 0;

        unsigned int quantity;

        header();

        printf("\033[1;33mModify quantity");
        printf("\033[0m");
        enter(1);

        printf("\033[33mNew quantity: ");
        scanf("%u", &quantity);
        enter(1);
        printf("\033[0m");

        for (int index = 0; index < books_size; index++)
        {
            if (data[index].id == book_id)
            {
                data[index].available = quantity;

                break;
            }
            else
            {
                continue;
            }
        }
    }

    print_books(data, books_size);
}

// print new book list to both file function
// Fungsi untuk mencetak daftar buku baru ke file "borrowed.txt" dan "books.txt".
void print_newlist(book data[], char *account_id, int books_size, int temp_index)
{
    FILE *output_fp;

    output_fp = fopen("borrowed.txt", "a");

    fprintf(output_fp, "\n\"%s\" %u %d", account_id, data[temp_index].id, 1);
    fclose(output_fp);

    output_fp = fopen("books.txt", "w");

    for (int index = 0; index < books_size; index++)
    {
        fprintf(output_fp, "%u \"%s\" \"%s\" \"%s\" %u %u %u", data[index].id, data[index].title, data[index].author, data[index].publisher, data[index].page, data[index].pub_year, data[index].available);

        if (index < (books_size - 1))
        {
            fprintf(output_fp, "\n");
        }
        else
        {
            continue;
        }
    }

    fclose(output_fp);
}

// print new book list to file function
// Fungsi untuk mencetak daftar buku baru ke file "books.txt".
void print_books(book data[], int books_size)
{
    FILE *output_fp;

    output_fp = fopen("books.txt", "w");

    for (int index = 0; index < books_size; index++)
    {
        fprintf(output_fp, "%u \"%s\" \"%s\" \"%s\" %u %u %u", data[index].id, data[index].title, data[index].author, data[index].publisher, data[index].page, data[index].pub_year, data[index].available);

        if (index < (books_size - 1))
        {
            fprintf(output_fp, "\n");
        }
        else
        {
            continue;
        }
    }

    fclose(output_fp);
}

// print new loans function
// Fungsi untuk mencetak daftar peminjaman baru ke file "borrowed.txt" berdasarkan ID buku.
void print_loans(user onloan[], int borrowed_size, int book_id)
{
    FILE *output_fp;

    output_fp = fopen("borrowed.txt", "w");

    for (int index = 0; index < borrowed_size; index++)
    {
        if (onloan[index].book_id == book_id)
        {
            continue;
        }
        else
        {
            fprintf(output_fp, "\"%s\" %u %u", onloan[index].username, onloan[index].book_id, 1);

            if (index < (borrowed_size - 1))
            {
                fprintf(output_fp, "\n");
            }
            else
            {
                break;
            }
        }
    }

    fclose(output_fp);
}