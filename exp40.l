%{
#include <stdio.h>
#include <string.h>

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int isKeyword(char *word)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%%

"//".*                         ;
"/*"([^*]|\*+[^*/])*\*+"/"     ;

[ \t\n]+                       ;

[a-zA-Z_][a-zA-Z0-9_]* {
    if (isKeyword(yytext))
        printf("Keyword       : %s\n", yytext);
    else
        printf("Identifier    : %s\n", yytext);
}

[0-9]+(\.[0-9]+)? {
    printf("Constant      : %s\n", yytext);
}

\"([^\"\\]|\\.)*\" {
    printf("String        : %s\n", yytext);
}

\'([^\'\\]|\\.)\' {
    printf("Character     : %s\n", yytext);
}

"=="|"!="|"<="|">="|"++"|"--"|"&&"|"||" {
    printf("Operator      : %s\n", yytext);
}

[+\-*/%=<>!] {
    printf("Operator      : %s\n", yytext);
}

[(){}\[\],;:.] {
    printf("Special Symbol : %s\n", yytext);
}

. {
    printf("Unknown Token : %s\n", yytext);
}

%%

int main()
{
    printf("Enter the C program:\n\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}