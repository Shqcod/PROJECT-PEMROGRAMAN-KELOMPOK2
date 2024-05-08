// import header.h
#include "header.h"

// main function
int main(int argc, char *argv[])
{
    /* Resolution:
    width: 140
    height: 35
    ratio: 1:4 */

    FILE *input_fp, *output_fp;

    int size = books_size();

    book data[size];
    char account_id[128], password[128];
    char account_file[128], password_file[128];
    char win_linux[8], accounts[256];

    if (argc == 2)
    {
        strcpy(win_linux, argv[1]);
    }
    else
    {
        printf("Format: %s <WIN/LINUX> \n", argv[0]);
        return EXIT_FAILURE;
    }

    system_clear(win_linux);
    // books_available(data);
    // book_list(data, size);
    loading(35, win_linux);

    welcome_screen();

    timesleep(3, "FALSE", win_linux);
    system_clear(win_linux);

home:
    home_screen();

    int option = 0, numof_trials = 0;

option:
    printf("\033[1;30;43m[1/2/3]");
    printf("\033[0m");
    printf("\033[33m: ");
    scanf("%d", &option);
    printf("\033[0m");

    if (option == 1)
    {
        numof_trials = 0;

        system_clear(win_linux);
        loading(35, win_linux);

    admin_login:
        input_fp = fopen("admin.txt", "r");

        if (input_fp == NULL)
        {
            printf("Error! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        hyphen("\033[1;33m", 130, 10, "TRUE");
        printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
        hyphen("\033[1;33m", 130, 10, "TRUE");

        printf("\033[1;33mAdmin log in \n");
        printf("\033[0m");
        printf("\033[33mAdmin ID\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        while (fgets(accounts, sizeof(accounts), input_fp) != NULL)
        {
            sscanf(accounts, "\"%[^\"]\" \"%[^\"]\"", account_file, password_file);

            if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        enter(28);
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printf("\033[0m");

        if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
        {
            numof_trials = 0;

            fclose(input_fp);

            system_clear(win_linux);
            loading(35, win_linux);

            hyphen("\033[1;33m", 130, 10, "TRUE");
            printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
            hyphen("\033[1;33m", 130, 10, "TRUE");

            admin_menu();
            enter(25);

            hyphen("\033[1;33m", 130, 10, "TRUE");

        admin_option:
            printf("\033[1;30;43m[1/2/3/4/5]");
            printf("\033[0m");
            printf("\033[33m: ");
            scanf("%d", &option);
            printf("\033[0m");

            if (option >= 1 && option <= 3)
            {
                numof_trials = 0;

                system_clear(win_linux);
                loading(35, win_linux);

                return EXIT_SUCCESS;
            }
            else if (option == 4)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                goto home;
            }
            else if (option == 5)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                goodbye_screen();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                return EXIT_SUCCESS;
            }
            else
            {
                numof_trials++;

                if (numof_trials < 3)
                {
                    option_invalid();

                    goto admin_option;
                }
                else
                {
                    option_end();

                    timesleep(3, "FALSE", win_linux);
                    system_clear(win_linux);

                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
            numof_trials++;

            fclose(input_fp);

            system_clear(win_linux);

            if (numof_trials < 3)
            {
                login_invalid();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                goto admin_login;
            }
            else
            {
                loading(35, win_linux);

                login_end();

                timesleep(3, "FALSE", win_linux);
                system_clear(win_linux);

                return EXIT_FAILURE;
            }
        }

        return EXIT_SUCCESS;
    }
    else if (option == 2)
    {
        numof_trials = 0;

        system_clear(win_linux);
        loading(35, win_linux);

    user_login:
        input_fp = fopen("users.txt", "r");

        if (input_fp == NULL)
        {
            printf("Error! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        hyphen("\033[1;33m", 130, 10, "TRUE");
        printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
        hyphen("\033[1;33m", 130, 10, "TRUE");

        printf("\033[1;33mUser log in \n");
        printf("\033[0m");
        printf("\033[33mUser ID\t\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        while (fgets(accounts, sizeof(accounts), input_fp) != NULL)
        {
            sscanf(accounts, "\"%[^\"]\" \"%[^\"]\"", account_file, password_file);

            if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        enter(28);
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printf("\033[0m");

        if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
        {
            numof_trials = 0;

            fclose(input_fp);

            input_fp = fopen("books.txt", "r");

            system_clear(win_linux);
            loading(35, win_linux);

            hyphen("\033[1;33m", 130, 10, "TRUE");
            printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
            hyphen("\033[1;33m", 130, 10, "TRUE");

            user_menu();
            enter(24);

            hyphen("\033[1;33m", 130, 10, "TRUE");

        user_option:
            printf("\033[1;30;43m[1/2/3/4/5/6]");
            printf("\033[0m");
            printf("\033[33m: ");
            scanf("%d", &option);
            printf("\033[0m");

            if (option >= 1 && option <= 4)
            {
                numof_trials = 0;

                system_clear(win_linux);
                loading(35, win_linux);

                if (option == 1)
                {
                    hyphen("\033[1;33m", 130, 10, "TRUE");
                    printin_center("%*s", "\033[1;30;43m+[ E-LIBRARY ]+", 130, 10, "TRUE");
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                    books_available(data);

                    printf("\033[33m");
                    book_list(data, size);

                    enter(10);
                    hyphen("\033[1;33m", 130, 10, "TRUE");
                }
            }
            else if (option == 5)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                goto home;
            }
            else if (option == 6)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                goodbye_screen();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                return EXIT_SUCCESS;
            }
            else
            {
                numof_trials++;

                if (numof_trials < 3)
                {
                    option_invalid();

                    goto user_option;
                }
                else
                {
                    option_end();

                    timesleep(3, "FALSE", win_linux);
                    system_clear(win_linux);

                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
            numof_trials++;

            fclose(input_fp);

            system_clear(win_linux);

            if (numof_trials < 3)
            {
                login_invalid();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                goto user_login;
            }
            else
            {
                loading(35, win_linux);

                login_end();

                timesleep(3, "FALSE", win_linux);
                system_clear(win_linux);

                return EXIT_FAILURE;
            }
        }

        return EXIT_SUCCESS;
    }
    else if (option == 3)
    {
        system_clear(win_linux);
        loading(35, win_linux);

        goodbye_screen();

        timesleep(2, "FALSE", win_linux);
        system_clear(win_linux);

        return EXIT_SUCCESS;
    }
    else
    {
        numof_trials++;

        if (numof_trials < 3)
        {
            option_invalid();

            goto option;
        }
        else
        {
            option_end();

            timesleep(3, "FALSE", win_linux);
            system_clear(win_linux);

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
