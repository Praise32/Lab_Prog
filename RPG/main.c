#include <stdio.h>
#include "funzioni.h"


int main(int argc, char const *argv[])
{
    
    struct Elenco elenco;

    init_Elenco(&elenco);

    load(&elenco, "personaggi.txt");

    print(elenco);

    printf("\n\nSCEGLI CHI VUOI FAR SFIDARE DIO CANE:\n");

    char nome1[32];
    char nome2[32];
    int a, b;

    printf("Inserisci il primo nome:\n");
    scanf("%s", nome1);
    printf("Inserisci il secondo nome:\n");
    scanf("%s", nome2);

    for (int i = 0; i < elenco.dimensione; i++)
    {
        if (strcmp(elenco.elenco[i]->nome, nome1) == 0)
        {
            a = i;
        }
        
        if (strcmp(elenco.elenco[i]->nome, nome2) == 0)
        {
            b = i;
        }
    }

    sfida(elenco.elenco[a], elenco.elenco[b]);
    print(elenco);




    return 0;
}
