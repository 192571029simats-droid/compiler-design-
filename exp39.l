%{
#include <stdio.h>
#include <string.h>

char oldWord[100];
char newWord[100];
%}

%%

[a-zA-Z]+ {
    if (strcmp(yytext, oldWord) == 0)
        printf("%s", newWord);
    else
        printf("%s", yytext);
}

[ \t\n]+ {
    printf("%s", yytext);
}

. {
    printf("%s", yytext);
}

%%

int main()
{
    printf("Enter the word to replace: ");
    scanf("%s", oldWord);

    printf("Enter the new word: ");
    scanf("%s", newWord);

    printf("\nEnter the file content:\n");

    yylex();

    return 0;
}

int yywrap()
{
    return 1;
}