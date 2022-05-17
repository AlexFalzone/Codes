#include "ListaDoppiaCircolare.h"

ListaDoppiaCircolare::~ListaDoppiaCircolare()
{   
    Nodo* supp;

    if (testa != NULL)
    {
        supp = testa->succ;
    }
    else
    {   
        while (supp != testa)
        {
            Nodo* tmp = supp->succ;
            delete supp;
            supp = tmp;
        }
        delete testa;
    }
}

void ListaDoppiaCircolare::stampa()
{
    if (this->testa == NULL )
    {
        cout << "Lista vuota!\n";
    }
    else if (this->testa->succ == this->testa)
    {
        cout << "Lista con un solo elemento: " << testa->valore << endl;;
    }
    else
    {
        Nodo* primo = testa;

        do
        {
            cout << " " << primo->valore << ":\tSuccessivo: ";
            cout << primo->succ->valore;
            cout << "\tPrecedente: ";
            cout << primo->prec->valore << endl;
            primo = primo->succ;

        } while (primo != testa);
        
    }
}

void ListaDoppiaCircolare::inserisci(int val)
{
    Nodo* nuovo = new Nodo;

    nuovo->valore = val;

    if (testa == NULL)                  //se la lista è vuota il succ di nuovo sarà nuovo stesso!    
    {
        nuovo->succ = nuovo;
        nuovo->prec = nuovo;
        testa = nuovo;
    }
    else if (testa->succ == testa)      //se la lista contiene un solo elemento, nuovo sarà il succ e il prec di testa
    {                                  
        nuovo->succ = testa;
        nuovo->prec = testa;
        testa->succ = nuovo;
        nuovo->succ->prec = nuovo; 
    }   
    else 
    {
        nuovo->succ = testa->succ;
        nuovo->prec = testa;
        testa->succ = nuovo;
        nuovo->succ->prec = nuovo;
    }
}

void ListaDoppiaCircolare::rimuovi(int val)
{   
    Nodo* current;
    Nodo* precedente;

    if (testa == NULL)
    {
        cout << "Lista vuota!\n";
    }
    else if (this->testa->valore == val)
    {
        current = testa->succ;
        testa = testa->succ;
        testa->prec = NULL;
        delete current;
    }
    else
    {   
        current = testa->succ;

        while ( (current != testa) && (current->valore != val) )
        {
            current = current->succ;
        }

        if (current->valore == val)
        {
            precedente = current->prec;
            precedente->succ = current->succ;
            current->succ->prec = precedente;
            delete current;
        }
        else
        {
            cout << "Elemento non presente!\n";
        }  
    }
}

Nodo* ListaDoppiaCircolare::ricerca(int val)
{
    Nodo* p;

    if (this->testa == NULL)
    {
        cout << "Lista vuota!\n";
    }
    else
    {
        for (p = this->testa; p <= testa->prec; p++)
        {
            if (p->valore == val)
            {
                return p;
            }
        }
        return NULL;
    }
}