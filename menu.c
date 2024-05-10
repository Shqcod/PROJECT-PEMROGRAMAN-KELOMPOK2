// import header.h
#include "header.h"

// book list length function
int booklist_length()
{
    FILE *input_fp;

    char books[1024], row[256];
    int size;

    input_fp = fopen("books.txt", "r");

    if (input_fp == NULL)
    {
        printf("Error! file doesn't exist\n");

        return EXIT_FAILURE;
    }

    while (fgets(books, sizeof(books), input_fp) != NULL)
    {
        sscanf(books, "%[^\n]s", row);

        if (strcmp(row, "\n"))
        {
            size++;
        }
    }

    fclose(input_fp);

    return size;
}

// borrowed books length function
int borrowed_length()
{
    FILE *input_fp;

    char data[512], row[256];
    int size;

    input_fp = fopen("borrowed.txt", "r");

    if (input_fp == NULL)
    {
        printf("Error! file doesn't exist\n");

        return EXIT_FAILURE;
    }

    while (fgets(data, sizeof(data), input_fp) != NULL)
    {
        sscanf(data, "%[^\n]s", row);

        if (strcmp(row, "\n"))
        {
            size++;
        }
    }

    fclose(input_fp);

    return size;
}

// welcome screen function
void welcome_screen()
{
    enter(16);
    printin_center("%*s", "\033[1;30;43m+[ WELCOME TO E-LIBRARY ]+", 130, 10, "FALSE");
    printf("\033[0m");
    enter(2);
    printin_center("%*s", "\033[1;33mAccess the library anywhere and anytime", 130, 10 - 2, "FALSE");
    printf("\033[0m");
    enter(16);
}

// home screen function
void home_screen()
{
    hyphen("\033[1;33m", 130, 10, "TRUE");
    printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
    hyphen("\033[1;33m", 130, 10, "TRUE");

    printf("\033[1;33mWelcome to E-Library \n");
    printf("\033[0m");
    printf("\033[33mE-Library is a digital library platform. \nYou can search books, borrow books, and return books.");
    enter(2);
    printf("\033[1;33mPlease log in to continue");
    enter(2);
    printf("\033[0m");

    printf("\033[1;33mLog in as: \n");
    printf("\033[0m");
    printf("\033[33m1. Administrator (full access) \n");
    printf("\033[33m2. User (limited access) \n");
    printf("\033[33m3. Exit \n");
    printf("\033[0m");
    enter(20);

    hyphen("\033[1;33m", 130, 10, "TRUE");
}

// admin menu function
void admin_menu()
{
    printf("\033[1;33mAdmin menu\n");
    printf("\033[0m");
    printf("\033[33m1. Add books\n");
    printf("\033[33m2. Delete books\n");
    printf("\033[33m3. Modify books\n");
    printf("\033[33m4. Home\n");
    printf("\033[33m5. Exit\n");
    printf("\033[0m");
}

// user menu function
void user_menu()
{
    printf("\033[1;33mUser menu\n");
    printf("\033[0m");
    printf("\033[33m1. Books available\n");
    printf("\033[33m2. Borrow books\n");
    printf("\033[33m3. On loan\n");
    printf("\033[33m4. Return books\n");
    printf("\033[33m5. Home\n");
    printf("\033[33m6. Exit\n");
    printf("\033[0m");
}

// log in invalid function
void login_invalid()
{
    enter(17);
    printin_center("%*s", "\033[1;33mInvalid username or password. Please try again!", 130, 10, "FALSE");
    printf("\033[0m");
    enter(17);
}

// log in end function
void login_end()
{
    enter(16);
    printin_center("%*s", "\033[1;33mInvalid username or password 3 times. Try again later!", 130, 10, "FALSE");
    enter(2);
    printin_center("%*s", "\033[1;33mThe program will close in 3 seconds", 130, 10 - 2, "FALSE");
    printf("\033[0m");
    enter(16);
}

// option invalid function
void option_invalid()
{
    printf("\033[1;33m-> ");
    printf("\033[0m");
    printf("\033[33mInvalid option. Please try again!");
    printf("\033[0m");
    enter(1);
}

// option end function
void option_end()
{
    printf("\033[33mInvalid option 3 times. Try again later! \nThe program will close in 3 seconds");
    printf("\033[0m");
    enter(1);
}

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

// goodbye screen function
void goodbye_screen()
{
    enter(17);
    printin_center("%*s", "\033[1;30;43m+[ Goodbye! ]+", 130, 10, "FALSE");
    printf("\033[0m");
    enter(17);
}