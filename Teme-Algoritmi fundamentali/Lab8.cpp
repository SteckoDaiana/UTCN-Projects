#include <iostream>
#include <random>
#include "Profiler.h"

using namespace std;

#define NR_TESTS 5
#define MAXSIZE 10000
#define STEPSIZE 100

Profiler profiler("multimi disjuncte");

int getRandomNumber(int l, int h)
{
	if (l > h)
		return -1;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(l, h);
	return distr(generator);
}

typedef struct nod {
	int rank;
	int id;
	struct nod* p;
} Node;

typedef struct edge {
	Node* first;
	Node* second;
	int weight;
} Edge;

Edge makeEdge(Node* a, Node* b, int w)
{
	Edge e;
	e.first = a;
	e.second = b;
	e.weight = w;
	return e;
}

void Heapify(Edge arr[], int n, int i, int size)
{
	int largest = i;
	int st = 2 * i + 1;
	int dr = 2 * i + 2;

	if (st < n && arr[st].weight > arr[largest].weight)
		largest = st;
	if (dr < n && arr[dr].weight > arr[largest].weight)
		largest = dr;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		Heapify(arr, n, largest, size);
	}
}
void BuildHeap(Edge arr[], int n, int size)
{
	for (int i = n / 2 - 1; i >= 0; --i)
		Heapify(arr, n, i, size);
}
void HeapSort(Edge arr[], int n, int size)
{
	BuildHeap(arr, n, size);
	for (int i = n - 1; i > 0; --i)
	{
		swap(arr[0], arr[i]);

		Heapify(arr, i, 0, size);
	}
}

Node* MAKESET(int id, Operation* op)
{
	Node* a = (Node*)malloc(sizeof(Node));
	if (a)
	{
		op->count(3);
		a->p = a;
		a->rank = 0;
		a->id = id;
	}
	return a;
}

Node* FINDSET(Node* n, Operation* op)
{
	op->count();
	if (n != n->p)
	{
		op->count();
		n->p = FINDSET(n->p, op);
	}
	op->count();
	return n->p;
}

void UNION(Node* x, Node* y, Operation* op)
{
	Node* a = FINDSET(x, op);
	Node* b = FINDSET(y, op);
	op->count(2);
	if (a->rank > b->rank)
		b->p = a;
	else
		a->p = b;
	op->count();
	if (a->rank == b->rank)
	{
		op->count();
		b->rank++;
	}
}

Edge* Kruskal(Node* V[], Edge E[], int N, int M, Operation opFND, Operation opUNI)
{

	Edge* result = (Edge*)calloc(N - 1, sizeof(Edge));
	if (result)
	{
		int rezsize = 0;
		HeapSort(E, 6, 0);
		for (int i = 0; i < M; ++i)
		{
			if (FINDSET(E[i].first, &opFND) != FINDSET(E[i].second, &opFND))
			{
				result[rezsize++] = E[i];
				UNION(E[i].first, E[i].second, &opUNI);
				if (rezsize == N - 1)
					break;
			}
		}
	}
	return result;
}
Node* noduri[10005];
Edge muchii[40005];
bool adiacenta[10005][10005];
void perf()
{

	for (int n = STEPSIZE; n <= MAXSIZE; n += STEPSIZE)
	{
		Operation opFND = profiler.createOperation("FIND", n);
		Operation opUNI = profiler.createOperation("UNION", n);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				adiacenta[i][j] = false;
		int m = 0;
		Operation opMAKE = profiler.createOperation("MAKE", n);
		for (int i = 1; i <= n; ++i)
		{
			noduri[i] = MAKESET(i, &opMAKE);
			int randomNode = getRandomNumber(1, i - 1);
			if (randomNode != -1)
			{
				adiacenta[randomNode][i] = 1;
				adiacenta[i][randomNode] = 1;
				muchii[m++] = makeEdge(noduri[i], noduri[randomNode], getRandomNumber(1, 50000)); // generam o muchie random intre nodul curent si un nod anterior
			}
		}
		for (int i = m; i < n * 4; ++i)
		{
			int first, second;
			do
			{
				first = getRandomNumber(1, n);
				second = getRandomNumber(1, n);
			} while (first == second || adiacenta[first][second] == true);
			adiacenta[first][second] = true;
			adiacenta[second][first] = true;
			muchii[i] = makeEdge(noduri[first], noduri[second], getRandomNumber(1, 50000));
		}

		//divide by n (?) 
		free(Kruskal(noduri, muchii, n, n * 4, opFND, opUNI));
		for (int i = 1; i <= n; ++i)
		{
			free(noduri[i]);
		}
	}
	profiler.addSeries("Total 1", "MAKE", "FIND");
	profiler.addSeries("TOTAL", "Total 1", "UNION");
	profiler.createGroup("OPERATII", "MAKE", "FIND", "UNION", "TOTAL");
	profiler.showReport();
}


void demo()
{
	Operation dummy = profiler.createOperation("dummy", 0);
	Node* arr[10];
	for (int i = 0; i < 10; ++i)
	{
		arr[i] = MAKESET(i, &dummy);
	}
	UNION(arr[1], arr[3], &dummy);
	UNION(arr[2], arr[7], &dummy);
	UNION(arr[5], arr[7], &dummy);
	UNION(arr[4], arr[1], &dummy);
	UNION(arr[6], arr[3], &dummy);
	cout << FINDSET(arr[3], &dummy)->id << " ";
	cout << FINDSET(arr[4], &dummy)->id << " ";
	cout << FINDSET(arr[5], &dummy)->id << " ";
	cout << FINDSET(arr[9], &dummy)->id << " ";
	cout << FINDSET(arr[8], &dummy)->id << " \n";


	Edge E[100];
	Node* V[100];
	int n = 5;
	int m = 6;
	for (int i = 1; i <= 5; ++i)
		V[i] = MAKESET(i, &dummy);
	E[0] = makeEdge(V[1], V[2], 1);
	E[1] = makeEdge(V[2], V[3], 8);
	E[2] = makeEdge(V[1], V[3], 5);
	E[3] = makeEdge(V[1], V[5], 2);
	E[4] = makeEdge(V[1], V[4], 7);
	E[5] = makeEdge(V[5], V[4], 6);
	Edge* REZ = Kruskal(V, E, n, m, dummy, dummy);
	for (int i = 0; i < n - 1; ++i)
		cout << "( " << REZ[i].first->id << " " << REZ[i].second->id << " ), ";
}

int main()
{
	//demo();
	perf();
}