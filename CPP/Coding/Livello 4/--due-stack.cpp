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
    Nodo(H val) {valore = val, succ = NULL;}

    //succ
    void setSucc(Nodo<H>* p) {this->succ = p;}
    Nodo<H>* getSucc() {return succ;}

    //valore
    H getValore() {return valore;}
};


template<class H>
class Stack
{
private:
    Nodo<H>* testa;

public:
    Stack() {testa = NULL;}

    Nodo<H>* getTesta() {return testa;}

    H push(H in)//inserimento nuovo nodo
    {
        Nodo<H>* nuovo = new Nodo<H>(in);

        nuovo->setSucc(testa);
        testa = nuovo;

        return nuovo->getValore();
    }

    void pop()
    {
        Nodo<H>* iter = testa;

        if (iter != NULL)//stack vuoto
        {
            testa = testa->getSucc();
            delete iter;
        }
    }

};


template<class H>
class Coda
{
private:
    Nodo<H>* testa;

public:
    Coda() {testa = NULL;}

    Nodo<H>* getTesta() {return testa;}

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

    void dequeue()
    {
        if (testa != NULL)//coda vuota
        {
            Nodo<H>* iter = testa;
            testa = testa->getSucc();
            delete iter;
        }
    }

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


};



int main(int argc, char const *argv[])
{
    ifstream in("input.txt", ios::in);
    ofstream out("output.txt");

    for (int j = 0; j < 100; j++)
    {
        string tipo; in >> tipo;
        int dim; in >>dim;

        if (tipo == "int")
        {
            Stack<int>* S1 = new Stack<int>;
            Stack<int>* S2 = new Stack<int>;
            Coda<int>* C = new Coda<int>;

            for (int i = 0; i < dim; i++)
            {
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    C->dequeue();
                }
                else
                {
                    string n = valore.substr( 1, valore.length() );
                    int valore_in_stringa = stoi(n);
                    
                    C->enqueue(  S2->push( S1->push( valore_in_stringa ) )  );
                }
            }
            C->stampa(out);
            delete S1;
            delete S2;
            delete C;
        }
        else if (tipo == "double")
        {
            Stack<double>* S1 = new Stack<double>;
            Stack<double>* S2 = new Stack<double>;
            Coda<double>* C = new Coda<double>;

            for (int i = 0; i < dim; i++)
            {
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    C->dequeue();
                }
                else
                {
                    string n = valore.substr( 1, valore.length() );
                    double valore_in_stringa = stod(n);
                    
                    C->enqueue(  S2->push( S1->push( valore_in_stringa ) )  );
                }
            }
            C->stampa(out);
            delete S1;
            delete S2;
            delete C;
        }
        else if (tipo == "bool")
        {
            Stack<bool>* S1 = new Stack<bool>;
            Stack<bool>* S2 = new Stack<bool>;
            Coda<bool>* C = new Coda<bool>;

            for (int i = 0; i < dim; i++)
            {
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    C->dequeue();
                }
                else
                {
                    string n = valore.substr( 1, valore.length() );
                    bool valore_in_stringa = stod(n);
                    
                    C->enqueue(  S2->push( S1->push( valore_in_stringa ) )  );
                }
            }
            C->stampa(out);
            delete S1;
            delete S2;
            delete C;
        }
        else if (tipo == "char")
        {
            Stack<char>* S1 = new Stack<char>;
            Stack<char>* S2 = new Stack<char>;
            Coda<char>* C = new Coda<char>;

            for (int i = 0; i < dim; i++)
            {
                string valore; in >> valore;

                if (valore == "dequeue")
                {
                    C->dequeue();
                }
                else
                {
                    string n = valore.substr( 1, valore.length() );
                    C->enqueue(  S2->push( S1->push( n[0] ) )  );
                }
            }
            C->stampa(out);
            delete S1;
            delete S2;
            delete C;
        }
    }
    

    return 0;
}
