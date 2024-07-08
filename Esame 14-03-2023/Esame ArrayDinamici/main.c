#include <stdio.h>
#include "funzioni.h"

int main() {
    struct Elenco e;
    init_Elenco(&e);


    read_file_and_push(&e, "brani.txt");


    stampaElenco(&e);

    printf("Scrittura sul file...");

    write_music_on_file(&e, "riassunto.txt");


    return 0;
}
