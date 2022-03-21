#include <iostream>
#include <algorithm>
#include "Profiler.h"
#include <random>

using namespace std;

enum { WHITE = 0, GREY, BLACK };

typedef struct node {
	int eticheta;
	int culoare;
	int parinte;
	int timpIntrare;
	int timpIesire;
	int adjSize;
	struct node** adj;

	int lowlink;
	bool isOnStack;
	int idT;
} Node;

typedef struct graf {
	int n;//numarul de nodri
	Node** noduri;
} Graf;

typedef struct lsNd {
	Node* val;
	struct lsNd* next;
} ListNode;

typedef struct ls {
	int lungime = 0;
	ListNode* begin;
	ListNode* end;
} List;

void push(List* l, Node* n)
{
	ListNode* nod = (ListNode*)malloc(sizeof(ListNode));
	nod->next = NULL;
	nod->val = n;
	if (l->lungime == 0)
	{
		l->begin = nod;
		l->end = nod;
		l->lungime++;
	}
	else
	{
		l->end->next = nod;
		l->end = nod;
		l->lungime++;
	}
}
void pop(List* l)
{
	ListNode* curr = l->begin;
	while (curr->next != l->end && curr->next != NULL)
		curr = curr->next;
	free(l->end);
	curr->next = NULL;
	l->end = curr;
	l->lungime--;
}


void adaugaMuchie(Node* sursa, Node* destinatie)
{
	if (sursa->adjSize == 0)
	{
		sursa->adj = (Node**)malloc(sizeof(Node*));
		sursa->adj[0] = destinatie;
		sursa->adjSize++;
	}
	else
	{
		sursa->adj = (Node**)realloc(sursa->adj, (sursa->adjSize + 1) * sizeof(Node*));
		sursa->adj[sursa->adjSize] = destinatie;
		sursa->adjSize++;
	}
}

int timp;
int parinti[100] = { -1 };

void DFSvisit(Node* n, Operation* op)
{
	op->count(2);
	n->timpIntrare = ++timp;
	n->culoare = GREY;
	cout << n->eticheta << " ";
	op->count();
	for (int i = 0; i < n->adjSize; ++i)
	{
		op->count(2);
		if (n->adj[i]->culoare == WHITE)
		{
			op->count();
			parinti[n->adj[i]->eticheta] = n->eticheta;
			DFSvisit(n->adj[i], op);
		}
	}
	op->count(2);
	n->culoare = BLACK;
	n->timpIesire = ++timp;
}



void DFS(Graf& g, Operation* op)
{

	for (int i = 0; i < g.n; ++i)
	{
		g.noduri[i]->culoare = WHITE;
		g.noduri[i]->parinte = NULL;
	}
	timp = 0;
	for (int i = 0; i < g.n; ++i)
	{
		if (g.noduri[i]->culoare == WHITE)
		{
			DFSvisit(g.noduri[i], op);
		}
	}
}

void TOPOvisit(Node* n, List* rez)
{
	n->culoare = GREY;
	for (int i = 0; i < n->adjSize; ++i)
	{
		if (n->adj[i]->culoare == WHITE)
		{
			TOPOvisit(n->adj[i], rez);
		}
	}
	n->culoare = BLACK;
	push(rez, n);
}

List* toposort(Graf& g)
{
	List* result = (List*)malloc(sizeof(List));
	List* actualResult = (List*)malloc(sizeof(List));
	result->lungime = 0;
	actualResult->lungime = 0;
	for (int i = 0; i < g.n; ++i)
		g.noduri[i]->culoare = WHITE;

	for (int i = 0; i < g.n; ++i)
		if (g.noduri[i]->culoare == WHITE)
			TOPOvisit(g.noduri[i], result);
	while (result->lungime != 0)
	{
		push(actualResult, result->end->val);
		pop(result);
	}
	return actualResult;
}

int comp(Node* a, Node* b)
{
	return a->timpIntrare < b->timpIntrare;
}
int numarcomp = 0;

