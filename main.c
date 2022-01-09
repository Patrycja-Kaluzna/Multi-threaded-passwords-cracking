//dd489a21e1ea665fc02297f5317a7eb2 //1
//8d61d00d9b71ff546866069b5bfc298b //3

#include "threads_functions.c"
#include "files_functions.c"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
//#include <asm/signal.h>

#define THREADS_NUMBER 1

int consumer_ended = 0;
int number_of_lines, number_of_passwords;
int found_passwords[1000];
int j, first_try = 1;
char** dictionary;
char* password;
char passwords[1000][33];
pthread_mutex_t mutex;
pthread_cond_t cond;

void handler (int signal) {
    int i, counter = 0;
    for (i = 0; 0 < number_of_passwords; i++) {
        if (found_passwords[i] == 1) {
            counter++;
        }
    }
    printf("Znaleziono %d haseł.\n", counter);
}

void* producer_1 (void* t1) {
    char md5[33];
    int i, unlocked = 1;

    if (first_try == 1) {
        sleep(1);
        first_try = 0;
    }
    for (i = 0; i < number_of_lines; i++) {
        if (unlocked == 1) {
            pthread_mutex_lock(&mutex); printf("P1: muteks zablokowany\n\n");
            unlocked = 0;
        }
        password = (char*)malloc(sizeof(dictionary[i]));
        strcpy(password, dictionary[i]);
        bytes2md5(password, strlen(password), md5);
        for (j = 0; j < number_of_passwords; j++) {
            if (found_passwords[j] == 0) {
                if (strcmp(md5, passwords[j]) == 0) {
                    pthread_cond_signal(&cond);
                    pthread_mutex_unlock(&mutex); printf("P1: muteks odblokowany\n\n");
                    unlocked = 1;
                    while (consumer_ended == 0) {}
                    consumer_ended = 0;
                }
            }
        }
        free(password);
    }

    pthread_exit(NULL);
}

int main () {
    char* dictionary_file = (char*)malloc(50 * sizeof(char));
    char* passwords_file = (char*)malloc(50 * sizeof(char));
    pthread_t threads[THREADS_NUMBER];
    int k, counter = 0, all_found = 0;
    long t1 = 1;

    signal(1, handler);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init (&cond, NULL);

    for (k = 0; k < 1000; k++) {
        found_passwords[k] = 0;
    }

    printf("Enter a passwords' file name: ");
    scanf("%s", passwords_file);
    number_of_passwords = read_passwords(passwords_file, passwords);

    printf("Enter a dictionary's file name: ");
    scanf("%s", dictionary_file);
    number_of_lines = count_lines(dictionary_file);
    dictionary = (char**)malloc(number_of_lines * sizeof(char*));
    read_dictionary(dictionary_file, dictionary);

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create(&threads[0], NULL, producer_1, (void *)t1);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);

    while (all_found == 0) {
        pthread_mutex_lock(&mutex); printf("K: muteks zablokowany\n\n");
        pthread_cond_wait(&cond, &mutex); 
        found_passwords[j] = 1;
        printf("Found the password number %d - %s\n", j , password);
        pthread_mutex_unlock(&mutex); printf("K: muteks odblokowany\n\n");
        consumer_ended = 1;
        for (k = 0; k < number_of_passwords; k++) {
            if (found_passwords[k] == 1) {
                counter++;
            }
        }
        if (counter == number_of_passwords) {
            all_found = 1;
        } else {
            counter = 0;
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    for (k = 0; k < number_of_lines; k++) {
        free(dictionary[k]);
    }
    free(dictionary_file);
    free(passwords_file);
    free(dictionary);

    pthread_exit(NULL);
}