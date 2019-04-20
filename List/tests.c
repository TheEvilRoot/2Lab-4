#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void assertEquals(const char *tag, int expected, int actual) {
  if (expected != actual) {
    printf("[%s]Test failed: \n\tExpected:\t%d\n\tActual:\t%d\n",tag ,expected, actual);
    exit(-1);
  }
}

void assertNotNull(const char *tag, void *pointer) {
  if (pointer == NULL) {
    printf("[%s] Test failed: Pointer is null\n", tag);
    exit(-1);
  }
}

void assertNull(const char *tag, void *pointer) {
  if (pointer != NULL) {
    printf("[%s] Test failed: Pointer is not null but expected so\n\tPointer:\t%p\n", tag, pointer);
    exit(-1);
  }
}

void test_listAdd() {
  List *list = emptyList();
  assertNotNull("create list", list);

  assertEquals("empty list size", list->size, 0);

  listAppend(list, 10);
  assertEquals("list size append", listSize(list), 1);

  listPush(list, 12);
  assertEquals("list size push", listSize(list), 2);

  Node *first = listGet(list, 0);
  assertNotNull("list first", first);
  assertEquals("list first pushed", first->data, 12);

  Node *second = listGet(list, 1);
  assertNotNull("list second", second);
  assertEquals("list second appended", second->data, 10);
}

void test_listSet() {
  List *list = emptyList();
  assertNotNull("create list", list);

  listAppend(list, 10);
  listAppend(list, 12);
  listAppend(list, 13);

  assertEquals("list size", listSize(list), 3);

  Node *node = listGet(list, 1);
  assertNotNull("list item", node);
  assertEquals("list item", node->data, 12);

  listSet(list, 1, 21);

  node = listGet(list, 1);
  assertNotNull("list new item", node);
  assertEquals("list new item", node->data, 21);
}

void test_listSize() {
  List *list = emptyList();
  assertNotNull("create list", list);

  for (int i = 0; i < 18; i++) {
    listPush(list, i * 12);
  }

  assertEquals("list size actual with function", listSize(list), 18);
  assertEquals("list size actual with value", list->size, 18);
  assertEquals("list size function with value", list->size, listSize(list));
}

void test_listOf() {
  int size = 182;
  int *ints = (int*) calloc(size, sizeof(int));
  assertNotNull("int array", ints);

  for (int i = 0; i < size; i++) {
    ints[i] = i % 12;
  }

  List *list = listOf(ints, size);
  assertNotNull("create list", list);

  assertEquals("list size", size, listSize(list));

  for (int i = 0; i < size; i++) {
    Node *node = listGet(list, i);
    assertNotNull("nth item in list", node);
    assertEquals("nth item in list", ints[i], node->data);
  }
}

void test_listIndexOf() {
  List *list = emptyList();
  assertNotNull("create list", list);

  for (int i = 0; i < 10; i++) {
    listAppend(list, i * 10);
  }

  assertEquals("list size", 10, listSize(list));

  int index = listIndexOf(list, 40);
  assertEquals("index of 40", 40 / 10, index);

  index = listIndexOf(list, 1234);
  assertEquals("index of not existing item", -1, index);
}

void test_listFind() {
  List *list = emptyList();
  assertNotNull("create list", list);

  for (int i = 0; i < 10; i++) {
    listAppend(list, i * 10);
  }

  assertEquals("list size", 10, listSize(list));

  Node *found = listFind(list, 40);
  assertNotNull("find 40", found);
  assertEquals("find 40", 40, found->data);
  assertNotNull("find 40 next", found->next);
  assertEquals("find 40 next", found->next->data, 50);

  found = listFind(list, 1234);
  assertNull("find not existing item", found);
}

void test_listFindAll() {
  List *list = emptyList();
  assertNotNull("create list", list);

  for (int i = 0; i < 100; i++) {
    listAppend(list, i % 10); // 0 1 ... 8 9 0 1 ... 8 9 0 ... 9
  }

  assertEquals("list size", 100, listSize(list));

  int count = 0;
  Node **matches = listFindAll(list, 8, &count);
  assertNotNull("list matches 8",matches);
  assertEquals("count of 8", 10, count);

  for (int i = 0; i < 10; i++) {
    assertNotNull("nth match of 8", matches[i]);
    assertEquals("nth match of 8", 8, matches[i]->data);
  }

  count = 0;
  matches = listFindAll(list, 12, &count);
  // matches can be null or not null, i can't determinate reason of this behaviour...

  assertEquals("count of matches of not existing item", 0, count);
}

int runTests() {

  test_listAdd();
  printf("Passed test_listAdd()\n");

  test_listSet();
  printf("Passed test_listSet()\n");

  test_listSize();
  printf("Passed test_listSize()\n");

  test_listOf();
  printf("Passed test_listOf()\n");

  test_listIndexOf();
  printf("Passed test_indexOf()\n");

  test_listFind();
  printf("Passed test_listFind()\n");

  test_listFindAll();
  printf("Passed test_listFindAll()\n");

  return 0;
}