/********************************************************************************
* Author:       Jacob M. Christensen
* Course:       CS315
* Assignment:   Homework #1
* Purpose:      Creating a basic linked list that sorts integers in ascending 
* 		order.
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct OrderedList
{
    int UserData;
    struct OrderedList *next;
} ORDERED_LIST;

// Prototype Functions
ORDERED_LIST *insertInt(ORDERED_LIST *start, ORDERED_LIST *lead, int intToInsert);
ORDERED_LIST *deleteInt(ORDERED_LIST *start, ORDERED_LIST *lead, int intToDelete);
bool searchInt(ORDERED_LIST *lead, int intToSearch);
void printList(ORDERED_LIST *lead);

/*******************************************************************************/
int main()
{
    // initialize variables
    ORDERED_LIST *start = NULL, *lead = NULL;
    int insertInput = 0, deleteInput = 0;
    bool continueLoop = true;

    // Loop inserting integers to linked list
    while(continueLoop)
    {
        lead = start;
        printf("Enter an integer: ");
        scanf("%d", &insertInput);
        if(insertInput == 0)
        {
            continueLoop = false;
        }
        else
        {   
            lead = (start = insertInt(start, lead, insertInput));
        }
    }
    printf("Ok, here's your list in numeric order: ");
    printList(lead);

    // Loop deleting integers from linked list
    continueLoop = true;
    while(continueLoop)
    {
        lead = start;
        printf("Enter integer to delete: ");
        scanf("%d", &deleteInput);
        if(deleteInput == 0)
        {
            continueLoop = false;
        }
        else if(searchInt(lead, deleteInput) == false)
        {
            printf("Can't delete, %d isn't in the list.\n", deleteInput);
        }
        else
        {
            lead = (start = deleteInt(start, lead, deleteInput));
        }
    }
    printf("Modified list in numeric order: ");
    printList(lead);
    printf("Bye.\n");
    return 0;
}

/*******************************************************************************/
ORDERED_LIST *insertInt(ORDERED_LIST *start, ORDERED_LIST *lead, int intToInsert)
{
    // initializing variables
    ORDERED_LIST *insertPtr = malloc(sizeof(ORDERED_LIST));
    insertPtr->UserData = intToInsert;

    // if list is empty
    if(start == NULL)
    {
        insertPtr->next = start;
        start = insertPtr;
    }
    // if element is first in list
    else if(start->UserData >= insertPtr->UserData)
    {
        insertPtr->next = start;
        start = insertPtr;
    }
    // if one or more elements in list
    else
    {
        while(lead->next != NULL && lead->next->UserData <= intToInsert)
        {
            lead = lead->next;
        }
        insertPtr->next = lead->next;
        lead->next = insertPtr;
    }
    return start;
}

/*******************************************************************************/
ORDERED_LIST *deleteInt(ORDERED_LIST *start, ORDERED_LIST *lead, int intToDelete)
{
    // initialize variables
    ORDERED_LIST *trail = start;
    lead = start->next;

    // if list is empty
    if(start == NULL)
    {
        printf("Can't delete, the list is empty.\n");
    }
    else if(start->UserData == intToDelete)
    {
        free(start);
        start = lead;
    }
    else
    {
        while(lead->UserData != intToDelete)
        {
            lead = lead->next;
            trail = trail->next;
        }
        trail->next = lead->next;
        free(lead);
    }
}

/*******************************************************************************/
bool searchInt(ORDERED_LIST *lead, int intToSearch)
{
    bool found = false;
    while(lead != NULL)
    {
        if(lead->UserData == intToSearch)
        {
            found = true;
            break;
        }
        else
        {
            lead = lead->next;
        }
    }
    return found?true:false;
}
/*******************************************************************************/
void printList(ORDERED_LIST *lead)
{
    while(lead != NULL)
    {
        printf("%d ", lead->UserData);
        lead = lead->next;
    }
    printf("\n");
}
