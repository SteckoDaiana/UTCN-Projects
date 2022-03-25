#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct _Node
{
    int id; //nume nodului
    struct _Node *left,*right;
} NodeT;


NodeT * createBinTreeFromFile(FILE *f)
{
    NodeT *p;
    int c;
    //se citeste id-ul nodului
    fscanf(f,"%d", &c);
    if(c == 0)
    {
        printf("Null \n");
        return NULL; //arbore vid
    }
    else //else inclus pentru claritate
        //construim nodul la care pointeaza p
    {
        p =(NodeT*) malloc(sizeof(NodeT));
        if(p == NULL)
        {
            printf("Nu mai avem memorie in createBinTree");
            return NULL;
        }
        printf("%d \n",c);
        p->id =c;
        printf("Left de %d : ",c);
        p->left = createBinTreeFromFile(f);
        printf("Right de %d : ",c);
        p->right = createBinTreeFromFile(f);
    }
    return p;
}

NodeT * create_balancing_tree(int nbOfNodes)
{
    NodeT *p;
    int nLeft, nRight;
    if(nbOfNodes <= 0 )
    {
        return NULL;
    }
    else
    {
        nLeft = nbOfNodes /2;
        nRight = nbOfNodes - nLeft -1;
        p =(NodeT*) malloc(sizeof(NodeT));

        printf("Node identifier = %d %d\n",nLeft,nRight);
        printf("Insert node:");
        scanf("%d",&(p->id));

        printf("Left de %d : \n",p->id);
        p->left = create_balancing_tree(nLeft);
        printf("Right de %d : \n",p->id);
        p->right = create_balancing_tree(nRight);
    }
    return p;
}

void print_preordine(NodeT *root)
{
    if(root==NULL)
    {
        return;
    }

    printf("%d ",root->id);
    print_preordine(root->left);
    print_preordine(root->right);

}

void print_inordine(NodeT *root)
{
    if(root==NULL)
    {
        return;
    }

    print_inordine(root->left);
    printf("%d ",root->id);
    print_inordine(root->right);

}

void print_postordine(NodeT *root)
{
    if(root==NULL)
    {
        return;
    }

    print_postordine(root->left);
    print_postordine(root->right);
    printf("%d ",root->id);
}


int leaf_node(NodeT *root)
{
    if(root==NULL)
    {
        return 0;
    }
    else if(root->left ==NULL && root->right==NULL)
    {
        printf("Leaf %d \n",root->id);
        return 1;
    }
    else
    {
        return leaf_node(root->left) + leaf_node(root->right);
    }
}

bool  is_leaf_node(NodeT *root,int id)
{
    if(root==NULL)
    {
        return 0;
    }
    if(id == root->id)
    {
        if((root->left == NULL) &&(root->right == NULL))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        bool left_check = is_leaf_node(root->left,id);
        bool right_check = is_leaf_node(root->right,id);
        return (left_check || right_check);
    }

}

int internal_node(NodeT *root)
{
    if(root==NULL)
    {
        return 0;
    }
    else if (root->left ==NULL && root->right == NULL)
    {
        return 0;
    }
    else
    {
        printf("Internal Node %d\n ",root->id);
        return 1+internal_node(root->left)+internal_node(root->right);
    }
}
//inaltime arbore
int height_tree(NodeT *root)
{
    if(root==NULL)
    {
        return -1;
    }
    else
    {
        return 1+ MAX(height_tree(root->left),height_tree(root->right));
    }
}

NodeT* search(NodeT *root, int key)
{
    if(root !=NULL)
    {
        if(root->id == key)
        {
            return root;
        }
        else
        {

            NodeT *left=search(root->left,key);
            NodeT *right=search(root->right,key);

            if(left != NULL)
            {
                return left;
            }
            else if (right !=NULL)
            {
                return right;
            }
            else
            {
                return NULL;
            }
        }
    }
    else
    {
        return NULL;
    }
}


int main()
{

    FILE *f = fopen("/Users/dantoderici/Desktop/SDA/Lab4_Tree/tree.txt","r");

    if (!f)
    {
        printf("Nu se poate deschide fisierul ArboreBinar.txt\n");
        return -1;
    }

    NodeT *root = createBinTreeFromFile(f);
    fclose(f);

    //printf("Tree: ");
    //print_postordine(root);
    //printf("Nb of leaf nodes %d \n",leaf_node(root));
    //printf("Nb of internal nodes %d \n",internal_node(root));
    //printf("Height of tree %d\n",height_tree(root));

    NodeT *p = search(root,9);
    if(p!=NULL)
    {
        printf("Found %d \n",p->id);
        if(is_leaf_node(root,p->id))
        {
            printf("Height of node %d \n",height_tree(root)-height_tree(p)-1);
        }
        else
        {
            printf("Height of node %d \n",height_tree(root)-height_tree(p));
        }
    }
    else
    {
        printf("Not found \n");
    }

    NodeT * root_balancing = NULL;
    int nbOfNodes=0;
    printf("Number of nodes:");
    scanf("%d",&nbOfNodes);
    root_balancing = create_balancing_tree(nbOfNodes);

    print_preordine(root_balancing);

    return 0;
}
