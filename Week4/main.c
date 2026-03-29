#define _CRT_SECURE_NO_WARNINGS  // Given by ChatGPT to avoid warnings for scanf
#include <stdio.h>
#include <time.h>


// Functions given in MyLo

long f1(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            k++;
        }
    }
    return k;
}

void f2(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < i; j++) {
            k++;
        }
        for (long t = 0; t < 10000; t++) {
            k++;
        }
    }
}

void f3(long n) {
    if (n > 0) {
        f3(n / 2);
        f3(n / 2);
    }
}

void f4(long n) {
    if (n > 0) {
        f4(n / 2);
        f4(n / 2);
        f2(n);
    }
}

void f5(long n) {
    long k = 0;
    for (long i = 0; i < 10; i++) {
        long j = n;
        while (j > 0) {
            f1(1000);
            k++;
            j = j / 2;
        }
    }
}

void f6(long n) {
    f2(n);
    f3(n);
    f5(n);
}

void f7(long n) {
    long k = 0;
    for (long i = 0; i < f1(n); i++) {
        k++;
    }
    for (long j = 0; j < n; j++) {
        k++;
    }
}

// Main Function

int main() {
    long n;
    int choice;

    printf("Enter value of n: ");
    scanf("%d", &n);

    printf("\nChoose function:\n");
    printf("1 f1\n2 f2\n3 f3\n4 f4\n5 f5\n6 f6\n7 f7\n");
    scanf("%d", &choice);

    clock_t start = clock();

    // Call function
    switch (choice) {
    case 1: f1(n); break;
    case 2: f2(n); break;
    case 3: f3(n); break;
    case 4: f4(n); break;
    case 5: f5(n); break;
    case 6: f6(n); break;
    case 7: f7(n); break;
    default: printf("Invalid choice"); return 0;
    }

    clock_t diff = clock() - start;
    long msec = diff * 1000 / CLOCKS_PER_SEC;

    printf("Time taken: %ld ms\n", msec);

    return 0;
}
