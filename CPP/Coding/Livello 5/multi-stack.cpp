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

    Nodo<H>* getSucc() {return succ;}
    void setSucc(Nodo<H>* z) {succ = z;}

    H getValore() {return valore;}

};

template<class H>
class Stack
{
private:
    Nodo<H>* testa;

public:
    Stack() {testa = NULL;}

    void push(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->setSucc(testa);
        testa = testa->getSucc();
    }

    Nodo<H>* pop()
    {
        Nodo<H>* iter = testa;
        if (iter)
        {
            testa = testa->getSucc();
        }
        return iter;
    }

    void newPush(H val)
    {
        Stack<H>* st = new Stack<H>*;
        st->push(val);
    }

    void print(ofstream& out)
    {
        Nodo<H>* iter = testa;
    }

};


int getDuePunti(string s)
{
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] == ':')
        {
            return i;
        }
    }
    return -1;
}

string getOp(string s)
{
    return s.substr(0, getDuePunti(s));
} 

string getVal(string s)
{
    return s.substr(getDuePunti(s) + 1, s.length());
}



int main(int argc, char const *argv[])
{
    ifstream in("input.txt", ios::in);
    ofstream out("output.txt");

    for (int k = 0; k < 3; k++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;

        if (tipo == "int")
        {   
            for (int i = 0; i < dim; i++)
            {
                string x; in >> x;
                string op = getOp(x);
                string val = getVal(x);
                int valore = stoi(val);

                if (op == "pop")
                {
                    
                }
                else if (op == "n") //newPush
                {
                    
                }
                else if (op == "p") //push
                {
                    
                }
                
            }
            
        }
        
    }
    

    return 0;
}
