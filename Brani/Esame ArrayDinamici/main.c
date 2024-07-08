#include <stdio.h>
#include "funzioni.h"

int main() {
    struct Elenco e;
    init_Elenco(&e);


    read_file_and_push(&e, "brani.txt");


    stampaElenco(&e);



    return 0;
}
