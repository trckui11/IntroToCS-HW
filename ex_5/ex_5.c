/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_5
*System username: feldmaaf
******************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 11

// Length of the phonebook (26):
const int abcLen = 'Z' - 'A' + 1;

typedef struct Contact {
    char *firstName;
    char *lastName;
    char *phoneNum;
    struct Contact *next;
} Contact;

/************************************************************************
* function name: doesPhoneExist *
* The Input: The phonebook and a phone number. *
* The output: If the phone is in the phonebook it returns a pointer to the
 * contact with that phone number, if not it returns NULL. *
* The Function operation: The function goes through the whole phonebook and
 * compares each phone number in it with the one it got. *
*************************************************************************/

Contact *doesPhoneExist(Contact *phoneBook[], char *findPhone) {
    for (int i = 0; i < abcLen; i++) {
        // The checker is used to go through all the contacts:
        Contact *checker = phoneBook[i];
        while (checker) {
            if (!strcmp(checker->phoneNum, findPhone))
                return checker;
            checker = checker->next;
        }
    }
    // If the loop ends it means the phone num wasn't found, so returns NULL:
    return NULL;
}

/************************************************************************
* function name: addContact *
* The Input: The phonebook. *
* The output: None. *
* The Function operation: the function does the entire 1st case. It asks the
 * user for a name and number and allocates the memory for them, then checks
 * if the contact's name or number already exist (using the "doesPhoneExist"
 * function) and if not adds ot to the phonebook. It also prints messages
 * accordingly. *
*************************************************************************/

void addContact(Contact *phoneBook[]) {
    int allocFail = 0;
    Contact *newContact = (Contact *) malloc(sizeof(Contact));
    char *newFirstName = (char *) malloc(sizeof(char) * MAX_STRING);
    char *newLastName = (char *) malloc(sizeof(char) * MAX_STRING);
    char *newPhoneNum = (char *) malloc(sizeof(char) * MAX_STRING);
    if (!newFirstName || !newLastName || !newPhoneNum || !newContact)
        allocFail = 1;

    printf("Enter a contact details "
           "(<first name> <last name> <phone number>): ");
    scanf("%s %s %s", newFirstName, newLastName, newPhoneNum);
    // I used "allocFail" so that I can print the message after the scanf:
    if (allocFail) {
        printf("The addition of the contact has failed!");
        free(newFirstName);
        free(newLastName);
        free(newPhoneNum);
        free(newContact);
        return;
    }

    // Inserting the information into the new contact:
    newContact->firstName = newFirstName;
    newContact->lastName = newLastName;
    newContact->phoneNum = newPhoneNum;
    newContact->next = NULL;

    // This is the index of the book according to first letter of last name:
    int bookIndex = newLastName[0] - 'A';
    // This checker points to the list's pointers:
    Contact **checker = &phoneBook[bookIndex];

    // Checks if the name already exists:
    while (*checker) {
        if ((!strcmp((*checker)->firstName, newFirstName)) &&
            (!strcmp((*checker)->lastName, newLastName))) {
            printf("The addition of the contact has failed, "
                   "since the contact %s %s already exists!\n",
                   newFirstName, newLastName);
            free(newContact);
            free(newFirstName);
            free(newLastName);
            free(newPhoneNum);
            return;
        }
        // Movies the checker to the next contact:
        checker = &((*checker)->next);
    }

    // Checks if the number already exists:
    if (doesPhoneExist(phoneBook, newPhoneNum)) {
        printf("The addition of the contact has failed, "
               "since the phone number %s already exists!\n",
               newPhoneNum);
        free(newContact);
        free(newFirstName);
        free(newLastName);
        free(newPhoneNum);
        return;
    }
    // Checks if there are no contacts with that letter in the phonebook:
    if (!phoneBook[bookIndex])
        phoneBook[bookIndex] = newContact;
    else {
        // If not then it goes to the end of the list and adds the contact:
        checker = &phoneBook[bookIndex];
        while (*checker)
            checker = &((*checker)->next);
        *checker = newContact;
    }
    printf("The contact has been added successfully!\n");
}
// End of function addContact

/************************************************************************
* function name: deleteContact *
* The Input: The phonebook. *
* The output: None. *
* The Function operation: The function does the entire 2nd case. It asks the
 * user for a name to delete and checks if it is indeed in the phonebook, then
 * deletes it if it is. It also prints messages accordingly. *
*************************************************************************/

