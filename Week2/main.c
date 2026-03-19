#include <stdio.h>
#include "list.h"

int main() {

    // Unit test
    list_test();

    // Adhoc test
    // list_adhoc_test();

    // Merge test
    List l1 = new_list();
    insert_in_order(&l1, 1);
    insert_in_order(&l1, 3);
    insert_in_order(&l1, 5);

    List l2 = new_list();
    insert_in_order(&l2, 2);
    insert_in_order(&l2, 4);
    insert_in_order(&l2, 6);

    List merged = merge(&l1, &l2);

    printf("Merged List: ");
    print_list(&merged);

    // Reverse test
    List rev = reverse(&merged);
    printf("Reversed List: ");
    print_list(&rev);

    return 0;
}