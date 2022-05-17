#include<iostream>

using namespace std;

struct Nodo
{
    int valore;
    Nodo* succ;   
};

class ListaSemplice
{
private:
    Nodo* testa;
    void ins_coda(Nodo* p, int val);
    void ins(Nodo* p, int val);

public:
    ListaSemplice() {testa = NULL;}
    void stampa();
    void insert(int val);
};



void ListaSemplice::stampa()
{
    Nodo* iter = testa;

    while (iter != NULL)
    {
        cout << " " << iter->valore << endl;
        iter = iter->succ;
    }
}

void ListaSemplice::ins_coda(Nodo* iter, int val)
{
    if (iter == NULL)
    {
        Nodo* nuovo = new Nodo;

        nuovo->valore = val;
        testa = nuovo;
        testa->succ = NULL;
    }
    else if (iter->succ == NULL)
    {
        Nodo* nuovo = new Nodo;

        nuovo->valore = val;
        nuovo->succ = NULL;
        iter->succ = nuovo;
    }
    else
    {
        ins_coda(iter->succ, val);
    }
}

void ListaSemplice::ins(Nodo* iter, int val)
{
    if (iter == NULL)
    {
        //lista vuota
        Nodo* nuovo = new Nodo;

        nuovo->valore = val;
        testa = nuovo;
        testa->succ = NULL;
    }
    else if ((iter==testa) && (iter->valore > val))
    {
        //inserimento in testa
        Nodo* nuovo = new Nodo;

        nuovo->valore = val;
        nuovo->succ = testa;
        testa = nuovo;
    }
    else if ((iter->succ) && (iter->succ->valore <= val))
    {
        ins(iter->succ, val);   
    }
    else
    {
        Nodo* nuovo = new Nodo;

        nuovo->valore = val;
        nuovo->succ = iter->succ;
        iter->succ = nuovo;
    }
}

void ListaSemplice::insert(int val)
{
    Nodo* p = testa;
    //ins_coda(p,val);
    ins(p,val);
}

int main(int argc, char const *argv[])
{
    ListaSemplice lista;
    Nodo* p;

    lista.insert(20);
    lista.insert(26);
    lista.insert(3);
    lista.insert(2);
    lista.insert(27);
    lista.stampa();

    return 0;
}
