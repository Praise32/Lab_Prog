#define MAX 10

struct Veicolo
 {
    char targa[10];
    float velocità;
    float limite; 
};

// Definizione della struttura Stack che rappresenta uno Stack di veicoli
struct Stack {
    struct Veicolo** stack; // Puntatore a un array di puntatori a Veicolo
    int length; // Lunghezza attuale dello stack
};
