#include "../include/my_malloc.h"
#include <stdio.h>
#include <sys/mman.h>
#include <stddef.h>

static struct Header *head = NULL;
static size_t total_pool_size = 0;

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

	total_pool_size = size;

	return true;
}

void* my_malloc(size_t size) {
    if (size == 0 || head == NULL) {
        return NULL;
    }
    
    struct Header *auxHead = head;

    while (auxHead != NULL && (!auxHead->is_free || auxHead->size < size)) {
        auxHead = auxHead->next;
    }

    if (auxHead == NULL) {
        fprintf(stderr, "Error: there's not enough space\n");
        return NULL;
    }

    if (auxHead->size >= size + sizeof(struct Header)) {
        struct Header *newHeader = (struct Header *)((char *)(auxHead + 1) + size);

        newHeader->is_free = true;
        newHeader->size = auxHead->size - size - sizeof(struct Header);
        newHeader->previous = auxHead;
        newHeader->next = auxHead->next;

        if (auxHead->next != NULL) {
            auxHead->next->previous = newHeader;
        }

        auxHead->size = size;
        auxHead->next = newHeader;
    }

    auxHead->is_free = false;

    return (void *)(auxHead + 1);
}