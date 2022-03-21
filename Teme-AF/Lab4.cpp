#include <iostream> 
#include "Profiler.h"

#define KMAX 505
#define NR_TESTS 5
#define NMAX 10005
#define K_STEP_SIZE 10
#define N_STEP_SIZE 100

using namespace std;

Profiler profiler;

typedef struct node {
    int val;
    struct node* next;
} Node;

Node* newNode(int val)
{
    Node* n = (Node*)malloc(sizeof(Node));
    if (n != NULL)
    {
        n->val = val;
        n->next = NULL;
    }
    return n;
}

typedef struct list {
    Node* front;// pointer catre primul elem 
    Node* rear;// pointer catre ultimul element
} List;

List* newList()
{
    List* l = (List*)malloc(sizeof(List));
    if (l != NULL)
    {
        l->front = NULL;
        l->rear = NULL;
    }
    return l;
}

void InsertNode(List* l, Node* n)
{
    if (l->front == NULL)
    {
        l->front = n;// inserare daca nu este nimic in lista 
        l->rear = n;
    }
    else {
        l->rear->next = n;// insert last 
        l->rear = n;
    }
}

void FreeList(List* l)
{
    Node* p = l->front;
    Node* aux;
    while (p != NULL)
    {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(l);
}

void PrintList(List* l)
{
    Node* p = l->front;
    while (p != NULL)
    {
        cout << p->val << " ";
        p = p->next;
    }
}

void Heapify(Node* arr[], int n, int i, int size)
{
    Operation op = profiler.createOperation("k1", size);
    int largest = i;
    if (2 * i <= n)
    {
        op.count();
        if (arr[2 * i]->val < arr[largest]->val)
            largest = 2 * i;
    }
    if (2 * i + 1 <= n)
    {
        op.count();
        if (arr[2 * i + 1]->val < arr[largest]->val)
            largest = 2 * i + 1;
    }
    if (largest != i)
    {
        op.count(3);
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest, size);
    }
}
void Heapify1(Node* arr[], int n, int i, int size)
{
    Operation op = profiler.createOperation("k2", size);
    int largest = i;
    if (2 * i <= n)
    {
        op.count();
        if (arr[2 * i]->val < arr[largest]->val)
            largest = 2 * i;
    }
    if (2 * i + 1 <= n)
    {
        op.count();
        if (arr[2 * i + 1]->val < arr[largest]->val)
            largest = 2 * i + 1;
    }
    if (largest != i)
    {
        op.count(3);
        swap(arr[i], arr[largest]);
        Heapify1(arr, n, largest, size);
    }
}
void Heapify2(Node* arr[], int n, int i, int size)
{
    Operation op = profiler.createOperation("k3", size);
    int largest = i;
    if (2 * i <= n)
    {
        op.count();
        if (arr[2 * i]->val < arr[largest]->val)
            largest = 2 * i;
    }
    if (2 * i + 1 <= n)
    {
        op.count();
        if (arr[2 * i + 1]->val < arr[largest]->val)
            largest = 2 * i + 1;
    }
    if (largest != i)
    {
        op.count(3);
        swap(arr[i], arr[largest]);
        Heapify2(arr, n, largest, size);
    }
}

void BuildHeap(Node* arr[], int n, int size)
{
    for (int i = n / 2; i >= 1; --i)
        Heapify(arr, n, i, size);
}
void BuildHeap1(Node* arr[], int n, int size)
{
    for (int i = n / 2; i >= 1; --i)
        Heapify1(arr, n, i, size);
}
void BuildHeap2(Node* arr[], int n, int size)
{
    for (int i = n / 2; i >= 1; --i)
        Heapify2(arr, n, i, size);
}

List* lists[KMAX];

List* mergeKlists0(int n, int k, int size)//impreuna cu buildheap ordoneaza tabloul de liste crescator dupa primul element din fiecare lista 
{
    Operation op = profiler.createOperation("k1", size);
    Node* aux;
    List* result = newList();
    Node* heap[KMAX];
    for (int i = 0; i < k; ++i) //heapurile incep de la 1 
        heap[i + 1] = lists[i]->front;

    BuildHeap(heap, k, size);
    while (k)
    {
        InsertNode(result, heap[1]);
        op.count();
        heap[1] = heap[1]->next;

        if (heap[1] != NULL)
            Heapify(heap, k, 1, size);
        else
        {
            aux = heap[1];
            heap[1] = heap[k];
            heap[k] = aux;
            k--;
            Heapify(heap, k, 1, size);
        }
    }
    return result;
}
List* mergeKlists1(int n, int k, int size)//impreuna cu buildheap ordoneaza tabloul de liste crescator dupa primul element din fiecare lista 
{
    Operation op = profiler.createOperation("k2", size);
    Node* aux;
    List* result = newList();
    Node* heap[KMAX];
    for (int i = 0; i < k; ++i) //heapurile incep de la 1 
        heap[i + 1] = lists[i]->front;

    BuildHeap1(heap, k, size);
    while (k)
    {
        InsertNode(result, heap[1]);
        op.count();
        heap[1] = heap[1]->next;

        if (heap[1] != NULL)
            Heapify1(heap, k, 1, size);
        else
        {
            aux = heap[1];
            heap[1] = heap[k];
            heap[k] = aux;
            k--;
            Heapify1(heap, k, 1, size);
        }
    }
    return result;
}

