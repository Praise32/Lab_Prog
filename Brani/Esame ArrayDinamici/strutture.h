#define MAX 10

struct Brano {
    char titolo[30];
    char autore[30];//Lettera Maiuscola
    int durata_in_sec;
    int rips;
};

struct Elenco {
    struct Brano** Elenco; // Puntatore a un array di puntatori a Brano
    int length; // Lunghezza dell'array di puntatori
};
