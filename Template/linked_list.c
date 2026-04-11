#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include "linked_list.h"

// initialize head
node *head = NULL;

// sequence counter
int seq_ctr = 0;

// Read the file on a line by line basis
char *read_line(char *fname, int line_no)
{
	// TODO
}

// traverse the linked list
void traversal(node *head)
{
	// TODO
}

// insert the node into the linked list
void insert(node **phead, node *newnode)
{
	// TODO
}

// create a new node structure
node *create_node(int line_no, char *line)
{
	// Allocating the node itself
	if (line == NULL)
	{
		return NULL;
	}
	node *newnode = malloc(sizeof(node));
	if (newnode == NULL)
	{
		return NULL;
	}
	// assigning simple fields
	newnode->seq_no = -1;
	newnode->line_no = line_no;
	newnode->next = NULL;

	// Allocating memory for the string
	newnode->content = malloc(strlen(line) + 1);
	if (newnode->content == NULL)
	{
		free(newnode);
		return NULL;
	}
	// Copying the string
	strcpy(newnode->content, line);
	return newnode;
}
