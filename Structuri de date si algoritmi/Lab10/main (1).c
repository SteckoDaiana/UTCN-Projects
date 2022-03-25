#include <stdio.h>
#define MAX 1000

int s,n, monede[MAX], nrmin[MAX + 1], valadaugata[MAX + 1];

void read();
void DP();
void write();

int main()
{
    read();
    DP();
    write();
	return 0;
}
void read()
{
    int i;
    scanf("%d",&n);
    scanf("%d",&s);
    for(i = 0; i < n; i++)
        scanf("%d",&monede[i]);
}
void DP()
{
    for (int i=1; i<=s; i++)
        nrmin[i]=s+1; //infinit
    nrmin[0]=0;
    for (int i=1; i<=s; i++)
        for (int j=0; j<n; j++)
            if (i>=monede[j] && 1+nrmin[i-monede[j]]<nrmin[i])
            {
                nrmin[i]=1+nrmin[i-monede[j]];
                valadaugata[i]=monede[j];
            }
}

void write()
{
    if (nrmin[s]==s+1) //infinit
        printf("\nNu se poate plati!");
    else
    {
        printf("%d \n", nrmin[s]);
        for(int i = 0; i <= s; i++)
            printf("%d ", nrmin[i]);

        printf("\nSuma se plateste astfel: ");
        int aux=s;
        while (aux>0)
        {
            printf("%d ",valadaugata[aux]);
            aux-=valadaugata[aux];
        }
    }
}