void deleteContact(Contact *phoneBook[]) {
    // you sure is to check if the user is sure:
    char youSure;
    // these 2 arrays are to scan the contact name into:
    char delFirstName[MAX_STRING];
    char delLastName[MAX_STRING];

    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", delFirstName, delLastName);
    // clean the buffer:
    while (getchar() != '\n') {}
    // the index of the first letter in the phone book:
    int bookIndex = delLastName[0] - 'A';

    Contact *current = phoneBook[bookIndex];
    // previous is to keep track of the previous contact to connect it to next
    Contact *previous;
    while (current) {
        // check if the name matches:
        if ((!strcmp(current->firstName, delFirstName)) &&
            (!strcmp(current->lastName, delLastName))) {
            printf("Are you sure? (y/n) ");
            scanf("%c", &youSure);
            if (youSure == 'Y' || youSure == 'y') {
                printf("The contact has been deleted successfully!\n");
                // if the contact is first on the list:
                if (current == phoneBook[bookIndex])
                    phoneBook[bookIndex] = current->next;
                else
                    previous->next = current->next;
                // free the allocs:
                free(current->firstName);
                free(current->lastName);
                free(current->phoneNum);
                free(current);
                current = NULL;
            } else {
                printf("The deletion of the contact has been canceled.\n");
            }
            return;
        }
        previous = current;
        current = current->next;
    }
    // End of while loop
    printf("The deletion of the contact has failed!\n");
}
// End of function deleteContact

/************************************************************************
* function name: findByPhone *
* The Input: The phonebook. *
* The output: None. *
* The Function operation: The function does the entire 3rd case. It asks the
 * user for a phone number to find and checks if it is indeed in the phonebook
 * using the "doesPhoneExist" function, then prints the contact if it is in
 * the phonebook. It also prints messages accordingly. *
*************************************************************************/

void findByPhone(Contact *phoneBook[]) {
    // array to scan the phone num into:
    char findPhone[MAX_STRING];
    printf("Enter a phone number: ");
    scanf("%s", findPhone);

    // checks if the phone num is in the book:
    Contact *conToFind = doesPhoneExist(phoneBook, findPhone);
    // if so, print it:
    if (conToFind) {
        printf("The following contact was found: %s %s %s\n",
               conToFind->firstName, conToFind->lastName, findPhone);
        return;
    }
    printf("No contact with a phone number %s was found in the phone book\n",
           findPhone);
}

/************************************************************************
* function name: findByName *
* The Input: The phonebook. *
* The output: If it finds the name the it returns a pointer to that contact,
 * if not then NULL. *
* The Function operation: The function does the entire 4th case. It asks the
 * user for a name to find and checks if it is indeed in the phonebook, then
 * prints the contact if it is. It also prints messages accordingly. *
*************************************************************************/

Contact *findByName(Contact *phoneBook[]) {
    // these 2 arrays are to scan the name into:
    char findFirstName[MAX_STRING];
    char findLastName[MAX_STRING];
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", findFirstName, findLastName);

    Contact *checker = phoneBook[findLastName[0] - 'A'];
    // go through the book and check if the name matches:
    while (checker) {
        if ((!strcmp(checker->firstName, findFirstName)) &&
            (!strcmp(checker->lastName, findLastName))) {
            printf("The following contact was found: %s %s %s\n",
                   findFirstName, findLastName, checker->phoneNum);
            return checker;
        }
        checker = checker->next;
    }
    printf("No contact with a name %s %s was found in the "
           "phone book\n", findFirstName, findLastName);
    return NULL;
}
// End of function findByName

/************************************************************************
* function name: updatePhone *
* The Input: The phonebook. *
* The output: None. *
* The Function operation: The function does the entire 5th case. Using the
 * "findByName" function, it asks the user for a name and locates it in the
 * phonebook. Then it asks for the new phone number and uses the
 * "doesPhoneExist" function to check if it's already in the phonebook. if it
 * isn't, it changes the number to the new one. It also prints messages
 * accordingly. *
*************************************************************************/

void updatePhone(Contact *phoneBook[]) {
    // finds the contact in the book:
    Contact *conToChange = findByName(phoneBook);
    // if found, ask for new phone:
    if (conToChange) {
        // array to scan phone into:
        char newPhone[MAX_STRING];
        printf("Enter the new phone number: ");
        scanf("%s", newPhone);
        // checks if phone already exists:
        if (doesPhoneExist(phoneBook, newPhone)) {
            printf("The update of the contact has failed, since "
                   "the phone number %s already exists!\n", newPhone);
            return;
        }
        printf("The contact has been updated successfully!\n");
        // replace phone num with new one:
        strcpy(conToChange->phoneNum, newPhone);
    }
}

