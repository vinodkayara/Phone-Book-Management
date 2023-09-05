

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Contact {
    char name[50];
    char phoneNumber[15];
    char email[100];
    struct Contact* next;
};


void addContact();
void searchContact();
void displayContacts();
void updateContact();
void deleteContact();
void saveContactsToFile();
void loadContactsFromFile();

struct Contact* head = NULL;

int main() {
    int choice;


    loadContactsFromFile();

    do {
        printf("\nPhone Book Management System\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display Contacts\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                displayContacts();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                saveContactsToFile();
                break;
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    
    saveContactsToFile();


    struct Contact* current = head;
    while (current) {
        struct Contact* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}



void addContact() {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        printf("Memory allocation failed. Unable to add contact.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", newContact->name);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", newContact->phoneNumber);


    if (strlen(newContact->phoneNumber) > 10) {
        printf("Error: Phone number cannot have more than 10 digits. Contact not added.\n");
        free(newContact);
        return;
    }

 
     printf("Enter Email: ");
    scanf(" %[^\n]", newContact->email);
    if (strstr(newContact->email, "@gmail.com") == NULL) {
        printf("Error: Email address must include '@gmail.com'. Contact not added.\n");
        free(newContact);
        return;
    }

    newContact->next = NULL;
    

    if (head == NULL) {
        head = newContact;
    } else {
        struct Contact* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newContact;
    }

    printf("Contact added successfully.\n");
}

void searchContact() {
    if (head == NULL) {
        printf("Phone book is empty. No contacts to search.\n");
        return;
    }

    char searchTerm[50];
    printf("Enter Name or Phone Number to search: ");
    scanf(" %[^\n]", searchTerm);

    struct Contact* current = head;
    int found = 0;

    while (current) {
        if (strcmp(current->name, searchTerm) == 0 || strcmp(current->phoneNumber, searchTerm) == 0) {
            printf("Contact found:\n");
            printf("Name: %s\n", current->name);
            printf("Phone Number: %s\n", current->phoneNumber);
            printf("Email: %s\n", current->email);
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Contact not found.\n");
    }
}

void displayContacts() {
    if (head == NULL) {
        printf("Phone book is empty. No contacts to display.\n");
        return;
    }

    printf("Contacts in the Phone Book:\n");
    struct Contact* current = head;

    while (current) {
        printf("Name: %s\n", current->name);
        printf("Phone Number: %s\n", current->phoneNumber);
        printf("Email: %s\n", current->email);
        printf("-----------------------\n");
        current = current->next;
    }
}

void updateContact() {
    if (head == NULL) {
        printf("Phone book is empty. No contacts to update.\n");
        return;
    }

    char searchTerm[50];
    printf("Enter Name or Phone Number of the contact to update: ");
    scanf(" %[^\n]", searchTerm);

    struct Contact* current = head;
    int found = 0;

    while (current) {
        if (strcmp(current->name, searchTerm) == 0 || strcmp(current->phoneNumber, searchTerm) == 0) {
            printf("Enter updated Name: ");
            scanf(" %[^\n]", current->name);
            printf("Enter updated Phone Number: ");
            scanf(" %[^\n]", current->phoneNumber);
            printf("Enter updated Email: ");
            scanf(" %[^\n]", current->email);
            printf("Contact updated successfully.\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Contact not found.\n");
    }
}

void deleteContact() {
    if (head == NULL) {
        printf("Phone book is empty. No contacts to delete.\n");
        return;
    }

    char searchTerm[50];
    printf("Enter Name or Phone Number of the contact to delete: ");
    scanf(" %[^\n]", searchTerm);

    struct Contact* current = head;
    struct Contact* previous = NULL;
    int found = 0;

    while (current) {
        if (strcmp(current->name, searchTerm) == 0 || strcmp(current->phoneNumber, searchTerm) == 0) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Contact deleted successfully.\n");
            found = 1;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (!found) {
        printf("Contact not found.\n");
    }
}

void saveContactsToFile() {
    FILE* file = fopen("phonebook.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Contact* current = head;

    while (current) {
        fprintf(file, "%s,%s,%s\n", current->name, current->phoneNumber, current->email);
        current = current->next;
    }

    fclose(file);
    printf("Contacts saved to file successfully.\n");
}

void loadContactsFromFile() {
    FILE* file = fopen("phonebook.txt", "r");
    if (file == NULL) {

        return;
    }

    char line[200];

    while (fgets(line, sizeof(line), file)) {
        char* name = strtok(line, ",");
        char* phoneNumber = strtok(NULL, ",");
        char* email = strtok(NULL, "\n");

        struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
        if (newContact == NULL) {
            printf("Memory allocation failed. Unable to load contact.\n");
            return;
        }

        strcpy(newContact->name, name);
        strcpy(newContact->phoneNumber, phoneNumber);
        strcpy(newContact->email, email);
        newContact->next = NULL;

        if (head == NULL) {
            head = newContact;
        } else {
            struct Contact* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newContact;
        }
    }

    fclose(file);
    printf("Contacts loaded from file successfully.\n");
}
