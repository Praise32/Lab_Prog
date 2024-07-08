#include "funzioni.h"

// Inizializzazione dello stack
void init_stack(struct Stack *s) {
    s->stack = (struct Foto**) malloc(MAX * sizeof(struct Foto*));
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

// Aggiunge un nuovo Foto allo stack
int push(struct Stack *s, struct Foto co) {
    // Controlla se lo stack è pieno
    if (len(s) >= MAX) {
        return 1;
    }

    // Alloca memoria per il nuovo Foto
    s->stack = realloc(s->stack, (s->length + 1) * sizeof(struct Foto*));
    s->stack[s->length] = (struct Foto*) malloc(sizeof(struct Foto));
    *(s->stack[s->length]) = co;
    s->length++;

    return 0;
}

/*******************************************************************************************************/

// Rimuove e restituisce il Foto in cima allo stack
struct Foto* pop(struct Stack *s) {
    // Controlla se lo stack è vuoto
    if (is_empty(s)) {
        return NULL;
    }

    // Ottiene il Foto in cima allo stack
    struct Foto *co = s->stack[s->length - 1];
    s->length--;

    return co;
}

/*******************************************************************************************************/

void deallocate(struct Stack *s) {
    while (!is_empty(s)) {
        struct Foto *co = pop(s);
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

    char img_path[50];
    char didascalia[100];
    int n_like; 
    struct Foto new_Foto;

    while (!feof(file)) {
        
        
        fgets(img_path, sizeof(img_path), file);
        img_path[strcspn(img_path, "\n")] = 0;
        fgets(didascalia, sizeof(didascalia), file);
        didascalia[strcspn(didascalia, "\n")] = 0;
        fscanf(file, "%d\n", &n_like);
        

       //fscanf(file, "%[^\n]\n%[^\n]\n%d\n", img_path, didascalia, &n_like);

        
        strncpy(new_Foto.img_path, img_path, sizeof(new_Foto.img_path));
        strncpy(new_Foto.didascalia, didascalia, sizeof(new_Foto.didascalia));
        new_Foto.n_like = n_like;


        if (is_Valid(new_Foto) == 1)
        {
            push(stack, new_Foto);
        }else {
            printf("Foto non valida: %s\n", new_Foto.img_path);
        }
        
    }

    fclose(file);
}

/*******************************************************************************************************/


// Funzione per stampare lo stack
void print_stack(struct Stack* stack, struct Foto* current) {


        // Stampa i dettagli del Foto
        printf("Path: %s\n", current->img_path);
        printf("Didascalia: %s\n", current->didascalia);
        printf("Like: %d\n", current->n_like);

        printf("\n");
        
        // Inserisci l'elemento nello stack temporaneo
        //push(stack, *current);

}

/*******************************************************************************************************/

int is_Valid(struct Foto sesso){

    int len = strlen(sesso.img_path);


    // Verifica se la lunghezza della stringa è sufficiente
    if (len == 0) {
        printf("Percorso vuoto\n");
        return 0;
    }

    char lastChar;

    for (int i = 0; i < len -1; i++)
    {
       lastChar = sesso.img_path[i];
    }
    
    // Verifica se l'ultimo carattere è una lettera e se il percorso inizia con '/'
    if (sesso.img_path[0] == '/' && 
        ((lastChar >= 'A' && lastChar <= 'Z') || (lastChar >= 'a' && lastChar <= 'z'))) {
        return 1;
    } else {
        printf("Percorso non valido: %s\n", sesso.img_path);
        return 0;
    }
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

    // Itera attraverso lo stack per trovare il Foto
    while (!is_empty(s)) {
        struct Foto *current = pop(s);

       for (int i = 0; i < current->n_like; i++)
            {
                fprintf(file, "*");
            }

            fprintf(file, "\n");
        free(current); // Libera la memoria del puntatore, non dei dati
    }

    fclose(file);
}


