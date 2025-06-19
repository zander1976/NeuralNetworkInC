#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    size_t count;
    size_t total;
    int *backing_array;
    int (*compare_func)(int, int);
} balance_tree_t;

balance_tree_t balance_tree_create(int (*compare_func)(int, int)) {
    int *backing = malloc(sizeof(int));
    assert(backing != NULL);
    return (balance_tree_t) { 
        .count=0, 
        .total=1, 
        .backing_array = backing, 
        .compare_func=compare_func
    };
}

void balance_tree_insert(balance_tree_t *list, int x) {
    list->backing_array[list->count] = x;
    list->count++;
    if (list->count == list->total) {
        list->total *= 2;
        int *backing = malloc(list->total * sizeof(int));
        assert(backing != NULL);
        for(size_t i = 0; i < list->count; i++) {
            backing[i] = list->backing_array[i];
        }
        free(list->backing_array);
        list->backing_array = backing;
    }
}

void balance_tree_print(balance_tree_t *list) {
    printf("Values: ");
    for(size_t i = 0; i < list->count; i++) {
        printf("%d ", list->backing_array[i]);
    }
    printf("\n");
    printf("Backing: ");
    for(size_t i = 0; i < list->total; i++) {
        printf("%d ", list->backing_array[i]);
    }
    printf("\n");
}

int balance_compare(int x, int y) {
    if (x == y) return 0;
    if (x > y) return 1;
    return -1;
}

int main() {
    balance_tree_t tree = balance_tree_create(balance_compare);
    balance_tree_insert(&tree, 1);
    balance_tree_insert(&tree, 10);
    balance_tree_insert(&tree, 5);
    balance_tree_insert(&tree, 20);
    balance_tree_insert(&tree, 15);
    balance_tree_print(&tree);
    return 0;
}