void DFS_TRJ(Graf& g, int Curent, List* Stiva) {
	static int t = 0;
	g.noduri[Curent]->idT = t;
	g.noduri[Curent]->lowlink = t;
	t++;
	push(Stiva, g.noduri[Curent]);
	g.noduri[Curent]->isOnStack = TRUE;
	for (int i = 0; i < g.noduri[Curent]->adjSize; ++i)
	{

		if (g.noduri[Curent]->adj[i]->idT == -1)
		{


			DFS_TRJ(g, g.noduri[Curent]->adj[i]->eticheta, Stiva);
			g.noduri[Curent]->lowlink = min(g.noduri[Curent]->lowlink, g.noduri[Curent]->adj[i]->lowlink);
		}
		else if (g.noduri[Curent]->adj[i]->isOnStack) {
			g.noduri[Curent]->lowlink = min(g.noduri[Curent]->lowlink, g.noduri[Curent]->adj[i]->idT);
		}
	}
	if (g.noduri[Curent]->lowlink == g.noduri[Curent]->idT) {
		while (Stiva->lungime > 0)
		{
			Node* nou = Stiva->end->val;
			pop(Stiva);
			nou->lowlink = g.noduri[Curent]->idT;
			nou->isOnStack = FALSE;
			if (nou->eticheta == Curent)
				break;
		}
		numarcomp++;

	}
}

void Tarjan(Graf& g) {
	List* Stiva = (List*)malloc(1 * sizeof(List));
	Stiva->lungime = 0;
	Stiva->end = (ListNode*)malloc(sizeof(ListNode));
	Stiva->begin = (ListNode*)malloc(sizeof(ListNode));

	Stiva->end = NULL;
	Stiva->begin = NULL;

	for (int i = 0; i < g.n; i++) {
		if (g.noduri[i]->idT == -1) {
			DFS_TRJ(g, i, Stiva);
		}
	}
}

void demo()
{
	Profiler P("demo");
	Operation op = P.createOperation("Operatii", 0);
	Graf g;
	g.noduri = (Node**)calloc(9, sizeof(Node*));
	g.n = 8;
	for (int i = 0; i < g.n; ++i)
	{
		g.noduri[i] = (Node*)malloc(sizeof(Node));
		g.noduri[i]->adj = (Node**)calloc(9, sizeof(Node*));
		g.noduri[i]->adjSize = 0;
		g.noduri[i]->timpIesire = 0;
		g.noduri[i]->timpIesire = 0;
		g.noduri[i]->parinte = -1;
		g.noduri[i]->eticheta = i;
		g.noduri[i]->idT = -1;
		g.noduri[i]->lowlink = -1;
		g.noduri[i]->isOnStack = FALSE;
		g.noduri[i]->culoare = WHITE;
	}

	adaugaMuchie(g.noduri[0], g.noduri[1]);
	adaugaMuchie(g.noduri[1], g.noduri[2]);
	adaugaMuchie(g.noduri[2], g.noduri[0]);
	adaugaMuchie(g.noduri[3], g.noduri[7]);
	adaugaMuchie(g.noduri[3], g.noduri[4]);
	adaugaMuchie(g.noduri[4], g.noduri[5]);
	adaugaMuchie(g.noduri[5], g.noduri[0]);
	adaugaMuchie(g.noduri[5], g.noduri[6]);
	adaugaMuchie(g.noduri[6], g.noduri[4]);
	adaugaMuchie(g.noduri[6], g.noduri[2]);
	adaugaMuchie(g.noduri[6], g.noduri[0]);
	adaugaMuchie(g.noduri[7], g.noduri[3]);
	/*adaugaMuchie(g.noduri[1], g.noduri[2]);
	adaugaMuchie(g.noduri[2], g.noduri[3]);
	adaugaMuchie(g.noduri[3], g.noduri[6]);
	adaugaMuchie(g.noduri[4], g.noduri[3]);
	adaugaMuchie(g.noduri[4], g.noduri[5]);
	adaugaMuchie(g.noduri[5], g.noduri[6]);
	adaugaMuchie(g.noduri[2], g.noduri[8]);
	adaugaMuchie(g.noduri[1], g.noduri[8]);
	adaugaMuchie(g.noduri[7], g.noduri[8]);*/
	//DFS(g,&op);
	List* rez = toposort(g);
	ListNode* curent = rez->begin;

	cout << "\n";
	printf("\nSortarea topologica este:");
	cout << "\n";
	while (curent)
	{
		cout << curent->val->eticheta << " ";
		curent = curent->next;
	}
	Tarjan(g);
	printf("\n");
	printf("Numarul de componente conexe este :%d", numarcomp);
	printf("\n");
	for (int i = 0; i < g.n; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 0; i < g.n; i++) {
		printf("%d ", g.noduri[i]->lowlink);
	}
}


