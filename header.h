// import library
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// book information struct
typedef struct book_information
{
    unsigned int id;
    char title[128];
    char author[128];
    unsigned int page;
    unsigned int pub_year;
    unsigned int available;
} book;

// user loans struct
typedef struct loans
{
    char username[32];
    unsigned int book_id;
    unsigned int numof_book;
} user;

// function prototype
int booklist_length();
int borrowed_length();
void welcome_screen();
void home_screen();
void printin_center(char *typeof_str, char *string, int screen_xy, int margin, char *enter);
void printin_left(char *typeof_str, char *string, int margin, char *enter);
void printin_right(char *typeof_str, char *string, int screen_xy, int margin, char *enter);
void printin_uppercase(char *typeof_str, char *string);
void printin_lowercase(char *typeof_str, char *string);
void hyphen(char *color, int hyphen_length, int margin, char *enter);
void enter(int row_length);
void clear_char(int clear_length);
void backspace(int backspace_length);
void timesleep(float limit, char *print_escape, char *power_arg);
void loading(int screen_width, char *arg);
void system_clear(char *clear_arg);
void option_invalid();
void option_end();
void admin_menu();
void user_menu();
void login_invalid();
void login_end();
void books_available(book data[]);
void user_loans(user onloans[]);
void table_row(book data[], int index);
void table_border(char *enter);
void book_status(char *win_linux, int option);
void add_books(struct book_information *book, int *numof_book);
int search_books(struct book_information *book, int numof_book, unsigned int book_id);
void print_newlist(book data[], char *account_id, int books_size, int temp_index);
void goodbye_screen();