#include <stdio.h>
#include <ctype.h>

int main()
{
    char str[200];
    int i, consonants = 0;
    char ch;

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    for (i = 0; str[i] != '\0'; i++)
    {
        ch = tolower(str[i]);

        if (ch >= 'a' && ch <= 'z')
        {
            if (ch != 'a' && ch != 'e' && ch != 'i' &&
                ch != 'o' && ch != 'u')
            {
                consonants++;
            }
        }
    }

    printf("Number of consonants = %d\n", consonants);

    return 0;
}