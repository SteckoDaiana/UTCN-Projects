#include <stdio.h>
#include <stdlib.h>



typedef struct
{
    int n;      // numar de varfuri
    int **m;    // matricea de adiacenta
} Graf;     // structura pentru memorarea grafului prin matrice de adiacenta

typedef struct elem
{
    int val;
    struct elem* next;
} NodeT;

typedef struct
{
    NodeT *first;
    NodeT *last;
} Coada;

enum { NEVIZITAT, VIZITAT };


void printErr()
{
    printf("Memorie insuficienta!\n");
    exit(1);
}

void initializeaza(Coada *Q)
{
    Q->first=Q->last=NULL;
}

void enqueue( int x, Coada *Q )
{
    NodeT *elem=(NodeT*)malloc(sizeof(NodeT));
    elem->val=x;
    elem->next=NULL;
    if (Q->last!=NULL)
    {
        Q->last->next=elem;
        Q->last=elem;
    }
    else
    {
        Q->first=Q->last=elem;
    }
}

int goala(Coada Q)
{
    return Q.first==NULL;
}

int dequeue(Coada *Q )
{
    int x=Q->first->val;
    NodeT* p = Q->first;

    Q->first=Q->first->next;
    if (Q->first==NULL)
        Q->last=NULL;

    free(p);
    return x;
}

void bfs( Graf G, int nodSursa )
{
    int* vizitate; /* pentru marcarea nodurilor vizitate */
    vizitate = calloc(G.n, sizeof(int));
    if (vizitate == NULL) printErr();

    Coada Q; /* coada nodurilor - intregi */

    int i, v, w; /* noduri */

    initializeaza( &Q );
    for ( i = 0; i < G.n; i++ ) /* marcam toate nodurile ca nevizitate */
        vizitate[ i ] = NEVIZITAT;
    vizitate[ nodSursa ] = VIZITAT; /* marcam nodul sursa ca vizitat */
    printf("%d ",nodSursa);
    enqueue( nodSursa, &Q );
    // nodSursa va fi primul nod scos din coada
    while( ! goala( Q ))
    {
        v = dequeue( &Q );
        for (w=0; w<G.n; w++)
            if (G.m[v][w]==1) //v e adiacent cu w
                if ( vizitate[ w ] == NEVIZITAT )
                {
                    vizitate[ w ] = VIZITAT;
                    printf("%d ",w);
                    enqueue( w, &Q );
                }
    }
    free(vizitate);
}

void citesteGraf(FILE* f, Graf* pG)
{
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic matricea de adiacenta:
    pG->m = calloc(pG->n, sizeof(int*));
    if (pG->m == NULL) printErr();  // alocare esuata
    int i;
    for (i=0; i<pG->n; i++)
    {
        // alocam dinamic linia i a matricii, cu n elemente intregi
        pG->m[i] = calloc(pG->n, sizeof(int));
        if (pG->m[i] == NULL) printErr();
    }

    int v, w;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in matricea de adiacenta:
    while (fscanf(f, "%d%d", &v, &w) == 2)
    {
        /// TODO: memoreaza arcul/muchia in matricea de adiacenta
        pG->m[v][w]=1;
        pG->m[w][v]=1; //graf neorientat
    }
}

int main()
{
    FILE* f = fopen("graf.txt", "r");
    if (f == NULL)
    {
        perror("graf.txt");
        exit(1);
    }
    Graf G;
    citesteGraf(f, &G);
    fclose(f);

    int v;
    printf("Numarul de noduri: %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);

    bfs(G, v);

    return 0;
}
