#include "../include/my_malloc.h"
#include <stdio.h>
#include <sys/mman.h>
#include <stddef.h>

static struct Header *head = NULL;

bool init_memory_pool(size_t size){
	void *pointer = mmap(NULL, (size+sizeof(struct Header)), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if(pointer == MAP_FAILED){
		fprintf(stderr, "Error: couldn't get the memory block\n");
		return false;
	}
	
	head = pointer;
	head->is_free = true;
	head->size = size;
	head->previous = NULL;
	head->next = NULL;

	return true;
}
