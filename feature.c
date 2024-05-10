#include "header.h"

// books available function
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
        sscanf(books, "%u \"%[^\"]\" \"%[^\"]\" %u %u %u", &data[index].id, data[index].title, data[index].author, &data[index].page, &data[index].pub_year, &data[index].available);
    }

    fclose(input_fp);
}

// table row function
void table_row(book data[], int index)
{
    printf("\033[33m");
    printf("| %-5u | %-47s | %-35s | %-11u | %-11u | %-11u |\n", data[index].id, data[index].title, data[index].author, data[index].page, data[index].pub_year, data[index].available);
    printf("\033[0m");
}

// table border function
void table_border(char *enter)
{
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 5, 2, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 50, 0, "FALSE");
    printf("\033[1;33m+");
    hyphen("\033[1;33m", 36, 1, "FALSE");
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
void user_loans(user onloans[])
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
        sscanf(borrowed, "\"%[^\"]\" %u %u", onloans[index].username, &onloans[index].book_id, &onloans[index].numof_book);
    }

    fclose(input_fp);
}

// book status function
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
    else
    {
        EXIT_FAILURE;
    }
}

// add books function
void add_books(struct book_information *book, int *numof_book)
{
    printf("\033[0m");
    printf("\033[33mBook id\t: ");
    scanf("%u", &book[*numof_book].id);

    printf("\033[33mBook title\t: ");
    scanf(" %[^\n]s", book[*numof_book].title);

    printf("\033[33mAuthor name\t: ");
    scanf(" %[^\n]s", book[*numof_book].author);

    printf("\033[33mNumber of pages\t: ");
    scanf("%u", &book[*numof_book].page);

    printf("\033[33mPublication year\t: ");
    scanf("%u", &book[*numof_book].pub_year);

    printf("\033[33mBooks available: ");
    scanf("%u", &book[*numof_book].available);
    printf("\033[0m");

    (*numof_book)++;
}

// search books function
int search_books(struct book_information *book, int numof_book, unsigned int book_id)
{
    for (int i = 0; i < numof_book; i++)
    {
        if (book[i].id == book_id)
        {
            return i;
        }
    }
    return -1;
}

// print new book list to files function
void print_newlist(book data[], char *account_id, int books_size, int temp_index)
{
    FILE *output_fp;

    output_fp = fopen("borrowed.txt", "a");

    fprintf(output_fp, "\n\"%s\" %u %d", account_id, data[temp_index].id, 1);
    fclose(output_fp);

    output_fp = fopen("books.txt", "w");

    for (int index = 0; index < books_size; index++)
    {
        fprintf(output_fp, "%u \"%s\" \"%s\" %u %u %u", data[index].id, data[index].title, data[index].author, data[index].page, data[index].pub_year, data[index].available);

        if (index < (books_size - 1))
        {
            fprintf(output_fp, "\n");
        }
    }

    fclose(output_fp);
}