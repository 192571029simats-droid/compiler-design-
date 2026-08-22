%{
#include <stdio.h>
%}

%%
<[^>]+>    { printf("%s\n", yytext); }
.|\n       ;
%%

int main()
{
    printf("HTML Tags:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}