#include "funzioni.h"

// Inizializzazione dello stack
void init_stack(struct Stack *s) {
    s->stack = (struct Veicolo**) malloc(MAX * sizeof(struct Veicolo*));
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

// Aggiunge un nuovo Veicolo allo stack
int push(struct Stack *s, struct Veicolo co) {
    // Controlla se lo stack è pieno
    if (len(s) >= MAX) {
        return 1;
    }

    // Alloca memoria per il nuovo Veicolo
    s->stack = realloc(s->stack, (s->length + 1) * sizeof(struct Veicolo*));
    s->stack[s->length] = (struct Veicolo*) malloc(sizeof(struct Veicolo));
    *(s->stack[s->length]) = co;
    s->length++;

    return 0;
}

/*******************************************************************************************************/

// Rimuove e restituisce il Veicolo in cima allo stack
struct Veicolo* pop(struct Stack *s) {
    // Controlla se lo stack è vuoto
    if (is_empty(s)) {
        return NULL;
    }

    // Ottiene il Veicolo in cima allo stack
    struct Veicolo *co = s->stack[s->length - 1];
    s->length--;

    return co;
}

/*******************************************************************************************************/

void deallocate(struct Stack *s) {
    while (!is_empty(s)) {
        struct Veicolo *co = pop(s);
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

    char targa[10];
    float velocità;
    float limite;
    struct Veicolo new_Veicolo;

    while (fscanf(file, "%s%f%f", targa, &velocità, &limite) == 3) {
        
        strncpy(new_Veicolo.targa, targa, sizeof(new_Veicolo.targa));
        new_Veicolo.velocità = velocità;
        new_Veicolo.limite = limite;

        push(stack, new_Veicolo);
    }

    fclose(file);
}

/*******************************************************************************************************/


// Funzione per stampare lo stack
void print_stack(struct Stack *stack) {
    // Temporaneo stack per contenere gli elementi processati
    struct Stack temp_stack;
    init_stack(&temp_stack);

    while (!is_empty(stack)) {
        struct Veicolo *current = pop(stack);

        // Stampa i dettagli del Veicolo
        printf("  Targa: %s\n", current->targa);
        printf("  Velocità: %.1f\n", current->velocità);
        printf("  Limite: %.1f\n", current->limite);

        printf("\n");
        
        // Inserisci l'elemento nello stack temporaneo
        push(&temp_stack, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Ricostruisci lo stack principale dallo stack temporaneo
    while (!is_empty(&temp_stack)) {
        struct Veicolo *current = pop(&temp_stack);
        push(stack, *current);
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    // Dealloca lo stack temporaneo
    free(temp_stack.stack);
}

int is_Crime(struct Veicolo sesso){

    float tolleranza = sesso.limite + (5/100)*sesso.limite;
    if(sesso.velocità > tolleranza){
        return 1;
    }else return 0;

}




// Funzione di scrittura nel nuovo file
void write_on_file(struct Stack *s, char nomeFile[]) {
    // Apro il file in modalità scrittura
    FILE *file = fopen(nomeFile, "w");
    // Controllo che il file sia stato aperto correttamente
    if (file == NULL) {
        printf("Qualcosa è andato storto con l'apertura del file\n");
        return;
    }

    // Itera attraverso lo stack per trovare il Veicolo
    while (!is_empty(s)) {
        struct Veicolo *current = pop(s);
        
        if(is_Crime(*current)){
            float sanzione = 0;
            float superato = current->velocità - current->limite;
            
            if (superato <= 10)
            {
                sanzione = 173.0;
            }else if (superato > 10 && superato <= 40)
            {
                sanzione = 695.0;
            }else if (superato > 40 && superato <= 60)
            {
                sanzione = 2170.0;
            }else sanzione = 3382.0;
            
            
            fprintf(file, "%s, ", current->targa);
            fprintf(file, "%.1f, ", superato);
            fprintf(file, "%.1f, ", sanzione);
            fprintf(file, "\n");
        }
        


        free(current); // Libera la memoria del puntatore, non dei dati
    }

    fclose(file);
}


