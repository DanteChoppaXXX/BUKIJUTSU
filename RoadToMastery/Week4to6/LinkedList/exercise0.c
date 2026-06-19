// Implementing a linked list.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *link;
} Node;

int main(void)
{
    // Create a head node.
    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]");
        return 1;
    }
    // Store value in the node.
    head->data = 419;
    head->link = NULL;

    // Create another node.
    Node *current = malloc(sizeof(Node));
    if (current == NULL) {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]");
        return 1;
    }

    // Store value inside the current node.
    current->data = 504;
    current->link = NULL;

    // Point head to the current node.
    head->link = current;

    // Create another node.
    current = malloc(sizeof(Node));
    if (current == NULL) {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]");
        return 1;
    }

    // Store value inside the current node.
    current->data = 720;
    current->link = NULL;

    // Point head to the current node.
    head->link->link = current;

    printf("Node 1 Data => %d\n", head->data);
    printf("Node 2 Data => %d\n", current->data);
    printf("Node 3 Data => %d\n", head->link->data);
    
    free(head->link);
    free(head);
    free(current);
    return 0;
}
