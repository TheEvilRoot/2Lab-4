#include <stdio.h>

#include "list.h"

int main() {

  int nums[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List *list = listOf(nums, 10);
  listPush(list, 11);

  listDebug(list);

  listSet(list, 2, 1237);

  listDebug(list);

  return 0;
}