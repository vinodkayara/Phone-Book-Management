#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Contact {
    char name[50];
    char phoneNumber[15];
    char email[100];
    struct Contact* next;
};

void adminMenu();
void userMenu();
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
    int isAdmin = 0;

    printf("Phone Book Management System\n");
    printf("Are you an admin? (1 for Admin, 0 for User): ");
    scanf("%d", &isAdmin);

    loadContactsFromFile();

    if (isAdmin) {
        adminMenu();
    } else {
        userMenu();
    }

    struct Contact* current = head;
    while (current) {
        struct Contact* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

void adminMenu() {
    int choice;

    do {
        printf("\nAdmin Menu\n");
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
}

void userMenu() {
    int choice;

    do {
        printf("\nUser Menu\n");
        printf("1. Search Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);
}




void addContact() {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        printf("Memory allocation failed. Unable to add contact.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", newContact->name);

    char phoneNumber[15];
    int isValidPhoneNumber = 0;
    do {
        printf("Enter Phone Number (up to 10 digits, no letters): ");
        scanf(" %[^\n]", phoneNumber);
        isValidPhoneNumber = 1;
        for (int i = 0; phoneNumber[i] != '\0'; i++) {
            if (!isdigit(phoneNumber[i])) {
                isValidPhoneNumber = 0;
                break;
            }
        }
        if (!isValidPhoneNumber || strlen(phoneNumber) >10 || strlen(phoneNumber) < 10) {
            printf("Invalid phone number. Please enter a valid phone number with up to 10 digits and no letters.\n");
        }
    } while (!isValidPhoneNumber || strlen(phoneNumber) > 10 || strlen(phoneNumber) < 10);
    strcpy(newContact->phoneNumber, phoneNumber);

   
    char email[100];
    int isValidEmail = 0;
    do {
        printf("Enter Email (must contain '@gmail.com'): ");
        scanf(" %[^\n]", email);
        isValidEmail = (strstr(email, "@gmail.com") != NULL);
        if (!isValidEmail) {
            printf("Invalid email. Please enter an email containing '@gmail.com'.\n");
        }
    } while (!isValidEmail);
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
            printf("Contact found:\n");
            printf("1. Update Name\n");
            printf("2. Update Phone Number\n");
            printf("3. Update Email\n");
            printf("4. Cancel\n");
            printf("Enter your choice: ");
            int updateChoice;
            scanf("%d", &updateChoice);

            switch (updateChoice) {
                case 1:
                    printf("Enter updated Name: ");
                    scanf(" %[^\n]", current->name);
                    break;
                case 2:
                    // Validate and update phone number (similar to the addContact function)
                    char phoneNumber[15];
                    int isValidPhoneNumber = 0;
                    do {
                        printf("Enter updated Phone Number (up to 10 digits, no letters): ");
                        scanf(" %[^\n]", phoneNumber);
                        isValidPhoneNumber = 1;
                        for (int i = 0; phoneNumber[i] != '\0'; i++) {
                            if (!isdigit(phoneNumber[i])) {
                                isValidPhoneNumber = 0;
                                break;
                            }
                        }
                        if (!isValidPhoneNumber || strlen(phoneNumber) > 10) {
                            printf("Invalid phone number. Please enter a valid phone number with up to 10 digits and no letters.\n");
                        }
                    } while (!isValidPhoneNumber || strlen(phoneNumber) > 10);
                    strcpy(current->phoneNumber, phoneNumber);
                    break;
                case 3:
                    // Validate and update email (similar to the addContact function)
                    char email[100];
                    int isValidEmail = 0;
                    do {
                        printf("Enter updated Email (must contain '@gmail.com'): ");
                        scanf(" %[^\n]", email);
                        isValidEmail = (strstr(email, "@gmail.com") != NULL);
                        if (!isValidEmail) {
                            printf("Invalid email. Please enter an email containing '@gmail.com'.\n");
                        }
                    } while (!isValidEmail);
                    strcpy(current->email, email);
                    break;
                case 4:
                    printf("Update canceled.\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
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