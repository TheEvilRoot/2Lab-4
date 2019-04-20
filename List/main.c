#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tests.h"

char * enterString(const char * message) {
  char *str = (char*) calloc(1,  sizeof(char)); // Checked
  if (str == NULL) {
    return NULL;
  }

  int i = 0;
  char c;

  printf("%s", message);

  fflush(stdin);
  fseek(stdin, 0, SEEK_END);
  while ((c = getchar()) != -1) {
    str[i++] = c;

    if (c == '\n') {
      str[i - 1] = '\0';
      break;
    }

    if (!(str = (char*) realloc(str, sizeof(char) * (i + 1)))) {
      break;
    }
  }

  return str;
}

int stringLength(char *str) {
  if (str == NULL) {
    return 0;
  }

  int len = 0;
  for (; str[len] != '\0'; ++len);
  return len;
}

int parseInt(char *str) {
  int number = 0;
  int sign = 1;
  int length = stringLength(str);

  for (int i = 0; i < length; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      number *= 10;
      number += str[i] - '0';
    } else if (str[i] == '-' && i == 0) { // - can be recognized as unary operator only if it located on 0 index in string
      sign = -1;
    } else {
      break;
    }
  }
  return number * sign;
}

int main(int argc, const char *argv[]) {
  runTests();

  List *list = emptyList();
  if (list == NULL) {
    printf("Sorry, but there's an unexpected error with list creation. Maybe memory is full.\n");
    return -1;
  }

  printf("Let's enter some initial list values... Print # to end input.\n");

  while (1) {
    char *inputString = enterString("Next number: ");
    if (inputString == NULL) {
      printf("Sorry, but there's some memory error has occurred while string input. We going to break initial list input\n");
      break;
    }

    int length = stringLength(inputString);
    if (length < 1) continue;

    if (inputString[0] == '#') { // input break
      break;
    }

    int newNumber = parseInt(inputString);
    if (listAppend(list, newNumber) == -1) {
      printf("Unexpected error has occurred while appending list. We will skip this number for now\n");
    }
  }

  printf("Sure. Let's see on your initial list: \n");

  for (int i = 0; i < listSize(list); i++) {
    Node *n = listGet(list, i);
    if (n == NULL) {
      printf("Ow! There's NULL on index %d. *silently went out the window*\n", i);
      continue;
    }
    printf("%d: %d\n", i, n->data);
  }

  return 0;
}
