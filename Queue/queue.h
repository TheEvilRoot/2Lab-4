#ifndef _queue_h
#define _queue_h

struct queue_node {
	int data;
	struct queue_node *next;
};

struct queue {
	unsigned int size;
	int limit;
	struct queue_node *head;
};

typedef struct queue_node QueueNode;
typedef struct queue Queue;

QueueNode * newNode(int data);
QueueNode * emptyNode();

Queue * newQueue(unsigned int limit);
Queue * unlimitedQueue();

void nPush(QueueNode *node, int data);
void nTraverse(QueueNode *node);

int qPush(Queue *queue, int data);
int qPop(Queue *queue);
int qPeek(Queue *queue);
void qTraverse(Queue *queue);

#endif
