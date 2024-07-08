#define MAX 10

struct Contribuente{
    char codice_fiscale[17];
    int *introiti;
    int introiti_size; // Dimensione dell'array degli introiti
};

// Definizione della struttura Coda che rappresenta una coda di contribuenti
struct Coda {
    struct Contribuente** Coda; // Puntatore a un array di puntatori a Contribuente
    int length; // Lunghezza attuale della coda
    int first_in; // Indice del primo elemento libero per l'inserimento
    int first_out; // Indice del primo elemento da rimuovere
};
