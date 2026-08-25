%{
#include <stdio.h>
#include <string.h>

char searchWord[100];
int count = 0;
%}

%%

[a-zA-Z]+ {
    if (strcmp(yytext, searchWord) == 0)
        count++;
}

[ \t\n]+ ;

. ;

%%

int main()
{
    printf("Enter the word to search: ");
    scanf("%s", searchWord);

    printf("Enter the sentence:\n");
    getchar();

    yylex();

    printf("\nFrequency of '%s' = %d\n", searchWord, count);

    return 0;
}

int yywrap()
{
    return 1;
}