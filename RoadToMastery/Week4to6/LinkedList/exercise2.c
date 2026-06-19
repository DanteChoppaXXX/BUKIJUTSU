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
    // Create a head node pointer.
    Node *head = NULL;

    // Ask user for number of nodes.
    int numOfNodes;

    printf("Enter number of nodes: ");
    scanf("%d%*c", &numOfNodes);

    // Create the nodes.
    for (int i = 0; i < numOfNodes; i++)
    {
        Node *node = malloc(sizeof(Node));
        if (node == NULL) {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]");
        return 1;
        }
        
        // Ask the user for number to store in the node data field.
        printf("Enter number for node %d: ", i + 1);
        scanf("%d%*c", &node->number);

        node->next = NULL;

        // Check if list is empty.
        if (head == NULL) {
            head = node;
        }
        else {
            // Append the node to the list.
            Node *ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = node;
        }
    }

    // Display the content of the linked list to the user.
    Node *ptr = head;
    int count = 0;
    while (ptr != NULL) {
        count++;
        printf("Node %d Data => %d\n", count, ptr->number);
        ptr = ptr->next;
    }

    printf("\nFreeing Nodes...\n"); 

    // Free all nodes.
    Node *clean = head;
    while (clean != NULL) {
        head = head->next;
        free(clean);
        clean = head;
    }
    printf("[+] All Nodes Freed [SUCCESS]\n"); 

    return 0;
}
