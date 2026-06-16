// INTERACTIVE HEAP-BASED CONTACT MANAGER.
// This program allows users to create and store contact, edit, search, and delete contacts.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
int count = 0;
int i = 0;

// Data Structure for contacts
typedef struct
{
    char name[64];
    char phone[32];
    char email[128];

} Contact;

enum Actions{
    store = 1,
    delete = 2,
    edit = 3,
    search = 4,
    list = 5,
    quit = 6,
};

// Function Prototypes.
void menu(void *arg);
void storeContact(void *arg);
void listContact(void *arg);
void deleteContact(void *arg);
void editContact(void *arg);
void searchContact(void *arg);

int main(void)
{
    // Create a dynamic array of contacts.
    Contact *contacts = calloc(SIZE, sizeof(Contact));
    if (contacts == NULL)
    {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]\n");
        return 0;
    }
  
    menu(contacts);

    free(contacts);
}

void menu(void *arg)
{
    Contact *contact = arg;
    int action;

    while (1) {
    
        printf("\nCONTACT MANAGER\n\n");
        printf("[1] Store Contact\n");
        printf("[2] Delete Contact\n");
        printf("[3] Edit Contact\n");
        printf("[4] Search Contact\n");
        printf("[5] List Contacts\n");
        printf("[6] Exit\n");
        
        printf("\nChoose [1, 2, 3, 4, 5, 6]\n");
        scanf("%d%*c", &action);
        
        switch (action) {
        
            case store:
                storeContact(contact);
                break;
            case delete:
                deleteContact(contact);
                break;
            case edit:
                editContact(contact);
                break;
            case search:
                searchContact(contact);
                break;  
            case list:
                listContact(contact);
                break; 
            case quit:
                return;
            default:
                printf("[x] Invalid Input! [FAILED]\n");
                break;
        }
        // continue;
    }
}

void storeContact(void *arg)
{
    Contact *contact = arg;
    // Prompt the user to imput name, phone and email.
    
    printf("[+] Enter Contact Details ('q' to go back)[+]\n");
    // Name.
    printf("Name: ");
    fgets(contact[i].name, sizeof(contact[i].name), stdin);
    contact[i].name[strcspn(contact[i].name, "\n")] = '\0';
    if (strcmp(contact[i].name, "q") == 0) {
        return;
    }
    
    // Phone number.
    printf("Phone: ");
    fgets(contact[i].phone, sizeof(contact[i].phone), stdin);
    contact[i].phone[strcspn(contact[i].phone, "\n")] = '\0';
    if (strcmp(contact[i].phone, "q") == 0) {
        return;
    }

    // Email Address.
    printf("Email: ");
    fgets(contact[i].email, sizeof(contact[i].email), stdin);
    contact[i].email[strcspn(contact[i].email, "\n")] = '\0';
    if (strcmp(contact[i].email, "q") == 0) {
        return;
    }
    i++;
    count++;
   
}

void listContact(void *arg)
{
    Contact *contact = arg;

    // Display the contacts.
    printf("\n[+] CONTACTS [+]\n");

    for (int i = 0; i < count; i++) {
        
        printf("[%d]\n", i + 1);
        printf("Name: \t%s\n", contact[i].name);
        printf("Phone: \t%s\n", contact[i].phone);
        printf("Email: \t%s\n\n", contact[i].email);
    }
    return;
}

void deleteContact(void *arg)
{
    Contact *contact = arg;
    int index;

    // Display the contacts.
    listContact(contact);

    // Ask the user to choose the contact to be deleted based on it's index.
    printf("Choose contact to delete by entering it's index (1, 2, 3, ...)('q' to go back): \n");
    scanf("%d%*c", &index);
    if (strcmp((char *)&index, "q") == 0) {
        return;
    }
    // Delete the contact.
    memset(&contact[index - 1], 0, sizeof(contact[index - 1]));
    printf("[-] Contact Deleted! [-]\n");

    return;
}

void editContact(void *arg)
{
    Contact *contact = arg;
    int i;

    // Ask the user to choose the contact to be edited based on it's index.
    printf("Choose contact to edit by entering it's index (1, 2, 3, ...): \n");
    scanf("%d%*c", &i);

    i = i - 1;

    printf("[+] Enter Contact Details ('q' to go back)[+]\n");
    // Name.
    printf("Name: ");
    fgets(contact[i].name, sizeof(contact[i].name), stdin);
    contact[i].name[strcspn(contact[i].name, "\n")] = '\0';
    if (strcmp(contact[i].name, "q") == 0) {
        return;
    }

    // Phone number.
    printf("Phone: ");
    fgets(contact[i].phone, sizeof(contact[i].phone), stdin);
    contact[i].phone[strcspn(contact[i].phone, "\n")] = '\0';
    if (strcmp(contact[i].phone, "q") == 0) {
        return;
    }

    // Email Address.
    printf("Email: ");
    fgets(contact[i].email, sizeof(contact[i].email), stdin);
    contact[i].email[strcspn(contact[i].email, "\n")] = '\0';
    if (strcmp(contact[i].email, "q") == 0) {
        return;
    }
    
    return;
}

void searchContact(void *arg)
{
    Contact *contact = arg;
    char buffer[64];
    int found = 0;

    // Ask the user to enter any string.
    printf("Search: ('q' to go back)");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strcmp(buffer, "q") == 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        if (strcasecmp(contact[i].name, buffer) == 0 || 
            strcasecmp(contact[i].phone, buffer) == 0 || 
            strcasecmp(contact[i].email, buffer) == 0) {

            printf("[+] Contact Found! [SUCCESS]\n");
            printf("Name: \t%s\n", contact[i].name);
            printf("Phone: \t%s\n", contact[i].phone);
            printf("Email: \t%s\n\n", contact[i].email);

            found = 1;
        }
    }

    if (!found) {
        printf("[x] Contact Not Found! [FAILED]\n");
    }

    return;
}

