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

// goodbye screen function
void goodbye_screen()
{
    enter(17);
    printin_center("%*s", "\033[1;30;43m+[ Goodbye! ]+", 130, 10, "FALSE");
    printf("\033[0m");
    enter(17);
}