#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"

//global line-number counter to be sync'ed and global sequence-number counter
int line_ctr = 0;
int seq_ctr = 0;


//initialization of mutex locks
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t seq_lock = PTHREAD_MUTEX_INITIALIZER;
//at least two mutex locks should be used: I used all of them

//start of the threads
void* process_file(void *param)
{
	// TODO: read the file line by line, create a node for each line and insert it into the linked list 
	// ensure no same line no or sequence no for different nodes
	if(param == NULL){
		return NULL;
	}
	while(1){ //based off of lecture while loops + textbook
		int line_no;
		pthread_mutex_lock(&line_lock); //lock line counter
		line_no = ++line_ctr;  //forced to read one at a time
		pthread_mutex_unlock(&line_lock); //unlock line counter
		char *line = read_line((char*)param, line_no); //read line from file
		if(line == NULL){ 
			break;
		}
		node *newnode = malloc(sizeof(node)); //create new node
		if(newnode == NULL){ //error handling
			free(line);
			return NULL;
		}
		newnode->line_no = line_no; //set line number
		newnode->content = line; //set content
		newnode->next = NULL;
		pthread_mutex_lock(&seq_lock); //lock sequence counter so no same sequence numbers are given out to different nodes
		newnode->seq_no = ++seq_ctr; //get next sequence number + update
		pthread_mutex_unlock(&seq_lock); //unlock sequence counter
		pthread_mutex_lock(&list_lock); //lock linked list
		insert(&head, newnode); //insert new node into linked list
		pthread_mutex_unlock(&list_lock); //unlock linked list
}
	return NULL;

}

int main(int argc, char* argv[])
{
	FILE* in_ptr;
	int threads;
	char *filename = NULL;

	if (argc != 3) {
		printf("Incorrect arg count. Enter file name and thread count\n");
		exit(EXIT_FAILURE);
	}

	threads = atoi(argv[2]);
	if (threads < 1 || threads > 16) {
		printf("Incorrect number of threads. Enter between 1 and 16\n");
		exit(EXIT_FAILURE);
	}

	// TODO: create threads and join them, pthread_create & pthread_join
	
	return 0;
}
