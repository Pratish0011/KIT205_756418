#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    Graph G;

    load_graph(&G, "pagerank.txt", 0);     // tutorial test graph (unweighted)
    // load_graph(&G, "graph.txt", 1);           // week 8 weighted graph
    // load_graph(&G, "musae_git_edges.csv", 0); // large GitHub social network

    // --- Calculate in-degrees ---
    int* in_degree = calloc(G.V, sizeof(int));
    if (in_degree == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_graph(&G);
        return 1;
    }

    for (int v = 0; v < G.V; v++) {
        EdgeNodePtr current = G.edges[v].head;
        while (current != NULL) {
            in_degree[current->edge.to_vertex]++;
            current = current->next;
        }
    }

    printf("Vertex | In-Degree\n");
    printf("-------+----------\n");
    for (int v = 0; v < G.V; v++) {
        printf("  %2d   |    %d\n", v, in_degree[v]);
    }

    free(in_degree);

    // --- Calculate and print PageRanks ---
    int iterations = 100;
    float* pr = page_rank(&G, iterations);
    if (pr == NULL) {
        fprintf(stderr, "PageRank failed\n");
        free_graph(&G);
        return 1;
    }

    printf("\nPageRank after %d iterations:\n", iterations);
    printf("Vertex | PageRank\n");
    printf("-------+----------\n");
    for (int v = 0; v < G.V; v++) {
        printf("  %2d   |  %.6f\n", v, pr[v]);
    }

    free(pr);
    free_graph(&G);

    return 0;
}