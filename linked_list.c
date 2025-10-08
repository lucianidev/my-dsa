#include<stdio.h>
#include<stdlib.h>

struct Node {
    int value;
    struct Node* next;
  };


struct Linked_list {
    struct Node* head;
    struct Node* tail;
};

struct Linked_list* init_link() {
    // malloc per nodo che punta  a NULL
    // malloc per linked list
    // aggiorna head e tail
    struct Linked_list* linked = (struct Linked_list*) malloc(sizeof(struct Linked_list));
    //struct Node* first_node = (struct Node*) malloc(sizeof(struct Node));
    linked->head = NULL;
    linked->tail = NULL;
    return linked;
}


void add(struct Linked_list* list, int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    printf("nodo allocato: %p\n", node);

    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
        list->head->next = list->tail;
    } else {
        list->tail->next = node;
        list->tail = node;
        printf("non vuota\n");
    }

}

void traverse(struct Linked_list* list) {
    struct Node* node = list->head;
    printf("head: %p\n", node);
    while(node != NULL) {
        printf("%d\n", node->value);
        node = node->next;
    }
}


void delete(struct Linked_list* list, int pos) {
    struct Node* node = list->head;
    struct Node* prev;
    struct Node* next;

    int index = 0;

    if(node == NULL) { // se la lista è vuota non fare niente
        printf("lista vuota\n");
        return;
    }
    if(pos == 0) { // se vuole eliminare la head : salva il nodo dopo | libera memoria | set head al nodo dopo
        next = list->head->next;
        free(node);
        list->head = next;
        return;
    }

    while(node->next != NULL && index < pos) { // scorre fino al nodo da eliminare
        // nel caso è out of bounds, si elimina la tail
        // salva il valore del nodo precedente e setta il nodo adiacente a quello che viene dopo il nodo eliminato
        // prev --> eliminato --> next
        // prev --> next
        prev = node;
        node = node->next;
        index++;
    };

    // prev --> del --> next
    prev->next = node->next;
    free(node);
}


int main() {
    struct Linked_list* list = init_link();
    printf("head: %p tail: %p \n", list->head, list->tail);
    add(list, 4);
    add(list, 6);
    add(list, 6);
    add(list, 6);
    add(list, 7);

    printf("head: %p tail: %p \n", list->head, list->tail);

    traverse(list);
    delete(list, 0);
    printf("\n");
    traverse(list);

    return 0;
}
