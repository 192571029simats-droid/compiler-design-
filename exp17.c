#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char rules[10][20];
char nonTerminals[MAX];
char leading[MAX][MAX];

int ruleCount;
int ntCount;
int leadingCount[MAX];

int getIndex(char ch)
{
    int i;

    for (i = 0; i < ntCount; i++)
    {
        if (nonTerminals[i] == ch)
            return i;
    }

    return -1;
}

int exists(int index, char ch)
{
    int i;

    for (i = 0; i < leadingCount[index]; i++)
    {
        if (leading[index][i] == ch)
            return 1;
    }

    return 0;
}

void addLeading(int index, char ch)
{
    if (!exists(index, ch))
    {
        leading[index][leadingCount[index]++] = ch;
    }
}

int main()
{
    int i, j;
    int changed = 1;

    printf("LEADING SET - OPERATOR PRECEDENCE PARSER\n");
    printf("-----------------------------------------\n");

    printf("\nGrammar:\n");
    printf("E -> E+T | T\n");
    printf("T -> T*F | F\n");
    printf("F -> (E) | i\n");

    /* Non-terminals */
    ntCount = 3;
    nonTerminals[0] = 'E';
    nonTerminals[1] = 'T';
    nonTerminals[2] = 'F';

    /* Productions */
    ruleCount = 6;

    strcpy(rules[0], "E->E+T");
    strcpy(rules[1], "E->T");
    strcpy(rules[2], "T->T*F");
    strcpy(rules[3], "T->F");
    strcpy(rules[4], "F->(E)");
    strcpy(rules[5], "F->i");

    /* Compute LEADING */
    while (changed)
    {
        changed = 0;

        for (i = 0; i < ruleCount; i++)
        {
            char lhs = rules[i][0];
            char *rhs = strchr(rules[i], '>');

            rhs++;

            int lhsIndex = getIndex(lhs);

            if (lhsIndex == -1)
                continue;

            /* Terminal as first symbol */
            if (!isupper((unsigned char)rhs[0]))
            {
                if (!exists(lhsIndex, rhs[0]))
                {
                    addLeading(lhsIndex, rhs[0]);
                    changed = 1;
                }
            }
            else
            {
                /* Non-terminal as first symbol */
                int rhsIndex = getIndex(rhs[0]);

                if (rhsIndex != -1)
                {
                    for (j = 0; j < leadingCount[rhsIndex]; j++)
                    {
                        if (!exists(lhsIndex, leading[rhsIndex][j]))
                        {
                            addLeading(lhsIndex, leading[rhsIndex][j]);
                            changed = 1;
                        }
                    }
                }
            }
        }
    }

    /* Display LEADING sets */
    printf("\nLEADING Sets:\n");
    printf("----------------\n");

    for (i = 0; i < ntCount; i++)
    {
        printf("LEADING(%c) = { ", nonTerminals[i]);

        for (j = 0; j < leadingCount[i]; j++)
        {
            printf("%c", leading[i][j]);

            if (j != leadingCount[i] - 1)
                printf(", ");
        }

        printf(" }\n");
    }

    return 0;
}