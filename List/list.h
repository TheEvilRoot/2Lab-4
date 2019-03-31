//
// Created by robot on 31.03.2019.
//

#ifndef INC_2LAB_4_LIST_H
#define INC_2LAB_4_LIST_H

struct list_node {
  int data;
  struct list_node *next;
};

struct list {
  int size;
  struct list_node *root;
};

typedef struct list_node Node;
typedef struct list List;

List * emptyList();
List * listOf(int *items, int count);

int listAppend(List *list, int data);
int listPush(List *list, int data);

Node * listGet(List *list, int index);
void listSet(List *list, int index, int newData);

int listSize(List *list);

Node * newNode(int data);
int nodeAppend(Node *node, int data, int index);
Node * nodeGet(Node *from, int index);
void nodeSet(Node *from, int index, int newData);

void listDebug(List *list);

#endif //INC_2LAB_4_LIST_H
