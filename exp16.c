#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int n, i;
    char input[100];
    char op1, op2, result, op;

    printf("BACK END OF COMPILER\n");
    printf("--------------------\n");

    printf("Enter number of Three Address Code statements: ");
    scanf("%d", &n);

    printf("\nEnter the Three Address Code statements:\n");

    printf("\nExample:\n");
    printf("t1=a+b\n");
    printf("t2=t1*c\n");
    printf("x=t2\n\n");

    printf("Enter statements:\n");

    printf("\nGenerated Target Code:\n");
    printf("----------------------\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s", input);

        /* Format: t1=a+b */
        if (sscanf(input, "%c=%c%c%c",
                   &result, &op1, &op, &op2) == 4)
        {
            printf("MOV R0, %c\n", op1);

            switch (op)
            {
                case '+':
                    printf("ADD R0, %c\n", op2);
                    break;

                case '-':
                    printf("SUB R0, %c\n", op2);
                    break;

                case '*':
                    printf("MUL R0, %c\n", op2);
                    break;

                case '/':
                    printf("DIV R0, %c\n", op2);
                    break;

                default:
                    printf("Invalid operator\n");
                    continue;
            }

            printf("MOV %c, R0\n\n", result);
        }
        else
        {
            printf("Invalid Three Address Code: %s\n", input);
        }
    }

    return 0;
}