int getRandomNumber(int l, int h)
{
	if (l > h)
		return -1;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(l, h);
	return distr(generator);
}

void performance()
{
	int n, i;
	Profiler p("dfs");
	bool adj[300][300];


	// vary the number of edges
	for (n = 1000; n <= 4500; n += 100) {
		for (int i = 0; i < 300; ++i)
			for (int j = 0; j < 300; ++j)
				adj[i][j] = false;
		Operation op = p.createOperation("dfs_edges", n);
		Graf graph;
		graph.n = 100;
		//initialize the nodes of the graph
		graph.noduri = (Node**)malloc(graph.n * sizeof(Node*));
		for (i = 0; i < graph.n; ++i) {
			graph.noduri[i] = (Node*)malloc(sizeof(Node));
			memset(graph.noduri[i], 0, sizeof(Node));
			graph.noduri[i]->eticheta = i;
			graph.noduri[i]->idT = -1;
			graph.noduri[i]->lowlink = -1;
			graph.noduri[i]->isOnStack = FALSE;
			graph.noduri[i]->culoare = WHITE;
		}
		// TODO: generate n random edges
		// make sure the generated graph is connected
		int j;
		for (j = 0; j < graph.n; ++j)
		{
			int NodeRand = getRandomNumber(0, j - 1);
			if (NodeRand != -1)
			{
				adj[j][NodeRand] = adj[NodeRand][j] = true;
				adaugaMuchie(graph.noduri[j], graph.noduri[NodeRand]);
			}
		}
		for (; j < n; ++j)
		{
			int nods, nodf;
			do
			{
				nods = getRandomNumber(0, graph.n - 1);
				nodf = getRandomNumber(0, graph.n - 1);
			} while (nods == nodf || adj[nods][nodf] == true);
			adaugaMuchie(graph.noduri[nods], graph.noduri[nodf]);
			adj[nods][nodf] = adj[nodf][nods] = true;

		}
		DFS(graph, &op);

	}

	// vary the number of vertices
	for (n = 100; n <= 200; n += 10) {
		for (int j = 0; j < n; ++j)
			for (int i = 0; i < n; ++i)
				adj[j][i] = false;

		Operation op = p.createOperation("dfs_vertices", n);
		Graf graph;
		graph.n = n;
		//initialize the nodes of the graph
		graph.noduri = (Node**)malloc(graph.n * sizeof(Node*));
		for (i = 0; i < graph.n; ++i) {
			graph.noduri[i] = (Node*)malloc(sizeof(Node));
			memset(graph.noduri[i], 0, sizeof(Node));
			graph.noduri[i]->eticheta = i;
			graph.noduri[i]->idT = -1;
			graph.noduri[i]->lowlink = -1;
			graph.noduri[i]->isOnStack = FALSE;
			graph.noduri[i]->culoare = WHITE;
		}
		// TODO: generate 4500 random edges
		// make sure the generated graph is connected
		int j;
		for (j = 0; j < graph.n; ++j)
		{
			int NodeRand = getRandomNumber(0, j - 1);
			if (NodeRand != -1)
			{
				adaugaMuchie(graph.noduri[j], graph.noduri[NodeRand]);
				adj[j][NodeRand] = adj[NodeRand][j] = true;
			}
		}
		for (; j < 4500; ++j)
		{
			int nods, nodf;
			do
			{
				nods = getRandomNumber(0, n - 1);
				nodf = getRandomNumber(0, n - 1);
			} while (nods == nodf || adj[nods][nodf] == true);

			adaugaMuchie(graph.noduri[nods], graph.noduri[nodf]);
			adj[nods][nodf] = adj[nodf][nods] = true;
		}
		DFS(graph, &op);

	}

	p.showReport();
}
int main()
{
	demo();
	//performance();
}