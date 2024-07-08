#include "funzioni.h"

// Inizializzazione dello stack
void init_stack(struct Stack *s) {
    s->stack = (struct Contribuente**) malloc(MAX * sizeof(struct Contribuente*));
    s->length = 0;
}

/*******************************************************************************************************/

// Restituisce la lunghezza attuale dello stack
int len(struct Stack *s) {
    return s->length;
}

/*******************************************************************************************************/

// Controlla se lo stack è vuoto
int is_empty(struct Stack *s) {
    return len(s) == 0;
}

/*******************************************************************************************************/

// Aggiunge un nuovo contribuente allo stack
int push(struct Stack *s, struct Contribuente co) {
    // Controlla se lo stack è pieno
    if (len(s) >= MAX) {
        return 1;
    }

    // Alloca memoria per il nuovo contribuente
    s->stack = realloc(s->stack, (s->length + 1) * sizeof(struct Contribuente*));
    s->stack[s->length] = (struct Contribuente*) malloc(sizeof(struct Contribuente));
    *(s->stack[s->length]) = co;
    s->length++;

    return 0;
}

/*******************************************************************************************************/

// Rimuove e restituisce il contribuente in cima allo stack
struct Contribuente* pop(struct Stack *s) {
    // Controlla se lo stack è vuoto
    if (is_empty(s)) {
        return NULL;
    }

    // Ottiene il contribuente in cima allo stack
    struct Contribuente *co = s->stack[s->length - 1];
    s->length--;

    return co;
}

/*******************************************************************************************************/

void deallocate(struct Stack *s) {
    while (!is_empty(s)) {
        struct Contribuente *co = pop(s);
        free(co->introiti);
        free(co);
    }
    free(s->stack);
}

/*******************************************************************************************************/

// Funzione per leggere i dati dal file e aggiungerli allo stack
void read_file_and_push(struct Stack *stack, const char *filename) {
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

        // Temporaneo stack per contenere gli elementi processati
        struct Stack temp_stack;
        init_stack(&temp_stack);

        // Itera attraverso lo stack per trovare il contribuente
        while (!is_empty(stack)) {
            struct Contribuente *current = pop(stack);

            if (strcmp(current->codice_fiscale, codice_fiscale) == 0) {
                // Aggiungi l'introito al contribuente esistente
                current->introiti = (int *) realloc(current->introiti, (current->introiti_size + 1) * sizeof(int));
                current->introiti[current->introiti_size] = introito;
                current->introiti_size++;
                found = 1;
            }

            // Inserisci l'elemento nello stack temporaneo
            push(&temp_stack, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Se il contribuente non è stato trovato, creane uno nuovo
        if (!found) {
            struct Contribuente new_contribuente;
            strcpy(new_contribuente.codice_fiscale, codice_fiscale);
            new_contribuente.introiti = (int *) malloc(sizeof(int));
            new_contribuente.introiti[0] = introito;
            new_contribuente.introiti_size = 1;
            push(&temp_stack, new_contribuente);
        }

        // Ricostruisci lo stack principale dallo stack temporaneo
        while (!is_empty(&temp_stack)) {
            struct Contribuente *current = pop(&temp_stack);
            push(stack, *current);
            free(current); // Libera la memoria del puntatore, non dei dati
        }

        // Dealloca lo stack temporaneo
        free(temp_stack.stack);
    }

    fclose(file);
}

/*******************************************************************************************************/

void stack_sospetti(struct Stack *stack, struct Stack *sospetti) {
    // Temporaneo stack per contenere gli elementi processati
    struct Stack temp_stack;
    init_stack(&temp_stack);

    // Itera attraverso lo stack per trovare il contribuente
    while (!is_empty(stack)) {
        struct Contribuente *current = pop(stack);
        int somma = 0;

        for (int i = 0; i < current->introiti_size; i++) {
            somma += current->introiti[i];
        }

        if (somma > 5000) {
            push(sospetti, *current);
        }

        // Inserisci l'elemento nello stack temporaneo (indipendentemente se è stato aggiunto a sospetti o no)
        push(&temp_stack, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Ricostruisci lo stack principale dallo stack temporaneo
    while (!is_empty(&temp_stack)) {
        struct Contribuente *current = pop(&temp_stack);
        push(stack, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Dealloca lo stack temporaneo
    free(temp_stack.stack);
}

/*******************************************************************************************************/

// Funzione per stampare lo stack
void print_stack(struct Stack *stack) {
    // Temporaneo stack per contenere gli elementi processati
    struct Stack temp_stack;
    init_stack(&temp_stack);

    while (!is_empty(stack)) {
        struct Contribuente *current = pop(stack);

        // Stampa i dettagli del contribuente
        printf("Codice Fiscale: %s\n", current->codice_fiscale);
        for (int i = 0; i < current->introiti_size; i++) {
            printf("  Introito: %d\n", current->introiti[i]);
        }

        // Inserisci l'elemento nello stack temporaneo
        push(&temp_stack, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Ricostruisci lo stack principale dallo stack temporaneo
    while (!is_empty(&temp_stack)) {
        struct Contribuente *current = pop(&temp_stack);
        push(stack, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Dealloca lo stack temporaneo
    free(temp_stack.stack);
}

/*******************************************************************************************************/

// Funzione di scrittura nel nuovo file
void write_on_file(struct Stack *s, char nomeFile[]) {
    // Apro il file in modalità scrittura
    FILE *file = fopen(nomeFile, "w");
    // Controllo che il file sia stato aperto correttamente
    if (file == NULL) {
        printf("Qualcosa è andato storto con l'apertura del file\n");
        return;
    }

    // Itera attraverso lo stack per trovare il contribuente
    while (!is_empty(s)) {
        struct Contribuente *current = pop(s);
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
