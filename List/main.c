#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#ifdef _WIN32
#define SHELL_CLEAR "cls"
#else
#define SHELL_CLEAR "clear"
#endif

#define clearScreen() { system(SHELL_CLEAR); }

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

// Should it be in list.c file?
void printList(List *list) {
  for (int i = 0; i < listSize(list); i++) {
    Node *n = listGet(list, i);
    if (n == NULL) {
      printf("Ow! There's NULL on index %d. *silently went out the window*\n", i);
      continue;
    }
    printf("%d: %d\n", i, n->data);
  }
}

int enterInt(const char *message) {
  int ret = 0;
  do {
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    rewind(stdin);
    printf("%s", message);
  } while (!scanf("%d", &ret));
  return ret;
}

int main(int argc, const char *argv[]) {
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

  printList(list);

  printf("Next...\nJust enter a new number, then enter number in list that will be followed by new number\n");

  while (1) {
    clearScreen()

    printf("[S]how list\n");
    printf("[E]nter new number\n");
    printf("[D]ubug list\n");
    printf("[Q]uit program\n");

    char *inputString = enterString("");
    int length = stringLength(inputString);
    if (inputString == NULL || length == 0) {
      continue;
    }
    switch(inputString[0]) {
      case 's': case 'S': {
        printList(list);
        break;
      }
      case 'd': case 'D': {
        listDebug(list);
        break;
      }
      case 'e': case 'E': {
        int newNumber = enterInt("So, enter new number: ");
        printf("Sure. Let's insert %d after...\n", newNumber);
        int followedNumber = enterInt("Enter number followed by your new number: ");
        int indexOfFollowed = listIndexOf(list, followedNumber);
        if (indexOfFollowed == -1) { // Number not in the list
          printf("Hmm... I think there's no such number in list...\n");
        } else {
          printf("Okay. Let's insert %d after all %d in the list...\n", newNumber, followedNumber);

          int count = 0;
          Node **matches = listFindAll(list, followedNumber, &count);
          if (matches != NULL) {
            printf("Inserting[");
            for (int i = 0; i < count; i++) {
              if (matches[i] != NULL) {
                listInsert(list, matches[i], newNumber);
              }
              printf("#");
            }
            printf("] Done! %d numbers inserted\n", count);
          } else {
            printf("Ooops... Something went wrong and there's no such numbers in the list or searching was fail... Can we just try again?\n");
          }
        }
        break;
      }
      case 'q': case 'Q': {
        printf("Sure. Goodbye!\n");
        return 0;
      }
    }

    enterString("Type any key to return to menu...\n");
  }
}
