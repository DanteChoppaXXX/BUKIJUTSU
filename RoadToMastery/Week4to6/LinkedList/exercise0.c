// Write a program in C to create and display a singly linked-list.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int number;
    struct Node *next;
} Node;

int main(void)
{
    // Declare a head node.
    Node *head;

    // Ask user for number of nodes.
    int numofNodes;
    printf("Enter number of node: ");
    scanf("%d%*c", &numofNodes);

    // Create the nodes and store user input.
    for (int i = 0; i < numofNodes; i++) {
        Node *node = malloc(sizeof(Node));
        if (node == NULL) {
            fprintf(stderr, "[x] Memory Allocation! [FAILED]");
            return 1;
        }

        // Ask user to enter number.
        printf("Enter data for node %d: ", i + 1);
        scanf("%d%*c", &node->number);

        node->next = NULL;

        // Point the head to the node.
        // Check if list is empty.
        if (head == NULL) {
            head = node;
        }
        else {
            // Iterate over nodes in list.
            for (Node *ptr = head; ptr != NULL; ptr = ptr->next) {
                // If at the end of list.
                if (ptr->next == NULL) {
                    ptr->next = node;
                    break;
                }
            }
        }
    }

    // Display the data in the nodes.
    printf("Data entered in the list:\n");
    Node *ptr = head;
    
    while (ptr != NULL) {
        printf("Data = %d\n", ptr->number);
        ptr = ptr->next;
    }

    // Free a node from memory.
    Node *clean = head;
    while (clean != NULL) {
        Node *next = clean->next;
        free(clean);
        clean = next;
    }
    return 0;
}
