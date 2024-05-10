#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int id;
    char title[48];
    char author[36];
    unsigned int page;
    unsigned int year;
    unsigned int available;
} book;

void books_available(book data[]) {
    FILE *input_fp = fopen("books.txt", "r");
    int count = 0;

    if (input_fp == NULL) {
        printf("Error! File doesn't exist\n");
        return;
    }

    while (!feof(input_fp)) {
        fscanf(input_fp, "%u,\"%[^\"]\",%[^,],%u,%u,%u\n", &data[count].id, data[count].title, data[count].author, &data[count].page, &data[count].year, &data[count].available);
        count++;
    }

    fclose(input_fp);
}

int booklist_length() {
    FILE *input_fp = fopen("books.txt", "r");
    int count = 0;
    char line[256];

    if (input_fp == NULL) {
        printf("Error! File doesn't exist\n");
        return 0;
    }

    while (fgets(line, sizeof(line), input_fp) != NULL) {
        count++;
    }

    fclose(input_fp);
    return count;
}

void table_border(char *option) {
    if (strcmp(option, "TRUE") == 0) {
        printf("+------+--------------------------------------------------+-------------------------------------+------------+------------+------------+\n");
    } else {
        printf("+------+--------------------------------------------------+-------------------------------------+------------+------------+------------+\n");
    }
}

void table_row(book data[], int index) {
    printf("| %-5u | %-47s | %-35s | %-11u | %-11u | %-11u |\n", data[index].id, data[index].title, data[index].author, data[index].page, data[index].year, data[index].available);
}

int main() {
    int books_size = booklist_length();
    book data[books_size];
    books_available(data);

    printf("\033[1;33m");
    table_border("TRUE");
    printf("| %-5s | %-47s | %-35s | %-11s | %-11s | %-11s |\n", "ID", "Title", "Author", "Page", "Year", "Available");
    table_border("TRUE");
    printf("\033[0m");

    for (int index = 0; index < books_size; index++) {
        table_row(data, index);
    }

    table_border("FALSE");
    printf("\033[0m");

    return 0;
}