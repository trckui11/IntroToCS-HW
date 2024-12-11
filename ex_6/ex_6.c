/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_6
*Submit username: feldmaaf
******************************************/

#include "BinTree.h"

/*************************************************************************
* function name: askTreeOrder *
* The Input: none *
* The output: prints the smaller menu to choose the print order *
* The Function operation: prints the smaller menu and asks to choose order *
*************************************************************************/

int askTreeOrder() {
    // For when you choose the order of printing:
    printf("please choose order:\n"
           "(1) preorder\n"
           "(2) inorder\n"
           "(3) postorder\n");
    int order;
    scanf("%d", &order);
    return order;
}

int main() {
    // To know when to exit the while loop:
    int exitProgram = FALSE;
    // The root of the tree:
    BinTree* allJews = NULL;

    while (!exitProgram) {
        printf("please choose action:\n"
               "(1) A child was born\n"
               "(2) Throw into the Nile\n"
               "(3) Find Moshe\n"
               "(4) Print All\n"
               "(5) Size of jews\n"
               "(6) Exit\n");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                // A child was born:
                ;
                // creating the child:
                BinTree* newChild = createChild();
                // if the tree is empty, add it manually:
                if (!allJews)
                    allJews = newChild;
                else
                    addChild(allJews, newChild);

                break;
            case 2:
                // Throw into the Nile:
                ;

                // activates throwToNile and checks if the tree is empty:
                if (generic_int_function(allJews, throwToNile))
                    allJews = NULL;

                break;
            case 3:
                // Find Moshe:
                ;
                // prints the small menu and asks for the order:
                int order = askTreeOrder();
                int wrongOrder = FALSE;

                // activates the child's tasks according to the chosen order:
                switch (order) {
                    case 1:
                        // preorder:
                        generic_function(allJews, childTaskPreorder);

                        break;
                    case 2:
                        // inorder:
                        generic_function(allJews, childTaskInorder);

                        break;
                    case 3:
                        // postorder:
                        generic_function(allJews, childTaskPostorder);

                        break;
                    default:
                        printf("wrong order!\n");
                        wrongOrder = TRUE;
                }
                // End of smaller switch-case.

                if (!wrongOrder) {
                    // checks if moshe is in the tree:
                    if (generic_int_function(allJews, findMoshe)) {
                        // activates throwToNile and checks if tree is empty:
                        if (generic_int_function(allJews, throwToNile))
                            allJews = NULL;
                    }
                    else
                        printf("Moshe Not Found!\n");
                }

                break;

            case 4:
                // Print All:
                order = askTreeOrder();

                // prints the tree according to the chosen order:
                switch (order) {
                    case 1:
                        // preorder:
                        generic_function(allJews, printPreorder);

                        break;
                    case 2:
                        // inorder:
                        generic_function(allJews, printInorder);

                        break;
                    case 3:
                        // postorder:
                        generic_function(allJews, printPostorder);

                        break;
                    default:
                        printf("wrong order!\n");
                }
                // End of smaller switch-case.

                break;
            case 5:
                // Size of jews:
                printf("please choose what you want to calculate:\n"
                       "(1) All jews\n"
                       "(2) Male\n"
                       "(3) Female\n");
                int choice;
                scanf("%d", &choice);
                // activates the counting function according to the chosen option:
                switch(choice) {
                    case 1:
                        // All jews:
                        printf("size of all jews is: %d\n",
                               generic_int_function(allJews, sizeAllJews));

                        break;
                    case 2:
                        // Male jews:
                        printf("size of all male jews is: %d\n",
                               generic_int_function(allJews, sizeAllMales));

                        break;
                    case 3:
                        // Female jews:
                        printf("size of all female jews is: %d\n",
                               generic_int_function(allJews, sizeAllFemales));

                        break;
                    default:
                        ;
                }
                // End of smaller switch-case.

                break;
            case 6:
                // Exit:
                exitProgram = TRUE;
                break;
            default:
                printf("wrong choose please choose again\n");
        }
        // End of switch-case.

        // increase everyone's age:
        if (generic_int_function(allJews, increaseAge)) {
            // if Moshe is 80 years old it frees everyone:
            generic_function(allJews, freeIsrael);
            return 0;
        } else if (!exitProgram)
            printf("\n");

        // activates checkDieAge and checks if the tree is empty:
        if (generic_int_function(allJews, checkDieAge))
            allJews = NULL;
    }
    // End of while loop.

    // Destroy the tree:
    generic_function(allJews, freeIsrael);

    return 0;
}
// End of main.
