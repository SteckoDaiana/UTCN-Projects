#include <iostream> 
#include <string>
#include <algorithm>
#include "Profiler.h"

#define TABLE_LENGTH 10007 
#define NR_TESTS 5

typedef struct {
    int id;
    char name[30];
} Entry;

using namespace std;

Profiler profiler;

Entry hashTable[TABLE_LENGTH];

int generated[TABLE_LENGTH];


int Hash(int key, int i) {
    return ((key % TABLE_LENGTH) + i * i) % TABLE_LENGTH;
}

bool Insert(Entry e)
{
    for (int i = 0; i < TABLE_LENGTH; ++i)
    {
        if (hashTable[Hash(e.id, i)].id == 0)
        {
            hashTable[Hash(e.id, i)] = e;
            return true;
        }
    }
    return false;
}

Entry Search(int id, Operation& op)
{
    for (int i = 0; i < TABLE_LENGTH; ++i)
    {
        op.count();
        if (hashTable[Hash(id, i)].id == id)
        {
            return hashTable[Hash(id, i)];
        }
        if (hashTable[Hash(id, i)].id == NULL)
            return hashTable[Hash(id, i)];
    }
    Entry e;
    e.id = 0;
    return e;
}

void HashWipe()
{
    for (int i = 0; i < TABLE_LENGTH; ++i)
        hashTable[i].id = 0;//fill hash table with null value
}

void demo()
{
    Operation dummy = profiler.createOperation("dummy", 1);
    Entry e = { 1, "Melania" };
    Entry e1 = { 2, "Donald" };
    Entry e2 = { 3, "Joe" };
    Entry e3 = { 4, "Joe" };

    Insert(e);
    Insert(e1);
    Insert(e2);
    //Insert(e3);

    Entry s1 = Search(1, dummy);
    Entry s2 = Search(2, dummy);
    Entry s3 = Search(3, dummy);
    Entry s4 = Search(4, dummy);
    if (s1.id != 0) cout << s1.name << "\n";
    else cout << "Nu exista!\n";
    if (s2.id != 0) cout << s2.name << "\n";
    else cout << "Nu exista!\n";
    if (s3.id != 0) cout << s3.name << "\n";
    else cout << "Nu exista!\n";
    if (s4.id != 0) cout << s4.name << "\n";
    else cout << "Nu exista!\n";
}


void Performance()
{
    int maximumfound[100] = { 0 };
    int maximumnotfound[100] = { 0 };
    for (int i = 0; i < NR_TESTS; ++i)
    {
        FillRandomArray(generated, TABLE_LENGTH, 5000, 50000, true, ASCENDING);
        for (int fillFactor = 80; fillFactor < 100; fillFactor += 5)
        {
            HashWipe();
            for (int j = 0; j < fillFactor * 100; ++j)
            {
                Entry dummy;
                dummy.id = generated[j];
                Insert(dummy);
            }



            Operation opFound = profiler.createOperation("AVG EFFORT FOUND", fillFactor);
            int last = opFound.get();
            for (int j = 0; j < 1500; ++j)
            {
                int idToSearch = generated[j * (fillFactor / 15)];
                Search(idToSearch, opFound);
                int diff = opFound.get() - last;
                last = opFound.get();
                maximumfound[fillFactor] = max(maximumfound[fillFactor], diff);
            }

            Operation opNotFound = profiler.createOperation("AVG EFFORT NOT FOUND", fillFactor);
            last = opNotFound.get();
            for (int j = 1; j <= 1500; ++j)// we will search ids from 50000 to  100000
            {
                int idToSearch = j * 33 + 50000;
                Search(idToSearch, opNotFound);
                int diff = opNotFound.get() - last;
                last = opNotFound.get();
                maximumnotfound[fillFactor] = max(maximumnotfound[fillFactor], diff);
            }
            if (fillFactor == 95)
                fillFactor--;
        }
    }

    profiler.divideValues("AVG EFFORT FOUND", 1500);// for 1500 searches
    profiler.divideValues("AVG EFFORT FOUND", NR_TESTS); // for 5 tests
    profiler.divideValues("AVG EFFORT NOT FOUND", 1500);
    profiler.divideValues("AVG EFFORT NOT FOUND", NR_TESTS);
    cout << "  FactorDeUmplere  " << "  EfortMediuGasite   " << "EfortMaximGasite" << "  EfortMediu ne-gasite  " << "  EfortMaxim ne-gasite " << "\n";
    for (int i = 80; i < 100; i += 5)
    {
        Operation opFound = profiler.createOperation("AVG EFFORT FOUND", i);
        Operation opNotFound = profiler.createOperation("AVG EFFORT NOT FOUND", i);
        cout << "   " << i << ":                " << opFound.get() << "                      " << maximumfound[i] << "                       " << opNotFound.get() << "                      " << maximumnotfound[i] << "\n";



        if (i == 95)
            i--;
    }
}

int main()
{
    //demo();
    Performance();
}