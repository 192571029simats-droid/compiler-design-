%{
#include <stdio.h>

int positive = 0;
int negative = 0;
%}

%%

[-][0-9]+(\.[0-9]+)? {
    printf("Negative Number : %s\n", yytext);
    negative++;
}

[+]?[0-9]+(\.[0-9]+)? {
    printf("Positive Number : %s\n", yytext);
    positive++;
}

[ \t\n]+ ;

. ;

%%

int main()
{
    printf("Enter numbers:\n");
    yylex();

    printf("\nTotal Positive Numbers = %d\n", positive);
    printf("Total Negative Numbers = %d\n", negative);

    return 0;
}

int yywrap()
{
    return 1;
}