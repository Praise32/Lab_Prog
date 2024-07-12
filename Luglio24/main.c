#include <stdio.h>
#include "funzioni.h"

int main() {

    struct autovelox queue;
    init_queue(&queue);

    struct autovelox queue2;
    init_queue(&queue2);

    read_file_and_enqueue(&queue, "autovelox1.txt");
    read_file_and_enqueue(&queue2, "autovelox2.txt");


    // Stampa la coda dei sospetti
    printf("\n\nAutovelox1:\n");
    print_queue(&queue);

    // Stampa la coda originale (ora senza i sospetti)
    printf("\n\nAutovelox2:\n");
    print_queue(&queue2);

    write_on_file(&queue,&queue2, "Multe.txt");

    deallocate(&queue);
    deallocate(&queue2);


    return 0;

}