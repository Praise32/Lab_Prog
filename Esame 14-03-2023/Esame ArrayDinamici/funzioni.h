#include "strutture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_Elenco(struct Elenco *e);
void insert(struct Elenco *s, struct Brano co);
void read_file_and_push(struct Elenco *e, const char *filename);
void stampaElenco(struct Elenco* elenco);
void write_music_on_file(struct Elenco *e, const char *filename);