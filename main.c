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

    int books_size = booklist_length();    // Menentukan ukuran buku
    int borrowed_size = borrowed_length(); // Menentukan ukuran buku yang dipinjam

    book data[64];   // Array untuk menyimpan data buku
    user onloan[32]; // Array untuk menyimpan data peminjam

    char account_id[128], password[128];        // Variabel untuk menyimpan ID dan kata sandi pengguna
    char account_file[128], password_file[128]; //  Variabel untuk menyimpan ID dan kata sandi dari file
    char win_linux[8], accounts[256];           // Variabel untuk sistem operasi dan akun
    char cmd_option[10];                        // Variabel untuk opsi perintah
    unsigned int book_id;                       // ID buku
    int temp_index;                             // Indeks sementara

    if (argc == 2)
    {
        strcpy(win_linux, argv[1]); // Mengatur sistem operasi
    }
    else
    {
        printf("Format: %s <WIN/LINUX> \n", argv[0]); // Menampilkan pesan kesalahan jika format argumen tidak sesuai
        return EXIT_FAILURE;
    }

    system_clear(win_linux); // Membersihkan layar
    loading(35, win_linux);  // Memuat tampilan loading

    welcome_screen(); // Menampilkan layar selamat datang

    timesleep(3, "FALSE", win_linux); // Menunggu beberapa detik
    system_clear(win_linux);          // Membersihkan layar

home:
    home_screen(); // Menampilkan layar utama

    int option = 0, numof_trials = 0; // Variabel untuk opsi dan jumlah percobaan

