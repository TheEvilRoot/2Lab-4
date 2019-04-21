#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define boolean int

char * enterString(const char *message) {

    char *string = (char*) calloc(1,  sizeof(char));

    if (string == NULL) {
        return NULL;
    }

    int i = 0;
    char c;

    printf("%s", message);

    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    while ((c = (char) getchar()) != -1) {
        string[i++] = c;

        if (c == '\n') {
            string[i - 1] = '\0';
            break;
        }

        if (!(string = (char*) realloc(string, sizeof(char) * (i + 1)))) {
            string[i - 1] = '\0';
            break;
        }
    }

    return string;
}

int stringLength(char *string) {
    int len = 0;
    for (; string[len] != '\0'; ++len);
    return len;
}

boolean isNumber(char c) {
    return c >= '0' && c <= '9';
}

int power(int num, int power) {
    int ret = 1;
    for (; power > 0; power--) {
        ret *= num;
    }

    return ret;
}

int toNumber(char c) {
    return c - '0';
}

int normalizeNumber(int number) {
    int ret = 0;

    while (number) {
        ret *= 10;
        ret += number % 10;
        number /= 10;
    }

    return ret;
}

void analyzeString(char *string, int length, Queue *queue) {

    // Will search for numbers
    for (int i = 0; i < length; i++) {
        char c = string[i];

        if (isNumber(c)) {
            int numPower = 0;
            int number = 0;

            for (; i < length && isNumber(string[i]); i++, numPower++) {
                number += toNumber(string[i]) * power(10, numPower);
            }

            // Normalization is necessary because
            // we reading string from start and all numbers are reversed
            // (12 -> 21, 1234 -> 4321)
            qPush(queue, normalizeNumber(number));
        }
    }
}

int main() {
    Queue *queue = unlimitedQueue();

    char *string = enterString("Enter string: ");
    if (string == NULL) {
        printf("Sorry. An unknown error occurred while string input. Program will be closed.\n");
        return 0;
    }
    int length = stringLength(string);

    analyzeString(string, length, queue);

    printf("Found %d numbers\n", queue->size);
    qTraverse(queue);

    int sum = 0;
    while (queue->head != NULL) {
        sum += qPop(queue);
    }

    printf("Sum is %d\n", sum);

	enterString("Print any symbol to exit the program...\n");

    return 0;
}