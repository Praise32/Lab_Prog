#include "funzioni.h"

void init_Elenco(struct Elenco *l) {
    l->elenco = (struct Personaggio**) malloc(MAX * sizeof(struct Personaggio*));
    l->dimensione = 0;
}

void insert(struct Elenco* l, struct Personaggio p){
    l->elenco =  realloc(l->elenco, (l->dimensione + 1) * sizeof(struct Personaggio*));
    l->elenco[l->dimensione] = (struct Personaggio*) malloc(sizeof(struct Personaggio));
    *(l->elenco[l->dimensione]) = p;
    l->dimensione ++;
}

void load(struct Elenco* l, char filename[]){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    struct Personaggio*  p = malloc (sizeof(struct Personaggio));


    while (fscanf(file, "%s%d%d%d", p->nome, &p->hp, &p->dp, &p->ap) == 4)
    {
        insert(l, *p);
    }


    fclose(file);
}

void vera_print(struct Personaggio** p  , int dimensione){
    if (dimensione == 0)
    {
        return;
    }
    
    printf("Nome: %s \n", p[0]->nome);
    printf("hp: %d \n", p[0]->hp);
    printf("dp: %d \n", p[0]->dp);
    printf("ap: %d \n", p[0]->ap);

    vera_print(p+1, dimensione-1);

}

void print(struct Elenco l){
    vera_print(l.elenco, l.dimensione);

}


void colpisci(struct Personaggio* p1, struct Personaggio* p2){
    printf("%s COLPISCE %s !!!!!!!!!!\n", p1->nome, p2->nome);

    p2->hp = p2->hp -(( p1->ap / p2->dp) * p2->hp);
    
    if (p2->hp < 0){
        p2->hp = 0;
    }

    printf("Gli hp di %s scendono a %d\n", p2->nome, p2->hp);
}

void sfida(struct Personaggio* p1, struct Personaggio* p2){
    while (p1->hp > 0 && p2->hp > 0)
    {
       colpisci(p2, p1);
       colpisci(p1, p2);
    }

    if (p1->hp == 0)
    {
        printf("\nIL VINCITORE E' %s\n\n", p2->nome);
    }else if (p2->hp == 0)
    {
        printf("\nIL VINCITORE E' %s\n\n", p1->nome);
    }
    
    
    
}
