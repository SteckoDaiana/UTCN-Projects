#include <iostream>
#include <random>
#include "Profiler.h"

#define NR_TESTS 10
#define MAXSIZE 10000
#define STEPSIZE 100

using namespace std;

typedef struct binari {
	int val;
	int size;
	struct binari* left;
	struct binari* right;
} ArboreBinar;

Profiler& profiler = *(new Profiler("Statistici de Ordine"));


void printPrietenos(ArboreBinar* arb, int nivel = 0)
{
	if (arb == NULL)
		return;

	printPrietenos(arb->right, nivel + 1);

	for (int i = 0; i < nivel; ++i)
		cout << "             ";
	cout << arb->val << "(" << arb->size << ")\n\n";

	printPrietenos(arb->left, nivel + 1);
}




ArboreBinar* OSselect(ArboreBinar* n, int i, Operation* op)
{
	int r = 0;

	if (n->left != NULL) {
		r = n->left->size;
	}
	r++;

	op->count(1);
	if (i == r)
		return n;

	op->count(1);
	if (i < r)
	{

		if (n->left != NULL)
			return OSselect(n->left, i, op);
	}

	else {
		if (i > r)
		{
			op->count();
			if (n->right != NULL)
				return OSselect(n->right, i - r, op);
		}
	}

}

ArboreBinar* searchSuccesor(ArboreBinar* n, Operation* op)
{
	op->count(3);
	ArboreBinar* aux = n;
	aux = aux->right;
	while (aux->left != NULL)
	{
		aux = aux->left;
		op->count(2);
	}

	return aux;
}

ArboreBinar* OSdelete(ArboreBinar* n, int key, Operation* op)
{
	//arborele e gol
	op->count();
	if (n == NULL)
		return n;
	op->count();
	if (key < n->val)
	{
		op->count(2);
		n->size--;
		n->left = OSdelete(n->left, key, op);
	}
	else {
		op->count(1);
		if (key > n->val)
		{
			op->count(2);
			n->size--;
			n->right = OSdelete(n->right, key, op);
		}
		else
		{
			op->count();
			if (n->left == NULL)
			{
				op->count();
				ArboreBinar* copil = n->right;
				free(n);
				return copil;
			}
			else if (n->right == NULL)
			{
				op->count();
				ArboreBinar* copil = n->left;
				free(n);
				return copil;
			}
			else
			{
				op->count(4);
				ArboreBinar* succesor = searchSuccesor(n, op);
				n->val = succesor->val;
				n->size--;
				n->right = OSdelete(n->right, succesor->val, op);
			}
		}
	}
	return n;
}

ArboreBinar* buildTree(int l, int r, Operation* op)
{
	op->count();
	if (l > r)
		return NULL;
	ArboreBinar* n = (ArboreBinar*)malloc(sizeof(ArboreBinar));
	int m = (l + r) / 2;
	op->count();
	if (n != NULL)
	{
		op->count(3);
		n->val = m;
		n->size = r - l + 1;
		n->left = buildTree(l, m - 1, op);
		n->right = buildTree(m + 1, r, op);

	}
	return n;
}

void perf()
{
	for (int k = 0; k < NR_TESTS; ++k)
	{
		for (int n = STEPSIZE; n <= MAXSIZE; n += STEPSIZE)
		{
			Operation opselect = profiler.createOperation("OSselect", n);
			Operation opdelete = profiler.createOperation("OSdelete", n);
			Operation opbuildTree = profiler.createOperation("buildTree", n);
			vector<int> v;
			for (int i = 0; i < n; ++i)
				v.push_back(i);

			ArboreBinar* arb = buildTree(1, n, &opbuildTree);
			for (int i = 1; i <= n; ++i)
			{
				int index = rand() % (v.size());
				int val = v.at(index) + 1;
				v.erase(v.begin() + index);
				OSselect(arb, val, &opselect);
				arb = OSdelete(arb, val, &opdelete);
			}

		}
	}
	profiler.divideValues("OSselect", NR_TESTS);
	profiler.divideValues("OSdelete", NR_TESTS);
	profiler.divideValues("buildTree", NR_TESTS);
	profiler.createGroup("OPERATII", "OSselect", "OSdelete", "buildTree");
	profiler.showReport();
}

void demo()
{
	int n = 11;
	Operation dummy = profiler.createOperation("dummy", 0);
	ArboreBinar* arb = buildTree(1, n, &dummy);
	printPrietenos(arb);
	cout << "\n\n\n\n";
	cout << OSselect(arb, 1, &dummy)->val << "\n";
	cout << OSselect(arb, 11, &dummy)->val << "\n";
	cout << OSselect(arb, 3, &dummy)->val << "\n";
	cout << "\n\n\n\n";


	cout << "\n\n\n\n\n\n\n";
	printPrietenos(arb);
	arb = OSdelete(arb, 1, &dummy);
	cout << "\n\n\n\n\n\n\n";
	printPrietenos(arb);
	arb = OSdelete(arb, 11, &dummy);
	cout << "\n\n\n\n\n\n\n";
	printPrietenos(arb);
	arb = OSdelete(arb, 3, &dummy);
	/*
	for (int i = 1; i <= 11; ++i)
	{
		cout << "\n\n\n\n\n\n\n";
		printPrietenos(arb);
		arb = OSdelete(arb, i, &dummy);
	}
	*/



}

int main()
{
	//demo();
	perf();
}