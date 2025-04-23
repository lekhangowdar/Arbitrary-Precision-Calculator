/*******************************************************************************************************************************************************************
* Title           : Subtraction
* Description     : This function performs subtraction of two given large numbers (represented as doubly linked lists) and stores the result in the resultant list.
* Prototype       : int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
* Input Parameters : 
*                   head1  : Pointer to the first node of the first doubly linked list (first number).
*                   tail1  : Pointer to the last node of the first doubly linked list.
*                   head2  : Pointer to the first node of the second doubly linked list (second number).
*                   tail2  : Pointer to the last node of the second doubly linked list.
*                   headR  : Pointer to the first node of the resultant doubly linked list where the result will be stored.
* Output          : 
*                   SUCCESS  : If the subtraction is successful.
*                   FAILURE  : If the subtraction fails (e.g., if the first number is smaller than the second one).
*******************************************************************************************************************************************************************/

#include "apc.h"
extern unsigned char sign;

// Helper function to remove leading zeros from the resultant list
int rem_zero(Slist **head);

// Main function to perform the subtraction of two large numbers represented by doubly linked lists
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR)
{
	unsigned int barrow = 0, dif = 0;
	Dlist *temptail1 = *tail1, *temptail2 = *tail2;

	// Subtraction loop for digits in both numbers
	while (temptail1 && temptail2)
	{
		// Check if borrowing is needed (i.e., when the current digit of the first number is smaller)
		if ((signed)((temptail1)->data - barrow) < (signed)(temptail2)->data)
		{
			dif = (temptail1)->data + 10 - (temptail2)->data - barrow;
			barrow = 1;  // Set borrow flag
		}
		else
		{
			dif = ((temptail1)->data - barrow) - (temptail2)->data;
			barrow = 0;  // No borrow needed
		}

		// Insert the result of subtraction at the beginning of the result list
		sl_insert_at_first(headR, dif);

		// Move to the previous node in each list
		temptail1 = (temptail1)->prev;
		temptail2 = (temptail2)->prev;
	}

	// If there are remaining digits in the first number, continue subtraction
	while (temptail1)
	{
		if ((signed)((temptail1)->data - barrow) < 0)
		{
			dif = (temptail1)->data + 10 - barrow;
			barrow = 1;
		}
		else
		{
			dif = (temptail1)->data - barrow;
			barrow = 0;
		}

		// Move to the previous node in the first list and insert the result
		temptail1 = (temptail1)->prev;
		sl_insert_at_first(headR, dif);
	}

	// If there are remaining digits in the second number, continue subtraction (if borrow is required)
	while (temptail2)
	{
		if ((signed)((temptail2)->data - barrow) < 0)
		{
			dif = (temptail2)->data + 10 - barrow;
			barrow = 1;
		}
		else
		{
			dif = (temptail2)->data - barrow;
			barrow = 0;
		}

		// Move to the previous node in the second list
		temptail2 = (temptail2)->prev;

		// Insert the result if it's a non-zero digit or if it's the last non-zero digit
		if ((temptail2) != NULL || (dif != 0))
		{
			sl_insert_at_first(headR, dif);
		}
	}

	// Remove any leading zeros from the result list
	rem_zero(headR);

	// If the first number is empty (i.e., no digits were subtracted), return failure
	if (*head1 == NULL)
	{
		return FAILURE;
	}

	return SUCCESS;
}

// Helper function to remove leading zeros from the result list
int rem_zero(Slist **head)
{
	int flag = 0;
	if (*head == NULL)
	{
		return 0;
	}
	else
	{
		// Remove zeros at the beginning of the list
		while ((*head)->link && ((*head)->data == 0))
		{
			sl_delete_first(head);
		}
	}
	return flag;
}
