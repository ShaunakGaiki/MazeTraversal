#pragma once
#include "linkedlist.h"

typedef struct node Stack;


struct node* createStack()
{
	return createList();
}

struct node* stackPop(struct node* head)
{
	struct node* curr;
	curr = deleteNode(head, head);
	return curr;
}

struct node* stackPush(void* data, struct node* head, int size)
{
	return (addToBeginning(data, head, size));
}