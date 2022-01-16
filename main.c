//dd489a21e1ea665fc02297f5317a7eb2 //1
//8d61d00d9b71ff546866069b5bfc298b //3

#include "threads_functions.c"
#include "files_functions.c"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define THREADS_NUMBER 4

int consumer_ended = 0;
int number_of_lines, number_of_passwords;
int found_passwords[1000];
int j, first_try = 1;
char** dictionary;
char* password;
char passwords[1000][33];
pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer_1 (void* t1) {
    int a = 1, b = 11, i, o, k, l, n = 10, m = 2, first = 1, unlocked = 1;
    char* number1, * number2, * pom;
    char md5[33];

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

    while (1) {
        if (unlocked == 1) {
            pthread_mutex_lock(&mutex); printf("P1: muteks zablokowany\n\n");
            unlocked = 0;
        }
        for (i = 0; i < number_of_lines; i++) {
            pom = (char*)malloc(sizeof(dictionary[i]) + m * sizeof(char));
            number1 = (char*)malloc(m / 2 * sizeof(char));
            number2 = (char*)malloc(m / 2 * sizeof(char));
            for (o = a; o < b; o++) {
                sprintf(number1, "%d" , o - 1);
                strcpy(pom, dictionary[i]);
                strcat(number1, pom);
                for (k = a; k < b; k++) {
                    strcpy(pom, number1);
                    sprintf(number2, "%d" , k - 1);
                    strcat(pom, number2);
                    strcpy(password, pom);
                    bytes2md5(password, strlen(password), md5);
                    for (l = 0; l < number_of_passwords; l++) {
                        if (found_passwords[l] == 0) {
                            if (strcmp(md5, passwords[l]) == 0) {
                                pthread_cond_signal(&cond);
                                pthread_mutex_unlock(&mutex); printf("P1: muteks odblokowany\n\n");
                                unlocked = 1;
                                while (consumer_ended == 0) {}
                                consumer_ended = 0;
                            }
                        }
                    }
                }
            }
            free(number2);
            free(number1);
            free(password);
        }
        if (first == 1) {
            a += 10;
            b = (b - 1) * 10 + 1;
            first = 0;
        } else {
            a = a + 9 * n;
            n *= 10;
            b = (b - 1) * 10 + 1;
        }
        m += 2;
    }

    pthread_exit(NULL);
}

void* producer_2 (void* t2) {
    int a = 1, b = 11, i, o, k, l, n = 10, m = 2, first = 1, unlocked = 1;
    char* number1, * number2, * pom;
    char md5[33];

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

    while (1) {
        if (unlocked == 1) {
            pthread_mutex_lock(&mutex); printf("P1: muteks zablokowany\n\n");
            unlocked = 0;
        }
        for (i = 0; i < number_of_lines; i++) {
            pom = (char*)malloc(sizeof(dictionary[i]) + m * sizeof(char));
            number1 = (char*)malloc(m / 2 * sizeof(char));
            number2 = (char*)malloc(m / 2 * sizeof(char));
            for (o = a; o < b; o++) {
                sprintf(number1, "%d" , o - 1);
                strcpy(pom, dictionary[i]);
                pom[0] = toupper(pom[0]);
                strcat(number1, pom);
                for (k = a; k < b; k++) {
                    strcpy(pom, number1);
                    sprintf(number2, "%d" , k - 1);
                    strcat(pom, number2);
                    strcpy(password, pom);
                    bytes2md5(password, strlen(password), md5);
                    for (l = 0; l < number_of_passwords; l++) {
                        if (found_passwords[l] == 0) {
                            if (strcmp(md5, passwords[l]) == 0) {
                                pthread_cond_signal(&cond);
                                pthread_mutex_unlock(&mutex); printf("P1: muteks odblokowany\n\n");
                                unlocked = 1;
                                while (consumer_ended == 0) {}
                                consumer_ended = 0;
                            }
                        }
                    }
                }
            }
            free(number2);
            free(number1);
            free(password);
            sleep(10);
        }
        if (first == 1) {
            a += 10;
            b = (b - 1) * 10 + 1;
            first = 0;
        } else {
            a = a + 9 * n;
            n *= 10;
            b = (b - 1) * 10 + 1;
        }
        m += 2;
    }

    pthread_exit(NULL);
}

void* producer_3 (void* t3) {
    int a = 1, b = 11, i, k, l, n = 10, m = 2, o, p, first = 1, unlocked = 1;
    char* number1, * number2, * pom;
    char md5[33];

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

    while (1) {
        if (unlocked == 1) {
            pthread_mutex_lock(&mutex); printf("P1: muteks zablokowany\n\n");
            unlocked = 0;
        }
        for (i = 0; i < number_of_lines; i++) {
            pom = (char*)malloc(sizeof(dictionary[i]) + m * sizeof(char));
            number1 = (char*)malloc(m / 2 * sizeof(char));
            number2 = (char*)malloc(m / 2 * sizeof(char));
            for (o = a; o < b; o++) {
                sprintf(number1, "%d" , o - 1);
                strcpy(pom, dictionary[i]);
                for (p = 0; p < (count_letters(dictionary[i]) + 1); p++) {
                    pom[p] = toupper(pom[p]);
                }
                strcat(number1, pom);
                for (k = a; k < b; k++) {
                    strcpy(pom, number1);
                    sprintf(number2, "%d" , k - 1);
                    strcat(pom, number2);
                    strcpy(password, pom);
                    bytes2md5(password, strlen(password), md5);
                    for (l = 0; l < number_of_passwords; l++) {
                        if (found_passwords[l] == 0) {
                            if (strcmp(md5, passwords[l]) == 0) {
                                pthread_cond_signal(&cond);
                                pthread_mutex_unlock(&mutex); printf("P1: muteks odblokowany\n\n");
                                unlocked = 1;
                                while (consumer_ended == 0) {}
                                consumer_ended = 0;
                            }
                        }
                    }
                }
            }
            free(number2);
            free(number1);
            free(password);
            sleep(1);
        }
        if (first == 1) {
            a += 10;
            b = (b - 1) * 10 + 1;
            first = 0;
        } else {
            a = a + 9 * n;
            n *= 10;
            b = (b - 1) * 10 + 1;
        }
        m += 2;
    }

    pthread_exit(NULL);
}

void* handler_thread (void* t4) {
    int i, counter = 0;
    sigset_t set;
    int* sig;
    
    sigemptyset(&set);
    sigaddset(&set, SIGHUP);
    while (1) {
        if (sigwait(&set, sig) >= 0) { //Tutaj nie wchodzi
            printf("TEST\n");
            pthread_mutex_lock(&mutex); printf("H: muteks zablokowany\n\n");
            for (i = 0; 0 < number_of_passwords; i++) {
                if (found_passwords[i] == 1) {
                    counter++;
                }
            }
            printf("Znaleziono %d haseł.\n", counter);
            pthread_mutex_unlock(&mutex); printf("H: muteks odblokowany\n\n");   
        }
    }

    pthread_exit(NULL);
}

int main () {
    char* dictionary_file = (char*)malloc(50 * sizeof(char));
    char* passwords_file = (char*)malloc(50 * sizeof(char));
    pthread_t threads[THREADS_NUMBER];
    int k, counter = 0, all_found = 0;
    long t1 = 1, t2 = 2, t3 = 3, t4 = 4;

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
    pthread_create(&threads[3], NULL, handler_thread, (void *)t4);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create(&threads[0], NULL, producer_1, (void *)t1);
    pthread_create(&threads[1], NULL, producer_2, (void *)t2);
    pthread_create(&threads[2], NULL, producer_3, (void *)t3);

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