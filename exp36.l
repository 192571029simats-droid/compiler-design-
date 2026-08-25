%{
#include <stdio.h>
#include <stdlib.h>

int num1, num2;
char op;
%}

%%

[0-9]+[ \t]*[+\-*/][ \t]*[0-9]+ {
    sscanf(yytext, "%d %c %d", &num1, &op, &num2);

    switch(op)
    {
        case '+':
            printf("Result = %d\n", num1 + num2);
            break;

        case '-':
            printf("Result = %d\n", num1 - num2);
            break;

        case '*':
            printf("Result = %d\n", num1 * num2);
            break;

        case '/':
            if(num2 != 0)
                printf("Result = %d\n", num1 / num2);
            else
                printf("Error: Division by zero\n");
            break;
    }
}

[ \t\n]+ ;

. {
    printf("Invalid expression\n");
}

%%

int main()
{
    printf("Enter mathematical expression:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}