List* mergeKlists2(int n, int k, int size)//impreuna cu buildheap ordoneaza tabloul de liste crescator dupa primul element din fiecare lista 
{
    Operation op = profiler.createOperation("k3", size);
    Node* aux;
    List* result = newList();
    Node* heap[KMAX];
    for (int i = 0; i < k; ++i) //heapurile incep de la 1 
        heap[i + 1] = lists[i]->front;

    BuildHeap2(heap, k, size);
    while (k)
    {
        InsertNode(result, heap[1]);
        op.count();
        heap[1] = heap[1]->next;

        if (heap[1] != NULL)
            Heapify2(heap, k, 1, size);
        else
        {
            aux = heap[1];
            heap[1] = heap[k];
            heap[k] = aux;
            k--;
            Heapify2(heap, k, 1, size);
        }
    }
    return result;
}

void demo()
{
    for (int i = 0; i < 3; ++i)
        lists[i] = newList();
    int arr1[] = { 1, 3, 4, 6, 8, 10 };
    int arr2[] = { 2, 6, 8, 10, 11, 12 };
    int arr3[] = { 4, 5, 7, 9, 13, 16 };
    int n = sizeof(arr1) / sizeof(arr1[0]);
    for (int i = 0; i < n; ++i)
        InsertNode(lists[0], newNode(arr1[i]));
    for (int i = 0; i < n; ++i)
        InsertNode(lists[1], newNode(arr2[i]));
    for (int i = 0; i < n; ++i)
        InsertNode(lists[2], newNode(arr3[i]));

    int size = 3;
    int k = 3;

    List* result = mergeKlists1(n, k, 3);
    PrintList(result);
}

int arraux[NMAX];



void mergeNvary(int k)//pt k1,k2,k3
{
    for (int i = 0; i < k; ++i)
        lists[i] = newList();

    for (int i = 1; i <= NR_TESTS; ++i)
    {
        for (int n = N_STEP_SIZE; n <= NMAX; n += N_STEP_SIZE)
        {
            for (int j = 0; j < k; ++j)
            {
                FillRandomArray(arraux, n, 10, 50000, false, ASCENDING);
                for (int b = 0; b < n; ++b)
                    InsertNode(lists[j], newNode(arraux[b]));
            }
            List* result = mergeKlists0(n, k, n);
            FreeList(result);
            for (int j = 0; j < k; ++j)
            {
                lists[j]->rear = lists[j]->front = NULL;
            }
        }
    }

}
void mergeNvary1(int k)
{
    for (int i = 0; i < k; ++i)
        lists[i] = newList();

    for (int i = 1; i <= NR_TESTS; ++i)
    {
        for (int n = N_STEP_SIZE; n <= NMAX; n += N_STEP_SIZE)
        {
            for (int j = 0; j < k; ++j)
            {
                FillRandomArray(arraux, n, 10, 50000, false, ASCENDING);
                for (int b = 0; b < n; ++b)
                    InsertNode(lists[j], newNode(arraux[b]));
            }
            List* result = mergeKlists1(n, k, n);
            FreeList(result);
            for (int j = 0; j < k; ++j)
            {
                lists[j]->rear = lists[j]->front = NULL;
            }
        }
    }

}
void mergeNvary2(int k)
{
    for (int i = 0; i < k; ++i)
        lists[i] = newList();

    for (int i = 1; i <= NR_TESTS; ++i)
    {
        for (int n = N_STEP_SIZE; n <= NMAX; n += N_STEP_SIZE)
        {
            for (int j = 0; j < k; ++j)
            {
                FillRandomArray(arraux, n, 10, 50000, false, ASCENDING);
                for (int b = 0; b < n; ++b)
                    InsertNode(lists[j], newNode(arraux[b]));
            }
            List* result = mergeKlists2(n, k, n);
            FreeList(result);
            for (int j = 0; j < k; ++j)
            {
                lists[j]->rear = lists[j]->front = NULL;
            }
        }
    }

}

void mergeKvary()//pt suma atr si a comp
{
    int n = 10000;
    for (int i = 0; i < KMAX; ++i)
        lists[i] = newList();
    for (int i = 1; i <= NR_TESTS; ++i)
    {
        for (int k = K_STEP_SIZE; k <= KMAX; k += K_STEP_SIZE)
        {
            for (int j = 0; j < k; ++j)
            {
                FillRandomArray(arraux, n, 10, 50000, false, ASCENDING);
                for (int b = 0; b < n; ++b)
                    InsertNode(lists[j], newNode(arraux[b]));
            }
            List* result = mergeKlists1(n, k, k);
            FreeList(result);
            for (int j = 0; j < k; ++j)
            {
                lists[j]->front = lists[j]->rear = NULL;
            }
        }
    }
    profiler.divideValues("k1", NR_TESTS);
}
void testall() {
    mergeNvary(5);

    mergeNvary1(10);

    mergeNvary2(100);
    profiler.createGroup("mergeK", "k1", "k2", "k3");
    //profiler.reset();
   // mergeKvary();
    profiler.showReport();


}
int main()
{
    // demo();
    testall();

}