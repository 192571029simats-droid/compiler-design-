%{
#include <stdio.h>
%}

%%

[0-9] {
    printf("%s is a Digit\n", yytext);
}

[^0-9\n] {
    printf("%s is Not a Digit\n", yytext);
}

\n ;

%%

int main()
{
    printf("Enter a character:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}