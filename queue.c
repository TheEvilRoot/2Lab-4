#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

QueueNode * emptyNode() {
	QueueNode *node = (QueueNode*) calloc(1, sizeof(QueueNode));

	return node;
}

QueueNode * newNode(int data) {
	QueueNode *node = emptyNode();
	node->data = data;

	return node;
}

Queue * unlimitedQueue() {
	Queue *queue = (Queue*) calloc(1, sizeof(Queue));

	queue->limit = -1;

	return queue;
}

Queue * newQueue(unsigned int limit) {
	Queue *queue = unlimitedQueue();

	queue->limit = limit;

	return queue;
}

void nPush(QueueNode *node, int data) {
	if (node->next != NULL) {
		nPush(node->next, data);
	} else {
		node->next = newNode(data);
	}
}

void nTraverse(QueueNode *node) {
	if (node == NULL) {
		return;
	}

	printf("%d\n", node->data);

	nTraverse(node->next);
}

int qPush(Queue *queue, int data) {
	if (queue->limit > 0 && queue->size >= queue->limit) {
		printf("Push: Queue limit(%d) was exceeded(%d)", queue->limit, queue->size);
		return 0;
	}

	if (queue->head == NULL) {
		queue->head = newNode(data);
	} else{
		nPush(queue->head, data);
	}
	queue->size++;

	return 1;
}

void qTraverse(Queue *queue) {
	if (queue->head == NULL) {
		printf("Queue is empty\n");
	} else {
		nTraverse(queue->head);
	}
}	

int qPop(Queue *queue) {
	if (queue->head == NULL) {
		printf("Pop: Queue is empty\n");
		return -1;
	} else {
		int popped = queue->head->data;
		queue->head = queue->head->next;
		queue->size--;
		return popped;
	}
}

int qPeek(Queue *queue) {
	if (queue->head == NULL) {
		printf("Peek: Queue is empty\n");
		return -1;
	}
	
	return queue->head->data;
}









