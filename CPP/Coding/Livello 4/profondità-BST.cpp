#include<iostream>
#include<fstream>
using namespace std;

template<class H>
class Nodo
{
private:
    H valore;
    Nodo<H>* padre;
    Nodo<H>* right;
    Nodo<H>* left;

public:
    Nodo(H val) {valore = val, padre = right = left = NULL;}

    H getValore() {return valore;}
    Nodo<H>* &getPadre() {return padre;}
    Nodo<H>* &getRight() {return right;}
    Nodo<H>* &getLeft() {return left;}

    void setPadre(Nodo<H>* x) {padre = x;}
    void setRight(Nodo<H>* x) {right = x;}
    void setLeft(Nodo<H>* x) {left = x;}
    void setValore(H val) {valore = val;}

};

template<class H>
class Tree
{
private:
    Nodo<H>* root;

    void trapianta(Nodo<H>* u, Nodo<H>* v)
    {
        if (u->getPadre() == NULL)
        {
            root = v;
        }
        else if (u == u->getPadre()->getLeft())
        {
            u->getPadre()->getLeft() = v;
        }
        else
        {
            u->getPadre()->getRight() = v;
        } 
    }


public:
    Tree() {root = NULL;}

    void insert(H val)
    {
        Nodo<H>* x = root;
        Nodo<H>* y = NULL;
        Nodo<H>* nuovo = new Nodo<H>(val);

        while (x != NULL)
        {
            y = x;
            if (x->getValore() >= val)
            {
                x = x->getLeft();
            }
            else
            {
                x = x->getRight();
            }
        }
        nuovo->setPadre(y);
        if (y == NULL)
        {
            root = nuovo;
        }
        else if (y->getValore() >= val)
        {
            y->setLeft(nuovo);
        }
        else
        {
            y->setRight(nuovo);
        }
    }

    Nodo<H>* minimo(Nodo<H>* x)
    {
        Nodo<H>* min = x;
        while (min != NULL)
        {
            min = min->getLeft();
        }
        return min;
    }

    void canc(Nodo<H>* z)
    {
        Nodo<H>* y;
        if (z->getLeft() == NULL)
        {
            trapianta(z, z->getRight());
        }
        else if (z->getRight() == NULL)
        {
            trapianta(z, z->getLeft());
        }
        else
        {
            y = minimo(z->getRight());
            if (y->getPadre() != z)
            {
                trapianta(y, y->getRight());
                y->getRight() = z->getRight();
                y->getRight()->getPadre() = y;                
            }
            trapianta(z, y);
            y->getLeft() = z->getLeft();
            y->getLeft()->getPadre() = y;
        }
        delete z;
    }

    void profondita(H val, ofstream& out)
    {
        Nodo<H>* iter = find(val);

        cout << "proof\n";
        if (iter)
        {
            int prof;
            while (iter->getPadre() != NULL)
            {
                iter = iter->getPadre();
                prof++;
            }
            out << prof << endl;
        }
        out << -1 << endl;
    }

    Nodo<H>* find(H val)
    {
        Nodo<H>* iter = root;
        while ( (iter != NULL) && (iter->getValore() != val) )
        {
            if (iter->getValore() > val)
            {
                iter = iter->getLeft();
            }
            else
            {
                iter = iter->getRight();
            }
        }
        return iter;
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

    for (int j = 0; j < 100; j++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;
        if (tipo == "int")
        {
            Tree<int>* tr = new Tree<int>();

            for (int i = 0; i < dim; i++)
            {
                string general; in >> general;
                string op = getOp(general);
                string val_tmp = getVal(general);
                int valore = stoi(val_tmp);

                if (op == "ins")
                {
                    tr->insert(valore);
                }
                else if (op == "canc")
                {
                    Nodo<int>* el = tr->find(valore);
                    tr->canc(el);
                }
            }
            int chiave; in >> chiave;
            tr->profondita(chiave, out);
        }
        
    }
    

    return 0;
}
