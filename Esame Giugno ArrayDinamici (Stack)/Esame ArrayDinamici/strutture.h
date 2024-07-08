#define MAX 10

struct Contribuente {
    char codice_fiscale[17];
    int *introiti;
    int introiti_size; // Dimensione dell'array degli introiti
};

// Definizione della struttura Stack che rappresenta uno Stack di contribuenti
struct Stack {
    struct Contribuente** stack; // Puntatore a un array di puntatori a Contribuente
    int length; // Lunghezza attuale dello stack
};
