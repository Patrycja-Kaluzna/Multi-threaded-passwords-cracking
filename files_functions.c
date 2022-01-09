#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int read_passwords (char* file_name, char passwords[][33]) {
    char* buffer = (char*)malloc(100*sizeof(char));
    FILE* file = fopen(file_name, "r");
    int i, j = 0, counter = 0;
    char c;

    do {
        do {
            c = fgetc(file);
        } while (!isspace(c));
        c = fgetc(file);
        for (i = 0; i < 32; i++) {
            passwords[j][i] = fgetc(file);
        }
        passwords[j][i] = '\0';
        fgets(buffer, 100, file);
        j++;
        counter++;
    } while (fgetc(file) != EOF);
    fclose(file);

    return counter;
}

int count_lines (char* file_name) {
    char* buffer = (char*)malloc(50 * sizeof(char));
    FILE* file = fopen(file_name, "r");
    int counter = 0;

    while (fgets(buffer, 100, file) != NULL) {
        counter++;
    }
    fclose(file);

    return counter;
}

int count_letters (char* word) {
    int counter = 0, i = 0;

    while (word[i] != '\0') {
        counter++;
        i++;
    }

    return (counter - 1); // it is because fgets funciton does not omit '\n' sign
}

void read_dictionary (char* file_name, char** dictionary) {
    char* buffer = (char*)malloc(50 * sizeof(char));
    FILE* file = fopen(file_name, "r");
    int number_of_letters, i = 0, j;

    while (fgets(buffer, 50, file) != NULL) {
        number_of_letters = count_letters(buffer);
        dictionary[i] = (char*)malloc((number_of_letters + 1) * sizeof(char));
        for (j = 0; j < number_of_letters; j++) {
            dictionary[i][j] = buffer[j];
        }
        dictionary[i][number_of_letters] = '\0';
        i++;
    }
    fclose(file);
}