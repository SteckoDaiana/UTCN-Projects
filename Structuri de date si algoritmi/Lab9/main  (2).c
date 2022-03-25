#include <stdio.h>
#include <stdlib.h>

#define n 5
#define p 4
int x[p+1];
int nrsol;

void afisare(int k)
{
    for (int i=1; i<=k;i++)
        printf("%d ",x[i]);
    printf("\n");
}

int phi(int k)
{
    if (k==1 || x[k]>x[k-1])
        return 1;
    return 0;
}

void backtr(int k)
{
    for (int alfa=1; alfa<=n; alfa++)
    {
        x[k]=alfa;
        if (phi(k))
        {
            if (k<p)
                backtr(k+1);
            else {
                afisare(p); //solutie!!!
                nrsol++;
            }
        }
    }
}


int main()
{
    backtr(1);
    printf("Nr de solutii: %d",nrsol);
    return 0;
}
