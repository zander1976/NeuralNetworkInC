#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node Node;
struct Node {
    Node *next;
    Node *previous;
    void *data;
};

typedef struct {
    Node *head;
    int count;
    int (*compare_func)(Node, Node);
} Linklist;

Linklist* linklist_create(int (*compare_func)(Node, Node)) {
    // Create the root node
    Node *n = malloc(sizeof(Node));
    assert(n != NULL);
    n->next = n;
    n->previous = n;
    n->data = NULL;

    // Create the list
    Linklist *list = malloc(sizeof(Linklist));
    assert(list != NULL);
    list->head = n;
    list->count = 0;
    list->compare_func = compare_func;

    return list;
}

void linklist_append(Linklist *list, void *data) {
    Node *n = malloc(sizeof(Node));
    assert(n != NULL);
    n->data = data;

    n->next = list->head->next;
    n->previous = list->head;
    n->previous->next = n;
    n->next->previous = n;
    
    list->count++;
}

void listlist_print(Linklist *list) {
    printf("------------------\n");
    printf("Forward Print: \nCount: %d\n", list->count);
    Node *p = list->head->next;
    for(int i = 0; i < list->count; i++, p=p->next) {
        printf("Location: %d Data: %d\n", i, *((int*)p->data));
    }
    printf("------------------\n\n");
}

// void listlist_print_reverse(Linklist *list) {
//     printf("------------------\n");
//     printf("Reverse Print: \nCount: %d\n", list->count);
//     Node *p = list->head->previous;
//     for(int i = list->count-1; i >= 0; i--, p=p->previous) {
//         printf("Location: %d Data: %d\n", i, *((int*)p->data));
//     }
//     printf("------------------\n\n");
// }

void* linklist_remove(Linklist *list, int location) {
    assert(list->count > location);
    Node *p = list->head;
    for(int i = 0; i <= location; i++, p=p->next);
    p->previous->next = p->next;
    p->next->previous = p->previous;
    void *data = p->data;
    free(p);
    list->count--;
    return data;
}

void linklist_delete(Linklist* list) {
    while (list->count > 0) {
        void* data = linklist_remove(list, 0);
        free(data);
    }
    // Check that the list is empty
    assert(list->count == 0);
    free(list->head);
    free(list);
}

int listlist_compare_func(Node a, Node b) {
    int dataA = *((int*)a.data);
    int dataB = *((int*)b.data);
    
    if (dataA > dataB) return 1;
    else if (dataA < dataB) return -1;
    else return 0;
    return 0;
}

int main() {

    // Create a link list and give it a compare function for sort
    Linklist *list = linklist_create(listlist_compare_func);

    for(int i = 0; i < 4; i++) {
        int *value = malloc(sizeof(int));
        assert(value != NULL);
        *value = i;
        linklist_append(list, value);
    }

    //listlist_print_reverse(list);
    listlist_print(list);

    void* data = linklist_remove(list, 0);
    free(data);
    listlist_print(list);

    // Free all the memory
    linklist_delete(list);
    list = NULL;

    return 0;
}