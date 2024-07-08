#include "funzioni.h"

// Inizializzazione della coda
void init_queue(struct Coda *c) {
    c->Coda = (struct Contribuente**) malloc(MAX * sizeof(struct Contribuente*));
    c->first_in = 0;
    c->first_out = 0;
    c->length = 0;
}

/**********************************************************************************************************************************************************************************************************************/

// Restituisce la lunghezza attuale della coda
int len(struct Coda *c) {
    return c->length;
}

/**********************************************************************************************************************************************************************************************************************/

// Controlla se la coda è vuota
int is_empty(struct Coda *c) {
    return len(c) == 0;
}

/**********************************************************************************************************************************************************************************************************************/

// Aggiunge un nuovo contribuente alla coda
int append(struct Coda *c, struct Contribuente co) {
    // Controlla se la coda è piena
    if (len(c) >= MAX) {
        return 1;
    }

    // Alloca memoria per il nuovo contribuente
    c->Coda[c->first_in] = (struct Contribuente*) malloc(sizeof(struct Contribuente));

    // Copia i dati del contribuente nella coda
    *(c->Coda[c->first_in]) = co;
    c->first_in = (c->first_in + 1) % MAX;
    c->length++;

    return 0;
}

/**********************************************************************************************************************************************************************************************************************/

// Rimuove e restituisce il contribuente in testa alla coda
struct Contribuente *pop(struct Coda *c) {
    // Controlla se la coda è vuota
    if (is_empty(c)) {
        return NULL;
    }

    // Ottiene il contribuente in testa alla coda
    struct Contribuente *co = c->Coda[c->first_out];
    c->first_out = (c->first_out + 1) % MAX;
    c->length--;

    return co;
}

/**********************************************************************************************************************************************************************************************************************/

void deallocate (struct Coda *c){
    while (!is_empty(c)) {
        struct Contribuente *co = pop(c);
        free(co->introiti);
        free(co);
    }
    free(c->Coda);
}

/**********************************************************************************************************************************************************************************************************************/

// Funzione per leggere i dati dal file e aggiungerli alla coda
void read_file_and_enqueue(struct Coda *queue, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    char codice_fiscale[17];
    int introito;

    while (fscanf(file, "%16s%d", codice_fiscale, &introito) == 2) {
        // Flag per controllare se il contribuente è stato trovato
        int found = 0;

        // Temporanea coda per contenere gli elementi processati
        struct Coda temp_queue;
        init_queue(&temp_queue);

        // Itera attraverso la coda per trovare il contribuente
        while (!is_empty(queue)) {
            struct Contribuente *current = pop(queue);

            if (strcmp(current->codice_fiscale, codice_fiscale) == 0) {
                // Aggiungi l'introito al contribuente esistente
                current->introiti = (int *) realloc(current->introiti, (current->introiti_size + 1) * sizeof(int));
                current->introiti[current->introiti_size] = introito;
                current->introiti_size++;
                found = 1;
            }

            // Inserisci l'elemento nella coda temporanea
            append(&temp_queue, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Se il contribuente non è stato trovato, creane uno nuovo
        if (!found) {
            struct Contribuente new_contribuente;
            strcpy(new_contribuente.codice_fiscale, codice_fiscale);
            new_contribuente.introiti = (int *) malloc(sizeof(int));
            new_contribuente.introiti[0] = introito;
            new_contribuente.introiti_size = 1;
            append(&temp_queue, new_contribuente);
        }

        // Ricostruisci la coda principale dalla coda temporanea
        while (!is_empty(&temp_queue)) {
            struct Contribuente *current = pop(&temp_queue);
            append(queue, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Dealloca la coda temporanea
        free(temp_queue.Coda);
    }

    fclose(file);
}

/**********************************************************************************************************************************************************************************************************************/

void coda_sospetti(struct Coda *queue, struct Coda *sospetti) {
    // Temporanea coda per contenere gli elementi processati
    struct Coda temp_queue;
    init_queue(&temp_queue);

    // Itera attraverso la coda per trovare il contribuente
    while (!is_empty(queue)) {
        struct Contribuente *current = pop(queue);
        int somma = 0;

        for (int i = 0; i < current->introiti_size; i++) {
            somma += current->introiti[i];
        }

        if (somma > 5000) {
            append(sospetti, *current);
        }

        // Inserisci l'elemento nella coda temporanea (indipendentemente se è stato aggiunto a sospetti o no)
        append(&temp_queue, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Ricostruisci la coda principale dalla coda temporanea
    while (!is_empty(&temp_queue)) {
        struct Contribuente *current = pop(&temp_queue);
        append(queue, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Dealloca la coda temporanea
    free(temp_queue.Coda);
}

/**********************************************************************************************************************************************************************************************************************/

// Funzione per stampare la coda
    void print_queue(struct Coda *queue) {
        // Temporanea coda per contenere gli elementi processati
        struct Coda temp_queue;
        init_queue(&temp_queue);

        while (!is_empty(queue)) {
            struct Contribuente *current = pop(queue);

            // Stampa i dettagli del contribuente
            printf("Codice Fiscale: %s\n", current->codice_fiscale);
            for (int i = 0; i < current->introiti_size; i++) {
                printf("  Introito: %d\n", current->introiti[i]);
            }

            // Inserisci l'elemento nella coda temporanea
            append(&temp_queue, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Ricostruisci la coda principale dalla coda temporanea
        while (!is_empty(&temp_queue)) {
            struct Contribuente *current = pop(&temp_queue);
            append(queue, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Dealloca la coda temporanea
        free(temp_queue.Coda);
    }

/**********************************************************************************************************************************************************************************************************************/

//funzione di scrittura nel nuovo file
void write_on_file (struct Coda *c, char nomeFile[]) {
	//apro il file in modalità scrittura
	FILE *file = fopen(nomeFile, "w");
	//controllo che il file sia stato aperto correttamente
	if (file == NULL) {
		printf("Qualcosa e' andato storto con l'apertura del file\n");
		return;
	}

 // Itera attraverso la coda per trovare il contribuente
    while (!is_empty(c)) {
        struct Contribuente *current = pop(c);
        int somma = 0;

	    fprintf(file, "%s, ", current->codice_fiscale);
        for (int i = 0; i < current->introiti_size; i++) {
            somma += current->introiti[i];
            fprintf(file, "%d, ", current->introiti[i]);
        }
            fprintf(file, "%d\n", somma);

        free(current); // Libera la memoria del puntatore, non dei dati
    }

	fclose(file);
}






























