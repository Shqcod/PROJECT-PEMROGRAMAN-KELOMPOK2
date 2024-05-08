// import header.h
#include "header.h"

// books size function
int books_size()
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
}

// void book_list(book data[], int size)
// {
//     int loop = 0;
//     int id_length, id_lengthtemp;
//     int title_length, title_lengthtemp;
//     int author_length, author_lengthtemp;
//     int page_length, page_lengthtemp;
//     int pubyear_length, pubyear_lengthtemp;
//     int available_length, available_lengthtemp;

//     for (int index = 0; index < size; index++)
//     {
//         loop++;

//         if (loop == 1)
//         {
//             id_lengthtemp = sizeof(data[index].id);
//             id_length = sizeof(data[index].id);
//             title_lengthtemp = strlen(data[index].title);
//             title_length = strlen(data[index].title);
//             author_lengthtemp = strlen(data[index].author);
//             author_length = strlen(data[index].author);
//             page_lengthtemp = sizeof(data[index].page);
//             page_length = sizeof(data[index].page);
//             pubyear_lengthtemp = sizeof(data[index].pub_year);
//             pubyear_length = sizeof(data[index].pub_year);
//             available_lengthtemp = sizeof(data[index].available);
//             available_length = sizeof(data[index].available);
//         }
//         else
//         {
//             if (sizeof(data[index].id) > id_lengthtemp)
//             {
//                 id_lengthtemp = sizeof(data[index].id);
//                 id_length = sizeof(data[index].id);
//             }
//         }
//     }
// }

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

// goodbye screen function
void goodbye_screen()
{
    enter(17);
    printin_center("%*s", "\033[1;30;43m+[ Goodbye! ]+", 130, 10, "FALSE");
    printf("\033[0m");
    enter(17);
}