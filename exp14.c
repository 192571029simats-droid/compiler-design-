#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[100];
char stack[100];
int top = -1;
int tempCount = 1;

void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    return stack[top--];
}

int precedence(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;

    if (ch == '*' || ch == '/')
        return 2;

    return 0;
}

/* Convert infix expression to postfix */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();

            if (top != -1)
                pop();
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/')
        {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

/* Generate Three Address Code */
void generateTAC(char postfix[])
{
    char operandStack[100][20];
    int operandTop = -1;

    int i;
    char op;
    char operand1[20], operand2[20], result[20];

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isalnum(postfix[i]))
        {
            operandTop++;
            operandStack[operandTop][0] = postfix[i];
            operandStack[operandTop][1] = '\0';
        }
        else
        {
            op = postfix[i];

            strcpy(operand2, operandStack[operandTop--]);
            strcpy(operand1, operandStack[operandTop--]);

            sprintf(result, "t%d", tempCount++);

            printf("%s = %s %c %s\n",
                   result, operand1, op, operand2);

            operandTop++;
            strcpy(operandStack[operandTop], result);
        }
    }
}

int main()
{
    char postfix[100];

    printf("THREE ADDRESS CODE GENERATOR\n");
    printf("----------------------------\n");

    printf("Enter an arithmetic expression: ");
    scanf("%s", expr);

    infixToPostfix(expr, postfix);

    printf("\nPostfix Expression: %s\n", postfix);

    printf("\nThree Address Code:\n");
    printf("-------------------\n");

    generateTAC(postfix);

    return 0;
}