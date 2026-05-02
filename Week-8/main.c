#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Insert a new edge at the front of an edge list
void insert_at_front(EdgeList* list, int to, int w) {
    EdgeNodePtr newNode = malloc(sizeof(struct edgeNode));
    newNode->edge.to_vertex = to;
    newNode->edge.weight = w;
    newNode->next = list->head;
    list->head = newNode;
}

// Add a directed edge from -> to with weight w
void add_edge(Graph* self, int from, int to, int w) {
    insert_at_front(&self->edges[from], to, w);
}

// Free all dynamically allocated memory
void free_graph(Graph* g) {
    for (int v = 0; v < g->V; v++) {
        EdgeNodePtr current = g->edges[v].head;
        while (current != NULL) {
            EdgeNodePtr temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->edges);
}

int main() {
    Graph G;

    // Open file
    FILE* file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read number of vertices
    fscanf(file, "%d\n", &G.V);

    // Allocate and initialise edge lists
    G.edges = malloc(G.V * sizeof(EdgeList));
    for (int v = 0; v < G.V; v++) {
        G.edges[v].head = NULL;
    }

    // Read edges from file
    int from, to, weight;
    while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
        add_edge(&G, from, to, weight);
    }

    fclose(file);

    // --- Calculate in-degrees ---
    int* in_degree = calloc(G.V, sizeof(int));

    for (int v = 0; v < G.V; v++) {
        EdgeNodePtr current = G.edges[v].head;
        while (current != NULL) {
            in_degree[current->edge.to_vertex]++;
            current = current->next;
        }
    }

    // Print in-degrees
    printf("Vertex | In-Degree\n");
    printf("-------+----------\n");
    for (int v = 0; v < G.V; v++) {
        printf("  %d    |    %d\n", v, in_degree[v]);
    }

    free(in_degree);
    free_graph(&G);

    return 0;
}