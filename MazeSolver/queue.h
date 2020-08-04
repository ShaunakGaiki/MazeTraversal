#pragma once
#include "linkedlist.h"

typedef struct {
	struct node* front;
	struct node* back;
}Queue;

Queue* createQueue()
{
	Queue* q;
	q = (Queue*)malloc(sizeof(Queue*));
	q->front = createList();
	q->back = q->front;
	return q;
}

Queue* enqueue(Queue* queue,void *data,int size)
{
	insertNode(data, queue->back, size);
	queue->back = queue->back->next;
	return queue;
}

Queue* dequeue(Queue* queue)
{
	queue->front = deleteNode(queue->front, queue->front);
	return queue;
}
