/*
* Stecko Daiana, GRUPA 10
* Am implementat 2 variante de constructie a unui heap, bottom-up si top-down,plus heap-sort pe care l-am testat cu ambele metode
* Am constatat ca metoda bottom up este mult mai eficienta decat top-down
*/
#include <stdio.h> 
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5

Profiler p("HEAP");
void heapify(int v[], int n, int i)
{
    Operation opComp = p.createOperation("bottomComp", n);
    Operation opAttr = p.createOperation("bottomAttr", n);
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    
    opComp.count();
    if (l <n && v[l] > v[largest])
        largest = l;

    opComp.count();
    if (r <n && v[r] > v[largest])
        largest = r;

    if (largest != i)
    {
        opAttr.count(3);
        int k; k = v[i];
        v[i] = v[largest];
        v[largest] = k;

       heapify(v, n, largest);
    }
}


void build_heap(int v[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);
}



int parent(int n) {
    return (n - 1) / 2;
}

void heap_increase_key(int v[], int heap_size, int key, int n)
{
    Operation opComp = p.createOperation("topdownComp", n);
    Operation opAttr = p.createOperation("topdownAttr", n);

    opAttr.count();
    v[heap_size] = key;
    while (heap_size > 0 && v[parent(heap_size)] < v[heap_size])
    {
        opComp.count();
        opAttr.count(3);
        int aux = v[parent(heap_size)];
        v[parent(heap_size)] = v[heap_size];
        v[heap_size] = aux;
        heap_size = parent(heap_size);
    }
    if (heap_size > 0)
        opComp.count();
}
void max_Heap_Insert(int v[], int* heap_size, int  key, int n)
{
    Operation opComp = p.createOperation("topdownComp", n);
    Operation opAttr = p.createOperation("topdownAttr", n);
    opAttr.count(2);
    heap_size = heap_size + 1;
    v[*heap_size - 1] = INT_MIN;
    heap_increase_key(v, *heap_size - 1, key, n);
}
void build_heap2(int v[], int n)
{
    Operation opComp = p.createOperation("topdownComp", n);
    Operation opAttr = p.createOperation("topdownAttr", n);
    int i;
    opAttr.count();
    int heap_size = 1;
    for (i = 1; i < n; i++)
        max_Heap_Insert(v, &heap_size, v[i], n);
}

void heapSort(int v[], int n)
{
    build_heap2(v, n);
    //buid_heap(v,n); 
    for (int i = n - 1; i > 0; i--)
    {
        
        int k; k = v[0];
        v[0] = v[i];
        v[i] = k;

        heapify(v, i, 0);
    }
}


void afisare(int v[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}


void demo()
{
    int v[] = { 4,6,1,10,5 };
    int n = sizeof(v) / sizeof(v[1]);
    heapSort(v, n);
    printf("Sorted array is \n");
    afisare(v, n);
}
void perf()
{
    
    int v[MAX_SIZE], v2[MAX_SIZE];
    int n, i;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
        for (int test = 0; test < NR_TEST; test++)
        {
            FillRandomArray(v, n, 10, 30000);
            for (int i = 0; i < n; i++)
                v2[i] = v[i];
            build_heap(v, n);
            build_heap2(v2, n);

        }
    p.divideValues("bottomAttr", NR_TEST);
    p.divideValues("bottomComp", NR_TEST);
    p.addSeries("bottom-up-operatii", "bottomAttr", "bottomComp");

    p.divideValues("topdownAttr", NR_TEST);
    p.divideValues("topdownComp", NR_TEST);
    p.addSeries("topdown-operatii", "topdownAttr", "topdownComp");

    p.createGroup("Total-atribuiri", "bottomAttr", "topdownAttr");
    p.createGroup("Total-comparatii", "bottomComp", "topdownComp");
    p.createGroup("Total-operatii", "bottom-up-operatii", "topdown-operatii");
    p.showReport();
}
int main()
{

    //demo();
    perf();
    return 0;
}