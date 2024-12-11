/******************************************
*Student name: Arbel Feldman
*Student ID: 216303990
*Exercise name: ex_6
*Submit username: feldmaaf
******************************************/

#include "BinTree.h"

/*************************************************************************
* function name: generic_function *
* The Input: the root of the tree and a void function to perform on the tree *
* The output: none *
* The Function operation: activates the inputted function on the root of the
 * tree *
*************************************************************************/

void generic_function(BinTree* root, void(*task)(void*)) {
    task(root);
}

/*************************************************************************
* function name: generic_int_function *
* The Input: the root of the tree and a function to perform on the tree that
 * returns int *
* The output: none *
* The Function operation: activates the inputted function on the root of the
 * tree and returns whatever it returns *
*************************************************************************/

int generic_int_function(BinTree* root, int(*task)(void*)) {
    return task(root);
}

/*************************************************************************
* function name: createChild *
* The Input: none *
* The output: a pointer to the child it created *
* The Function operation: asks the user for information about the new child
 * and creates the object of the child *
*************************************************************************/

BinTree* createChild() {
    // allocates space for the child:
    BinTree* newChild = (BinTree*) malloc(sizeof(BinTree));
    if (!newChild)
        exit(1);

    printf("please enter child id:\n");
    int newID;
    scanf("%d", &newID);

    printf("please insert child name:\n");
    // allocates space for the name:
    char* newName = (char*) malloc(MAX_STRING * sizeof(char));
    if (!newName) {
        free(newChild);
        exit(1);
    }
    scanf("%s", newName);

    printf("please insert child gender:\n");
    char newGender;
    scanf(" %c", &newGender);

    // puts the inputted info into the child:
    newChild->id = newID;
    newChild->name = newName;
    // starts at negative because it increases it immediately:
    newChild->age = -AGE_PER_ITERATION;
    newChild->gender = newGender;
    // checks if the child is the leader to give according task:
    if (!strcmp(newName, LEADER) && newGender == MALE)
        newChild->task = moshe_task;
    else
        newChild->task = child_task;
    newChild->action = newChild->name;
    newChild->left = NULL;
    newChild->right = NULL;
    newChild->parent = NULL;

    return newChild;
}
// End of function createChild.

/*************************************************************************
* function name: addChild *
* The Input: the tree's root and the child to add *
* The output: none *
* The Function operation: goes through the tree while matching the child's id
 * and placing it in the right place *
*************************************************************************/

void addChild(BinTree* root, BinTree* child) {
    // if the child id is bigger, it goes right:
    if (root->id < child->id) {
        if (root->right) {
            addChild(root->right, child);
            return;
        }
        // if it reaches the end it connects the child to the tree:
        root->right = child;
    // if the child id is smaller, it goes left:
    } else if (root->id > child->id) {
        if (root->left) {
            addChild(root->left, child);
            return;
        }
        // if it reaches the end it connects the child to the tree:
        root->left = child;
    }
    // if the child is the root it has no parent:
    if (child != root)
        child->parent = root;
}
// End of function addChild.

/*************************************************************************
* function name: child_task *
* The Input: the name of the child *
* The output: prints "<name> cry waaaa" *
* The Function operation: prints "<name> cry waaaa" *
*************************************************************************/

void child_task(void* val) {
    // casting the input to char pointer:
    char* valCast = (char*) val;
    printf("%s cry waaaa\n", valCast);
}

/*************************************************************************
* function name: moshe_task *
* The Input: the child's name (moshe) *
* The output: prints "<name> quiet" *
* The Function operation: prints "<name> quiet" (moshe) *
*************************************************************************/

void moshe_task(void* val) {
    // casting the input to char pointer:
    char* valCast = (char*) val;
    printf("%s quiet\n", valCast);
}

/*************************************************************************
* function name: increaseAge *
* The Input: the tree's root *
* The output: returns 1 if the leader is at his dying age *
* The Function operation: goes through the tree inorder and increases all the
 * children's ages by AGE_PER_ITERATION (20).
* also checks if moshe is 80 years old. if he is, it frees Israel. *
*************************************************************************/

int increaseAge(void* root) {
    // casting the input to BinTree pointer:
    BinTree *rootCast = (BinTree *) root;
    int isLeaderOld = 0;
    if (!rootCast)
        return FALSE;
    //by using += I can return 1 to main even if leader was deep in recursion:
    isLeaderOld += increaseAge(rootCast->left);
    rootCast->age += AGE_PER_ITERATION;
    // if the leader is at his dying age he frees everyone:
    if (!strcmp(rootCast->name, LEADER) && rootCast->gender == MALE
        && rootCast->age == LEADER_FREE_AGE) {
        printf("%s say: let my people go!\n", rootCast->name);
        return TRUE;
    }
    isLeaderOld += increaseAge(rootCast->right);
    return isLeaderOld;
}

