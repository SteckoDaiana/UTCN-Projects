#include <stdio.h>
#include <stdlib.h>


typedef struct NodeT
{
    int key;
    struct NodeT *left;
    struct NodeT *right;
    struct NodeT *parent;
} NodeT;


NodeT* insertNode(NodeT *root, int key)
{
    if(root)
    {
        if (key<(root->key))
            root->left=insertNode(root->left,key);
        else if (key>(root->key))
            root->right=insertNode(root->right,key);
        else
            printf("\nNodul exista in arbore!");
        return root;
    }
    else
    {
        NodeT *p=(NodeT*)malloc(sizeof(NodeT));
        p->left=NULL;
        p->right=NULL;
        p->key=key;
        return p;
    }
}


NodeT* searchKey(NodeT *root, int key)
{
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key)
        return searchKey(root->right, key);
    return searchKey(root->left, key);
}

NodeT *findMin(NodeT *root)
{
    while(root->left != NULL)
        root=root->left;
    return root;

}

NodeT *findMax(NodeT *root)
{
    while(root->right != NULL)
        root=root->right;
    return root;
}

NodeT* succesor(NodeT *root, NodeT *node)
{
    if(node->right != NULL)
        return findMin(node->right);
    NodeT *p=NULL;
    while(root!=NULL)
    {
        if(root->key<node->key)
        {
            root=root->right;
        }
        else if(root->key>node->key)
        {
            p=root;
            root=root->left;
        }
        else
            break;
    }
    return p;
}


NodeT* predecesor(NodeT *root, NodeT *node)
{
    if(node == NULL)
        return NULL;
    NodeT *p=NULL;
    if(node->left!=NULL)
        return findMax(node->left);
    else
    {
        while(root!=NULL)
        {
            if(root->key<node->key)
            {
                p=root;
                root=root->right;

            }
            else if(root->key>node->key)
            {
                root=root->left;
            }
            else
                break;
        }

    }
    return p;
}

NodeT *deleteKey(NodeT *root, int key)
{
    NodeT *p;
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteKey(root->left, key);
    else if (key > root->key)
        root->right = deleteKey(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            p = root->right;
            free(root);
            return p;
        }
        else if (root->right == NULL)
        {
            p = root->left;
            free(root);
            return p;
        }
        p = findMin(root->right);
        root->key = p->key;
        root->right = deleteKey(root->right, p->key);
    }
    return root;
}

void inOrder(NodeT *root, int space)
{
    if ( root != NULL )
    {
        space=space+4;
        inOrder( root->left,space);
        for(int i=0; i<space; i++)
        {
            printf(" ");
        }
        printf( "%d \n", root->key );
        inOrder( root->right,space);
    }
}

void preOrder(NodeT *root,int space)
{
    if ( root != NULL )
    {
        space=space+4;
        for(int i=0; i<space; i++)
        {
            printf(" ");
        }
        printf( "%d \n", root->key );
        preOrder( root->left,space);
        preOrder( root->right,space);
    }
}

void postOrder(NodeT *root,int space)
{
    if ( root != NULL )
    {
        space=space+4;
        postOrder( root->left,space);
        postOrder( root->right,space);
        for(int i=0; i<space; i++)
        {
            printf(" ");
        }
        printf( "%d \n", root->key );
    }
}

int main()
{

    NodeT *root = NULL;
    NodeT *p;

    int n = 11;
    int keys[] = {15, 6, 18, 17, 20, 3, 7, 2, 4, 13, 9};

    root = insertNode(root, keys[0]);

    for (int i = 1; i < n; i++)
    {
        insertNode(root, keys[i]);
    }

    printf( "\nPreorder listing\n" );
    preOrder( root,0);
    printf( "\nInorder listing\n" );
    inOrder( root,0);
    printf( "\nPostorder listing\n" );
    postOrder( root,0);

    int key = 15;
    p = searchKey( root, key );
    if ( p != NULL )
    {
        printf( "\nNod cu cheia = %d gasit\n", key);
        NodeT *m = findMin(p);
        printf("Minimul din subarborele care are ca radacina nodul %d este %d \n", p->key, m->key);
    }
    else
        printf( "Nodul NU a fost gasit \n" );

    NodeT *s = succesor(root, p);
    if ( s != NULL )
    {
        printf( "Nod cu cheia = %d are sucesor pe %d\n", p->key, s->key);
    }
    else
        printf( "Nodul NU are succesor !\n" );

    NodeT *q = predecesor(root, p);
    if ( q != NULL )
    {
        printf( "Nod cu cheia = %d are predecesor pe %d\n", p->key, q->key);
    }
    else
        printf( "Nodul NU are predecesor !\n" );


    key = 15;
    printf("Nodul de sters este: %d\n", key);
    root = deleteKey( root, key );
    inOrder( root,0);

    return 0;
}
