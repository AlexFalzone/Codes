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
    Nodo(H x) :valore(x) {succ = NULL;}

    H getValore() {return valore;}

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

    void dequeue()
    {
        Nodo<H>* iter = testa;

        if (testa == NULL)
        {
            cout << "Coda Vuota!\n";
        }
        else    
        {   
            testa = testa->getSucc();
            delete iter;
        }
    }

    void stampa(ofstream& out)
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


    for (int j = 0; j < 100; j++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;

        if (tipo == "int")
        {   
            Coda<int>* coda = new Coda<int>[dim];

            for (int i = 0; i < dim; i++)
            {   
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    coda->dequeue();
                }
                else
                {
                    string value = valore.substr( 1, valore.length() );
                    int valore_finale = stoi(value);
                    
                    coda->enqueue(valore_finale);
                }
            }
            coda->stampa(out);
            delete coda;
        }
        else if (tipo == "double")
        {
            Coda<double>* coda = new Coda<double>;

            for (int i = 0; i < dim; i++)
            {   
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    coda->dequeue();
                }
                else
                {
                    string value = valore.substr( 1, valore.length() );
                    double valore_finale = stod(value);
                    
                    coda->enqueue(valore_finale);
                }
            }
            coda->stampa(out);
            delete coda;
        }
        else if (tipo == "bool")
        {
            Coda<bool>* coda = new Coda<bool>;

            for (int i = 0; i < dim; i++)
            {
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    coda->dequeue();
                }
                else
                {
                    string value = valore.substr( 1, valore.length() );
                    bool valore_finale = stoi(value);
                    
                    coda->enqueue(valore_finale);
                }
            }
            coda->stampa(out);
            delete coda;
        }
        
        else if (tipo == "char")
        {
            Coda<char>* coda = new Coda<char>;

            for (int i = 0; i < dim; i++)
            {
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    coda->dequeue();
                }
                else
                {
                    string value = valore.substr( 1, valore.length() );   

                    coda->enqueue(value[0]);
                }
            }
            coda->stampa(out);
            delete coda;
        }
    }
    

    return 0;
}
