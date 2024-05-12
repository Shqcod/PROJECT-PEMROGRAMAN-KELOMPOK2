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

    int books_size = booklist_length();
    int borrowed_size = borrowed_length();

    book data[64];
    user onloan[32];

    char account_id[128], password[128];
    char account_file[128], password_file[128];
    char win_linux[8], accounts[256];
    char cmd_option[10];
    unsigned int book_id;
    int temp_index;

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
    loading(35, win_linux);

    welcome_screen();

    timesleep(3, "FALSE", win_linux);
    system_clear(win_linux);

home:
    home_screen();

    int option = 0, numof_trials = 0;

option:
    option_length(4);

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
            printf("\033[33mError! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        header();

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

        admin_menu:
            header();

            admin_menu();
            enter(23);

            hyphen("\033[1;33m", 130, 10, "TRUE");

        admin_option:
            option_length(6);

            scanf("%d", &option);
            printf("\033[0m");

            if (option >= 1 && option <= 4)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                if (option == 1)
                {
                    numof_trials = 0;
                    books_size = 0;

                    books_size = booklist_length();

                    header();

                    books_available(data);

                    printf("\033[1;33mBook list");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m");
                    table_border("TRUE");
                    printf("| %-5s | %-47s | %-35s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Pages", "Year", "Available");
                    table_border("TRUE");
                    printf("\033[0m");

                    for (int index = 0; index < books_size; index++)
                    {
                        table_row(data, index);
                    }

                    table_border("TRUE");
                    printf("\033[0m");

                    enter(29 - books_size - 4);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                admin_cmd_option1:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto admin_cmd_option1;
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
                else if (option == 2)
                {
                    unsigned int id;
                    char title[128];
                    char author[128];
                    unsigned int pages;
                    unsigned int pub_year;
                    unsigned int quantity;

                    numof_trials = 0;
                    books_size = 0;

                add_books:
                    header();

                    printf("\033[1;33mAdd books");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33mBook ID\t\t: ");
                    scanf("%u", &id);
                    printf("\033[33mTitle\t\t: ");
                    scanf(" %[^\n]s", title);
                    printf("\033[33mAuthor\t\t: ");
                    scanf(" %[^\n]s", author);
                    printf("\033[33mNum. of pages\t: ");
                    scanf("%u", &pages);
                    printf("\033[33mPub. year\t: ");
                    scanf("%u", &pub_year);
                    printf("\033[33mQuantity\t: ");
                    scanf("%u", &quantity);
                    printf("\033[0m");
                    enter(1);

                    books_size = booklist_length();
                    books_available(data);

                    for (int index = 0; index < books_size; index++)
                    {
                        if (data[index].id == id)
                        {
                            book_status(win_linux, 3);

                            goto add_books;
                        }
                        else
                        {
                            if (index == (books_size - 1))
                            {
                                add_books(id, title, author, pages, pub_year, quantity, win_linux);

                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                admin_cmd_option2:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto admin_cmd_option2;
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
                else if (option == 3)
                {
                    numof_trials = 0;
                    books_size = 0;

                delete_books:
                    header();

                    printf("\033[1;33mDelete books");
                    printf("\033[0m");
                    enter(1);

                    books_size = booklist_length();
                    books_available(data);

                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    for (int index = 0; index < books_size; index++)
                    {
                        if (index == (books_size - 1))
                        {
                            if (data[index].id != book_id)
                            {
                                book_status(win_linux, 2);

                                goto delete_books;
                            }
                            else
                            {
                                delete_books(data, book_id, books_size, win_linux);

                                break;
                            }
                        }
                        else
                        {
                            if (data[index].id == book_id)
                            {
                                delete_books(data, book_id, books_size, win_linux);

                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                    enter(27);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                admin_cmd_option3:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto admin_cmd_option3;
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
                    numof_trials = 0;
                    books_size = 0;

                modify_books:
                    header();

                    printf("\033[1;33mModify books");
                    printf("\033[0m");
                    enter(1);

                    books_size = booklist_length();
                    books_available(data);

                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    for (int index = 0; index < books_size; index++)
                    {
                        if (index == (books_size - 1))
                        {
                            if (data[index].id != book_id)
                            {
                                book_status(win_linux, 2);

                                goto modify_books;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            if (data[index].id == book_id)
                            {
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                    timesleep(1, "FALSE", win_linux);

                    printf("\033[1;33mOption");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m1. Title\n");
                    printf("\033[33m2. Author\n");
                    printf("\033[33m3. Num. of pages\n");
                    printf("\033[33m4. Pub. year\n");
                    printf("\033[33m5. Quantity\n");
                    printf("\033[0m");

                    enter(21);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                modify_options:
                    option_length(5);

                    scanf("%d", &option);
                    printf("\033[0m");

                    system_clear(win_linux);
                    loading(35, win_linux);

                    if (option >= 1 && option <= 5)
                    {
                        modify_books(data, book_id, books_size, option, numof_trials);
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto modify_options;
                        }
                        else
                        {
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }

                    timesleep(1, "FALSE", win_linux);

                    printf("\033[33mBook modified successfully!");
                    printf("\033[0m");

                    enter(27);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                admin_cmd_option4:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto admin_cmd_option4;
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
            printf("\033[33mError! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        header();

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

            system_clear(win_linux);
            loading(35, win_linux);

        user_menu:
            header();

            user_menu();
            enter(23);

            hyphen("\033[1;33m", 130, 10, "TRUE");

        user_option:
            option_length(6);

            scanf("%d", &option);
            printf("\033[0m");

            if (option >= 1 && option <= 4)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                if (option == 1)
                {
                    numof_trials = 0;
                    books_size = 0;

                    books_size = booklist_length();

                    header();

                    books_available(data);

                    printf("\033[1;33mBooks available");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m");
                    table_border("TRUE");
                    printf("| %-5s | %-47s | %-35s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Pages", "Year", "Available");
                    table_border("TRUE");
                    printf("\033[0m");

                    for (int index = 0; index < books_size; index++)
                    {
                        table_row(data, index);
                    }

                    table_border("TRUE");
                    printf("\033[0m");

                    enter(29 - books_size - 4);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                user_cmd_option1:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option1;
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
                else if (option == 2)
                {
                    numof_trials = 0;
                    books_size = 0;
                    borrowed_size = 0;

                    books_size = booklist_length();
                    books_available(data);

                    borrowed_size = borrowed_length();
                    user_loans(onloan);

                borrow_books:
                    header();

                    printf("\033[1;33mBorrow books");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    for (int index = 0; index < borrowed_size; index++)
                    {
                        if (index < (borrowed_size - 1))
                        {
                            if ((strcmp(onloan[index].username, account_id) == 0) && (onloan[index].book_id == book_id))
                            {
                                book_status(win_linux, 1);

                                goto borrow_books;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else
                        {
                            if ((strcmp(onloan[index].username, account_id) == 0) && (onloan[index].book_id == book_id))
                            {
                                book_status(win_linux, 1);

                                goto borrow_books;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    for (int index = 0; index < books_size; index++)
                    {
                        if (data[index].id == book_id)
                        {
                            if (data[index].available == 0)
                            {
                                book_status(win_linux, 2);

                                goto borrow_books;
                            }
                            else
                            {
                                --(data[index].available);
                                temp_index = index;

                                timesleep(1, "TRUE", win_linux);

                                printf("\033[33mBook borrowing successful!");
                                printf("\033[0m");
                                enter(1);

                                break;
                            }
                        }
                        else if ((index == (books_size - 1)) && (data[index].id != book_id))
                        {
                            book_status(win_linux, 2);

                            goto borrow_books;
                        }
                        else
                        {
                            continue;
                        }
                    }

                    enter(26);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                    print_newlist(data, account_id, books_size, temp_index);

                user_cmd_option2:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option2;
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
                else if (option == 3)
                {
                    numof_trials = 0;
                    books_size = 0;
                    borrowed_size = 0;

                    books_size = booklist_length();
                    books_available(data);

                    borrowed_size = borrowed_length();
                    user_loans(onloan);

                    printf("%d", borrowed_size);

                    header();

                    printf("\033[1;33mOn loan (%s)", account_id);
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m");
                    table_border("TRUE");
                    printf("| %-5s | %-47s | %-35s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Pages", "Year", "Quantity");
                    table_border("TRUE");
                    printf("\033[0m");

                    for (int onloan_index = 0; onloan_index < borrowed_size; onloan_index++)
                    {
                        for (int books_index = 0; books_index < books_size; books_index++)
                        {
                            if (onloan[onloan_index].book_id == data[books_index].id)
                            {
                                onloan_table_row(data, books_index);

                                table_border("TRUE");
                                printf("\033[0m");
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                    int free_space = borrowed_size * 2;

                    enter(35 - free_space - 9);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                user_cmd_option3:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option3;
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
                    numof_trials = 0;
                    books_size = 0;
                    borrowed_size = 0;

                    books_size = booklist_length();
                    books_available(data);

                    borrowed_size = borrowed_length();
                    user_loans(onloan);

                return_books:
                    header();

                    printf("\033[1;33mReturn books");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    for (int index = 0; index < borrowed_size; index++)
                    {
                        if (index == (borrowed_size - 1))
                        {
                            if ((strcmp(onloan[index].username, account_id) == 0) && (onloan[index].book_id != book_id))
                            {
                                book_status(win_linux, 2);

                                goto return_books;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            if ((strcmp(onloan[index].username, account_id) == 0) && (onloan[index].book_id == book_id))
                            {
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                    for (int index = 0; index < books_size; index++)
                    {
                        if (data[index].id == book_id)
                        {
                            timesleep(1, "TRUE", win_linux);

                            printf("\033[33mBook returning successful!");
                            printf("\033[0m");
                            enter(1);

                            data[index].available++;
                        }
                    }

                    print_books(data, books_size);
                    print_loans(onloan, borrowed_size, book_id);

                    enter(26);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                user_cmd_option4:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option4;
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
    }
    else if (option == 3)
    {
        int indicator;
        numof_trials = 0;

        system_clear(win_linux);
        loading(35, win_linux);

    create_account:
        input_fp = fopen("users.txt", "r");

        if (input_fp == NULL)
        {
            printf("\033[33mError! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        header();

        printf("\033[1;33mCreate new account (User)\n");
        printf("\033[0m");
        printf("\033[33mUser ID\t\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        while (fgets(accounts, sizeof(accounts), input_fp) != NULL)
        {
            sscanf(accounts, "\"%[^\"]\" \"%[^\"]\"", account_file, password_file);

            if (strcmp(account_id, account_file) == 0)
            {
                indicator = 1;

                break;
            }
            else
            {
                indicator = 0;

                continue;
            }
        }

        if (indicator != 1)
        {
            fclose(input_fp);

            output_fp = fopen("users.txt", "a");

            fprintf(output_fp, "\n\"%s\" \"%s\"", account_id, password);

            fclose(output_fp);

            system_clear(win_linux);
            loading(35, win_linux);
            newacc_success();

            timesleep(2, "FALSE", win_linux);
            system_clear(win_linux);

            goto home;
        }
        else
        {
            numof_trials++;

            fclose(input_fp);

            system_clear(win_linux);

            if (numof_trials < 3)
            {
                newacc_invalid();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                goto create_account;
            }
            else
            {
                loading(35, win_linux);

                newacc_end();

                timesleep(3, "FALSE", win_linux);
                system_clear(win_linux);

                return EXIT_FAILURE;
            }
        }
    }
    else if (option == 4)
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

    fclose(input_fp);
    fclose(output_fp);

    return EXIT_SUCCESS;
}