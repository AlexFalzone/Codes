#include<iostream>
#include<fstream>

using namespace std;

template<class H>
class Nodo
{
private:
    H valore;
    Nodo* succ;

public:
    Nodo(H x) {valore = x; succ = NULL;}
    H getValore() {return valore;}
    void setValore(H x) {valore = x;}
    Nodo* getSucc() {return succ;}
    void setSucc(Nodo<H>* x) {succ = x;}
};


template<class H>
class Pila
{
private:
    Nodo<H>* p; //testa

public:
    Pila() {p = NULL;}
    void push(H val); //inserisce un elemento nella pila
    void stampa(ofstream &out);
};


template<class H>
void Pila<H>::stampa(ofstream &out)
{
    Nodo<H>* pnodo = p;

    if (p == NULL)
    {
        out << "Pila vuota!\n";
    }
    else
    {
        while (pnodo != NULL)
        {
            out << pnodo->getValore() << " ";
            pnodo = pnodo->getSucc();
        }
    }
    out << endl; 
}

template<class H>
void Pila<H>::push(H val)
{
    Nodo<H>* nuovo = new Nodo<H>(val);
    //nuovo->setValore(val);
    
    nuovo->setSucc(p);
    p = nuovo;
}


int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int j = 0; j < 100; j++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;

        if (tipo == "int")
        {
            Pila<int>* pila = new Pila<int>;

            for (int i = 0; i < dim; i++)
            {   
                int val; in >> val;
                pila->push(val);
            }

            pila->stampa(out);
            delete pila;

        }
        else if (tipo == "double")
        {
            Pila<double>* pila = new Pila<double>;

            for (int i = 0; i < dim; i++)
            {   
                double val; in >> val;
                pila->push(val);
            }

            pila->stampa(out);
            delete pila;

        }
        else if (tipo == "bool")
        {
            Pila<bool>* pila = new Pila<bool>;

            for (int i = 0; i < dim; i++)
            {   
                bool val; in >> val;
                pila->push(val);
            }

            pila->stampa(out);
            delete pila;

        }
        else if (tipo == "char")
        {
            Pila<char>* pila = new Pila<char>;

            for (int i = 0; i < dim; i++)
            {   
                char val; in >> val;
                pila->push(val);
            }

            pila->stampa(out);
            delete pila;

        }
    }
    

    return 0;
}
