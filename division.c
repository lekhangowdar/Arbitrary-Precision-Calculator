/*******************************************************************************************************************************************************************
* Title           : Division
* Description     : This function performs division of two given large numbers and stores the result in the resultant list.
* Prototype       : int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
* Input Parameters : head1  : Pointer to the first node of the first doubly linked list.
*                   tail1  : Pointer to the last node of the first doubly linked list.
*                   head2  : Pointer to the first node of the second doubly linked list.
*                   tail2  : Pointer to the last node of the second doubly linked list.
*                   headR  : Pointer to the first node of the resultant doubly linked list.
* Output          : Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"

// Helper function to check the remainder during division
int check_rem(Dlist *head2, Slist *head);

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR)
{
    // If the second list (divisor) is empty, division by zero
    if (*head2 == NULL)
    {
        printf("\nCannot divide by 0\n");
        return FAILURE;
    }
    // If the first list (dividend) is empty, result is zero
    else if (*head1 == NULL)
    {
        printf("\nResult : 0\n");
        return FAILURE;
    }

    int res, count = 0;
    Dlist *res1 = *head1, *resTail1 = *tail1;  // Accumulated result
    Slist *res3 = NULL;
    Dlist *res2 = *head2, *resTail2 = *tail2;  // Partial product result for each digit

    // Declaring a Dlist containing value 1 for adding each time when loop is called to store quotient as single linked list
    Dlist *one_h1 = NULL, *one_t1 = NULL;
    dl_insert_last(&one_h1, &one_t1, 1);
    Dlist *one_h2 = NULL, *one_t2 = NULL;
    dl_insert_last(&one_h2, &one_t2, 0);

    do
    {
        // Subtract the divisor from the dividend
        subtraction(&res1, &resTail1, &res2, &resTail2, &res3);
        // Check if remainder is valid
        res = check_rem(res2, res3);

        // Clean up temporary lists and copy result for the next iteration
        dl_delete_list(&res1, &resTail1);
        copy_sl_to_dl(&res1, &resTail1, &res3);
        sl_delete_list(&res3);

        // Add 1 to quotient for the next iteration
        addition(&one_h2, &one_t2, &one_h1, &one_t1, headR);
        dl_delete_list(&one_h2, &one_t2);
        copy_sl_to_dl(&one_h2, &one_t2, headR);
        sl_delete_list(headR);
    }
    // Repeat division until remainder is valid
    while (res);

    // Copy the final result to the result list
    copy_dl_to_sl(headR, &one_h2);

    return SUCCESS;
}

// Function to check the remainder during the division
int check_rem(Dlist *head2, Slist *head1)
{
    int flag = -1;
    if (head1 == NULL)
    {
        return 0;
    }

    // Compare corresponding nodes from both lists to determine if division is possible
    while (head1 && head2)
    {
        if (head1->data < head2->data && flag == -1)
        {
            flag = 0;
        }
        else if (head1->data > head2->data && flag == -1)
        {
            flag = 1;
        }
        head1 = head1->link;
        head2 = head2->next;
    }

    // If there's a remaining node in the first list, division can continue
    if (head1)
    {
        flag = 1;
    }
    // If there's a remaining node in the second list, division is not possible
    if (head2)
    {
        flag = 0;
    }
    return flag;
}
