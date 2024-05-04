// import header.h
#include "header.h"

// main function
int main(void)
{
    char account_id[64], password[64];

    /* Resolution:
    width: 140
    height: 35
    ratio: 1:4 */

    system("clear");
    loading(35);

    enter(16);
    printin_center("%*s", "\033[1;30;43m+[ WELCOME TO E-LIBRARY ]+", 130, 10 + 2, "FALSE");
    printf("\033[0m");
    enter(2);
    printin_center("%*s", "\033[1;33mAccess the library anywhere and anytime", 130, 10, "FALSE");
    printf("\033[0m");
    enter(16);

    timesleep(3, "FALSE");
    system("clear");

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
    printf("\033[0m");
    enter(21);

    hyphen("\033[1;33m", 130, 10, "TRUE");

    int option = 0, numof_trials = 0;

option:
    printf("\033[1;30;43m[1/2]");
    printf("\033[0m");
    printf("\033[33m: ");
    scanf("%d", &option);
    printf("\033[0m");

    if (option == 1)
    {
        system("clear");
        loading(35);

    admin_login:
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
        hyphen("\033[1;33m", 130, 10, "TRUE");

        printf("\033[1;33mAdmin log in \n");
        printf("\033[0m");
        printf("\033[33mAdmin ID\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        enter(27);
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printf("\033[0m");
        timesleep(1, "FALSE");

        system("clear");
        loading(35);

        return EXIT_SUCCESS;
    }
    else if (option == 2)
    {
        system("clear");
        loading(35);

    user_login:
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
        hyphen("\033[1;33m", 130, 10, "TRUE");

        printf("\033[1;33mUser log in \n");
        printf("\033[0m");
        printf("\033[33mUser ID\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        enter(27);
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printf("\033[0m");
        timesleep(1, "FALSE");

        system("clear");
        loading(35);

        return EXIT_SUCCESS;
    }
    else
    {
        numof_trials++;

        if (numof_trials < 3)
        {
            printf("\033[1;33m-> ");
            printf("\033[0m");
            printf("\033[33mInvalid option. Please try again!");
            printf("\033[0m");
            enter(1);

            goto option;
        }
        else
        {
            printf("\033[33mInvalid option 3 times. Try again later! \nThe program will close in 3 seconds");
            printf("\033[0m");
            enter(1);

            timesleep(3, "FALSE");
            system("clear");

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}