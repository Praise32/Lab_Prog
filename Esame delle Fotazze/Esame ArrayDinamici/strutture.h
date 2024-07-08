#define MAX 10

struct Foto
 {
    char img_path[50];
    char didascalia[100];
    int n_like; 
};

// Definizione della struttura Stack che rappresenta uno Stack di veicoli
struct Stack {
    struct Foto** stack; // Puntatore a un array di puntatori a Veicolo
    int length; // Lunghezza attuale dello stack
};
