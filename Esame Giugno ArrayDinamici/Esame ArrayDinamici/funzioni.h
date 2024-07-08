#include "strutture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//funzione di inizializzazione della coda
void init_queue (struct Coda *);

//funzione restituisce il numero di elementi contenuti nella coda
int len (struct Coda *);

//funzione di controllo se la coda è vuota
int is_empty (struct Coda *);

//funzione di inserimento dati nella coda
int append (struct Coda *, struct Contribuente);

//funzione di pop dalla coda
struct Contribuente *pop (struct Coda *);

//funzione di deeallocazione
void deallocate (struct Coda *);

//Leggo i file rispettando la politica d'accesso CODA
void read_file_and_enqueue(struct Coda *queue, const char *filename);

//Creo la coda dei sospetti (Questa funzione conserva i dati della coda principale)
void coda_sospetti(struct Coda *queue, struct Coda *sospetti);

//Funzione per stampare la coda (Questa funzione conserva i dati della coda principale)
void print_queue(struct Coda *queue);

//Funzione per scrivere sul file sospetti cazzo
void write_on_file (struct Coda *c, char nomeFile[]);