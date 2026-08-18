#include <stdio.h>
#include <string.h>

void first(char ch)
{
    switch(ch)
    {
        case 'S':
            printf("{ a, b }\n");
            break;

        case 'A':
            printf("{ ε }\n");
            break;

        case 'B':
            printf("{ ε }\n");
            break;

        default:
            printf("Invalid Non-Terminal\n");
    }
}

int main()
{
    printf("Grammar:\n");
    printf("S -> AaAb | BbBa\n");
    printf("A -> ε\n");
    printf("B -> ε\n\n");

    printf("FIRST(S) = ");
    first('S');

    printf("FIRST(A) = ");
    first('A');

    printf("FIRST(B) = ");
    first('B');

    return 0;
}