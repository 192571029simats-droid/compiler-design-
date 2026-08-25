%{
#include <stdio.h>
%}

%%

(0[1-9]|[12][0-9]|3[01])\/(0[1-9]|1[0-2])\/[0-9]{4} {
    printf("Valid DOB   : %s\n", yytext);
}

[^\n]+ {
    printf("Invalid DOB : %s\n", yytext);
}

\n ;

%%

int main()
{
    printf("Enter DOB (DD/MM/YYYY):\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}