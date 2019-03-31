#include <stdlib.h>
#include <stdio.h>

#include "list.h"

Node * newNode(int data) {
  Node *node = (Node*) calloc(1, sizeof(Node));

  node->data = data;
  node->next = NULL;

  return node;
}

int nodeAppend(Node *node, int data, int index) {
  if (node->next == NULL) {
    node->next = newNode(data);
    return index + 1;
  } else {
    return nodeAppend(node->next, data, index + 1);
  }
}

Node * nodeGet(Node *from, int index) {
  if (from == NULL) {
    return NULL;
  }

  if (index == 0) {
    return from;
  } else {
    return nodeGet(from->next, index - 1);
  }
}

void nodeSet(Node *from, int index, int newData) {
  if (from == NULL) {
    return;
  }

  if (index == 0) {
    from->data = newData;
  } else {
    nodeSet(from->next, index - 1, newData);
  }
}

List * emptyList() {
  List *list = (List*) calloc(1, sizeof(List));

  list->size = 0;
  list->root = NULL;

  return list;
}

List * listOf(int *items, int count) {
  List *list = emptyList();

  if (list == NULL) {
    return NULL;
  }

  if (items == NULL) {
    return list;
  }

  for (int i = 0; i < count; i++) {
    listAppend(list, items[i]);
  }

  return list;
}

int listAppend(List *list, int data) {
  if (list->root == NULL) {
    list->root = newNode(data);
    list->size = 1;
    return 0;
  } else {
    int index = nodeAppend(list->root, data, 0);
    list->size++;
    return index;
  }
}

int listPush(List *list, int data) {
  if (list->root == NULL) {
    list->root = newNode(data);
    list->size = 1;
  } else {
    Node *node = newNode(data);
    node->next = list->root;
    list->root = node;
    list->size++;
  }
  return 0;
}


Node * listGet(List *list, int index) {
  if (index >= listSize(list)) {
    return NULL;
  }

  return nodeGet(list->root, index);
}

void listSet(List *list, int index, int newData) {
  if (index >= listSize(list)) {
    return;
  }

  nodeSet(list->root, index, newData);
}


void listDebug(List *list) {
  printf("\nList (%d)\n", listSize(list));

  for (int i = 0; i < listSize(list); i++) {
    Node *next = listGet(list, i);

    if (next == NULL) {
      printf("0x%0X NULL at index %d\n", next, i);
    } else {
      printf("0x%0X %d at index %d\n", next, next->data, i);
    }
  }
  printf("End of list\n");
}

int listSize(List *list) {
  return list->size;
}