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
	if(fname == NULL || line_no <= 0){ //error handling 
		return NULL;
	}
	FILE *fp = fopen(fname, "r"); 
	if(fp == NULL){ //error handling
		return NULL;
	}
	char buffer[257]; // 256 chars + null terminator
	int curr_line_no = 0;
	while(fgets(buffer, sizeof(buffer), fp) != NULL){
		curr_line_no++;
		if(curr_line_no == line_no){ //line found
			char *line = malloc(strlen(buffer) + 1); //heap allocated copy
			if(line == NULL){
				fclose(fp);
				return NULL;
			}
			strcpy(line, buffer); //dont need strncpy because it is 256 chars + null terminator
			fclose(fp);
			return line;
		}
	}
	fclose(fp);
	return NULL;
}

// traverse the linked list
void traversal(node *head)
{
	node *curr = head;

	while(curr != NULL){
		printf("%d, %d, %s", curr->seq_no, curr->line_no, curr->content);
		curr = curr->next;
	}
}

// insert the node into the linked list
void insert(node **phead, node *newnode)
{
	// bad input handling
	if (phead == NULL || newnode == NULL)
	{
		return;
	}

	// empty list handling
	if (*phead == NULL)
	{
		*phead = newnode;
		return;
	}
	// inserting before current head
	if (newnode->line_no < (*phead)->line_no)
	{
		newnode->next = *phead;
		*phead = newnode;
		return;
	}

	// Walking the list
	node *prev = *phead;
	node *curr = (*phead)->next;

	while (curr != NULL && curr->line_no < newnode->line_no)
	{
		prev = curr;
		curr = curr->next;
	}
	// inserting between prev and curr
	prev->next = newnode;
	newnode->next = curr;
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
