#include "strutture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//funzione di inizializzazione della autovelox
void init_queue (struct autovelox *);

//funzione restituisce il numero di elementi contenuti nella autovelox
int len (struct autovelox *);

//funzione di controllo se la autovelox è vuota
int is_empty (struct autovelox *);

//funzione di inserimento dati nella autovelox
int append (struct autovelox *, struct vettura);

//funzione di pop dalla autovelox
struct vettura *pop (struct autovelox *);

//funzione di deeallocazione
void deallocate (struct autovelox *);

//Leggo i file rispettando la politica d'accesso autovelox
void read_file_and_enqueue(struct autovelox *queue, const char *filename);



//Funzione per stampare la autovelox (Questa funzione conserva i dati della autovelox principale)
void print_queue(struct autovelox *queue);

//Funzione per scrivere sul file sospetti cazzo
void write_on_file (struct autovelox *,struct autovelox *, char nomeFile[]);


struct vettura *search (struct autovelox *, char []);