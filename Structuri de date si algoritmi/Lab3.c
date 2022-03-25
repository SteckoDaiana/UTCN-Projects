#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int key;
    struct _Node* prev;
}Node;

typedef struct
{
    Node* first;
}Stack;

void push(Stack** s, int key)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->key=key;
    p->prev=NULL;
    if(*s==NULL)
    {
        *s=(Stack*)malloc(sizeof(Stack));
        (*s)->first=p;
    }
    else
    {
        p->prev=(*s)->first;
        (*s)->first=p;
    }
}

void afisare(Stack *s)
{
    if (s==NULL)
        return;
    else
    {
    Node*p= s->first;
    while(p!=NULL)
    {
        printf("%d ",p->key);
        p=p->prev;
    }
    }
}

int pop(Stack** s)
{
    if(*s!=NULL)
    {
        if((*s)->first->prev!=NULL)
        {
            Node*p=(*s)->first;
            int x=p->key;
            (*s)->first=(*s)->first->prev;
            free(p);
            return x;
        }
        printf("Warning: 1 element left\n");
        return (*s)->first->key;
    }
    return -1;
}

int main()
{
    Stack* s=NULL;
    for(int i=1;i<=10;i++)
        push(&s,i);
    afisare(s);
    for(int i=1;i<=3;i++)
    {
    int x=pop(&s);
    printf("\n");
    printf("%d\n",x);
    }
    afisare(s);
    return 0;
}
