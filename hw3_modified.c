
/**********************************************************************************************
 * Author:      Jacob M. Christensen
 * Course:      CS315
 * Assignment:  Homework #3
 * Purpose:     Implement four operations for a binary search tree implemented via pointers.
 *                  - Insert
 *                  - In-order traversal
 *                  - Pre-order traversal
 *                  - Find
**********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* Initializing Binary Search Tree Structure */
typedef struct _BinarySearchTreeNode
{
    int value;
    struct _BinarySearchTreeNode *leftChild;
    struct _BinarySearchTreeNode *rightChild;
} BSTN; // Binary Search Tree Node

/* Initializing Traversal Management Structure */
typedef struct _TraversalStackNode
{
    struct _BinarySearchTreeNode *bstnPtr;
    struct _TraversalStackNode *next;
}TSN; // Traversal Stack Node

/* Prototype Functions */
void splashText();
BSTN *memoryAllocateNewNode();
void search();
void inOrderTraversal();
void preOrderTraversal();
void insert();
void traversalStackPush();
BSTN *traversalStackPop();

/*********************************************************************************************/
int main()
{
    BSTN *rootPtr = NULL;
    int userInput = 0;
    char charToFind, charToInsert;
    bool quitProgram = false;

    splashText();
    do {

        printf("----------------------------------------\n"
               " Insert[1]        Find[2]       Quit[3] \n"
               "----------------------------------------\n"
               " Command: ");
        scanf("%d", &userInput);

        switch (userInput) {

        case 1: /* Insert Value in BST */
            printf(" * Enter Character to Insert: ");
            scanf(" %c", &charToInsert);
            insert(&rootPtr, charToInsert);

            // Display Traversal Patterns
            inOrderTraversal(rootPtr);
            preOrderTraversal(rootPtr);
            break;
        
        case 2: /* Search Value in BST */
            printf(" * Enter Character to Find: ");
            scanf(" %c", &charToFind);
            search(rootPtr, charToFind);
            break;
        
        case 3: /* Terminate Program */
            quitProgram = true;
            break;

        default:
            printf(" *** Invalid Entry ***\n");
            break;
        }

    } while (!quitProgram);

    return 0;
}

/*********************************************************************************************/
void splashText()
{
    printf("CS315 Homework v3 -- Binary Search Trees\n");
}

/*********************************************************************************************/
BSTN *memoryAllocateNewNode(int nodeValue)
{
    BSTN *newNode = malloc(sizeof(BSTN));
    newNode->value = nodeValue;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    
    return newNode;
}

/*********************************************************************************************/
void search(BSTN *rootPtr, int searchValue)
{
    if (rootPtr == NULL) {
        printf("Character Not in Tree\n\n");
    }
    else if (searchValue == rootPtr->value) {
        printf("Character Found in Tree\n\n");
    }
    else if (searchValue < rootPtr->value) {
        search(rootPtr->leftChild, searchValue);
    }
    else {
        search(rootPtr->rightChild, searchValue);
    }
}

/*********************************************************************************************/
void inOrderTraversal(BSTN *rootPtr)
{
    BSTN *travelPtr = rootPtr;
    TSN *traversalStackTop = NULL;

    printf(" * In-Order Traversal: ");

    traversalStackPush(travelPtr, &traversalStackTop);

    while (traversalStackTop) {

        while (travelPtr->leftChild) {
            traversalStackPush(travelPtr->leftChild, &traversalStackTop);
            travelPtr = travelPtr->leftChild;
        }

        travelPtr = traversalStackPop(&traversalStackTop);
        printf("%c ", travelPtr->value);

        while (travelPtr->rightChild == NULL && traversalStackTop) {
            travelPtr = traversalStackPop(&traversalStackTop);
            printf("%c ", travelPtr->value);
        }
        if (travelPtr->rightChild) {
            traversalStackPush(travelPtr->rightChild, &traversalStackTop);
            travelPtr = travelPtr->rightChild;
        }
    }
    printf("\n");
}

/*********************************************************************************************/
void preOrderTraversal(BSTN *rootPtr)
{
    BSTN *travelPtr = rootPtr;
    TSN *traversalStackTop = NULL;

    printf(" * Pre-Order Traversal: ");

    traversalStackPush(travelPtr, &traversalStackTop);

    while (traversalStackTop) { // != NULL
        travelPtr = traversalStackPop(&traversalStackTop);
        printf("%c ", travelPtr->value); // Visit the Root
        if (travelPtr->rightChild) { // != NULL
            traversalStackPush(travelPtr->rightChild, &traversalStackTop);
        }
        if (travelPtr->leftChild) { // != NULL
            traversalStackPush(travelPtr->leftChild, &traversalStackTop);
        }
    }
    printf("\n");
}

/*********************************************************************************************/
void insert(BSTN **rootPtr, int charToInsert)
{
    if (*rootPtr == NULL) {
        *rootPtr = memoryAllocateNewNode(charToInsert);
    }
    else if (charToInsert == (*rootPtr)->value) {
        printf(" * Character Already in Tree\n");
    }
    else if (charToInsert < (*rootPtr)->value) {
        insert(&((*rootPtr)->leftChild), charToInsert);
    }
    else { // valueToInsert > (*rootPtr)->value
        insert(&((*rootPtr)->rightChild), charToInsert);
    }
    // insert(valueToInsert < rootPtr->data ? rootPtr->leftChild : rootPtr->rightChild, valueToInsert);
}

/*********************************************************************************************/
void traversalStackPush(BSTN *travelPtr, TSN **traversalStackTop)
{
    TSN *temp = malloc(sizeof(TSN));
    temp->bstnPtr = travelPtr;
    temp->next = *traversalStackTop;
    *traversalStackTop = temp;
}

/*********************************************************************************************/
BSTN *traversalStackPop(TSN **traversalStackTop)
{
    TSN *temp = *traversalStackTop;
    BSTN *returnValue = (*traversalStackTop)->bstnPtr;
    if (*traversalStackTop) { // != NULL
        *traversalStackTop = (*traversalStackTop)->next;
        free(temp);
        return returnValue;
    }
    else {
        return NULL;
    }
}
