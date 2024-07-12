#include "funzioni.h"

// Inizializzazione della autovelox
void init_queue(struct autovelox *c) {
    c->autovelox = (struct vettura**) malloc(MAX * sizeof(struct vettura*));
    c->first_in = 0;
    c->first_out = 0;
    c->length = 0;
}

/**********************************************************************************************************************************************************************************************************************/

// Restituisce la lunghezza attuale della autovelox
int len(struct autovelox *c) {
    return c->length;
}

/**********************************************************************************************************************************************************************************************************************/

// Controlla se la autovelox è vuota
int is_empty(struct autovelox *c) {
    return len(c) == 0;
}

/**********************************************************************************************************************************************************************************************************************/

// Aggiunge un nuovo vettura alla autovelox
int append(struct autovelox *c, struct vettura co) {
    // Controlla se la autovelox è piena
    if (len(c) >= MAX) {
        return 1;
    }

    // Alloca memoria per il nuovo vettura
    c->autovelox[c->first_in] = (struct vettura*) malloc(sizeof(struct vettura));

    // Copia i dati del vettura nella autovelox
    *(c->autovelox[c->first_in]) = co;
    c->first_in = (c->first_in + 1) % MAX;
    c->length++;

    return 0;
}

/**********************************************************************************************************************************************************************************************************************/

// Rimuove e restituisce il vettura in testa alla autovelox
struct vettura *pop(struct autovelox *c) {
    // Controlla se la autovelox è vuota
    if (is_empty(c)) {
        return NULL;
    }

    // Ottiene il vettura in testa alla autovelox
    struct vettura *co = c->autovelox[c->first_out];
    c->first_out = (c->first_out + 1) % MAX;
    c->length--;

    return co;
}

/**********************************************************************************************************************************************************************************************************************/

void deallocate (struct autovelox *c){
    while (!is_empty(c)) {
        struct vettura *co = pop(c);
        free(co);
    }
    free(c->autovelox);
}

/**********************************************************************************************************************************************************************************************************************/

// Funzione per leggere i dati dal file e aggiungerli alla autovelox
void read_file_and_enqueue(struct autovelox *queue, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    struct vettura new_vettura;
    char targa[10];
    int orario;
    float x;
    float y;

    while (fscanf(file, "%s%d%f%f", targa, &orario, &x, &y) == 4) {

            strcpy(new_vettura.targa, targa);
            new_vettura.orario = orario;
            new_vettura.x = x;
            new_vettura.y = y;

            append(queue, new_vettura);

    }

    fclose(file);
}

/**********************************************************************************************************************************************************************************************************************/

// Funzione per stampare la autovelox
    void print_queue(struct autovelox *queue) {
        // Temporanea autovelox per contenere gli elementi processati
        struct autovelox temp_queue;
        init_queue(&temp_queue);

        while (!is_empty(queue)) {
            struct vettura *current = pop(queue);

            // Stampa i dettagli del vettura
            printf("Targa: %s\n", current->targa);
            printf("Orario: %d\n", current->orario);
            printf("X: %f\n", current->x);
            printf("Y: %f\n", current->y);
            

            // Inserisci l'elemento nella autovelox temporanea
            append(&temp_queue, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Ricostruisci la autovelox principale dalla autovelox temporanea
        while (!is_empty(&temp_queue)) {
            struct vettura *current = pop(&temp_queue);
            append(queue, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Dealloca la autovelox temporanea
        free(temp_queue.autovelox);
    }

/**********************************************************************************************************************************************************************************************************************/

//funzione di scrittura nel nuovo file
void write_on_file (struct autovelox *c, struct autovelox *c2, char nomeFile[]) {
	//apro il file in modalità scrittura
	FILE *file = fopen(nomeFile, "w");
	//controllo che il file sia stato aperto correttamente
	if (file == NULL) {
		printf("Qualcosa e' andato storto con l'apertura del file\n");
		return;
	}

 // Itera attraverso la autovelox per trovare il vettura
    while (!is_empty(c)) {
        struct vettura *v1 = pop(c);
        struct vettura *v2 = search(c2, v1->targa);

   if (v2 != NULL) {
            float distanza = sqrt(((v1->x - v2->x) * (v1->x - v2->x)) + ((v1->y - v2->y) * (v1->y - v2->y)));
            float velocita = 3.6 * (distanza / (v2->orario - v1->orario));

            if (velocita > 50) {
                fprintf(file, "%s, %.2f\n", v1->targa, velocita);
            }

            free(v2);
        }

        free(v1);
    }

	fclose(file);
}

/**********************************************************************************************************************************************************************************************************************/

/*
//Search Con Coda Temporanea
struct vettura *search(struct autovelox *v2, char targa[]) {
    struct autovelox temp;
    init_queue(&temp);

    struct vettura *result = NULL;
    while (!is_empty(v2)) {
        struct vettura* ve = pop(v2);
        if (strcmp(ve->targa, targa) == 0) {
            result = malloc(sizeof(struct vettura));
            *result = *ve;
        }
        append(&temp, *ve);
        free(ve);
    }

    // Restore the original queue
    while (!is_empty(&temp)) {
        append(v2, *pop(&temp));
    }

    return result;
}
*/

//Search senza l'utilizzo di una coda temporanea
struct vettura *search(struct autovelox *v2, char targa[]) {


    struct vettura *result = NULL;

    for (int i = 0; i < v2->length; i++)
    {
        struct vettura* ve = pop(v2);
        if (strcmp(ve->targa, targa) == 0) {
            result = malloc(sizeof(struct vettura));
            *result = *ve;
        }
        append(v2, *ve);
        free(ve);
    }


    return result;
}














