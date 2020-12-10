#include<iostream>

using namespace std;

struct Nodo
{
    int valore;
    Nodo* prec;
    Nodo* succ;
};

class ListaDoppia
{
private:
    Nodo* testa;

public:
    ListaDoppia() { testa = NULL;}
    ~ListaDoppia();
    void stampa();
    void inserisci_in_testa(int val);
    void inserisci(Nodo* precedente, Nodo* successivo, int val);
    void inserisci_in_coda(Nodo* p, int val);
    void rimuovi(int val);
    Nodo* ricerca(int val);
    Nodo* GetTesta() {return testa;}
};

ListaDoppia::~ListaDoppia() 
{
    Nodo* aux = testa;

    while (aux != NULL)
    {
        Nodo* tmp = aux->succ;
        delete aux;
        aux = tmp;
    }
}

void ListaDoppia::stampa()
{
    Nodo* iter = this->testa;

    while (iter != NULL)
    {
        cout << " " << iter->valore << "\tSuccessivo: ";
        if (iter->succ != NULL)
        {
            cout << iter->succ->valore;
        }
        else
        {
            cout << "NULL";
        }
        cout << "\tPrecedente: ";
        if (iter->prec != NULL)
        {
            cout << iter->prec->valore;
        }
        else
        {
            cout << "NULL\n";
        }
        iter = iter->succ;
    }
}

void ListaDoppia::inserisci_in_testa(int val)
{
    Nodo* nuovo = new Nodo;

    nuovo->valore = val;
    if (this->testa != NULL)
    {
        nuovo->succ = testa;
        nuovo->prec = NULL;
        testa->prec = nuovo;
        testa = nuovo;
    }
    else
    {
        testa = nuovo;
        nuovo->succ = NULL;
        nuovo->prec = NULL;
    } 
}

void ListaDoppia::inserisci(Nodo* precedente, Nodo* successivo, int val)
{
    Nodo* nuovo = new Nodo;

    nuovo->valore = val;
    nuovo->succ = successivo;
    nuovo->prec = precedente;
    precedente->succ = nuovo;
    successivo->prec = nuovo;
}

void ListaDoppia::inserisci_in_coda(Nodo* coda, int val)
{
    Nodo* nuovo = new Nodo;

    nuovo->valore = val;
    nuovo->succ = NULL;
    nuovo->prec = coda;
    coda->succ = nuovo;
}

void ListaDoppia::rimuovi(int val)
{
    Nodo* preced;
	Nodo* current; 

    if (this->testa == NULL)
    {
        cout << "Lista vuota!" << endl;
    }
    else if (this->testa == val)
    {
        current = testa->succ;
        testa = testa->succ;
        testa->prec = NULL;
        delete current;
    }
    else
    {
        while ((current->succ != NULL) && (current->valore != val));
        {
            current = current->succ;
        }
        if (current->valore == val)
        {
            preced = current->prec;
            preced->succ = current->succ;
            if (current->succ != NULL)
            {
                current->succ->prec = preced;
            }
            delete current;
        } 
    }
}



