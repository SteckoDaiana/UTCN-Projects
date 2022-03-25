#include <iostream>

using namespace std;

typedef struct multicai {
	int nrCopii = 0;
	int val;
	struct multicai** succesori = NULL;
} ArboreMultical;

void AdaugaSuccesor(ArboreMultical* arb, ArboreMultical* par)
{
	if (par->succesori == NULL)
	{
		par->nrCopii = 1;
		par->succesori = (ArboreMultical**)calloc(1, sizeof(ArboreMultical*));
		if (par->succesori != NULL)
			par->succesori[0] = arb;
	}
	else
	{
		int i = ++(par->nrCopii);
		ArboreMultical** p = (ArboreMultical**)realloc(par->succesori, i * sizeof(ArboreMultical*));
		par->succesori = p;
		if (par->succesori != NULL)
			par->succesori[par->nrCopii - 1] = arb;
	}
}

void creazaNod(int parinte[], int i, ArboreMultical** noduri, ArboreMultical** radacina)
{
	if (noduri[i] != NULL)
		return;

	noduri[i] = (ArboreMultical*)malloc(sizeof(ArboreMultical));
	if (noduri[i])
	{
		noduri[i]->val = i;
		noduri[i]->nrCopii = 0;
		noduri[i]->succesori = NULL;
	}

	if (parinte[i] == -1)
	{
		*radacina = noduri[i];
		return;
	}

	if (noduri[parinte[i]] == NULL)
		creazaNod(parinte, parinte[i], noduri, radacina);

	AdaugaSuccesor(noduri[i], noduri[parinte[i]]);
}


ArboreMultical* T1(int parinte[], int n)
{
	ArboreMultical** noduri = (ArboreMultical**)calloc(n + 1, sizeof(ArboreMultical*));
	ArboreMultical* radacina = NULL;
	for (int i = 1; i <= n; ++i)
		if (noduri != NULL)
			noduri[i] = NULL;
	for (int i = 1; i <= n; ++i)
		creazaNod(parinte, i, noduri, &radacina);
	return radacina;
}

void printPrietenos(ArboreMultical* arb, int nivel = 0)
{
	if (arb == NULL)
		return;
	for (int i = 0; i < nivel; ++i)
		cout << "  ";
	cout << arb->val << "\n";

	for (int i = 0; i < arb->nrCopii; ++i)
		printPrietenos(arb->succesori[i], nivel + 1);
}

typedef struct binari {
	int val;
	struct binari* left;
	struct binari* right;
} ArboreBinar;

void creazaBin(ArboreBinar* b, ArboreMultical* m)
{
	if (m->nrCopii == 0)
	{
		b->left = NULL;
		return;
	}

	ArboreBinar** arr = (ArboreBinar**)calloc(m->nrCopii + 1, sizeof(ArboreBinar*));
	if (arr != NULL)
	{
		arr[0] = (ArboreBinar*)malloc(sizeof(ArboreBinar));

		for (int i = 0; i < m->nrCopii; ++i)
		{
			if (i + 1 == m->nrCopii)
				arr[i + 1] = NULL;
			else
				arr[i + 1] = (ArboreBinar*)malloc(sizeof(ArboreBinar));

			if (arr[i] != NULL)
			{
				arr[i]->val = m->succesori[i]->val;

				arr[i]->right = arr[i + 1];

				creazaBin(arr[i], m->succesori[i]);
			}
			else
				cout << "NULL";
		}
		b->left = arr[0];

	}
	else
		cout << "NULL";

}

ArboreBinar* T2(ArboreMultical* m)
{
	ArboreBinar* radacina = (ArboreBinar*)malloc(sizeof(ArboreBinar));
	if (radacina != NULL)
	{
		radacina->val = m->val;
		radacina->right = NULL;
		creazaBin(radacina, m);
	}
	return radacina;
}

void printPrietenos(ArboreBinar* arb, int nivel = 0)
{
	if (arb == NULL)
		return;
	for (int i = 0; i < nivel; ++i)
		cout << "  ";
	cout << arb->val << "\n";

	printPrietenos(arb->left, nivel + 1);
	printPrietenos(arb->right, nivel);
}

void printPrietenos2(int arry[], int viz[], int n, int k, int nivel)
{

	if (viz[k] == 1)
		return;
	else {
		viz[k] = 1;
		for (int i = 0; i < nivel; ++i)
			cout << "  ";
		cout << k << "\n";

		for (int i = 1; i <= n; ++i)
			if (arry[i] == k)
				printPrietenos2(arry, viz, n, i, nivel + 1);
	}
}

void demo()
{
	int arr[] = { 0, 2 , 7 , 5 , 2 , 7 , 7 ,-1 ,5 ,2 };
	int n = sizeof(arr) / sizeof(arr[0]) - 1;
	int viz[10] = { 0,0,0,0,0,0,0,0,0,0 };
	ArboreMultical* arbMul = T1(arr, n);
	ArboreBinar* arbBin = T2(arbMul);
	printPrietenos2(arr, viz, n, 7, 0);
	cout << "\n";
	printPrietenos(arbMul);
	cout << "\n";
	printPrietenos(arbBin);

}

int main()
{
	demo();
}