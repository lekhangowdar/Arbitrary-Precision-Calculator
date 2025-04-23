/*******************************************************************************************************************************************************************
* Title           : Read and Validate
* Description     : This file contains functions to check the operation type, validate arguments, and read input for large number operations.
* Prototype       : 
*                   char check_operation_type(char *argv[]);
*                   int read_and_validate_args(char *argv[]);
*                   char read_input(char *str, Dlist **head, Dlist **tail, char *new_str);
* Input Parameters : argv[]  : Array of command-line arguments.
*                   str     : String containing the input number to be read.
*                   head    : Pointer to the first node of the doubly linked list for storing digits.
*                   tail    : Pointer to the last node of the doubly linked list for storing digits.
*                   new_str : String to hold the input number after removing leading zeros.
* Output          : 
*                   check_operation_type: Returns the operation type ('+', '-', 'x', or '/') based on the argument.
*                   read_and_validate_args: Returns SUCCESS if arguments are valid, FAILURE otherwise.
*                   read_input: Returns the sign of the number ('+' or '-') and populates the doubly linked list with digits.
*******************************************************************************************************************************************************************/

#include "apc.h"
#include <ctype.h>
#include <string.h>

// Function to check the operation type based on the user input (argv[2])
char check_operation_type(char *argv[])
{
    if (strcmp(argv[2], "+") == 0)   // Check if "+" is entered
    {
        return '+';
    }
    else if (strcmp(argv[2], "-") == 0)  // Check if "-" is entered
    {
        return '-';
    }
    else if (strcmp(argv[2], "x") == 0)  // Check if "x" is entered
    {
        return 'x';
    }
    else if (strcmp(argv[2], "/") == 0)  // Check if "/" is entered
    {
        return '/';
    }
    else 
    {
        return 0;  // Invalid operation
    }
}

// Function to read and validate arguments passed from the user
int read_and_validate_args(char *argv[])
{
    int ind1 = 0, ind2 = 0;
    if (argv[1][0] == '+' || argv[1][0] == '-')
    {
        ind1++;
    }
    if (argv[3][0] == '+' || argv[3][0] == '-')
    {
        ind2++;
    }

    // Validate 1st operand (argv[1])
    for (int i = ind1; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))  // If any non-digit is found
        {
            printf("ERROR: Invalid 1st operand\n");
            return FAILURE;
        }
    }

    // Validate 2nd operand (argv[3])
    for (int i = ind2; i < strlen(argv[3]); i++)
    {
        if (!isdigit(argv[3][i]))  // If any non-digit is found
        {
            printf("ERROR: Invalid 2nd operand\n");
            return FAILURE;
        }
    }

    // Check if the operation symbol is valid (+, -, x, or /)
    if (strlen(argv[2]) == 1 && (argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == 'x' || argv[2][0] == '/'))
    {
        return SUCCESS;
    }
    else
    {
        printf("ERROR: Invalid operand\n");
        return FAILURE;
    }
}

// Function to read the input number and store its digits in a doubly linked list
char read_input(char *str, Dlist **head, Dlist **tail, char *new_str)
{
    char sign_op = '+';  // Default sign is '+'
    
    // Determine the sign of the number
    if (*str == '+')
    {
        str++;
    }
    else if (*str == '-')
    {
        sign_op = '-';
        str++;
    }

    // Remove leading zeros from the string
    while (*str == '0')
    {
        str++;
    }

    // Copy the number without leading zeros to the new_str
    strcpy(new_str, str);

    // Read and store each digit in the doubly linked list
    while (*str)
    {
        if (*str >= '0' && *str <= '9')  // If a valid digit is found
        {
            if ((dl_insert_last(head, tail, (*str++ - 48)) ) == FAILURE)  // Insert digit into the list
            {
                printf("Reading failed\n");
                break;
            }
        }
        else
        {
            printf("Reading failed\n");
            break;  // If an invalid character is encountered, stop reading
        }
    }

    return sign_op;  // Return the sign of the number
}
