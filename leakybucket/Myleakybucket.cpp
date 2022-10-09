#include <stdio.h>
#include <stdlib.h>

#define min(x, y) (x < y) ? x : y

void main()
{
    int bsize, outrate, n, i, rem = 0, k, drop;

    printf("Enter the bucket size : ");
    scanf("%i", &bsize);

    printf("Enter the out rate : ");
    scanf("%i", &outrate);

    printf("Enter the number of packets : ");
    scanf("%i", &n);
    int input[50] = {0};

    printf("Enter the size of packets : \n");
    for (i = 0; i < n; i++)
    {
        scanf("%i", &input[i]);
    }
    printf("Time\tRecieved\tSent\tDropped\tRemaining\n");
    for (i = 0; i < n || rem; i++)
    {
        if (input[i] + rem > bsize)
        {
            k = min(rem, outrate);
            rem -= k;
            drop = input[i];
        }
        else
        {
            k = min(rem + input[i], outrate);
            rem = rem + input[i] - k;
            drop = 0;
        }
        printf("%i\t%i\t\t%i\t%i\t\t%i\n", i + 1, input[i], k, drop, rem);
    }
}
