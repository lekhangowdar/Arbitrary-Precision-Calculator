/**************************************************************************************************************************************************************
* Name           : Lekhan Gowda R
* File Name      : main.c
* Description    : Driver function for Arbitrary Precision Calculator (APC)
*                  Handles command-line arguments, determines operation type, reads inputs, and calls respective operation functions (add, sub, mul, div).
***************************************************************************************************************************************************************/

#include "apc.h"

unsigned char sign;

int main(int argc, char *argv[])
{
    // Check if minimum 3 arguments are passed
    if (argc < 3)
    {
        printf("CLA should not be less than 3\n");
        return 0;
    }

    // Validate CLA format
    if(read_and_validate_args(argv) == FAILURE)
    {
        printf("Pass CLA in the correct format\n");
        return 0;
    }

    // Declare and initialize pointers for operands and result
    Dlist *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL;
    Slist *headR = NULL;

    // Determine the operation type
    char option, operator;
    operator = check_operation_type(argv);
    option = operator;  

    // Initialize input buffers
    char str1[100] = {0};
    char str2[100] = {0};

    // Read inputs and get signs
    char sign_op1 = read_input(argv[1], &head1, &tail1, str1);
    char sign_op2 = read_input(argv[3], &head2, &tail2, str2);

    // Compare string lengths to determine operand precedence
    int comp;
    if(strlen(str1) > strlen(str2))
    {
        comp = 1;
    }
    else if(strlen(str1) < strlen(str2))
    {
        comp = -1;
    }
    else
        comp = strcmp(str1, str2);

    // Sign evaluation based on operator and operand signs
    if(sign_op1 == sign_op2)
    {
        if(operator == 'x' || operator == '/')
        {
            sign = '+';
        }
    }
    else
    {
        if(operator == '+')
        {
            operator = '-';
        }
        else if(operator == '-')
        {
            operator = '+';
        }
        else if(operator == 'x' || operator == '/')
        {
            sign = '-';
        }
    }

    // Execute the chosen arithmetic operation
    switch (operator)
    {
        case '+':
            // Perform addition
            if(comp < 0)
            {
                sign = sign_op2;
            }
            else
            {
                sign = sign_op1;
            }

            if (addition(&head1, &tail1, &head2, &tail2, &headR) == FAILURE && option == '-')
            {
                // Flip sign if result is negative
                sign = (sign == '-') ? '+' : '-';
            }

            // Display result
            printf("\nresult : ");
            if(sign == '-')
            {
                printf("%c",sign);
            }
            print_list(headR);
            printf("\n");
            break;

        case '-':
            // Perform subtraction
            if(comp < 0)
            {
                sign = sign_op2;
            }
            else
            {
                sign = sign_op1;
            }

            if (subtraction(&head1, &tail1, &head2, &tail2, &headR) == FAILURE && option == '-')
            {
                // Flip sign if result is negative
                sign = (sign == '-') ? '+' : '-';
            }

            // Display result
            printf("\nresult : ");
            if(sign == '-')
            {
                printf("%c",sign);
            }
            print_list(headR);
            printf("\n");
            break;

        case 'x':
            // Perform multiplication
            if(multiplication(&head1, &tail1, &head2, &tail2, &headR) == FAILURE)
            {
                break;
            }

            // Display result
            printf("\nresult : ");
            if(sign == '-')
            {
                printf("%c",sign);
            }
            print_list(headR);
            printf("\n");
            break;

        case '/':
            // Perform division
            if(comp < 0)
            {
                printf("\nResult : 0\n");
                break;
            }

            if(division(&head1, &tail1, &head2, &tail2, &headR) == FAILURE)
            {
                break;
            }

            // Display result
            printf("\nresult : ");
            if(sign == '-')
            {
                printf("%c",sign);
            }
            print_list(headR);
            printf("\n");
            break;

        default:
            // Invalid operator
            printf("Invalid Input:-( Try again...\n");
    }

    return 0;
}
