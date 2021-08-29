#include<iostream>

using namespace std;

struct Nodo
{
    int valore;
    Nodo* prec;
    Nodo* succ;
};

class ListaDoppiaCircolare
{
private:
    Nodo* testa;

public:
    ListaDoppiaCircolare() { testa = NULL;}
    ~ListaDoppiaCircolare();
    void stampa();
    void inserisci(int val);
    //void inserisci_in_coda(Nodo* p, int val);
    //void rimuovi(int val);
    //Nodo* ricerca(int val);
    Nodo* GetTesta() {return testa;}
};

ListaDoppiaCircolare::~ListaDoppiaCircolare()
{
    Nodo* iter;

    if (testa != NULL)
    {
        iter = testa->succ;
    }
    else
    {
        return;
    }
    
    while (iter != testa)
    {
        Nodo* tmp = iter->succ;
        delete iter;
        iter = tmp;
    }
    delete testa;
}

void ListaDoppiaCircolare::stampa()
{
    Nodo* iter = testa;

    if (testa == NULL)
    {
        cout << "Lista vuota!\n";
    }
    else if (testa->succ == testa)
    {
        cout << "Lista contenente un solo elemento: " << testa->valore << endl;
    }
    else
    {
        do
        {
            cout << " " << iter->valore << "\tSuccessivo: ";
            cout << iter->succ->valore;
            cout << "\tPrecedente: ";
            cout << iter->prec->valore;
            iter = iter->succ;

        } while (iter != testa);
    }
}

void ListaDoppiaCircolare::inserisci(int val)
{
    Nodo* nuovo = new Nodo;

    nuovo->valore = val;

    if (testa != NULL)
    {
        nuovo->succ = testa->succ;
        testa->succ = nuovo;
        nuovo->prec = testa;
        nuovo->succ->prec = nuovo;
    }
    else
    {
        nuovo->succ = nuovo;
        nuovo->prec = nuovo;
        testa = nuovo;
    }
}

int main(int argc, char const *argv[])
{
    ListaDoppiaCircolare lista;

    for(int i = 10; i > 0; i--)
    {
        lista.inserisci(i*10);
    }
    lista.stampa();

    return 0;
}
