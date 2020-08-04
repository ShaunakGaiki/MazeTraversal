#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
	void* value;
	struct node* next;
};

typedef struct {
	struct node* head;
}List;

struct node* createList()
{
	struct node* new_node;
	new_node = (struct node*)malloc(sizeof(struct node));
	(new_node->next) = NULL;
	return new_node;
}


struct node* addToBeginning(void* data, struct node* first, int size)
{
	struct node* new_node;
	//allocates and sets value
	new_node = (struct node*)malloc(sizeof(struct node));
	(new_node->value) = malloc(size);
	memcpy(new_node->value, data, size);
	//makes it the real first
	new_node->next = first;
	return new_node;
}

void insertNode(void* data, struct node* previous_node, int size)
{
	struct node* new_node, * temp;
	//creates and allocates node and node data
	new_node = (struct node*)malloc(sizeof(struct node));
	(new_node->value) = malloc(size);
	memcpy(new_node->value, data, size);


	//changes the pointing adresses of each nodes
	temp = previous_node->next;
	new_node->next = temp;
	previous_node->next = new_node;

	return;
}

struct node* deleteNode(struct node* deletion, struct node* first)
{
	struct node* trailing, * temp, * ret;
	trailing = (struct node*)malloc(sizeof(struct node));
	temp = (struct node*)malloc(sizeof(struct node));

	temp = first;

	while (temp != deletion)
	{
		trailing = temp;
		temp = temp->next;
	}
	if (deletion == first)
	{
		ret = deletion->next;
		free(deletion);
		return ret;
	}
	trailing->next = temp->next;
	free(deletion);
	return first;
}