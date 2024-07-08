#include "funzioni.h"

// Inizializzazione dello stack
void init_Elenco(struct Elenco *e) {
    e->Elenco = (struct Brano**) malloc(MAX * sizeof(struct Brano*));
    e->length = 0;
}

// Aggiunge un nuovo brano allo stack
void insert(struct Elenco *e, struct Brano brano) {
    e->Elenco = realloc(e->Elenco, (e->length + 1) * sizeof(struct Brano*));
    e->Elenco[e->length] = (struct Brano*) malloc(sizeof(struct Brano));
    *(e->Elenco[e->length]) = brano;
    e->length++;
}

// Funzione per leggere i dati dal file e aggiungerli allo stack
void read_file_and_push(struct Elenco *e, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    char durata[5];
    init_Elenco(e);
    struct Brano current;
    int flag = 0;
    char c; //variabile di appoggio per la lettura

    while (!feof(file)) {
        if (fscanf(file, "%[^\n]\n%[^\n]\n%s\n", current.titolo, current.autore, durata) != 3) {
            break; // Se non riesce a leggere tre elementi, esci dal ciclo
        }

  
        current.durata_in_sec = (durata[0] - '0') * 60 + (durata[2] - '0') * 10 + (durata[3] - '0');
        current.rips = 1;

        for (int i = 0; i < e->length; i++) {
            if (strcmp(e->Elenco[i]->titolo, current.titolo) == 0 && strcmp(e->Elenco[i]->autore, current.autore) == 0) {
                e->Elenco[i]->rips++;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            insert(e, current);
        }
        flag = 0;
    }

    fclose(file);
}

// Funzione per stampare l'elenco di brani
void stampaElenco(struct Elenco* elenco) {
    if (elenco == NULL) {
        printf("Elenco non valido\n");
        return;
    }

    printf("Elenco di brani:\n");
    for (int i = 0; i < elenco->length; ++i) {
        struct Brano* brano = elenco->Elenco[i];
        printf("Brano %d:\n", i + 1);
        printf("Titolo: %s\n", brano->titolo);
        printf("Autore: %s\n", brano->autore);
        printf("Durata in secondi: %d\n", brano->durata_in_sec);
        printf("Riproduzioni: %d\n", brano->rips);
        printf("\n");
    }
}