/************************************************************************
* function name: printPhoneBook *
* The Input: The phonebook. *
* The output: None. *
* The Function operation: The function does the entire 6th case. It goes
 * through the phonebook and prints each linked list from the end using a
 * counter to know when to print. *
*************************************************************************/

void printPhoneBook(Contact *phoneBook[]) {
    // this goes through the book and prints the lists:
    for (int i = 0; i < abcLen; i++) {
        Contact *printer = phoneBook[i];
        int counter = 0;
        // this checks the length of the list:
        while (printer) {
            printer = printer->next;
            counter++;
        }
        // this prints the list from the end going backwards:
        for (int k = counter; k > 0; k--) {
            printer = phoneBook[i];
            for (int l = 1; l < k; l++)
                printer = printer->next;
            int j;
            printf("%s", printer->firstName);
            // complete the spaces:
            for (j = 0; j < MAX_STRING - strlen(printer->firstName); j++)
                printf(" ");
            printf("%s", printer->lastName);
            for (j = 0; j < MAX_STRING - strlen(printer->lastName); j++)
                printf(" ");
            printf("%s", printer->phoneNum);
            for (j = 0; j < MAX_STRING - strlen(printer->phoneNum); j++)
                printf(" ");
            printf("\n");
        }
    }
}
// End of function printPhoneBook

/************************************************************************
* function name: freeList *
* The Input: The head of the list you want to free. *
* The output: None. *
* The Function operation: The function frees the whole list of contact
 * allocations. It is using recursion to get to the end of the list (NULL is
 * the stopping signal) and frees the contacts and their details from the end
 * to the beginning (if you free the head first you won't have access to free
 * the rest of the list). *
*************************************************************************/

void freeList(Contact *freeHead) {
    // recursive freeing, stops when null and frees from the end of the list:
    if (freeHead) {
        freeList(freeHead->next);
        // set freed pointer to null:
        freeHead->next = NULL;
        // free all allocs:
        free(freeHead->firstName);
        free(freeHead->lastName);
        free(freeHead->phoneNum);
        free(freeHead);
        return;
    }
}

int main() {

    /*
     * Variables:
     * - option is for the menu choise.
     * - exitProgram is for case 7, so the while would stop.
     * - menuWrong is for incorrect inputs in the menu, so it would know not
     * to print it again.
     */

    int option, exitProgram = 0, menuWrong = 0;

    Contact *phoneBook[abcLen];
    // Initialize the phonebook to NULL:
    for (int i = 0; i < abcLen; i++)
        phoneBook[i] = NULL;

    while (!exitProgram) {
        if (!menuWrong) {
            printf("Welcome to the phone book manager!\n"
                   "Choose an option:\n"
                   "1. Add a new contact to the phone book.\n"
                   "2. Delete a contact from the phone book.\n"
                   "3. Find a contact in the phone book by phone number.\n"
                   "4. Find a contact in the phone book by name.\n"
                   "5. Update phone number for a contact.\n"
                   "6. Print phone book.\n"
                   "7. Exit.\n");
        }
        menuWrong = 0;

        scanf("%d", &option);
        switch (option) {
            case 1:
                // Add a new contact to the phone book.
                addContact(phoneBook);

                break;
            case 2:
                // Delete a contact from the phone book.
                deleteContact(phoneBook);

                break;
            case 3:
                // Find a contact in the phone book by phone number.
                findByPhone(phoneBook);

                break;
            case 4:
                // Find a contact in the phone book by name.
                findByName(phoneBook);

                break;
            case 5:
                // Update phone number for a contact.
                updatePhone(phoneBook);

                break;
            case 6:
                // Print phone book.
                printPhoneBook(phoneBook);

                break;
            case 7:
                // Exit.
                printf("Bye!");
                exitProgram = 1;

                break;
            default:
                printf("Wrong option, try again:\n");
                menuWrong = 1;
        }
        // End of switch

    }
    // End of while loop

    // This goes through the phonebook and frees each linked list:
    for (int i = 0; i < abcLen; i++) {
        Contact *freer = phoneBook[i];
        freeList(freer);
    }

    return 0;
}
// End of main
