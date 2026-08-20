%{
#include <stdio.h>

int characters = 0;
int lines = 0;
int words = 0;
%}

%%

"//".*                  { /* Ignore single-line comment */ }

"/*"([^*]|\*+[^*/])*\*+"/" {
                            /* Ignore multi-line comment */
                            int i;
                            for (i = 0; i < yyleng; i++)
                            {
                                if (yytext[i] == '\n')
                                    lines++;
                            }
                          }

[ \t\r]+                { /* Ignore spaces and tabs */ }

\n                      { lines++; }

[A-Za-z_][A-Za-z0-9_]*  {
                            words++;
                            characters += yyleng;
                          }

[0-9]+                  {
                            characters += yyleng;
                          }

.                       {
                            characters++;
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

    yylex();

    fclose(fp);

    printf("\n===== LEXICAL ANALYSIS RESULT =====\n");
    printf("Number of characters : %d\n", characters);
    printf("Number of lines      : %d\n", lines);
    printf("Number of words      : %d\n", words);

    return 0;
}

int yywrap()
{
    return 1;
}