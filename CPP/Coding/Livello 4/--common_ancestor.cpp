#include<iostream>
#include<fstream>
using namespace std;

template<class H>
class Nodo
{
private:
    H valore;
    Nodo<H>* padre;
    Nodo<H>* left;
    Nodo<H>* right;

public:
    Nodo(H val) :valore(val) {padre = left = right = NULL;}

    void setValore(H val) {valore = val;}
    void setPadre(Nodo<H>* val) {padre = val;}
    void setLeft(Nodo<H>* val) {left = val;}
    void setRight(Nodo<H>* val) {right = val;}

    H &getValore() {return valore;}
    Nodo<H>* &getPadre() {return padre;}
    Nodo<H>* &getLeft() {return left;}
    Nodo<H>* &getRight() {return right;}

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
        else if (u->getPadre()->getLeft() == u)
        {
            u->getPadre()->getLeft() = v;
        }
        else
        {
            u->getPadre()->getRight() = v;
        }
        if (v != NULL)
        {
            v->setPadre(u->getPadre());
        }
    }

    public:
    Tree() {root = NULL;}

    void ins(H val)
    {
        Nodo<H>* x = root;
        Nodo<H>* y = NULL;
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->getLeft() = nuovo->getRight() = NULL;
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

    Nodo<H>* minimum(Nodo<H>* val)
    {
        Nodo<H>* min = val;
        while (min->getLeft() != NULL)
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
            trapianta(z,z->getRight());
        }
        else if (z->getRight() == NULL)
        {
            trapianta(z,z->getLeft());
        }
        else
        {
            y = minimum(z->getRight());
            if (y->getPadre() != z)
            {
                trapianta(y,y->getRight());
                y->getRight() = z->getRight();
                y->getRight()->getPadre() = y;
            }
            trapianta(z,y);
            y->getLeft() = z->getLeft();
            y->getLeft()->getPadre() = y;
        }
        delete z;
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

    H ancestor(H x, H y,ofstream& out)
    {
        Nodo<H>* i = find(x);
        Nodo<H>* j = find(y);
        Nodo<H>* iter = root;
        bool done = false;

        if (i->getPadre() == NULL)
        {
            return i->getValore();
        }
        else if (j->getPadre() == NULL)
        {
            return j->getValore();
        }
        else
        {
           while (done == false)
           {
               if ( (iter->getValore() >= i->getValore() && iter->getValore() <= j->getValore()) || (iter->getValore() <= i->getValore() && iter->getValore() >= j->getValore()) ) 
               {    //condizione di uscita; abbiamo trovato l'antenato
                   done = true;
                    return  iter->getValore();   
               }
               
                if (i->getValore() < iter->getValore() && j->getValore() < iter->getValore())
                {
                    iter = iter->getLeft();
                }else if (i->getValore() > iter->getValore() && j->getValore() > iter->getValore())
                {
                    iter = iter->getRight();
                }
                else if ( (i->getValore() > iter->getValore() && j->getValore() < iter->getValore()) || (i->getValore() < iter->getValore() && j->getValore() > iter->getValore()) )
                {
                    done = true;
                    return iter->getValore();
                }
            }
        }
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
                string dato; in >> dato;
                string op = getOperation(dato);
                string v = getValue(dato);
                int valore = stoi(v);

                if (op == "ins")
                {
                    tr->ins(valore);
                }
                else if (op == "canc")
                {
                    Nodo<int>* el = tr->find(valore);
                    tr->canc(el); 
                }
            }
            int val1, val2;
            in >> val1; in >> val2;
            out << tr->ancestor(val1, val2, out);     
            out << endl;
            delete tr;
        }
        else if (tipo == "double")
        {
            Tree<double>* tr = new Tree<double>();
            for (int i = 0; i < dim; i++)
            {
                string dato; in >> dato;
                string op = getOperation(dato);
                string v = getValue(dato);
                double valore = stod(v);

                if (op == "ins")
                {
                    tr->ins(valore);
                }
                else if (op == "canc")
                {
                    Nodo<double>* el = tr->find(valore);
                    tr->canc(el); 
                }
            }
            double val1, val2;
            in >> val1; in >> val2;
            out << tr->ancestor(val1, val2, out);     
            out << endl;
            delete tr;
        }
        
    }

}