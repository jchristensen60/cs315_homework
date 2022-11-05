/********************************************************************************
* Author:       Jacob M. Christensen
* Course:       CS315
* Assignment:   Homework #1
* Purpose:      Creating a basic linked list that sorts integers in ascending 
* 		        order.
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
    // Initialize variables
    ORDERED_LIST *start = NULL, *lead = NULL;
    int userInput = 0;
    bool continueLoop = true;

    // Insertion loop -- Entering zero sets loop to FALSE
    while(continueLoop)
    {
        printf("Enter an integer: ");
        scanf("%d", &userInput);
        if(userInput == 0)
        {
            continueLoop = false;
        }
        else
        {
            lead = (start = insertInt(start, lead, userInput));
        }
    }

    // Check if list is empty, if TRUE terminate program
    continueLoop = true;
    if(start == NULL)
    {
        printf("Your list is empty\n");
    }
    else
    {
        printf("Ok, here's your list in numeric order: ");
        printList(lead);
        // Deletion loop -- Entering zero sets loop to FALSE
        while(continueLoop)
        {
            printf("Enter integer to delete: ");
            scanf("%d", &userInput);
            if(userInput == 0)
            {
                continueLoop = false;
            }
            // Cannot find integer to delete
            else if(searchInt(lead, userInput) == false)
            {
                printf("Can't delete, %d isn't in the list.\n", userInput);
            }
            // Delete selected integer
            else
            {
                lead = (start = deleteInt(start, lead, userInput));
                printf("Modified list: ");
                printList(lead);
            }
        }
        printf("Bye.\n");
    }
    return 0;
}

/*******************************************************************************/
/************************ INSERT SPECIFIED NODE TO LIST ************************/
/*******************************************************************************/
ORDERED_LIST *insertInt(ORDERED_LIST *start, ORDERED_LIST *lead, int intToInsert)
{
    // Initialize variables
    ORDERED_LIST *insertPtr = malloc(sizeof(ORDERED_LIST));
    insertPtr->UserData = intToInsert;

    // List is empty
    if(start == NULL)
    {
        insertPtr->next = start;
        start = insertPtr;
    }
    // Element to insert is first in list
    else if(start->UserData >= insertPtr->UserData)
    {
        insertPtr->next = start;
        start = insertPtr;
    }
    // Insert integer in list
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
/*********************** DELETE SPECIFIED NODE FROM LIST ***********************/
/*******************************************************************************/
ORDERED_LIST *deleteInt(ORDERED_LIST *start, ORDERED_LIST *lead, int intToDelete)
{
    // Initialize variables
    ORDERED_LIST *trail = start;
    lead = start->next;

    // List is empty
    if(start == NULL)
    {
        printf("Can't delete, the list is empty.\n");
    }
    // Integer to delete is first in list
    else if(start->UserData == intToDelete)
    {
        free(start);
        start = lead;
    }
    // Delete integer from list, free allocated memory
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
    return start;
}

/*******************************************************************************/
/********************** SEARCH FOR SPECIFIED NODE IN LIST **********************/
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
        lead = lead->next;
    }
    return found;
}
/*******************************************************************************/
/*********************** PRINT ALL NODES FROM LINKED LIST **********************/
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
