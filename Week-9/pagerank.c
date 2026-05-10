#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

float* page_rank(Graph* g, int iterations) {
    int V = g->V;
    float d = 0.85f;

    float* pr = malloc(V * sizeof(float));
    float* sums = malloc(V * sizeof(float));
    int* out_deg = calloc(V, sizeof(int));

    // Calculate out-degrees
    for (int v = 0; v < V; v++) {
        EdgeNodePtr cur = g->edges[v].head;
        while (cur != NULL) {
            out_deg[v]++;
            cur = cur->next;
        }
    }

    // Initialise all PageRanks to 1
    for (int v = 0; v < V; v++) {
        pr[v] = 1.0f;
    }

    for (int iter = 0; iter < iterations; iter++) {

        // Step 1: Reset sums to zero
        for (int v = 0; v < V; v++) {
            sums[v] = 0.0f;
        }

        // Step 2: Accumulate sums from all edges
        for (int v = 0; v < V; v++) {
            if (out_deg[v] == 0) continue;
            EdgeNodePtr cur = g->edges[v].head;
            while (cur != NULL) {
                int to = cur->edge.to_vertex;
                sums[to] += pr[v] / out_deg[v];
                cur = cur->next;
            }
        }

        // Step 3: Apply damping factor
        for (int v = 0; v < V; v++) {
            pr[v] = (1.0f - d) + d * sums[v];
        }
    }

    free(sums);
    free(out_deg);

    return pr;
}