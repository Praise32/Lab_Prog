#include <stdio.h>
#include "funzioni.h"

int main() {
    struct Stack stack;
    init_stack(&stack);

    read_file_and_push(&stack, "autovelox.txt");

    printf("Stack originale:\n");
    print_stack(&stack);

    write_on_file(&stack, "criminali.txt");

    deallocate(&stack);

    return 0;
}
