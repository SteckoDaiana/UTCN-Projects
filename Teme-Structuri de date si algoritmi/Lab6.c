#include <stdio.h>
#include <stdlib.h>

#define  ln 7

typedef struct NodeT_
{
    int key;
    int frequency;
    struct NodeT_ *next;
} NodeT;

int modulo(int key)
{
    return key%ln;
}

int modulo2(int key)
{
    return 5-(key%5);
}

//exercitiul 1
void insertElement(NodeT* hTable[ln], int key)
{
    NodeT *node = NULL;
    node = (NodeT*)malloc(sizeof(NodeT));
    node->key = key;
    node->frequency = 1;
    node->next = NULL;
    int aux = modulo(key);
    if(hTable[aux] == NULL)
        hTable[aux] = node;
    else
    {
        NodeT *p=hTable[aux];
        while(p->next)
        {
            if(p->key == key)
            {
                p->frequency++;
                break;
            }
            p = p->next;
        }
        p->next = node;
    }
}

NodeT* findElement(NodeT* hTable[ln], int Key)
{
    int aux = modulo(Key);
    NodeT *p = hTable[aux];
    while(p)
    {
        if(p->key == Key)
            return p;
        p = p->next;
    }
    printf("Nu s-a gasit niciun element egal cu %d =(\n",Key);
    return NULL;
}

void deleteElement(NodeT* hTable[ln], int key)
{
    NodeT *p = hTable[modulo(key)];
    if(p->key == key)
    {
        hTable[modulo(key)]=hTable[modulo(key)]->next;
        free(p);
    }
    else
    {
        NodeT *q = p;
        p = p->next;
        while(p)
        {
            if(p->key == key)
            {
                q->next = p->next;
                free(p);
                break;
            }
            p=p->next;
            q=q->next;
        }
    }
}

//exercitiul 2
void liniar(NodeT *hashTable[ln],int key)
{
    int i;
    int hashValue = modulo(key);
    NodeT *node = (NodeT*)malloc(sizeof(NodeT));
    node->key = key;
    node->next = NULL;
    node->frequency = 1;
    if (hashTable[hashValue] == NULL)
        hashTable[hashValue] = node;
    else
    {
        for (i = hashValue+1 ; i < ln ; i++)
            if (hashTable[i] == NULL)
            {
                hashTable[i] = node;
                return;
            }
        for (i = 0 ; i < hashValue ; i++)
            if (hashTable[i] == NULL)
            {
                hashTable[i] = node;
                return;
            }
    }
}

//exercitiul 3
void polinomial(NodeT *hashTable[ln],int key)
{
    int hashValue = modulo(key);
    NodeT *node = (NodeT*)malloc(sizeof(NodeT));
    node->key = key;
    node->next = NULL;
    node->frequency = 1;
    if (hashTable[hashValue] == NULL)
        hashTable[hashValue] = node;
    else
    {
        for(int i = 0 ; i < ln ; i++)
        {
            hashValue = modulo(hashValue+i+(i*i));
            if(hashTable[hashValue] == NULL)
            {
                hashTable[hashValue]=node;
                return;
            }
        }
    }
}

//exercitiul 4
void double_check(NodeT *hashTable[ln],int key)
{
    int hashValue = modulo(key);
    NodeT *node = (NodeT*)malloc(sizeof(NodeT));
    node->key = key;
    node->next = NULL;
    node->frequency = 1;
    if (hashTable[hashValue] == NULL)
        hashTable[hashValue] = node;
    else
    {
        for(int i = 1 ; i < ln ; i++)
        {
            hashValue = modulo(hashValue+i*modulo2(key));
            if(hashTable[hashValue] == NULL)
            {
                hashTable[hashValue]=node;
                return;
            }
        }
    }
}

void printHashTable(NodeT *hTable[ln])
{
    for(int i = 0; i<ln; i++)
    {
        NodeT* iterator= hTable[i];
        printf("%d : ",i);

        while (iterator != NULL)
        {
            printf("[ %d ] -> ",iterator->key);
            iterator = iterator->next;
        }
        printf(" [ NULL ]");
        printf("\n");
    }
}

int main()
{
    NodeT *stash_table[ln];
    for(int i = 0; i < ln; i++ )
        stash_table[i] = NULL;
    insertElement(stash_table,50);
    insertElement(stash_table,46);
    insertElement(stash_table,43);
    insertElement(stash_table,2);
    insertElement(stash_table,41);
    printHashTable(stash_table);
    deleteElement(stash_table,2);
    deleteElement(stash_table,50);
    printf("\n");
    printHashTable(stash_table);
    if(findElement(stash_table,46))
        printf("Elementul %d cautat se afla in stash table =) \n",findElement(stash_table,46)->key);
    if(findElement(stash_table,35))
        printf("Elementul %d cautat se afla in stash table =) \n",findElement(stash_table,46)->key);

    NodeT *stash_linear[ln];
    for(int i = 0; i < ln; i++ )
        stash_linear[i] = NULL;
    liniar(stash_linear,19);
    liniar(stash_linear,36);
    liniar(stash_linear,5);
    liniar(stash_linear,21);
    liniar(stash_linear,4);
    liniar(stash_linear,26);
    liniar(stash_linear,14);
    printHashTable(stash_linear);
    return 0;
}
