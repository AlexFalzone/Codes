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
class tree
{
private:
    Nodo<H>* radice;

public:
    tree() {radice = NULL;}

    void insert(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);
        Nodo<H>* x = radice;
        Nodo<H>* y = NULL;
        nuovo->getLeft() = nuovo->getRight() = NULL;

        while (x != NULL)
        {
            y = x;
            if (x->getValore() > val)
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
            radice = nuovo;
        }
        else if (y->getValore() > val)
        {
            y->setLeft(nuovo);
        }
        else
        {
            y->setRight(nuovo);
        }
    }

    Nodo<H>* Minimo(Nodo<H>* val)
    {
        Nodo<H>* min = val;
        while (min->getLeft() != NULL)
        {
            min = min->getLeft();
        }
        return min;
    }

    void Trapianta(Nodo<H>* u, Nodo<H>* v)
    {
        if (u->getPadre() == NULL)
        {
            radice = v;
        }
        else if (u == u->getPadre()->getLeft())
        {
            u->getPadre()->getLeft() = v;
        }
        else if (u == u->getPadre()->getRight())
        {
            u->getPadre()->getRight() = v;
        }

        if (v != NULL)
        {
            v->setPadre(u->getPadre());
        }
    }

    void canc(Nodo<H>* z)
    {
        Nodo<H>* y;

        if (z->getLeft() == NULL)
        {
            Trapianta(z, z->getRight());
        }
        else if (z->getRight() == NULL)
        {
            Trapianta(z, z->getLeft());
        }
        else
        {
            y = Minimo(z->getRight());
            if (y->getPadre() != z)
            {
                Trapianta(y, y->getRight());
                y->getRight() = z->getRight();
                y->getRight()->getPadre() = y;
            }
            Trapianta(z, y);
            y->getLeft() = z->getLeft();
            y->getLeft()->getPadre() = y;
        }
        delete z;
    }

    int foglie(Nodo<H>* p)
    {
        if (p == NULL)
        {
            return 0;
        }
        else
        {
            if ( (p->getLeft() == NULL) && (p->getRight() == NULL) )
            {
                return 1;
            }
            else
            {
                return ( foglie( p->getLeft() ) + foglie( p->getRight() ) );
            }
        }
    }

    int getFoglie() {return foglie(radice);}

    Nodo<H>* cerca(H val)
    {
        Nodo<H>* iter = radice;

        while ( (iter != NULL) && (iter->getValore() != val))
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
            tree<int>* albero = new tree<int>;

            for (int i = 0; i < dim; i++)
            {
                string x; in >> x;
                string op = getOp(x);
                string val = getVal(x);
                int valore = stoi(val);

                if (op == "ins")
                {
                    albero->insert(valore);
                }
                else if (op == "canc")
                {
                    Nodo<int>* el = albero->cerca(valore);
                    albero->canc(el);
                }
            }
            out << albero->getFoglie() << endl;
            delete albero;
        }
        else if (tipo == "double")
        {
            tree<double>* albero = new tree<double>;

            for (int i = 0; i < dim; i++)
            {
                string x; in >> x;
                string op = getOp(x);
                string val = getVal(x);
                double valore = stoi(val);

                if (op == "ins")
                {
                    albero->insert(valore);
                }
                else if (op == "canc")
                {
                    Nodo<double>* el = albero->cerca(valore);
                    albero->canc(el);
                }
            }
            out << albero->getFoglie() << endl;
            delete albero;
        }
        
    }

    return 0;
}
