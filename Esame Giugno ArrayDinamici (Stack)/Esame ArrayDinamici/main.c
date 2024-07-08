#include <stdio.h>
#include "funzioni.h"

int main() {
    struct Stack stack;
    init_stack(&stack);

    struct Stack sospetti;
    init_stack(&sospetti);

    read_file_and_push(&stack, "impiegati.txt");

    stack_sospetti(&stack, &sospetti);

    // Stampa lo stack dei sospetti
    printf("\n\nSospetti:\n");
    print_stack(&sospetti);

    // Stampa lo stack originale (ora senza i sospetti)
    printf("\n\nStack originale:\n");
    print_stack(&stack);

    write_on_file(&sospetti, "Sospetti.txt");

    deallocate(&stack);
    deallocate(&sospetti);

    return 0;
}
