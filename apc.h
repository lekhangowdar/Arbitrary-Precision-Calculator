/**************************************************************************************************************************************************************
* Name           : Lekhan Gowda R
* File Name      : apc.h
* Description    : Header file for Arbitrary Precision Calculator (APC)
*                  Defines data structures, function prototypes, and necessary macros for the APC operations.
**************************************************************************************************************************************************************/

#ifndef APC_H
#define APC_H

#define SUCCESS 0  // Indicates successful operation
#define FAILURE -1 // Indicates failure in operation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define data type for APC (arbitrary precision calculator)
typedef int data_t;

/* Doubly Linked List node structure */
typedef struct node_d
{
    struct node_d *prev;  // Pointer to previous node
    data_t data;          // Data value
    struct node_d *next;  // Pointer to next node
} Dlist;

/* Singly Linked List node structure */
typedef struct node_s
{
    data_t data;           // Data value
    struct node_s *link;   // Pointer to next node
} Slist;

/* Function Prototypes */

/* Check operation type from command-line arguments */
char check_operation_type(char *argv[]);

/* Validate and read input arguments from command-line */
int read_and_validate_args(char *argv[]);

/* Read input values and store them in linked lists */
char read_input(char *str, Dlist **head, Dlist **tail, char *new_str);

/* Insert data at the first position in singly linked list */
int sl_insert_at_first(Slist **head, data_t);

/* Insert data at the last position in doubly linked list */
int dl_insert_last(Dlist **head, Dlist **tail, int data);

/* Print the elements of a doubly linked list */
void print_dlist(Dlist *head);

/* Print the elements of a singly linked list */
void print_list(Slist *head);

/* Perform addition on two numbers represented as linked lists */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR);

/* Perform subtraction on two numbers represented as linked lists */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR);

/* Delete the entire singly linked list */
int sl_delete_list(Slist **head);

/* Delete the entire doubly linked list */
int dl_delete_list(Dlist **head, Dlist **tail);

/* Copy data from singly linked list to doubly linked list */
int copy_sl_to_dl(Dlist **head, Dlist **tail, Slist **src);

/* Perform multiplication on two numbers represented as linked lists */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR);

/* Insert data at the first position in doubly linked list */
int dl_insert_first(Dlist **head, Dlist **tail, int data);

/* Copy data from doubly linked list to singly linked list */
int copy_dl_to_sl(Slist **head, Dlist **src);

/* Perform division on two numbers represented as linked lists */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Slist **headR);

/* Delete the first node from singly linked list */
int sl_delete_first(Slist **head);

#endif
