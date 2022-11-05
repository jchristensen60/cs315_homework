/******************************************************************
 * Author:       Jacob M. Christensen
 * Course:       CS315
 * Assignment:   Homework #2
 * Purpose:      Queue algorithm implemented in a circular list.
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Initializing Queue Node Structure
typedef struct QueueNode
{
    char userData;
    struct QueueNode *nextPtr;
} QUEUE_NODE;

// Prototype Functions
void insertNode(QUEUE_NODE **mainPtr);
void removeNode(QUEUE_NODE **mainPtr);

/*****************************************************************/
int main()
{
    QUEUE_NODE *mainPtr = NULL;
    char userInput;
    bool continueLoop = true;

    while(continueLoop) {

        printf("Insert[I]   Remove[R]   Quit[Q]: ");
        scanf(" %c", &userInput);

        switch(userInput) {

        case 'I':
            insertNode(&mainPtr);
            break;

        case 'R':
            removeNode(&mainPtr);
            break;
        
        case 'Q':
            continueLoop = false;
            break;

        default:
            printf("Invalid Entry\n");
            break;
        }
    }
    return 0;
}

/*****************************************************************/
/****************** INSERT NEW ELEMENT IN QUEUE ******************/
/*****************************************************************/
void insertNode(QUEUE_NODE **mainPtr)
{
    QUEUE_NODE *insertionPtr = malloc(sizeof(QUEUE_NODE));

    printf("Enter Character to Insert: ");
    scanf(" %c", &(insertionPtr->userData));
    printf("\n");

    // Special Case: If Queue is Empty, Point Back to Self
    if ((*mainPtr) == NULL) {

        insertionPtr->nextPtr = insertionPtr;
        (*mainPtr) = insertionPtr;
    }
    // Normal Insertion
    else {

        insertionPtr->nextPtr = (*mainPtr)->nextPtr;
        (*mainPtr)->nextPtr = insertionPtr;
        (*mainPtr) = insertionPtr;
    }
}

/*****************************************************************/
/******************* REMOVE ELEMENT FROM QUEUE *******************/
/*****************************************************************/
void removeNode(QUEUE_NODE **mainPtr)
{
    QUEUE_NODE *deletionPtr = NULL;

    // Error if Queue is Empty
    if ((*mainPtr) == NULL) {

        printf("Cannot remove from an empty queue\n\n");
    }
    // Else, Deletion Logic...
    else {

        deletionPtr = (*mainPtr)->nextPtr;
        // Special Case: Only One Element in Queue
        if (deletionPtr == (*mainPtr)) {

            printf("Removing %c from queue...\n\n", deletionPtr->userData);
            (*mainPtr) = NULL;
            free(deletionPtr);
        }
        // Normal Deletion
        else {

            printf("Removing %c from queue...\n\n", deletionPtr->userData);
            (*mainPtr)->nextPtr = (*mainPtr)->nextPtr->nextPtr;
            free(deletionPtr);
        }
    }
}
