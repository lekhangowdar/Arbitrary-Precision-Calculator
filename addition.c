/*******************************************************************************************************************************************************************
* Title           : Addition
* Description     : This function performs addition of two given large numbers and stores the result in the resultant list.
* Prototype       : int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
* Input Parameters : head1  : Pointer to the first node of the first doubly linked list.
*                   tail1  : Pointer to the last node of the first doubly linked list.
*                   head2  : Pointer to the first node of the second doubly linked list.
*                   tail2  : Pointer to the last node of the second doubly linked list.
*                   headR  : Pointer to the first node of the resultant doubly linked list.
* Output          : Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"
extern unsigned char sign;

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR)
{
    // Initialize carry and sum variables
    unsigned int carry = 0, sum = 0;
    Dlist *temp1 = *tail1;  // Start from the last node of the first list
    Dlist *temp2 = *tail2;  // Start from the last node of the second list

    // Loop to add corresponding digits from both lists
    while (temp1 && temp2)
    {
        sum = temp1->data + temp2->data + carry;
        
        // If sum is greater than 9, set carry to 1
        if (sum > 9)
        {
            sum %= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        // Insert the result sum at the beginning of the result list
        sl_insert_at_first(headR, sum);

        // Move to the previous nodes in both lists
        temp1 = temp1->prev;
        temp2 = temp2->prev;
    }

    // If the first list still has remaining nodes
    while (temp1)
    {
        sum = temp1->data + carry;

        // Check if carry should be added
        if (sum > 9)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        // Insert the result sum at the beginning of the result list
        sl_insert_at_first(headR, sum);
        temp1 = temp1->prev;
    }

    // If the second list still has remaining nodes
    while (temp2)
    {
        sum = temp2->data + carry;

        // Check if carry should be added
        if (sum > 9)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        // Insert the result sum at the beginning of the result list
        sl_insert_at_first(headR, sum);
        temp2 = temp2->prev;
    }

    // If there's a carry left after processing both lists, insert it into the result list
    if (carry)
    {
        sl_insert_at_first(headR, carry);
    }

    // Return FAILURE if the first list is empty
    if (*head1 == NULL)
    {
        return FAILURE;
    }

    // Return SUCCESS after completing the addition
    return SUCCESS;
}
