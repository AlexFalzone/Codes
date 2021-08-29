#include<iostream>

using namespace std;

struct Nodo
{
    int valore;
    Nodo* succ;
    Nodo* prec;
};

class ListaDoppiaCircolare
{
private:
    Nodo* testa;

public:
    ListaDoppiaCircolare() {testa = NULL;}
    ~ListaDoppiaCircolare();
    void stampa();
    void inserisci(int);
    void rimuovi(int);
    Nodo* ricerca(int);
    Nodo* getTesta();
};

