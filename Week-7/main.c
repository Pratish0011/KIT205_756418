#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;


void swap(String* a, String* b) {
	String temp = *a;
	*a = *b;
	*b = temp;
}



void quicksort(String* a, int first, int last) {
	if (first < last) {
		// use last element as pivot
		int i = first;
		int j = last - 1;

		while (i <= j) {
			// move i right while a[i] <= pivot
			while (i < last && strcmp(a[i], a[last]) <= 0)
				i++;
			// move j left while a[j] > pivot
			while (j >= first && strcmp(a[j], a[last]) > 0)
				j--;
			// if pointers haven't crossed, swap
			if (i < j)
				swap(&a[i], &a[j]);
		}

		// place pivot in correct position
		swap(&a[i], &a[last]);

		// recurse on left and right partitions
		quicksort(a, first, i - 1);  
		quicksort(a, i + 1, last);
	}
}



int main() {
	// buffer for reading input
	char buffer[100];

	// read number of strings
	int n;
	printf("Enter number of strings: ");
	scanf("%d", &n);

	// dynamically allocate array of n strings
	String* strings = malloc(n * sizeof(String));

	// read n strings into array
	for (int i = 0; i < n; i++) {
		scanf("%s", buffer);
		// allocate exact memory and copy
		strings[i] = malloc(strlen(buffer) + 1);
		strcpy(strings[i], buffer);
	}

	// sort using quicksort
	quicksort(strings, 0, n - 1);

	printf("\nSorted strings:\n");
	for (int i = 0; i < n; i++) {
		printf("%s\n", strings[i]);
	}

	// free all memory
	for (int i = 0; i < n; i++) {
		free(strings[i]);
	}
	free(strings);

	return 0;
}