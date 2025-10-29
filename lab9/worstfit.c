#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int is_free; // 1 if free, 0 if allocated
    struct Block *next;
} Block;

Block *head = NULL;

// Function to allocate a block with given size using worst-fit strategy
void* worst_fit(int size) {
    Block *current = head, *worst = NULL;
    int max_size = -1;

    // Traverse the list to find the worst fit (largest block)
    while (current != NULL) {
        if (current->is_free && current->size >= size && current->size > max_size) {
            max_size = current->size;
            worst = current;
        }
        current = current->next;
    }

    if (worst == NULL) {
        printf("Not enough memory to allocate %d bytes.\n", size);
        return NULL; // No suitable block found
    }

    // Allocate memory by splitting the worst block if necessary
    if (worst->size > size) {
        Block *new_block = (Block *)((char *)worst + size);
        new_block->size = worst->size - size;
        new_block->is_free = 1;
        new_block->next = worst->next;

        worst->size = size;
        worst->is_free = 0;
        worst->next = new_block;
    } else {
        worst->is_free = 0; // Fully allocate the worst block
    }

    return (void *)(worst + 1); // Return pointer to memory after the block structure
}

// Function to free a previously allocated block
void worst_fit_free(void *ptr) {
    Block *block = (Block *)ptr - 1;
    block->is_free = 1;

    // Optionally, merge adjacent free blocks
    Block *current = head;
    while (current != NULL && current->next != NULL) {
        if (current->is_free && current->next->is_free) {
            current->size += current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

// Function to initialize memory for the dynamic memory pool
void init_memory_pool(int size) {
    head = (Block *)malloc(size);
    if (head == NULL) {
        printf("Memory pool allocation failed.\n");
        exit(1);
    }

    head->size = size;
    head->is_free = 1;
    head->next = NULL;
}

int main() {
    int memory_pool_size = 1024;
    init_memory_pool(memory_pool_size); // Initialize a memory pool of 1024 bytes

    // Simulate dynamic allocations and deallocations
    printf("Allocating 200 bytes...\n");
    void *block1 = worst_fit(200);

    printf("Allocating 100 bytes...\n");
    void *block2 = worst_fit(100);

    printf("Allocating 50 bytes...\n");
    void *block3 = worst_fit(50);

    // Freeing blocks
    printf("Freeing block 1...\n");
    worst_fit_free(block1);

    printf("Freeing block 2...\n");
    worst_fit_free(block2);

    printf("Allocating 150 bytes...\n");
    void *block4 = worst_fit(150);

    return 0;
}
