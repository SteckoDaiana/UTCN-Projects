#include <stdio.h>
#define MAX 1000

int s,n, monede[MAX], combinatii[MAX + 1];

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
    combinatii[0]=1;
    for (int i=0; i<n; i++)
        for (int cantitate=0; cantitate<=s; cantitate++)
            if (cantitate>=monede[i])
                combinatii[cantitate]+=combinatii[cantitate-monede[i]];
}
void write()
{
    printf("%d \n", combinatii[s]);
    for(int i = 0; i <= s; i++)
        printf("%d ", combinatii[i]);
}
