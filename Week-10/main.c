#include <stdio.h>
#include <stdlib.h>


int knapsackValue(int w[], int v[], int W, int n) {

    // Create 2D table A[i][j] = best value using first i items with capacity j
    // Using n+1 rows and W+1 columns to handle base cases (i=0 and j=0)
    int** A = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        A[i] = calloc((W + 1), sizeof(int));  // calloc zeroes the row (base case)
    }

    // Fill the table row by row
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {

            if (w[i - 1] > j) {
                // Item too heavy to include 
                A[i][j] = A[i - 1][j];
            }
            else {
                // Choose the better option: skip it or take it
                int skip = A[i - 1][j];
                int take = v[i - 1] + A[i - 1][j - w[i - 1]];
                A[i][j] = (take > skip) ? take : skip;
            }
        }
    }

    int result = A[n][W];

    // Free the table
    for (int i = 0; i <= n; i++) {
        free(A[i]);
    }
    free(A);

    return result;
}

int main() {
    int w[10] = { 1, 1, 3, 3, 2, 4, 3, 6, 5, 7 };
    int v[10] = { 100, 150, 50, 25, 2, 15, 1000, 25, 55, 225 };
    int n = 10;

    printf("Knapsack capacity | Max value\n");
    printf("-----------------+-----------\n");
    for (int W = 1; W <= 15; W++) {
        printf("        %2d       |   %d\n", W, knapsackValue(w, v, W, n));
    }

    return 0;
}