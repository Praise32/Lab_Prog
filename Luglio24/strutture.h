#define MAX 10

struct vettura{
    char targa[10];
    float x;
    float y;
    int orario;
};

// Definizione della struttura Coda che rappresenta una coda di contribuenti
struct autovelox {
    struct vettura** autovelox; // Puntatore a un array di puntatori a Contribuente
    int length; // Lunghezza attuale della coda
    int first_in; // Indice del primo elemento libero per l'inserimento
    int first_out; // Indice del primo elemento da rimuovere
};