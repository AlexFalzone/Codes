#include<fstream>
using namespace std;

template<class H>
class Nodo
{
private:
    H valore;
    Nodo<H>* succ;

public:
    Nodo(H val) :valore(val){succ = NULL;}

    //succ
    void setSucc(Nodo<H>* p) {this->succ = p;}
    Nodo<H>* getSucc() {return succ;}

    //valore
    H getValore() {return valore;}
};                                                    //fine class Nodo


template<class H>
class Stack
{
private:
    Nodo<H>* testa;

public:
    Stack() {testa = NULL;}

    //testa
    void setTesta(Nodo<H>* nodo) {testa = nodo;}
    Nodo<H>* getTesta() {return testa;}

    bool Pilavuota(){return testa == NULL;}

    void push(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->setSucc(testa);
        testa = nuovo;
    }

    H pop()
    {
        if (testa != NULL)
        {
            H el = testa->getValore();
            Nodo<H>* tmp = testa;
            testa = testa->getSucc();
            delete tmp;
            return el;
        } 
        return -1;
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

};                                                    //fine class Stack


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

    H dequeue()
    {
        if(testa != NULL){
            H el = testa->getValore();
            Nodo<H>* tmp = testa;
            testa = testa->getSucc();
            delete tmp;
            return el;
        }   
        return (H) -1;
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

};                                                    //fine class Coda


template<class H>
class Stack_Coda
{
private:
    Stack<H>* stack;
    Coda<H>* coda;

public:
    Stack_Coda() {stack = new Stack<H>(); coda = new Coda<H>();}

    Stack<H>* getStack(){return stack;}
    Coda<H>* getCoda(){return coda;}

    void travasa()
    {
        if (!stack->Pilavuota())
        {
            while (!stack->Pilavuota())
            {
                coda->enqueue( stack->pop() );
            }   
        }
    }

};                                                    //fine classe supporto

int getDuePunti(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ':')
        {
            return i;
        }
    }
    return 0;
}

string getOperation(string x)
{
    return x.substr( 0, getDuePunti(x) );
}

string getValue(string x)
{
    return x.substr( getDuePunti(x)+1, x.length() );
}


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
            Stack_Coda<int>* p = new Stack_Coda<int>;
            
            for (int i = 0; i < dim; i++)
            {
                string tmp; in >> tmp;

                if (tmp == "pop")
                {
                    p->getStack()->pop();
                }
                else if (tmp == "dequeue")
                {
                    p->getCoda()->dequeue();
                }
                else if (tmp == "travasa")
                {
                    p->travasa();
                }
                else
                {
                    string op = getOperation(tmp);
                    string value = getValue(tmp);
                    int val = stoi(value);

                    if (op == "e")
                    {
                        p->getCoda()->enqueue(val);
                    }
                    else if (op == "p")
                    {
                        p->getStack()->push(val);
                    }
                }
            }
            p->getCoda()->stampa(out);
        }//fine caso int
        else if (tipo == "double")
        {
            Stack_Coda<double>* p = new Stack_Coda<double>;
            
            for (int i = 0; i < dim; i++)
            {
                string tmp; in >> tmp;

                if (tmp == "pop")
                {
                    p->getStack()->pop();
                }
                else if (tmp == "dequeue")
                {
                    p->getCoda()->dequeue();
                }
                else if (tmp == "travasa")
                {
                    p->travasa();
                }
                else
                {
                    string op = getOperation(tmp);
                    string value = getValue(tmp);
                    double val = stod(value);

                    if (op == "e")
                    {
                        p->getCoda()->enqueue(val);
                    }
                    else if (op == "p")
                    {
                        p->getStack()->push(val);
                    }
                }
            }
            p->getCoda()->stampa(out);
        }//fine caso double
        else if (tipo == "bool")
        {
            Stack_Coda<bool>* p = new Stack_Coda<bool>;
            
            for (int i = 0; i < dim; i++)
            {
                string tmp; in >> tmp;

                if (tmp == "pop")
                {
                    p->getStack()->pop();
                }
                else if (tmp == "dequeue")
                {
                    p->getCoda()->dequeue();
                }
                else if (tmp == "travasa")
                {
                    p->travasa();
                }
                else
                {
                    string op = getOperation(tmp);
                    string value = getValue(tmp);
                    bool val = stoi(value);

                    if (op == "e")
                    {
                        p->getCoda()->enqueue(val);
                    }
                    else if (op == "p")
                    {
                        p->getStack()->push(val);
                    }
                }
            }
            p->getCoda()->stampa(out);
        }//fine caso bool
        else if (tipo == "char")
        {
            Stack_Coda<char>* p = new Stack_Coda<char>;
            
            for (int i = 0; i < dim; i++)
            {
                string tmp; in >> tmp;

                if (tmp == "pop")
                {
                    p->getStack()->pop();
                }
                else if (tmp == "dequeue")
                {
                    p->getCoda()->dequeue();
                }
                else if (tmp == "travasa")
                {
                    p->travasa();
                }
                else
                {
                    string op = getOperation(tmp);
                    string value = getValue(tmp);
                    char val = value[0];

                    if (op == "e")
                    {
                        p->getCoda()->enqueue(val);
                    }
                    else if (op == "p")
                    {
                        p->getStack()->push(val);
                    }
                }
            }
            p->getCoda()->stampa(out);
        }
    }


    return 0;
}