/*************************************************************************
* function name: removeChild *
* The Input: the child to remove *
* The output: returns 1 if the child is the root and it has no sons, so it
 * knows to set it to NULL in the main *
* The Function operation: deletes a child from the tree *
*************************************************************************/

int removeChild(BinTree* child) {
    BinTree* parent = child->parent;
    // if the child is the root and doesn't have 2 sons:
    if (!parent && !(child->left && child->right)) {
        // if it has no sons:
        if (!(child->left) && !(child->right)) {
            free(child->name);
            free(child);
            // returns TRUE so the main can set allJews to NULL:
            return TRUE;
        // if it only has left son:
        } else if (child->left) {
            // temp is used to keep the child's next, to move the info:
            BinTree* temp = child->left;

            // connect the parents:
            if (temp->left)
                temp->left->parent = child;
            if (temp->right)
                temp->right->parent = child;

            // move all the of the next son info to the child:
            child->id = temp->id;
            strcpy(child->name, temp->name);
            child->age = temp->age;
            child->gender = temp->gender;
            child->task = temp->task;
            child->left = temp->left;
            child->right = temp->right;
            // free temp:
            free(temp->name);
            free(temp);
            return FALSE;
        // if it only has right son:
        } else {
            // temp is used to keep the child's next, to move the info:
            BinTree* temp = child->right;

            // connect the parents:
            if (temp->left)
                temp->left->parent = child;
            if (temp->right)
                temp->right->parent = child;

            // move all the of the next son info to the child:
            child->id = temp->id;
            strcpy(child->name, temp->name);
            child->age = temp->age;
            child->gender = temp->gender;
            child->task = temp->task;
            child->left = temp->left;
            child->right = temp->right;
            // free temp:
            free(temp->name);
            free(temp);
            return FALSE;
        }
        // End of if-else.
    }
    // End of if.


    // if the child has both sons:
    if (child->left && child->right) {
        // temp is used to move the info from the next child to the current:
        BinTree* temp = child->right;
        // it goes one right and to the most left to find next child by id:
        while (temp->left)
            temp = temp->left;
        // move the temp's info into the current child:
        child->id = temp->id;
        strcpy(child->name, temp->name);
        child->age = temp->age;
        child->gender = temp->gender;
        child->task = temp->task;
        // remove the temp now because all it's info is in the current child:
        removeChild(temp);
        return FALSE;
    }
    // End of if-else.

    // if the child has no sons:
    if (!(child->left) && !(child->right)) {
        // if the child is a left son:
        if (parent->left == child)
            // disconnect parent:
            parent->left = NULL;
        // if it's a right son:
        else
            // disconnect parent:
            parent->right = NULL;
    // if it only has left son:
    } else if (child->left) {
        // if it is a left son:
        if (parent->left == child) {
            // connect previous to the next:
            parent->left = child->left;
            // connect the parent:
            child->left->parent = parent;
        }
        // if it is a right son:
        else {
            // connect previous to the next:
            parent->right = child->left;
            // connect the parent:
            child->left->parent = parent;
        }
    // if it only has right son:
    } else {
        // if it is a left son:
        if (parent->left == child) {
            // connect previous to the next:
            parent->left = child->right;
            // connect the parent:
            child->right->parent = parent;
        }
        // if it is a right son:
        else {
            // connect previous to the next:
            parent->right = child->right;
            // connect the parent:
            child->right->parent = parent;
        }

    }
    // End of if-else.


    // free the child:
    free(child->name);
    free(child);
    return FALSE;
}
// End of function removeChild.

/*************************************************************************
* function name: throwToNile *
* The Input: the tree's root *
* The output: returns 1 if the male is the root and it has no sons (and 0
 * otherwise), so it knows to set it to NULL in the main (from the removeChild
 * function) *
* The Function operation: goes through the tree postorder and removes all the
 * males. *
*************************************************************************/

int throwToNile(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return FALSE;
    throwToNile(rootCast->left);
    throwToNile(rootCast->right);
    // checks if the child is a male and not the leader, removes it if it is:
    if (rootCast->gender == MALE && strcmp(LEADER, rootCast->name) != 0)
        return removeChild(rootCast);
    return FALSE;
}

/*************************************************************************
* function name: childTaskPreorder *
* The Input: the tree's root *
* The output: each child's task *
* The Function operation: goes through the tree preorder and activates each
 * child's task *
*************************************************************************/

void childTaskPreorder(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    // activates the child's task:
    rootCast->task(rootCast->action);
    childTaskPreorder(rootCast->left);
    childTaskPreorder(rootCast->right);
}

/*************************************************************************
* function name: childTaskInorder *
* The Input: the tree's root *
* The output: each child's task *
* The Function operation: goes through the tree inorder and activates each
 * child's task *
*************************************************************************/

void childTaskInorder(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    childTaskInorder(rootCast->left);
    // activates the child's task:
    rootCast->task(rootCast->action);
    childTaskInorder(rootCast->right);
}

/*************************************************************************
* function name: childTaskPostorder *
* The Input: the tree's root *
* The output: each child's task *
* The Function operation: goes through the tree postorder and activates each
 * child's task *
*************************************************************************/

