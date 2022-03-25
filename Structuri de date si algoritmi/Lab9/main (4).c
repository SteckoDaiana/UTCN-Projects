#include <stdio.h>
#include <stdlib.h>

#define n 3
int x[n+1];

void afisare(int k)
{
    for (int i=1; i<=k;i++)
        printf("%d ",x[i]);
    printf("\n");
}

int phi(int k)
{
    for (int i=1; i<k; i++)
        if (x[k]==x[i])
            return 0;
    return 1;
}

void backtr(int k)
{
    for (int alfa=1; alfa<=n; alfa++)
    {
        x[k]=alfa;
        afisare(k); //pt a afisa spatiul de cautare
        if (phi(k))
        {
            if (k<n)
                backtr(k+1);
            else {
                 printf("SOLUTIE!\n");
                //afisare(n); //solutie
            }
        }
    }
}


int main()
{
    backtr(1);
    return 0;
}
