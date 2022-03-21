#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <queue>
#include <random>
#include "bfs.h"
#include "PrintPrietenos.h"

int getRandomNumber(int l, int h)
{
    if (l > h)
        return -1;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(l, h);
    return distr(generator);
}
bool adiacenta[300][300];

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    int directiex[] = {-1, 0, 1, 0};
    int directiey[] = { 0, 1, 0,-1};
    int sz = 0;
    for (int i = 0; i < 4; ++i)
    {
        int px = p.col + directiex[i];
        int py = p.row + directiey[i];
        if (grid->mat[py][px] == 0 && px >= 0 && py >= 0 && px <= grid->cols && py <= grid->rows)//daca nu e perete si e in matrice
        {
            neighb[sz].col = px;
            neighb[sz].row = py;
            sz++;
        }
    }
    return sz;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph *graph, Node *s, Operation *op)
{
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    if (op != NULL) op->count(2);
    s->color = COLOR_GRAY;
    s->dist = 0;
    std::queue<Node*> q;
    q.push(s);
    while (!q.empty())
    {
        Node* curent = q.front();
        q.pop();
        if (op != NULL) op->count(2);
        curent->color = COLOR_BLACK;
        for (int i = 0; i < curent->adjSize; ++i)
        {
            if (op != NULL) op->count(6);// 5 dereferentieri + 1 pentru for
            Node* urmator = curent->adj[i];
            if (urmator->color == COLOR_WHITE)
            {
                urmator->parent = curent;
                urmator->dist = curent->dist + 1;
                urmator->color = COLOR_GRAY;
                q.push(urmator);
            }
        }
    }


}

void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs
        
        ArboreMultical* BFStree = T1(p, n);
        printPrietenos(BFStree, repr);
    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000
    return -1;
}

bool adj[500][500];
//makes a connection between node n1 and n2
void leagamuchii(Node* a, Node* b)
{
    if (a->adjSize == 0)
    {

        a->adj = (Node**)malloc(sizeof(Node*));
        a->adjSize++;
        a->adj[0] = b;
    }
    else
    {
        a->adj = (Node**)realloc(a->adj, (++(a->adjSize)) * sizeof(Node*));
        a->adj[a->adjSize - 1] = b;
    }
    if (b->adjSize == 0)
    {
        b->adj = (Node**)malloc(sizeof(Node*));
        b->adjSize++;
        b->adj[0] = a;
    }
    else
    {
        b->adj = (Node**)realloc(b->adj, (++(b->adjSize)) * sizeof(Node*));
        b->adj[b->adjSize - 1] = a;
    }
}

void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for (n = 1000; n <= 4500; n += 100) {
        for (int i = 0; i < 500; ++i)
            for (int j = 0; j < 500; ++j)
                adj[i][j] = false;
        Operation op = p.createOperation("bfs_edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected
        int j;
        for (j = 0; j < graph.nrNodes; ++j)
        {
            int NodeRand = getRandomNumber(0, j - 1);
            if (NodeRand != -1)
            {
                adj[j][NodeRand] = adj[NodeRand][j] = true;
                leagamuchii(graph.v[j], graph.v[NodeRand]);
            }
        }
        for (; j < n; ++j)
        {
            int nods, nodf;
            do
            {
                nods = getRandomNumber(0, graph.nrNodes - 1);
                nodf = getRandomNumber(0, graph.nrNodes - 1);
            } while (nods == nodf || adj[nods][nodf] == true);
            leagamuchii(graph.v[nods], graph.v[nodf]);
            adj[nods][nodf] = adj[nodf][nods] = true;

        }
        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // vary the number of vertices
    for (n = 100; n <= 200; n += 10) {
        for (int j = 0; j < n; ++j)
            for (int i = 0; i < n; ++i)
                adj[j][i] = false;
           
        Operation op = p.createOperation("bfs_vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected
        int j;
        for (j = 0; j < graph.nrNodes; ++j)
        {
            int NodeRand = getRandomNumber(0, j - 1);
            if (NodeRand != -1)
            {
                leagamuchii(graph.v[j], graph.v[NodeRand]);
                adj[j][NodeRand] = adj[NodeRand][j] = true;
            }
        }
        for (; j < 4500; ++j)
        {
            int nods, nodf;
            do
            {
                nods = getRandomNumber(0, n - 1);
                nodf = getRandomNumber(0, n - 1);
            } while (nods == nodf || adj[nods][nodf] == true);

            leagamuchii(graph.v[nods], graph.v[nodf]);
            adj[nods][nodf] = adj[nodf][nods] = true;
        }
        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
