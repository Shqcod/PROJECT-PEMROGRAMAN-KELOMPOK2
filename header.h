// import library
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function prototype
void printin_center(char *typeof_str, char *string, int screen_xy, int margin, char *enter);
void printin_left(char *typeof_str, char *string, int margin, char *enter);
void printin_right(char *typeof_str, char *string, int screen_xy, int margin, char *enter);
void printin_uppercase(char *typeof_str, char *string);
void printin_lowercase(char *typeof_str, char *string);
void hyphen(char *color, int hyphen_length, int margin, char *enter);
void enter(int row_length);
void clear_char(int clear_length);
void backspace(int backspace_length);
void timesleep(float limit, char *print_escape);
void loading(int screen_width);