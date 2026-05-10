#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge {
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode {
    Edge edge;
    struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
    EdgeNodePtr head;
} EdgeList;

typedef struct graph {
    int V;
    EdgeList* edges;
} Graph;

void add_edge(Graph* self, int from, int to, int w);
void load_graph(Graph* G, const char* filename, int weighted);
void free_graph(Graph* g);
float* page_rank(Graph* g, int iterations);

#endif