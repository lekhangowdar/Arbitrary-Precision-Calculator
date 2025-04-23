/*******************************************************************************************************************************************************************
* Title           : Multiplication
* Description     : This function performs multiplication of two given large numbers and stores the result in the resultant list.
* Prototype       : int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
* Input Parameters : head1  : Pointer to the first node of the first doubly linked list.
*                   tail1  : Pointer to the last node of the first doubly linked list.
*                   head2  : Pointer to the first node of the second doubly linked list.
*                   tail2  : Pointer to the last node of the second doubly linked list.
*                   headR  : Pointer to the first node of the resultant doubly linked list.
* Output          : Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"

// Function to perform multiplication of two large numbers and store the result in a resultant list
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR)
{
    // If either number is empty, the result is 0
    if (*head1 == NULL || *head2 == NULL)
    {
        printf("\nResult : 0\n");
        return FAILURE;
    }

    int carry = 0, res, count = 0;
    Dlist *res1 = NULL, *resTail1 = NULL;  // Accumulated result
    Dlist *tempTail1 = *tail1;
    Slist *res3 = NULL;

    // Iterate through each digit of the first number (in reverse)
    while (tempTail1)
    {
        Dlist *tempTail2 = *tail2;
        Dlist *res2 = NULL, *resTail2 = NULL; // Partial product result for each digit
        carry = 0;

        // Add leading zeros for the current place value (multiplier)
        for (int i = 0; i < count; i++)
        {
            dl_insert_first(&res2, &resTail2, 0);
        }

        // Multiply each digit of the second number by the current digit of the first
        while (tempTail2)
        {
            res = tempTail2->data * tempTail1->data + carry;
            carry = res / 10;
            res = res % 10;

            // Append the result to the partial product list (res2)
            dl_insert_first(&res2, &resTail2, res);
            tempTail2 = tempTail2->prev;
        }

        count++;

        // If there's a carry left after the inner loop, add it to the partial product
        if (carry)
        {
            dl_insert_first(&res2, &resTail2, carry);
        }

        // Add the current partial product to the accumulated result
        addition(&res1, &resTail1, &res2, &resTail2, &res3);

        // Clean up temporary lists and copy result for the next iteration
        dl_delete_list(&res2, &resTail2);
        dl_delete_list(&res1, &resTail1);
        copy_sl_to_dl(&res1, &resTail1, &res3);
        sl_delete_list(&res3);

        tempTail1 = tempTail1->prev;
    }

    // Copy the final result from headR to the result list, if necessary
    copy_dl_to_sl(headR, &res1);

    return SUCCESS;
}
