// import header.h
#include "header.h"

/* Regular colors
\e[0;30m 	Black
\e[0;31m 	Red
\e[0;32m 	Green
\e[0;33m 	Yellow
\e[0;34m 	Blue
\e[0;35m 	Purple
\e[0;36m 	Cyan
\e[0;37m 	White */

/* Bold colors
\e[1;30m 	Black
\e[1;31m 	Red
\e[1;32m 	Green
\e[1;33m 	Yellow
\e[1;34m 	Blue
\e[1;35m 	Purple
\e[1;36m 	Cyan
\e[1;37m 	White */

/* Underline colors
\e[4;30m 	Black
\e[4;31m 	Red
\e[4;32m 	Green
\e[4;33m 	Yellow
\e[4;34m 	Blue
\e[4;35m 	Purple
\e[4;36m 	Cyan
\e[4;37m 	White */

/* Background colors
\e[40m 	Black
\e[41m 	Red
\e[42m 	Green
\e[43m 	Yellow
\e[44m 	Blue
\e[45m 	Purple
\e[46m 	Cyan
\e[47m 	White */

/* High intensity colors
\e[0;90m 	Black
\e[0;91m 	Red
\e[0;92m 	Green
\e[0;93m 	Yellow
\e[0;94m 	Blue
\e[0;95m 	Purple
\e[0;96m 	Cyan
\e[0;97m 	White */

/* Bold high intensity colors
\e[1;90m 	Black
\e[1;91m 	Red
\e[1;92m 	Green
\e[1;93m 	Yellow
\e[1;94m 	Blue
\e[1;95m 	Purple
\e[1;96m 	Cyan
\e[1;97m 	White */

/* High intensity background colors
\e[0;100m 	Black
\e[0;101m 	Red
\e[0;102m 	Green
\e[0;103m 	Yellow
\e[0;104m 	Blue
\e[0;105m 	Purple
\e[0;106m 	Cyan
\e[0;107m 	White */

/* Reset
\e[0m 	Reset/Default */

