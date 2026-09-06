// Testing for my_malloc

#include "../include/my_malloc.h"
#include <stdio.h>

int main(int argc, char *argv[]){

	if(!init_memory_pool(4096)){
		fprintf(stderr, "Error: couldn't init the memory pool\n");
		return -1;
	}

	printf("Memory pool asigned correctly!\n");

	return 0;
}
