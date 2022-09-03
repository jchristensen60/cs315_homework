/***********************************************************************
* Author:       Jacob M. Christensen
* Course:       CS315
* Assignment:   Homework #0
* Purpose:      Review of pointers and linked lists.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct intList
{
    int userData;
    struct intList *next;
} INT_LIST;

// Prototype Functions
INT_LIST *pushInt(INT_LIST *start, INT_LIST *temp);
INT_LIST *popInt(INT_LIST *start, INT_LIST *temp);

/**********************************************************************/
int main()
{
    INT_LIST *start = NULL, *temp = NULL;
    bool continueLoop = true;
    char input;

    while(continueLoop)
    {
        printf("\nWhat do you want to do? [P]ush  [p]op  [q]uit: ");
        scanf(" %c", &input);
        if(input == 'P') // Push
        {
            start = (temp = pushInt(start, temp));
        }
        else if(input == 'p') // Pop
        {
            temp = (start = popInt(start, temp));
        }
        else if(input == 'q') // Quit
        {
            printf("\nBye\n");
            continueLoop = false;
        }
        else
        {
            printf("  Invalid Input\n");
        }
    }
    return 0;
}

/***********************************************************************/
INT_LIST *pushInt(INT_LIST *start, INT_LIST *temp)
{
    temp = malloc(sizeof(INT_LIST));
    printf("  Enter an Integer: ");
    scanf("%d", &(temp->userData));
    temp->next = start;
    return temp;
}

/***********************************************************************/
INT_LIST *popInt(INT_LIST *start, INT_LIST *temp)
{
    if(start != NULL)
    {
        start = start->next;
        printf("  Popped %d\n", temp->userData);
        free(temp);
    }
    else
    {
        printf("  Cannot Pop an Empty Stack\n");
    }
    return start;
}
