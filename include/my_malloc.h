#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

struct Header{
	bool is_free;
	size_t size;
	struct Header *previous;
	struct Header *next;
};

bool init_memory_pool(size_t size);
void* my_malloc(size_t size);

#endif
