// Linked list implementation of stack data structure.

#include <stdio.h>
#include <stdlib.h>

// Globals.
struct Node
{
    int data;
    struct Node *next;
} *top = NULL;

// Function Prototypes.
void push(int data);
void print();
int pop();
int isEmpty();
int peek();

int main(void)
{
    int choice, data;
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Print all data\n4. Print first data\n5. Quit\n\nPlease enter your choice(1, 2, 3, 4, 5): ");
        scanf("%d%*c", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to push onto the stack: ");
                scanf("%d%*c", &data);
                push(data);
                break;
            case 2:
                data = pop();
                printf("\n[+] Popped %d from the stack [SUCCESS]\n", data);
                break;
            case 3:
                print();
                break;
            case 4:
                printf("\n[+] Top Element => [%d]\n", peek());
                break;
            case 5:
                exit(1);
            default:
                printf("Invalid Choice!\n");
                break;
        }
    
    }
    return 0;

}

void push(int data)
{
    // Create a node.
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "[x] Stack Overflow! [FAILED]\n");
        exit(1);
    }

    // Store data inside node.
    node->data = data;
    node->next = NULL;

    // Point top to new node.
    node->next = top;
    top = node;
}

int pop()
{
    // Check if stack is empty.
    if (isEmpty()) {
        printf("[x] Stack Underflow! [FAILED]\n");
        exit(1);
    }
    // Store the data in a variable.
    int data = top->data;
    
    struct Node *ptr = top;
    top = top->next;
    free(ptr);
    ptr = NULL;

    return data;
}

void print()
{
    // Check if stack is empty.
    if (isEmpty()) {
        fprintf(stderr, "[x] Stack Is Empty! [FAILED]\n");
        return;
    }

    // Traverse and display data on the stack.
    struct Node *ptr = top;
    while (ptr != NULL) {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
}

int isEmpty()
{
    if (top == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int peek()
{
    // Check if stack is empty.
    if (isEmpty()) {
        printf("[x] Stack Underflow! [FAILED]\n");
        return 1;
    }

    return top->data;

}
