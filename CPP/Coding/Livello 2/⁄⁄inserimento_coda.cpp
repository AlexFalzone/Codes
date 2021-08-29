#include<iostream>
#include<fstream>

using namespace std;

template<class H>
class Nodo
{
private:
    H valore;
    Nodo<H>* succ;

public:
    Nodo(H x) {valore = x; succ = NULL;}
    H getValore() {return valore;}
    void setValore(H x) {valore = x;}
    Nodo* getSucc() {return succ;}
    void setSucc(Nodo<H>* x) {succ = x;};
};

template<class H>
class Coda
{
private:
    Nodo<H>* testa;

public:
    Coda() {testa = NULL;}
    void enqueue(H val)
    {   
        Nodo<H>* nuovo = new Nodo<H>(val);

        if (testa == NULL)
        {
            testa = nuovo;
        }
        else
        {
            Nodo<H>* iter = testa;

            while (iter->getSucc() != NULL)
            {
                iter = iter->getSucc();
            }
            iter->setSucc(nuovo);
        }
        
    }

    void print(ofstream &out)
    {   
        Nodo<H>* iter = testa;

        while (iter != NULL)
        {
            out << iter->getValore() << " "; 
            iter = iter->getSucc();
        }
        out << endl;
    }
};


int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int i = 0; i < 100; i++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;

        if (tipo == "int")
        {
            Coda<int>* coda = new Coda<int>;

            for (int i = 0; i < dim; i++)
            {   
                int val; in >> val;
                coda->enqueue(val);
            }
            coda->print(out);
            delete coda;

        }
        else if (tipo == "double")
        {
            Coda<double>* coda = new Coda<double>;

            for (int i = 0; i < dim; i++)
            {   
                double val; in >> val;
                coda->enqueue(val);
            }
            coda->print(out);
            delete coda;

        }
        else if (tipo == "bool")
        {
            Coda<bool>* coda = new Coda<bool>;

            for (int i = 0; i < dim; i++)
            {   
                bool val; in >> val;
                coda->enqueue(val);
            }
            coda->print(out);
            delete coda;

        }
        else if (tipo == "char")
        {
            Coda<char>* coda = new Coda<char>;

            for (int i = 0; i < dim; i++)
            {   
                char val; in >> val;
                coda->enqueue(val);
            }
            coda->print(out);
            delete coda;

        }
    }
    

    return 0;
}

