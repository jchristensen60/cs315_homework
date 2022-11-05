
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

// Initializing Binary Search Tree Structure
typedef struct _BinarySearchTreeNode
{
    int data;
    struct _BinarySearchTreeNode *leftChild;
    struct _BinarySearchTreeNode *rightChild;
} BSTN; /* Binary Search Tree Node */

// Initializing Traversal Management Structure
typedef struct _TraversalStackNode
{
    struct _BinarySearchTreeNode *data;
    struct _TraversalStackNode *next;
}TSN; /* Traversal Stack Node */

// Prototype Functions
void splashText();
BSTN *memoryAllocateNewNode();
void userSelectInsert();
void userSelectFind();
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
    int valueToFind = 0;
    bool quitProgram = false;

    splashText();
    do {

        printf("----------------------------------------\n"
               " Insert[1]        Find[2]       Quit[3] \n"
               "----------------------------------------\n"
               " Command: ");
        scanf("%d", &userInput);

        switch (userInput) {

        case 1:
            userSelectInsert(&rootPtr);
            break;
        
        case 2:
            printf(" * Enter Integer to Find: ");
            scanf("%d", &valueToFind);
            userSelectFind(rootPtr, valueToFind);
            break;
        
        case 3:
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
    newNode->data = nodeValue;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    
    return newNode;
}

/*********************************************************************************************/
void userSelectInsert(BSTN **rootPtr)
{
    int valueToInsert = 0;

    printf(" * Enter Integer to Insert: ");
    scanf("%d", &(valueToInsert));

    // Binary Tree is Empty
    if (*rootPtr == NULL) {
        *rootPtr = memoryAllocateNewNode(valueToInsert);
    }
    // Binary Tree is Not Empty
    else {
        insert(rootPtr, valueToInsert);
    }
    // Display Traversal Patterns
    inOrderTraversal(*rootPtr);
    preOrderTraversal(*rootPtr);
}

/*********************************************************************************************/
void userSelectFind(BSTN *rootPtr, int valueToFind)
{
    if (valueToFind == rootPtr->data) {
        printf("Value Found in Tree\n");
    }
    else if (valueToFind < rootPtr->data) {
        userSelectFind(rootPtr->leftChild, valueToFind);
    }
    else if (valueToFind > rootPtr->data) {
        userSelectFind(rootPtr->rightChild, valueToFind);
    }
    else {
        printf("Value Not in Tree");
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
        printf("%d ", travelPtr->data);

        while (travelPtr->rightChild == NULL && traversalStackTop) {
            travelPtr = traversalStackPop(&traversalStackTop);
            printf("%d ", travelPtr->data);
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
        printf("%d ", travelPtr->data); // Visit the Root
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
void insert(BSTN **rootPtr, int valueToInsert)
{
    if (*rootPtr == NULL) {
        *rootPtr = memoryAllocateNewNode(valueToInsert);
    }
    else if (valueToInsert == (*rootPtr)->data) {
        printf(" * Value Already in Tree\n");
    }
    else if (valueToInsert < (*rootPtr)->data) {
        insert(&((*rootPtr)->leftChild), valueToInsert);
    }
    else { // valueToInsert > (*rootPtr)->data
        insert(&((*rootPtr)->rightChild), valueToInsert);
    }
    // insert(valueToInsert < rootPtr->data ? rootPtr->leftChild : rootPtr->rightChild, valueToInsert);
}

/*********************************************************************************************/
void traversalStackPush(BSTN *travelPtr, TSN **traversalStackTop)
{
    TSN *temp = malloc(sizeof(TSN));
    temp->data = travelPtr;
    temp->next = *traversalStackTop;
    *traversalStackTop = temp;
}

/*********************************************************************************************/
BSTN *traversalStackPop(TSN **traversalStackTop)
{
    TSN *temp = *traversalStackTop;
    BSTN *returnValue = (*traversalStackTop)->data;
    if (*traversalStackTop) { // != NULL
        *traversalStackTop = (*traversalStackTop)->next;
        free(temp);
        return returnValue;
    }
    else {
        return NULL;
    }
}
