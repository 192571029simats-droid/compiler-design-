%{
#include <stdio.h>
#include <string.h>

int maxLength = 0;
char longestWord[100];
%}

%%

[a-zA-Z]+ {
    if (strlen(yytext) > maxLength)
    {
        maxLength = strlen(yytext);
        strcpy(longestWord, yytext);
    }
}

[ \t\n]+ ;

. ;

%%

int main()
{
    printf("Enter a sentence:\n");
    yylex();

    printf("\nLongest Word = %s\n", longestWord);
    printf("Length = %d\n", maxLength);

    return 0;
}

int yywrap()
{
    return 1;
}