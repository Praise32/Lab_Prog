#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "strutture.h"

#define MAX 20

//inizializzo Elenco 
void init_Elenco(struct Elenco *);

//Inserimento di un personaggio nell'elenco
void insert(struct Elenco*, struct Personaggio);

//Stampa dell'elenco ricorsiva
void print(struct Elenco);

//Carichiamo l'elenco con i dati contenuti nel file
void load(struct Elenco*, char[]);

void vera_print(struct Personaggio** p, int dimensione);

//funzione che fa colpire due personaggi
void colpisci(struct Personaggio*, struct Personaggio*);

//Fa colpire i personaggio in maniera alternata finchè uno dei due non finisce gli hp
void sfida(struct Personaggio*, struct Personaggio*);


/*
//Elimina dall'elenco il personaggio con il nome inserito, se va a buon fine restituisce 1, altrimenti 0
int remove(struct Elenco*, char[32]);





//Funzione falcoltativa A, scrive un file aggiornato dopo che si sono svolte le sfide
void write(struct Elenco*, char[]);

//Funzione facoltativa B, Fa scontrare personaggi random po vrimm

*/