/**************************************************************************************************************************************************************
* Name           : Lekhan Gowda R
* File Name      : linked_list.c
* Description    : Implementation file for linked list operations.
*                  Defines various functions to manipulate singly and doubly linked lists.
**************************************************************************************************************************************************************/

#include "apc.h"

/* Insert a node at the beginning of a singly linked list */
int sl_insert_at_first(Slist **head, data_t data)
{
    Slist *new = malloc(sizeof(Slist)); // Create a new node
    
    // Return failure if memory allocation for the node fails
    if(new == NULL)
    {
        return FAILURE;
    }
    
    // Set data and link to the current head node
    new->data = data;
    new->link = *head;
    
    // Update head to point to the new node
    *head = new;
    return SUCCESS;
}

/* Insert a node at the end of a doubly linked list */
int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist)); // Create a new node
    
    // Return failure if memory allocation fails
    if(new == NULL)
    {
        return FAILURE;
    }
    
    // Initialize node data and set next/prev pointers to NULL
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    
    // Check if the list is empty and update head and tail
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    // Insert the node at the end of the list
    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}

/* Print all nodes in a doubly linked list */
void print_dlist(Dlist *head)
{
    // Check if the list is empty
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        // Traverse the list and print data
        while (head)        
        {
            printf("%d", head->data);
            head = head->next; // Move to next node
        }
    }
}

/* Print all nodes in a singly linked list */
void print_list(Slist *head)
{
    // Check if the list is empty
    if (head == NULL)
    {
        return;
    }
    else
    {
        // Traverse the list and print data
        while (head)        
        {
            printf("%d", head->data);
            head = head->link; // Move to next node
        }
    }
}

/* Delete all nodes in a doubly linked list */
int dl_delete_list(Dlist **head, Dlist **tail)
{
    // Return failure if the list is empty
    if(*head == NULL)
    {
        return FAILURE;
    }
    
    // Traverse and free each node
    while((*head)->next)
    {
        *head = (*head)->next; // Update head to next node
        free((*head)->prev);  // Free the previous node
    }
    
    // Free the last node and reset head and tail to NULL
    free(*head);
    *head = *tail = NULL;
}

/* Delete all nodes in a singly linked list */
int sl_delete_list(Slist **head)
{
    // Return failure if the list is empty
    if(*head == NULL)
    {
        return FAILURE;
    }

    Slist *temp = *head; // Save current head in temp
    
    // Traverse and free each node
    while(temp)
    {
        *head = (*head)->link; // Update head to next node
        free(temp);             // Free the current node
        temp = *head;           // Move to the next node
    }
    return SUCCESS;
}

/* Copy data from a singly linked list to a doubly linked list */
int copy_sl_to_dl(Dlist **head, Dlist **tail, Slist **src)
{
    // Return failure if the source list is empty
    if(*src == NULL)
    {
        return FAILURE;
    }

    Slist *temp = *src; // Save the source head in temp

    // Traverse the singly linked list and insert nodes into the doubly linked list
    while(temp)
    {
        dl_insert_last(head, tail, temp->data);
        temp = temp->link; // Move to the next node
    }
    return SUCCESS;
}

/* Insert a node at the end of a singly linked list */
int sl_insert_last(Slist **head, data_t data)
{
    Slist *new = malloc(sizeof(Slist)); // Create a new node
    
    // Return failure if memory allocation fails
    if(new == NULL)
    {
        return FAILURE;
    }
    
    // Initialize node data and set link to NULL (end of list)
    new->data = data;
    new->link = NULL;
    
    // Check if the list is empty
    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    
    // Traverse to the end of the list and insert the new node
    Slist *temp = *head;
    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new; // Set the last node's link to the new node
    return SUCCESS;
}

/* Copy data from a doubly linked list to a singly linked list */
int copy_dl_to_sl(Slist **head, Dlist **src)
{
    // Return failure if the source list is empty
    if(*src == NULL)
    {
        return FAILURE;
    }

    Dlist *temp = *src; // Save the source head in temp

    // Traverse the doubly linked list and insert nodes into the singly linked list
    while(temp)
    {
        sl_insert_last(head, temp->data);
        temp = temp->next; // Move to the next node
    }
    return SUCCESS;
}

/* Insert a node at the beginning of a doubly linked list */
int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist)); // Create a new node
    
    // Return failure if memory allocation fails
    if (new == NULL)
    {
        return FAILURE;
    }
    
    // Initialize node data and set next/prev pointers to NULL
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    
    // If the list is empty, set head and tail to the new node
    if(*tail == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    
    // Insert the new node at the beginning
    new->next = *head;
    (*head)->prev = new;
    *head = new;
    return SUCCESS;
}

/* Delete the first node from a singly linked list */
int sl_delete_first(Slist **head)
{
    // Return failure if the list is empty
    if(*head == NULL)
    {
        return FAILURE;
    }

    Slist *temp = *head; // Save current head in temp
    *head = (*head)->link; // Update head to the second node
    free(temp); // Free the current node
    return SUCCESS;
}
