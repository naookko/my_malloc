#Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

#Directories and target
TARGET = my_malloc
OBJS = test/main.o src/my_malloc.o

#Main rule
all:$(TARGET)

#Linking the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

#Compilation rules
test/main.o: test/main.c include/my_malloc.h
	$(CC) $(CFLAGS) -c test/main.c -o test/main.o

src/my_malloc.o: src/my_malloc.c include/my_malloc.h
	$(CC) $(CFLAGS) -c src/my_malloc.c -o src/my_malloc.o

#Cleaning
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
