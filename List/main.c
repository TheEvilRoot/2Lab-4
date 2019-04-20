#include <stdio.h>

#include "list.h"

int main() {

  int nums[10] = { 4, 2, 3, 4, 2, 4, 7, 4, 9, 4};
  List *list = listOf(nums, 10);
  listPush(list, 11);
  listAppend(list, 12333);

  listDebug(list);

  listSet(list, 2, 1237);

  listDebug(list);

  Node *found = listFind(list, 1222);
  printf("index of 8 : %p: %d\n",found, found == NULL ? -1 : found->data);

  int count = 0;
  Node **matches = listFindAll(list, 12371, &count);

  if (matches == NULL) {
    printf("NULL!\n");
  } else {
    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
      printf("Next by 4 is %p -> %d\n", matches[i]->next, matches[i]->next == NULL ? -1 : matches[i]->next->data);
    }
  }

  return 0;
}