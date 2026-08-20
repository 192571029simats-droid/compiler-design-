#include <stdio.h>
#include <string.h>

#define MAX 20

char productions[][20] = {
    "E+T",
    "T",
    "T*F",
    "F",
    "(E)",
    "id"
};

int n = 6;

/* Check whether a symbol is a non-terminal */
int isNonTerminal(char c)
{
    return (c == 'E' || c == 'T' || c == 'F');
}

/* Find TRAILING set */
void findTrailing(char symbol, char trailing[], int *count)
{
    int i, len;
    char last;

    for (i = 0; i < n; i++)
    {
        /* Determine LHS of production */
        char lhs;

        if (i < 2)
            lhs = 'E';
        else if (i < 4)
            lhs = 'T';
        else
            lhs = 'F';

        if (lhs != symbol)
            continue;

        len = strlen(productions[i]);

        /* Last symbol of RHS */
        last = productions[i][len - 1];

        if (!isNonTerminal(last))
        {
            /* Add terminal directly */
            int exists = 0;
            int j;

            for (j = 0; j < *count; j++)
            {
                if (trailing[j] == last)
                    exists = 1;
            }

            if (!exists)
                trailing[(*count)++] = last;
        }
        else
        {
            /* Find TRAILING of the last non-terminal */
            char temp[MAX];
            int tempCount = 0;

            findTrailing(last, temp, &tempCount);

            int j, k;

            for (j = 0; j < tempCount; j++)
            {
                int exists = 0;

                for (k = 0; k < *count; k++)
                {
                    if (trailing[k] == temp[j])
                        exists = 1;
                }

                if (!exists)
                    trailing[(*count)++] = temp[j];
            }

            /*
             * If the last symbol is a non-terminal and the symbol
             * before it is a terminal, add that terminal.
             */
            if (len >= 2 && !isNonTerminal(productions[i][len - 2]))
            {
                char prev = productions[i][len - 2];
                int exists = 0;

                for (j = 0; j < *count; j++)
                {
                    if (trailing[j] == prev)
                        exists = 1;
                }

                if (!exists)
                    trailing[(*count)++] = prev;
            }
        }
    }
}

int main()
{
    char trailingE[MAX], trailingT[MAX], trailingF[MAX];
    int countE = 0, countT = 0, countF = 0;

    printf("Grammar:\n");
    printf("E -> E + T | T\n");
    printf("T -> T * F | F\n");
    printf("F -> ( E ) | id\n\n");

    findTrailing('E', trailingE, &countE);
    findTrailing('T', trailingT, &countT);
    findTrailing('F', trailingF, &countF);

    printf("TRAILING(E) = { ");
    for (int i = 0; i < countE; i++)
        printf("%c ", trailingE[i]);
    printf("}\n");

    printf("TRAILING(T) = { ");
    for (int i = 0; i < countT; i++)
        printf("%c ", trailingT[i]);
    printf("}\n");

    printf("TRAILING(F) = { ");
    for (int i = 0; i < countF; i++)
        printf("%c ", trailingF[i]);
    printf("}\n");

    return 0;
}