/*
* Stecko Daiana-grupa 10
* Această funcție face 2 sau mai multe partiții din matricea noastră. Partițiile se fac după compararea elementului curent cu pivotul. Deci, dacă elementul
    este mai mic decât pivotul, atunci acesta va fi în partea stângă și dacă elementul este mai mare decât pivotul, elementul va rămâne în partea dreaptă.

    / * Quicksort sortează recursiv o matrice, utilizând partiții. Cu ajutorul funcției de partiție, sortăm părțile folosind apeluri repetate de
    sortare rapida.
    Acum, despre complexitate. Complexitatea sa depinde de modul în care sunt făcute partițiile. Dacă există doar 2 partiții, vom introduce cel mai bun caz și după aplicarea
    Teorema Maestru obținem timpul de funcționare O (nlgn). Cel mai rău caz este atunci când o partiție conține doar 1 element și cealaltă va avea (n-1) alte
    elemente. De asemenea, dacă min / max se află pe prima poziție, avem și cel mai rău caz. Complexitatea pentru cel mai rău caz este O (n ^ 2).
    Acest algoritm nu este stabil, datorită faptului că ordinea relativă a cheilor egale nu rămâne în toate cazurile la aceiași indici ca atunci când era
    initial. => NOT STABLE
    Deoarece poate fi vizualizat în diagramele generate, cel mai bun caz pentru Quicksort este O (nlgn), în timp ce cel mai rău caz este O (n ^ 2), datorită faptului că
    oferim ca intrare o matrice deja comandată. Acest lucru se datorează faptului că fiecare element va fi schimbat și partiționarea nu are efect. Cel mai rău caz poate fi evitat dacă alegem o partiție aleatorie, iar cel mai bun este aproape de medie
    , deci împărțim matricea în două jumătăți egale. * /
*/
#include <iostream> 
#include "Profiler.h"

using namespace std;
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 30

Profiler profiler;

void Heapify(int arr[], int n, int i, int size)
{
    Operation comp = profiler.createOperation("heapsort-comp", size);
    Operation attr = profiler.createOperation("heapsort-attr", size);
    int largest = i;
    int st = 2 * i + 1;
    int dr = 2 * i + 2;
    comp.count();
    if (st <n && arr[st] > arr[largest]) {
        attr.count();
        largest = st;
    }
    comp.count();
    if (dr < n && arr[dr] > arr[largest]) {
        attr.count();
        largest = dr;
    }
    comp.count();
    if (largest != i) {
        swap(arr[i], arr[largest]);
        attr.count(3);

        Heapify(arr, n, largest, size);
    }
}
void BuildHeap(int arr[], int n, int size)
{
    for (int i = n / 2 - 1; i >= 0; --i)
        Heapify(arr, n, i, size);
}
void HeapSort(int arr[], int n, int size)
{
    Operation comp = profiler.createOperation("heapsort-comp", size);
    Operation attr = profiler.createOperation("heapsort-attr", size);

    BuildHeap(arr, n, size);
    for (int i = n - 1; i > 0; --i)
    {
        attr.count(3);
        swap(arr[0], arr[i]);
   
        Heapify(arr, i, 0, size);
    }
}

int partition(int arr[], int low, int high, int size)
{
    Operation comp = profiler.createOperation("quickSort-comp", size);
    Operation attr = profiler.createOperation("quickSort-attr", size);
    
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
        
    {
        comp.count();
        comp.count();
        if (arr[j] < pivot)
        {
            i++;
            attr.count(3);
            swap(arr[i], arr[j]);
        }
    }
    attr.count(3);
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int size)
{
    Operation comp = profiler.createOperation("quickSort-comp", size);
    Operation attr = profiler.createOperation("quickSort-attr", size);
    
    comp.count();
    if (low < high)
    {
        attr.count();
        int pi = partition(arr, low, high, size);

        quickSort(arr, low, pi - 1, size);
        quickSort(arr, pi + 1, high, size);
    }
}
///quickSelect
int quickSelect(int arr[], int first, int last, int i, int size){

        if(first == last) return arr[first];
        int q = partition(arr, first, last, size);
        int k = q - first + 1;
        if (i == k) return arr[q];
  else if (i < k) return quickSelect(arr, first, q - 1, i, size);
else quickSelect(arr, q + 1, last, i - k, size);
}


void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void corectitudine() {
    int arr[] = { 2, 7, 15, 24, 1, 3, 12, 5, 38 };
    int arr1[] = { 2, 7, 15, 24, 1, 3, 12, 5, 38 };
    int arr2[] = { 2, 7, 15, 24, 1, 3, 12, 5, 38 };
    
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Array: \n";
    printArray(arr, n);

    quickSort(arr, 0, n-1, n);
    cout << "Sorted array: \n";
    printArray(arr, n);
    HeapSort(arr1, n, n);

    cout << "Sorted array: \n";
    printArray(arr1, n);

    cout << quickSelect(arr2, 0, n-1, 2, n) << endl;
    cout << "quickArray: \n";
    printArray(arr2, n);
    

}

int arr1[MAX_SIZE + 1];
int arr2[MAX_SIZE + 1];
void perfomanta()
{
    for (int i = 1; i <= NR_TESTS; i++) {
        for (int n = 100; n <= MAX_SIZE; n += STEP_SIZE)
        {
            FillRandomArray(arr1, n);
            for (int k = 1; k <= n; k++)
                arr2[k] = arr1[k];
            quickSort(arr1, 1, n, n);
            HeapSort(arr2, n, n);
        }

    }
    profiler.divideValues("quickSort-comp", NR_TESTS);
    profiler.divideValues("quickSort-attr", NR_TESTS);
    profiler.addSeries("quickSort-total", "quickSort-comp", "quickSort-attr");

    profiler.divideValues("heapsort-comp", NR_TESTS);
    profiler.divideValues("heapsort-attr", NR_TESTS);
    profiler.addSeries("heapsort-total", "heapsort-comp", "heapsort-attr");

    profiler.createGroup("atribuiri", "quickSort-attr", "heapsort-attr");
    profiler.createGroup("comparatii", "quickSort-comp", "heapsort-comp");
    profiler.createGroup("operatii", "quickSort-total", "heapsort-total");

    profiler.showReport();
}
int main()
{
    //corectitudine();
    perfomanta();
}