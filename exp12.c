#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    printf("\nString is NOT accepted.\n");
    exit(0);
}

/* E -> T E' */
void E()
{
    T();
    Eprime();
}

/* E' -> + T E' | epsilon */
void Eprime()
{
    if (input[pos] == '+')
    {
        pos++;
        T();
        Eprime();
    }
}

/* T -> F T' */
void T()
{
    F();
    Tprime();
}

/* T' -> * F T' | epsilon */
void Tprime()
{
    if (input[pos] == '*')
    {
        pos++;
        F();
        Tprime();
    }
}

/* F -> (E) | id */
void F()
{
    if (strncmp(&input[pos], "id", 2) == 0)
    {
        pos += 2;
    }
    else if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            error();
    }
    else
    {
        error();
    }
}

int main()
{
    printf("Recursive Descent Parser\n");
    printf("Grammar:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | epsilon\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | epsilon\n");
    printf("F  -> (E) | id\n\n");

    printf("Enter the input string: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("\nString is ACCEPTED.\n");
    else
        printf("\nString is NOT accepted.\n");

    return 0;
}