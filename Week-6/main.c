#include <stdio.h>
#include "list_wk5.h"
#include "hashtable_wk5.h"

int main() {
    // Run list tests first
    list_test();

    printf("\n*** Hash Table Ad Hoc Test ***\n");
    printf("Commands: 1 <word> = insert, 2 <word> = remove, 3 = print, 0 = quit\n");
    hash_adhoc_test();

    return 0;
}