#include <stdio.h>
#include "funzioni.h"

int main() {

    struct Coda queue;
    init_queue(&queue);

    struct Coda sospetti;
    init_queue(&sospetti);

    read_file_and_enqueue(&queue, "impiegati.txt");

    coda_sospetti(&queue, &sospetti);

    // Stampa la coda dei sospetti
    printf("\n\nSospetti:\n");
    print_queue(&sospetti);

    // Stampa la coda originale (ora senza i sospetti)
    printf("\n\nCoda originale:\n");
    print_queue(&queue);

    write_on_file(&sospetti, "Sospetti");

    deallocate(&queue);
    deallocate(&sospetti);


    return 0;

}