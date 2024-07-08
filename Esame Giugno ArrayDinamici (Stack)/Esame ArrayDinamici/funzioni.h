#include "strutture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzioni per gestire lo stack
void init_stack(struct Stack *s);
int len(struct Stack *s);
int is_empty(struct Stack *s);
int push(struct Stack *s, struct Contribuente co);
struct Contribuente* pop(struct Stack *s);
void deallocate(struct Stack *s);

// Funzioni specifiche per la logica del programma
void read_file_and_push(struct Stack *stack, const char *filename);
void stack_sospetti(struct Stack *stack, struct Stack *sospetti);
void print_stack(struct Stack *stack);
void write_on_file(struct Stack *s, char nomeFile[]);