void childTaskPostorder(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    childTaskPostorder(rootCast->left);
    childTaskPostorder(rootCast->right);
    // activates the child's task:
    rootCast->task(rootCast->action);
}

/*************************************************************************
* function name: findMoshe *
* The Input: the tree's root *
* The output: returns 1 if moshe was found and 0 if not *
* The Function operation: goes through the tree preorder and activates each
 * child's task *
*************************************************************************/

int findMoshe(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return FALSE;
    // activates findMoshe each time and returns TRUE if it found him:
    if (findMoshe(rootCast->left))
        return TRUE;
    if (findMoshe(rootCast->right))
        return TRUE;
    // checks if the child is Moshe:
    if (!strcmp(rootCast->name, LEADER) && rootCast->gender == MALE)
        return TRUE;
    return FALSE;
}

/*************************************************************************
* function name: printPreorder *
* The Input: the tree's root *
* The output: all the children's info (id, name, gender, age) *
* The Function operation: goes through the three preorder and prints all the
 * info *
*************************************************************************/

void printPreorder(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    // prints info:
    printf("id: %d, name: %s, gender: %c, age: %d\n", rootCast->id,
           rootCast->name, rootCast->gender, rootCast->age);
    printPreorder(rootCast->left);
    printPreorder(rootCast->right);
}

/*************************************************************************
* function name: printInorder *
* The Input: the tree's root *
* The output: all the children's info (id, name, gender, age) *
* The Function operation: goes through the three inorder and prints all the
 * info *
*************************************************************************/

void printInorder(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    printInorder(rootCast->left);
    // prints info:
    printf("id: %d, name: %s, gender: %c, age: %d\n", rootCast->id,
           rootCast->name, rootCast->gender, rootCast->age);
    printInorder(rootCast->right);
}

/*************************************************************************
* function name: printPostorder *
* The Input: the tree's root *
* The output: all the children's info (id, name, gender, age) *
* The Function operation: goes through the three postorder and prints all the
 * info *
*************************************************************************/

void printPostorder(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    printPostorder(rootCast->left);
    printPostorder(rootCast->right);
    // prints info:
    printf("id: %d, name: %s, gender: %c, age: %d\n", rootCast->id,
           rootCast->name, rootCast->gender, rootCast->age);
}

/*************************************************************************
* function name: sizeAllJews *
* The Input: the tree root *
* The output: returns the number of children in the tree *
* The Function operation: goes through the tree preorder and counts all the
 * children *
*************************************************************************/

int sizeAllJews(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    int count = 0;
    if (!rootCast)
        return 0;
    // counts all the children:
    count++;
    count += sizeAllJews(rootCast->left);
    count += sizeAllJews(rootCast->right);
    return count;
}

/*************************************************************************
* function name: sizeAllMales *
* The Input: the tree root *
* The output: returns the number of male children in the tree *
* The Function operation: goes through the tree preorder and counts all the
 * male children *
*************************************************************************/

int sizeAllMales(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    int count = 0;
    if (!rootCast)
        return 0;
    // counts the males:
    if (rootCast->gender == MALE)
        count++;
    count += sizeAllMales(rootCast->left);
    count += sizeAllMales(rootCast->right);
    return count;
}

/*************************************************************************
* function name: sizeAllFemales *
* The Input: the tree root *
* The output: returns the number of female children in the tree *
* The Function operation: goes through the tree preorder and counts all the
 * female children *
*************************************************************************/

int sizeAllFemales(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    int count = 0;
    if (!rootCast)
        return 0;
    // counts the females:
    if (rootCast->gender == FEMALE)
        count++;
    count += sizeAllFemales(rootCast->left);
    count += sizeAllFemales(rootCast->right);
    return count;
}

/*************************************************************************
* function name: checkDieAge *
* The Input: the tree's root *
* The output: returns 1 if the child to remove is the root and it has no sons
 * (and 0 otherwise), so it knows to set it to NULL in the main (from the
 * removeChild function) *
* The Function operation: goes through the tree postorder and checks if
 * someone is DIE_AGE (120) years old and if so, it removes them *
*************************************************************************/

int checkDieAge(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return FALSE;
    checkDieAge(rootCast->left);
    checkDieAge(rootCast->right);
    // if the child is too old it removes it from the tree:
    if (rootCast->age >= DIE_AGE)
        return removeChild(rootCast);
    return FALSE;
}

/*************************************************************************
* function name: freeIsrael *
* The Input: the tree's root *
* The output: none *
* The Function operation: goes through the tree postorder and frees all the
 * children *
*************************************************************************/

void freeIsrael(void* root) {
    // cast the root into BinTree pointer:
    BinTree* rootCast = (BinTree*) root;
    if (!rootCast)
        return;
    // free all children:
    freeIsrael(rootCast->left);
    freeIsrael(rootCast->right);
    free(rootCast->name);
    free(rootCast);
}
