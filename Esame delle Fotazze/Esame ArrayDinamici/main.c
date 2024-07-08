#include <stdio.h>
#include "funzioni.h"

int main() {
    struct Stack stack;
    init_stack(&stack);
    struct Stack stack2;
    init_stack(&stack2);

    read_file_and_push(&stack, "Utente42.txt");

    struct Foto* foto;
    foto = pop(&stack);
    print_stack(&stack, foto);
    


    int scelta = 666;

    while (scelta != 0)
    {
        printf("\nScegli cosa vuoi fare\n");
        printf("0. fermati:\n");
        printf("1. Vai alla prossima foto:\n");
        printf("2.Aggiungi un bel like alla tua fotazza:\n\n");
        scanf("%d", &scelta);


        switch (scelta)
        {
            case 0:
                push(&stack2, *foto);
                printf("\n\n Stai Uscendo dal programma... \n\n");
            break;
        case 1:
            push(&stack2, *foto);
            printf("\n\n Caricamento foto... \n\n");
            foto = pop(&stack);
            print_stack(&stack2, foto);
            break;
        case 2:
            foto->n_like++;
            printf("\n\n Caricamento foto... \n\n");
            print_stack(&stack2, foto);
            break;   
        default:
            printf("\n\n HAI SBAGLIATO... \n\n");
            break;
        }

    }
    

    printf("\n\n Creazione delle statistiche... \n\n");
    write_on_file(&stack2, "statistica.txt");

    deallocate(&stack);
    deallocate(&stack2);

    return 0;
}