// print text in_center function
// Mencetak teks yang diatur di tengah layar dengan jenis string tertentu dan margin tertentu.
void printin_center(char *typeof_str, char *string, int screen_xy, int margin, char *enter)
{
    screen_xy = (screen_xy / 2);

    int align_center = (screen_xy + (strlen(string) / 2));
    int condition;

    if (((align_center + margin) % 2) == 0)
    {
        condition = (align_center + margin) + 1;
    }
    else
    {
        condition = (align_center + margin);
    }

    printf(typeof_str, condition, string);
    printf("\033[0m");

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

// print text in left function
// Mencetak teks yang diatur di kiri layar dengan jenis string tertentu dan margin tertentu.
void printin_left(char *typeof_str, char *string, int margin, char *enter)
{
    printf(typeof_str, margin, string);
    printf("\033[0m");

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

// print text in right function
// Mencetak teks yang diatur di kanan layar dengan jenis string tertentu dan margin tertentu.
void printin_right(char *typeof_str, char *string, int screen_xy, int margin, char *enter)
{
    int condition;

    if (((screen_xy + margin) % 2) == 0)
    {
        condition = (screen_xy + margin) - 1;
    }
    else
    {
        condition = (screen_xy + margin);
    }

    printf(typeof_str, condition, string);
    printf("\033[0m");

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

// print text in uppercase function
// Mencetak teks dalam huruf kapital dari sebuah string.
void printin_uppercase(char *typeof_str, char *string)
{
    char temp_string[strlen(string)];

    strcpy(temp_string, string);

    for (int index = 0; temp_string[index] != '\0'; index++)
    {
        if (temp_string[index] >= 'a' && temp_string[index] <= 'z')
        {
            temp_string[index] = toupper(temp_string[index]);
        }
        else
        {
            continue;
        }
    }

    printf("%s", temp_string);
}

// print text in lowercase function
// Mencetak teks dalam huruf kecil dari sebuah string.
void printin_lowercase(char *typeof_str, char *string)
{

    char temp_string[strlen(string)];

    strcpy(temp_string, string);

    for (int index = 0; temp_string[index] != '\0'; index++)
    {
        if (temp_string[index] >= 'A' && temp_string[index] <= 'Z')
        {
            temp_string[index] = tolower(temp_string[index]);
        }
        else
        {
            continue;
        }
    }

    printf("%s", temp_string);
}

// print hyphen (-) function
// Mencetak garis pemisah (hyphen) sepanjang panjang tertentu dengan warna tertentu dan margin tertentu.
void hyphen(char *color, int hyphen_length, int margin, char *enter)
{
    int condition;

    if (((hyphen_length + margin) % 2) == 0)
    {
        condition = (hyphen_length + margin) - 1;
    }
    else
    {
        condition = (hyphen_length + margin);
    }

    for (int number = 1; number <= condition; number++)
    {
        printf("%s-", color);
    }

    printf("\033[0m");

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

// print enter function
// Memasukkan baris kosong sebanyak yang diinginkan.
void enter(int row_length)
{
    for (int number = 1; number <= row_length; number++)
    {
        printf("\n");
    }
}

// print clear char function
// Menghapus karakter dari posisi saat ini sebanyak yang diinginkan.
void clear_char(int clear_length)
{
    for (int number = 1; number <= clear_length; number++)
    {
        printf("\r");
    }
}

// print backspace function
// Menghapus karakter sebelum posisi saat ini sebanyak yang diinginkan.
void backspace(int backspace_length)
{
    for (int number = 1; number <= backspace_length; number++)
    {
        printf("\b");
    }
}

// time sleep function
// Memberi jeda waktu dengan batas waktu tertentu.
void timesleep(float limit, char *print_escape, char *power_arg)
{
    float seconds = 0;
    clock_t start, time;

    start = clock();

    while (seconds <= limit)
    {
        time = clock();

        if (strcmp(power_arg, "WIN") == 0)
        {
            seconds = ((time - start) / pow(10, 3));
        }
        else if (strcmp(power_arg, "LINUX") == 0)
        {
            seconds = ((time - start) / pow(10, 6));
        }
        else
        {
            EXIT_FAILURE;
        }

        if (strcmp(print_escape, "TRUE") == 0)
        {
            printf("\e");
        }
        else if (strcmp(print_escape, "FALSE") == 0)
        {
            continue;
        }
        else
        {
            EXIT_FAILURE;
        }
    }
}

// loading screen function
// Menampilkan layar loading dengan animasi loading.
void loading(int screen_width, char *arg)
{
    int half_screen_width = (screen_width / 2);

    if ((half_screen_width % 2) != 0)
    {
        enter(half_screen_width - 1);
    }
    else
    {
        enter(half_screen_width);
    }

    printin_center("%*s", "\033[1;33mLoading", 130, 10 - 2, "TRUE");
    printf("%*s", ((130 - 10) / 2) + 1, " ");

    for (int loading = 1; loading <= 10; loading++)
    {
        if (strcmp(arg, "WIN") == 0)
        {
            timesleep(0.3, "TRUE", arg);
        }
        else if (strcmp(arg, "LINUX") == 0)
        {
            timesleep(0.3, "TRUE", arg);
        }
        else
        {
            EXIT_FAILURE;
        }

        printf("\033[0m%*s\033[1;30;43m%s", 0, " ", " ");
        printf("\033[0m");
    }

    enter(half_screen_width);

    system_clear(arg);
}

// system clear function
// Membersihkan layar konsol tergantung pada platform yang digunakan (Windows atau Linux).
void system_clear(char *clear_arg)
{
    if (strcmp(clear_arg, "WIN") == 0)
    {
        system("cls");
    }
    else if (strcmp(clear_arg, "LINUX") == 0)
    {
        system("clear");
    }
}