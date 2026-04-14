#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"

//global line-number counter to be sync'ed.
int line_ctr = 0;

//initialization of mutex locks
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t seq_lock = PTHREAD_MUTEX_INITIALIZER;
//at least two mutex locks should be used

static void free_list(node *phead)
{
	node *curr = phead;
	while (curr != NULL) {
		node *next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
}

//start of the threads
void* process_file(void *param)
{
	(void)param; //cast the parameter to void
	return NULL;
}

int main(int argc, char* argv[])
{
	FILE* in_ptr;
	int threads;
	char *filename = NULL;
	

	pthread_t *tids = NULL; //initialize the thread id array as NULL
	int i;

	if (argc != 3) {
		printf("Incorrect arg count. Enter file name and thread count\n");
		exit(EXIT_FAILURE);
	}

	threads = atoi(argv[2]);
	if (threads < 1 || threads > 16) {
		printf("Incorrect number of threads. Enter between 1 and 16\n");
		exit(EXIT_FAILURE);
	}

	filename = argv[1];
	in_ptr = fopen(filename, "r"); 
	if (in_ptr == NULL) {
		printf("Could not open input file: %s\n", filename);
		exit(EXIT_FAILURE); 
	}
	fclose(in_ptr);

	tids = malloc(sizeof(pthread_t) * threads);
	if (tids == NULL) { //if the thread array is not allocated, exit
		printf("Failed to allocate thread array\n");
		exit(EXIT_FAILURE);
	}

	//create the threads
	for (i = 0; i < threads; i++) {
		if (pthread_create(&tids[i], NULL, process_file, filename) != 0) {
			printf("pthread_create failed at thread %d\n", i);
			threads = i;
			break;
		}
	}

	//join the threads
	for (i = 0; i < threads; i++) {
		pthread_join(tids[i], NULL);
	}

	traversal(head); //traverse the linked list and output the info

	free_list(head);
	head = NULL;
	free(tids); 

	pthread_mutex_destroy(&line_lock); //destroy the mutex locks
	pthread_mutex_destroy(&list_lock);
	pthread_mutex_destroy(&seq_lock);

	return 0;
}
