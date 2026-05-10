#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void insert_at_front(EdgeList* list, int to, int w) {
    EdgeNodePtr newNode = malloc(sizeof(struct edgeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->edge.to_vertex = to;
    newNode->edge.weight = w;
    newNode->next = list->head;
    list->head = newNode;
}

void add_edge(Graph* self, int from, int to, int w) {
    insert_at_front(&self->edges[from], to, w);
}

void load_graph(Graph* G, const char* filename, int weighted) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "%d\n", &G->V);

    G->edges = malloc(G->V * sizeof(EdgeList));
    for (int v = 0; v < G->V; v++) {
        G->edges[v].head = NULL;
    }

    int from, to, weight;
    if (weighted) {
        while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
            add_edge(G, from, to, weight);
        }
    }
    else {
        while (fscanf(file, "%d,%d", &from, &to) == 2) {
            add_edge(G, from, to, 0);
        }
    }

    fclose(file);
}

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