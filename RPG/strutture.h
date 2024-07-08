struct Personaggio
{
    char nome [32];
    int hp;
    int dp;
    int ap;
};

struct Elenco
{
    struct Personaggio** elenco;
    int dimensione;
};

