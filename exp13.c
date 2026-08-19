#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

/* Push character into stack */
void push(char ch)
{
    if (top < MAX - 1)
        stack[++top] = ch;
}

/* Display stack */
void displayStack()
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

/* Reduce the stack */
int reduce()
{
    /* E -> id */
    if (top >= 1 &&
        stack[top - 1] == 'i' &&
        stack[top] == 'd')
    {
        top -= 1;
        stack[top] = 'E';

        printf("\tReduce: E -> id\n");
        return 1;
    }

    /* E -> (E) */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';

        printf("\tReduce: E -> (E)\n");
        return 1;
    }

    /* E -> E+E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';

        printf("\tReduce: E -> E+E\n");
        return 1;
    }

    /* E -> E*E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';

        printf("\tReduce: E -> E*E\n");
        return 1;
    }

    return 0;
}

int main()
{
    char input[MAX];
    int i = 0;

    printf("BOTTOM-UP (SHIFT-REDUCE) PARSER\n");
    printf("--------------------------------\n");
    printf("Grammar:\n");
    printf("E -> E+E | E*E | (E) | id\n\n");

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nStack\t\tAction\n");
    printf("--------------------------------\n");

    while (input[i] != '\0')
    {
        /* Shift */
        push(input[i]);

        printf("\n");
        displayStack();
        printf("\tShift: %c", input[i]);

        i++;

        /* Perform reductions repeatedly */
        while (reduce())
        {
            printf("\n");
            displayStack();
        }
    }

    /* Final reduction */
    while (reduce())
    {
        printf("\n");
        displayStack();
    }

    printf("\n\nFinal Stack: ");
    displayStack();

    if (top == 0 && stack[0] == 'E')
        printf("\n\nString is ACCEPTED.\n");
    else
        printf("\n\nString is NOT ACCEPTED.\n");

    return 0;
}