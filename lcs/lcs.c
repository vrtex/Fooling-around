#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SLEN 20

#define MAX(a, b) (a > b ? a : b)

int lcs(const char *, const char *)
//takes two pointer to strings, returns lcs


int lcs(const char *string1, const char *string2)
{
    int i, j;
    int len1 = strlen(string1) + 1;
    int len2 = strlen(string2) + 1;

    int *t = malloc(len1 * len2 * sizeof(int));
    for(i = 0; i < len1; ++i)
    {
        *(t + i) = 0;
    }
    for(i = 0; i < len2; ++i)
    {
        *(t + i * len1) = 0;
    }

    for(i = 1; i < len1; ++i)
    {
        for(j = 1; j < len2; ++j)
        {
            if( *(string1 + i - 1) == *(string2 + j - 1))
            {
                *(t + i + j * len1) = *(t + (i - 1) + (j -1) * len1 ) + 1;
            }
            else
            {
                *(t + i + j * len1) = MAX(*(t + (i - 1) + j * len1), *(t + i + (j - 1) * len1));
            }
        }
    }
    i = *(t + i - 1 + len1 * (len2 - 1));

    return i;
}



int main(int argc, char const *argv[]) {
    char string1[SLEN], string2[SLEN];
    int len1, len2;
    int a = 0;
    do {
        printf("Enter first word:\n");
        a = scanf("%s", string1);
    } while(a != 1);
    do {
        printf("Enter second word:\n");
        a = scanf("%s", string2);
    } while(a != 1);
    a = lcs(string1, string2);
    printf("\n\n%d\n\n", a);

    return 0;
}
