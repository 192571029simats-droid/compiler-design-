%{
#include <stdio.h>

int macros = 0;
int headers = 0;
%}

%%

^[ \t]*#[ \t]*define[ \t]+[A-Za-z_][A-Za-z0-9_]* {
    macros++;
}

^[ \t]*#[ \t]*include[ \t]*<[^>]+> {
    headers++;
}

\"([^\"\\]|\\.)*\" {
    /* Ignore strings */
}

[0-9]+(\.[0-9]+)? {
    printf("Constant: %s\n", yytext);
}

.|\n {
    /* Ignore other characters */
}

%%

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc != 2)
    {
        printf("Usage: %s <input-file.c>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    yyin = fp;

    printf("===== CONSTANTS =====\n");
    yylex();

    fclose(fp);

    printf("\n===== PREPROCESSOR INFORMATION =====\n");
    printf("Number of Macros defined : %d\n", macros);
    printf("Number of Header files   : %d\n", headers);

    return 0;
}

int yywrap()
{
    return 1;
}