option:
    option_length(4); // Menentukan panjang opsi

    scanf("%d", &option); // Memasukkan opsi
    printf("\033[0m");    // Membersihkan terminal

    if (option == 1) // Jika opsi adalah 1 (masuk sebagai admin)
    {
        numof_trials = 0;

        system_clear(win_linux);
        loading(35, win_linux);

    admin_login:
        input_fp = fopen("admin.txt", "r"); // Membuka file admin.txt untuk login sebagai admin

        if (input_fp == NULL) // Jika file tidak ditemukan
        {
            printf("\033[33mError! file doesn't exist\n"); // Menampilkan pesan kesalahan

            return EXIT_FAILURE;
        }

        header(); // Menampilkan header

        // Menampilkan pesan untuk masuk sebagai admin
        printf("\033[1;33mAdmin log in \n");
        printf("\033[0m");
        printf("\033[33mAdmin ID\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        // Loop untuk membaca dan membandingkan ID admin dan password yang dimasukkan dengan yang ada dalam file
        while (fgets(accounts, sizeof(accounts), input_fp) != NULL)
        {
            sscanf(accounts, "\"%[^\"]\" \"%[^\"]\"", account_file, password_file);

            // Memeriksa apakah ID admin dan password yang dimasukkan cocok dengan yang ada dalam file
            if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        enter(28);                             // Memberi jarak setelah proses autentikasi admin
        hyphen("\033[1;33m", 130, 10, "TRUE"); // Membuat garis pemisah dengan panjang ddan warna tertentu
        printf("\033[0m");                     // Menampilkan pesan standar untuk kembali ke tampilan awal

        // Memeriksa apakah autentikasi admin berhasil
        if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
        {
            numof_trials = 0; // Mengatur jumlah percobaan kembali ke nol setelah berhasil masuk

            fclose(input_fp); // Menutup file yang digunakan untuk autentikasi

            system_clear(win_linux);
            loading(35, win_linux);

        admin_menu:
            header();

            admin_menu(); // Menampilkan menu admin
            enter(23);    // Memberi jarak setelah menu admin ditampilkan

            hyphen("\033[1;33m", 130, 10, "TRUE"); // Membuat garis pemisah setelah menu admin

        admin_option:
            // Menampilkan opsi admin dan mengambil pilihan dari admin
            option_length(6);

            scanf("%d", &option);
            printf("\033[0m");

            // Memeriksa pilihan admin
            if (option >= 1 && option <= 4)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                if (option == 1) // Opsi untuk menampilkan daftar buku
                {
                    // Reset jumlah percobaan dan ukuran buku
                    numof_trials = 0;
                    books_size = 0;

                    books_size = booklist_length(); // Mendapatkan jumlah buku yang tersedia

                    // Menampilkan header dan daftar buku
                    header();

                    books_available(data);

                    // Menampilkan daftar buku dalam tabel
                    printf("\033[1;33mBook list");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m");
                    table_border("TRUE");
                    printf("| %-5s | %-27s | %-27s | %-25s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Publisher", "Pages", "Year", "Available");
                    table_border("TRUE");
                    printf("\033[0m");

                    for (int index = 0; index < books_size; index++)
                    {
                        table_row(data, index);
                    }

                    table_border("TRUE");
                    printf("\033[0m");

                    // Memberikan opsi untuk kembali atau keluar
                    enter(29 - books_size - 4);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                // Menu untuk perintah setelah menampilkan daftar buku
                admin_cmd_option1:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0) // Memeriksa pilihan perintah
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home; // Kembali ke menu utama
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu; // Kembali ke menu admin
                    }
                    else
                    {
                        numof_trials++;

                        if (numof_trials < 3) // Memeriksa jumlah percobaan
                        {
                            // Jika pilihan tidak valid, berikan pesan dan beri kesempatan untuk memasukkan lagi
                            option_invalid();

                            goto admin_cmd_option1;
                        }
                        else
                        {
                            // Jika percobaan lebih dari 3, beri pesan dan keluar dari program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
                else if (option == 2) // Opsi untuk menambah buku
                {
                    // Mendeklarasikan variabel
                    unsigned int id;
                    char title[128];
                    char author[128];
                    char publisher[128];
                    unsigned int pages;
                    unsigned int pub_year;
                    unsigned int quantity;

                    // Reset jumlah percobaan dan ukuran buku
                    numof_trials = 0;
                    books_size = 0;

                // Menu untuk menambah buku
                add_books:
                    header();

                    // Meminta input atribut buku dari admin
                    printf("\033[1;33mAdd books");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33mBook ID\t\t: ");
                    scanf("%u", &id);
                    printf("\033[33mTitle\t\t: ");
                    scanf(" %[^\n]s", title);
                    printf("\033[33mAuthor\t\t: ");
                    scanf(" %[^\n]s", author);
                    printf("\033[33mPublisher\t: ");
                    scanf(" %[^\n]s", publisher);
                    printf("\033[33mNum. of pages\t: ");
                    scanf("%u", &pages);
                    printf("\033[33mPub. year\t: ");
                    scanf("%u", &pub_year);
                    printf("\033[33mQuantity\t: ");
                    scanf("%u", &quantity);
                    printf("\033[0m");
                    enter(1);

                    // Mendapatkan jumlah buku yang tersedia
                    books_size = booklist_length();
                    books_available(data);

                    // Memeriksa apakah buku dengan ID yang sama sudah ada
                    for (int index = 0; index < books_size; index++)
                    {
                        if (data[index].id == id)
                        {
                            // Jika buku dengan ID yang sama sudah ada, berikan pesan dan minta input lagi
                            book_status(win_linux, 3);

                            goto add_books;
                        }
                        else
                        {
                            if (index == (books_size - 1))
                            {
                                // Jika buku belum ada, tambahkan buku ke daftar
                                add_books(id, title, author, publisher, pages, pub_year, quantity, win_linux);

                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                // Menu untuk perintah selain menambah buku
                admin_cmd_option2:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0) // Memeriksa pilihan perintah
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home; // Kembali ke menu utama
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu; // Kembali ke menu admin
                    }
                    else
                    {
                        numof_trials++;

                        // Memeriksa jumlah percobaan
                        if (numof_trials < 3)
                        {
                            // Jika pilihan tidak valid, beri pesan dan beri kesempatan untuk memasukkan lagi
                            option_invalid();

                            goto admin_cmd_option2;
                        }
                        else
                        {
                            // Jika percobaan lebih dari 3, beri pesan dan keluar dari program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
                else if (option == 3) // Opsi untuk menghapus buku
                {
                    // Reset jumlah percobaan dan ukuran buku
                    numof_trials = 0;
                    books_size = 0;

                // Menu untuk menghapus buku
                delete_books:
                    header(); // Header dan judul untuk opsi penghapusan buku

                    printf("\033[1;33mDelete books");
                    printf("\033[0m");
                    enter(1);

                    // Mendapatkan jumlah buku yang tersedia dan menampilkannya
                    books_size = booklist_length();
                    books_available(data);

                    // Meminta admin untuk memasukkan ID buku yang ingin dihapus
                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    // Memeriksa apakah ID buku yang dimasukkan oleh admin ada dalam daftar buku
                    for (int index = 0; index < books_size; index++)
                    {
                        if (index == (books_size - 1))
                        {
                            // Jika ID buku tidak ditemukan, berikan pesan dan minta input lagi
                            if (data[index].id != book_id)
                            {
                                book_status(win_linux, 2);

                                goto delete_books;
                            }
                            else
                            {
                                // Jika ID ditemukan, panggil fungsi untuk menghapus buku
                                delete_books(data, book_id, books_size, win_linux);

                                break;
                            }
                        }
                        else
                        {
                            // Memeriksa setiap ID buku dalam daftar buku
                            if (data[index].id == book_id)
                            {
                                // Jika ID buku ditemukan, panggil fungsi untuk menghapus buku
                                delete_books(data, book_id, books_size, win_linux);

                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                    // Memberikan jarak setelah proses penghapusan buku dan membuat garis pemisah
                    enter(27);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                // Menu untuk perintah setelah menghapus buku
                admin_cmd_option3:
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0) // Memeriksa pilihan perintah
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home; // Kembali ke menu utama
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu; // Kembali ke menu admin
                    }
                    else
                    {
                        // Memeriksa jumlah percobaan
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            // Jika pilihan tidak valid, beri pesan dan beri kesempatan untuk memasukkan lagi
                            option_invalid();

                            goto admin_cmd_option3;
                        }
                        else
                        {
                            // Jika percobaan lebih dari 3, beri pesan dan keluar dari program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
                else
                {
                    // Reset jumlah percobaan dan ukuran buku
                    numof_trials = 0;
                    books_size = 0;

                // Menampilkan header dan judul untuk opsi modifikasi buku
                modify_books:
                    header();

                    printf("\033[1;33mModify books");
                    printf("\033[0m");
                    enter(1);

                    // Mendapatkan jumlah buku yang tesedia dan menampilkannya
                    books_size = booklist_length();
                    books_available(data);

                    // Meminta admin untuk memasukkan ID buku yang ingin dimodifikasi
                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    for (int index = 0; index < books_size; index++)
                    {
                        if (index == (books_size - 1))
                        {
                            // Jika ID buku tidak ditemukan, berikan pesan dan minta input lagi
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
                            // Memeriksa setiap ID buku dalam daftar buku
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

                    // Memberikan jeda sebelum menampilkan opsi modifikasi buku
                    timesleep(1, "FALSE", win_linux);

                    // Menampilkan opsi untuk memodifikasi buku
                    printf("\033[1;33mOption");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m1. Title\n");
                    printf("\033[33m2. Author\n");
                    printf("\033[33m3. Publisher\n");
                    printf("\033[33m4. Num. of pages\n");
                    printf("\033[33m5. Pub. year\n");
                    printf("\033[33m6. Quantity\n");
                    printf("\033[0m");

                    // Memberikan jarak setelah menampilkan opsi dan membuat garis pemisah
                    enter(21);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                modify_options:
                    // Menentukan panjang opsi modifikasi
                    option_length(6);

                    scanf("%d", &option);
                    printf("\033[0m");

                    system_clear(win_linux);
                    loading(35, win_linux);

                    // Memeriksa pilihan opsi modifikasi
                    if (option >= 1 && option <= 6)
                    {
                        // Memanggil fungsi untuk memodifikasi buku
                        modify_books(data, book_id, books_size, option, numof_trials);
                    }
                    else
                    {
                        // Jika pilihan tidak valid, tingkatkan jumlah percobaan
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            // Jiika percobaan masih kurang dari 3, beri pesan dan minta input lagi
                            option_invalid();

                            goto modify_options;
                        }
                        else
                        {
                            // Jika percobaan lebih dari 3, beri pesan dan keluar dari program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }

                    // Memberikan jeda setelah proses modifikasi buku dan menampilkan pesan sukses
                    timesleep(1, "FALSE", win_linux);

                    printf("\033[33mBook successfully modified!");
                    printf("\033[0m");

                    // Memberikan jarak setelah pesan sukses dan membuat garis pemisah
                    enter(27);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                admin_cmd_option4:
                    // Menu untuk perintah setelah memodifikasi buku
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0) // Memeriksa pilihan perintah
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home; // Kembali ke menu utama
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto admin_menu; // Kembali ke menu admin
                    }
                    else
                    {
                        // Memeriksa jumlah percobaan
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            // Jika pilihan tidak valid, beri pesan dan beri kesempatan untuk memasukkan lagi
                            option_invalid();

                            goto admin_cmd_option4;
                        }
                        else
                        {
                            // Jika percobaan lebih dari 3 , beri pesan dan keluar dari program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
            }
            else if (option == 5) // Opsi untuk kembali ke menu utama
            {
                system_clear(win_linux);
                loading(35, win_linux);

                goto home;
            }
            else if (option == 6) // Opsi untuk keluar dari program
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
                // Jika pilihan tidak valid, tingkatkan jumlah percobaan
                numof_trials++;

                if (numof_trials < 3)
                {
                    // Jika percobaan masih kurang dari 3, beri pesan dan minta input lagi
                    option_invalid();

                    goto admin_option;
                }
                else
                {
                    // Jika percobaan lebih dari 3, beri pesan dan keluar dari program
                    option_end();

                    timesleep(3, "FALSE", win_linux);
                    system_clear(win_linux);

                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
            // Jika opsi yang dimasukkan tidak valid, jumlah percobaan ditingkatkan
            numof_trials++;

            fclose(input_fp);

            system_clear(win_linux);

            // Jika percobaan masih kurang dari 3
            if (numof_trials < 3)
            {
                // Menampilkan pesan kesalahan login
                login_invalid();

                // Jeda selama 2 detik sebelum membersihkan layar dan kembali ke proses login
                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                goto admin_login;
            }
            else
            {
                // Jika percobaan sudah lebih dari 3, menampilkan pesan akhir
                loading(35, win_linux);

                login_end();

                // Jeda selama 3 detik sebelum membersihkan layar dan keluar dari program
                timesleep(3, "FALSE", win_linux);
                system_clear(win_linux);

                return EXIT_FAILURE;
            }
        }
    }
    else if (option == 2)
    {
        // Jika pengguna memilih opsi 2, menginisialisasi ulang jumlah percobaan dan membersihkan layar
        numof_trials = 0;

        system_clear(win_linux);
        loading(35, win_linux);

    user_login:
        // Membuka file users.txt untuk dibaca
        input_fp = fopen("users.txt", "r");

        // Memeriksa apakah file berhasil dibuka
        if (input_fp == NULL)
        {
            // Jika file tidak dapat dibuka , menampilkan pesan kesalahan
            printf("\033[33mError! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        // Menampilkan header dan pesan login untuk pengguna
        header();

        printf("\033[1;33mUser log in \n");
        printf("\033[0m");
        printf("\033[33mUser ID\t\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        // Membaca baris-baris dari file dan memeriksa akun pengguna
        while (fgets(accounts, sizeof(accounts), input_fp) != NULL)
        {
            sscanf(accounts, "\"%[^\"]\" \"%[^\"]\"", account_file, password_file);

            // Memeriksa apakah akun dan kata sandi yang dimasukkan sesuai dengan yang ada di file
            if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
            {
                // Jika cocok, keluar dari loop
                break;
            }
            else
            {
                // Jika tidak cocok, lanjut ke baris berikutnya
                continue;
            }
        }

        // Memberikan jarak sebelum menampilkan garis pemisah
        enter(28);
        hyphen("\033[1;33m", 130, 10, "TRUE");
        printf("\033[0m");

        // Memeriksa apakah akun yang dimasukkan sesuai dengan yang ada di file
        if (strcmp(account_id, account_file) == 0 && strcmp(password, password_file) == 0)
        {
            // Jika sesuai, menginisialisasi ulang jumlah percobaan, menutup file, membersihkan layar, dan menampilkan tampilan loading
            numof_trials = 0;

            fclose(input_fp);

            system_clear(win_linux);
            loading(35, win_linux);

        user_menu:
            // Menampilkan header dan menu pengguna
            header();

            user_menu();
            enter(23);

            hyphen("\033[1;33m", 130, 10, "TRUE");

        user_option:
            option_length(6); // Menentukan panjang opsi

            // Membaca opsi yang dimasukkan pengguna
            scanf("%d", &option);
            printf("\033[0m");

            // Memeriksa apakah opsi yang dimasukan berada dalam rentang yang valid
            if (option >= 1 && option <= 4)
            {
                system_clear(win_linux);
                loading(35, win_linux);

                if (option == 1)
                {
                    // Inisialisasi ulang jumlah percobaan dan variabel yang berhubungan dengan buku
                    numof_trials = 0;
                    books_size = 0;

                    // Mendapatkan jumlah buku yang tersedia dan menampilkannya
                    books_size = booklist_length();

                    header();

                    books_available(data);

                    printf("\033[1;33mBooks available");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33m");
                    table_border("TRUE");
                    printf("| %-5s | %-27s | %-27s | %-25s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Publisher", "Pages", "Year", "Available");
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
                    // Mengatur input dan aksi dari pengguna
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home; // Kembali ke menu utama
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu; // Kembali ke menu user
                    }
                    else
                    {
                        // Menangani input yang tidak valid
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option1;
                        }
                        else
                        {
                            // Jika percobaan melebihi batas, menampilkan pesan dan mengakhiri programnya
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
                else if (option == 2)
                {
                    // Inisialisasi ulang jumlah percobaan dan variabel yang berhubungan dengan buku
                    numof_trials = 0;
                    books_size = 0;
                    borrowed_size = 0;

                    // Mendapatkan jumlah buku yang tersedia dan dipinjam oleh user, serta menampilkan daftar pinjaman
                    books_size = booklist_length();
                    books_available(data);

                    borrowed_size = borrowed_length();
                    user_loans(onloan);

                borrow_books:
                    // Menampilkan header dan menu peminjaman buku
                    header();

                    printf("\033[1;33mBorrow books");
                    printf("\033[0m");
                    enter(1);

                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    // Memeriksa apakah buku sudah dipinjam oleh user atau tidak
                    for (int index = 0; index < borrowed_size; index++)
                    {
                        if (index < (borrowed_size - 1))
                        {
                            if ((strcmp(onloan[index].username, account_id) == 0) && (onloan[index].book_id == book_id))
                            {
                                // Jika sudah dipinjam, menampilkan pesan dan meminta input lagi
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
                                // Jika sudah dipinjam, menampilkan pesan dan meminta input lagi
                                book_status(win_linux, 1);

                                goto borrow_books;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    // Memeriksa apakah buku tersedia untuk dipinjam
                    for (int index = 0; index < books_size; index++)
                    {
                        if (data[index].id == book_id)
                        {
                            if (data[index].available == 0)
                            {
                                // Jika tidak tersedia, menampilkan pesan dan meminta input lagi
                                book_status(win_linux, 2);

                                goto borrow_books;
                            }
                            else
                            {
                                // Jika tersedia, mengurangi jumlah buku yang tersedia dan menampilkan pesan sukses
                                --(data[index].available);
                                temp_index = index;

                                timesleep(1, "TRUE", win_linux);

                                printf("\033[33mBook successfully borrowed!");
                                printf("\033[0m");
                                enter(1);

                                break;
                            }
                        }
                        else if ((index == (books_size - 1)) && (data[index].id != book_id))
                        {
                            // Jika buku tidak ditemukan, menampilkan pesan dan meminta input lagi
                            book_status(win_linux, 2);

                            goto borrow_books;
                        }
                        else
                        {
                            continue;
                        }
                    }

                    // Menampilkan daftar buku yang baru dipinjam
                    enter(26);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                    print_newlist(data, account_id, books_size, temp_index);

                user_cmd_option2:
                    // Mengatur input dan aksi dari pengguna setelah peminjaman buku
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        // Kembali ke menu utama
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        // Kembali ke menu pengguna
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        // Mengatur input yang tidak valid
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option2;
                        }
                        else
                        {
                            // Jika percobaan melebihi batas, menampilkan pesan dan mengakhiri program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
                else if (option == 3)
                {
                    // Reset jumlah percobaan dan ukuran daftar buku serta daftar buku yang dipinjam
                    numof_trials = 0;
                    books_size = 0;
                    borrowed_size = 0;

                    // Mengambil ukuran daftar buku yang tersedia dan daftar buku yang dipinjam
                    books_size = booklist_length();
                    books_available(data);

                    borrowed_size = borrowed_length();
                    user_loans(onloan);

                    // Menampilkan header
                    header();

                    printf("\033[1;33mOn loan (%s)", account_id);
                    printf("\033[0m");
                    enter(1);

                    // Menampilkan daftar buku yang sedang dipinjam oleh pengguna
                    printf("\033[33m");
                    table_border("TRUE");
                    printf("| %-5s | %-27s | %-27s | %-25s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Publisher", "Pages", "Year", "Quantity");
                    table_border("TRUE");
                    printf("\033[0m");

                    // Menampilkan detail setiap buku yang dipinjam
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

                    // Menghitung jumlah ruang kosong untuk keseimbangan tata letak
                    int free_space = borrowed_size * 2;

                    enter(35 - free_space - 9);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                user_cmd_option3:
                    // Mengatur input dan aksi dari pengguna setelah menampilkan daftar buku yang dipinjam
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        // Kembali ke menu utama
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        // Kembali ke menu user
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        // Mengatur input yang tidak valid
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option3;
                        }
                        else
                        {
                            // Jika percobaan melebihi batas, menampilkan pesan dan mengakhiri program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
                else
                {
                    // Jika opsi yang dimasukkan tidak valid, reset jumlah percobaan dan ukuran daftar bukku serta daftar buku yang dipinjam
                    numof_trials = 0;
                    books_size = 0;
                    borrowed_size = 0;

                    // Mengambil ukuran daftar buku yang tersedia dan daftar buku yang dipinjam
                    books_size = booklist_length();
                    books_available(data);

                    borrowed_size = borrowed_length();
                    user_loans(onloan);

                return_books:
                    // Menampilkan header untuk menu pengembalian buku
                    header();

                    printf("\033[1;33mReturn books");
                    printf("\033[0m");
                    enter(1);

                    // Meminta pengguna untuk memasukkan ID buku yang akan dikemablikan
                    printf("\033[33mEnter book ID: ");
                    scanf("%u", &book_id);
                    enter(1);
                    printf("\033[0m");

                    // Mengecek apakah pengguna memeiliki buyku yang sedang dipinjam
                    for (int index = 0; index < borrowed_size; index++)
                    {
                        if (index == (borrowed_size - 1))
                        {
                            if ((strcmp(onloan[index].username, account_id) == 0) && (onloan[index].book_id != book_id))
                            {
                                // Menampilkan pesan jika buku tidak ditemukan dalam daftar yang sedang dipinjam
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

                    // Mencari buku yang akan dikemablikan dalam daftar buku yang tersedia
                    for (int index = 0; index < books_size; index++)
                    {
                        if (data[index].id == book_id)
                        {
                            // Menampilkan pesan bahwa buku berhasil dikembalikan dan meningkatkan jumlah buku yang tersedia
                            timesleep(1, "TRUE", win_linux);

                            printf("\033[33mBook successfully returned!");
                            printf("\033[0m");
                            enter(1);

                            data[index].available++;
                        }
                    }

                    // Menampilkan daftar buku yang tersedia seteleha pengembalian
                    print_books(data, books_size);
                    // Memperbarui daftar peminjaman setelah pengembalian
                    print_loans(onloan, borrowed_size, book_id);

                    // Menambahkan spasi dan garis pemisah
                    enter(26);
                    hyphen("\033[1;33m", 130, 10, "TRUE");

                user_cmd_option4:
                    // Mengatur input dan aksi dari pengguna setelah melakukan pengembalian buku
                    home_escape();

                    scanf("%s", cmd_option);
                    printf("\033[0m");

                    if (strcmp(cmd_option, "HOME") == 0)
                    {
                        // Kembali ke menu utama
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto home;
                    }
                    else if (strcmp(cmd_option, "ESCAPE") == 0)
                    {
                        // Kembali ke menu user
                        system_clear(win_linux);
                        loading(35, win_linux);

                        goto user_menu;
                    }
                    else
                    {
                        // Mengatur input yang tidak valid
                        numof_trials++;

                        if (numof_trials < 3)
                        {
                            option_invalid();

                            goto user_cmd_option4;
                        }
                        else
                        {
                            // Jika percobaan melebihi batas, menampilkan pesan dan mengakhiri program
                            option_end();

                            timesleep(3, "FALSE", win_linux);
                            system_clear(win_linux);

                            return EXIT_FAILURE;
                        }
                    }
                }
            }
            else if (option == 5) // Opsi untuk kembali ke menu utama
            {
                system_clear(win_linux);
                loading(35, win_linux);

                goto home;
            }
            else if (option == 6) // Opsi untuk mengakhiri program
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
                // Mengatur opsi yang tidak valid
                numof_trials++;

                if (numof_trials < 3)
                {
                    option_invalid();

                    goto user_option;
                }
                else
                {
                    // Jika percobaan melebihi batas, menampilkan pesan dan mengakhiri program
                    option_end();

                    timesleep(3, "FALSE", win_linux);
                    system_clear(win_linux);

                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
            // Mengatur jika opsi tidak valid
            numof_trials++;

            fclose(input_fp);

            system_clear(win_linux);

            if (numof_trials < 3)
            {
                // Menampilkan pesan bahwa login tidak valid dan meminta masukan kembali
                login_invalid();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                goto user_login;
            }
            else
            {
                // Jika percobaan melebihi batas, menampilkan pesan dan mengakhiri program
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
        // Reset nilai percobaan dan menampilkan menu utama
        int indicator;
        numof_trials = 0;

        system_clear(win_linux);
        loading(35, win_linux);

    create_account:
        // Membuka file untuk dibaca
        input_fp = fopen("users.txt", "r");

        // Memeriksa apakah file berhasil dibuka
        if (input_fp == NULL)
        {
            // Menampilkan pesan error jika file tidak dapat dibuka
            printf("\033[33mError! file doesn't exist\n");

            return EXIT_FAILURE;
        }

        // Menampilkan header dan meminta input ID pengguna dan kata sandi baru
        header();

        printf("\033[1;33mCreate new account (User)\n");
        printf("\033[0m");
        printf("\033[33mUser ID\t\t: ");
        scanf("%s", account_id);
        printf("\033[33mPassword\t: ");
        scanf("%s", password);

        // Membaca setiap baris dari file pengguna
        while (fgets(accounts, sizeof(accounts), input_fp) != NULL)
        {
            sscanf(accounts, "\"%[^\"]\" \"%[^\"]\"", account_file, password_file);

            // Memeriksa apakah ID pengguna sudah ada dalam file
            if (strcmp(account_id, account_file) == 0)
            {
                // Jika ID pengguna sudah ada, indikator menjadi 1 dan hentikan pencarian
                indicator = 1;

                break;
            }
            else
            {
                // Jika ID pengguna belum ada, indikator menjadi 0 dan lanjutkan pencarian
                indicator = 0;

                continue;
            }
        }

        // Memeriksa nilai indikator
        if (indicator != 1)
        {
            // Jika ID pengguna belum ada dalam file
            fclose(input_fp);

            // Membuka file untuk menulis dan menambahkan ID pengguna baru
            output_fp = fopen("users.txt", "a");

            fprintf(output_fp, "\n\"%s\" \"%s\"", account_id, password);

            fclose(output_fp);

            // Membersihkan layar, menampilkan pesan sukses, dan kembali ke menu utama
            system_clear(win_linux);
            loading(35, win_linux);
            newacc_success();

            timesleep(2, "FALSE", win_linux);
            system_clear(win_linux);

            goto home;
        }
        else
        {
            // Jika ID pengguna sudah ada dalam file
            numof_trials++;

            fclose(input_fp);

            system_clear(win_linux);

            if (numof_trials < 3)
            {
                // Menampilkan pesan kesalahan dan meminta input baru jika percobaan masih dalam batas
                newacc_invalid();

                timesleep(2, "FALSE", win_linux);
                system_clear(win_linux);

                goto create_account;
            }
            else
            {
                // Menampilkan pesan bahwa pembuatan akun baru gagal dan mengakhiri program
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
        // Membersihkan layar, menampilkan layar selamat tinggal, dan keluar dari program
        system_clear(win_linux);
        loading(35, win_linux);

        goodbye_screen();

        timesleep(2, "FALSE", win_linux);
        system_clear(win_linux);

        return EXIT_SUCCESS;
    }
    else
    {
        // Jika opsi tidak valid, menambah jumlah percobaan dan memeriksa jumlah percobaan
        numof_trials++;

        if (numof_trials < 3)
        {
            // Jika jumlah percobaan masih dalam batas, menampilkan pesan kesalahan dan kembali ke opsi
            option_invalid();

            goto option;
        }
        else
        {
            // Jika jumlah percobaan sudah melewati batas, menampilkan pesan akhir dan keluar dari program
            option_end();

            timesleep(3, "FALSE", win_linux);
            system_clear(win_linux);

            return EXIT_FAILURE;
        }
    }

    // Menutup file input dan output
    fclose(input_fp);
    fclose(output_fp);

    return EXIT_SUCCESS;
}
