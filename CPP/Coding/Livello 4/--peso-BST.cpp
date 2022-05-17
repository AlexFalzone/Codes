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
    H peso;

public:
    tree() {radice = NULL, peso = 0;}

    void insert(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->getRight() = nuovo->getLeft() = NULL;
        Nodo<H>* x = radice;
        Nodo<H>* y = NULL;

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

    Nodo<H>* Minimo(Nodo<H>* z)
    {
        Nodo<H>* min = z;
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
        else
        {
            u->getPadre()->getRight() = v;
        }
        if (v!=NULL)
        {
            v->setPadre(u->getPadre());
        }
    }

    void canc(Nodo<H>* z)
    {
        if (z->getLeft() == NULL)
        {
            Trapianta(z,z->getRight());
        }
        else if (z->getRight() == NULL)
        {
            Trapianta(z,z->getLeft());
        }
        else
        {
            Nodo<H>* y = Minimo(z->getRight());
            if (y->getPadre() != z)
            {
                Trapianta(y,y->getRight());
                y->getRight() = z->getRight();
                y->getRight()->getPadre() = y;
            }
            Trapianta(z,y);
            y->getLeft() = z->getLeft();
            y->getLeft()->getPadre() = y;
        }
        delete z;
    }

    Nodo<H>* search(H val)
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

    H Peso(Nodo<H>* p)
    {
        peso+=p->getValore();
        if (p->getRight() != NULL)
        {
            Peso(p->getRight());
        }
        if (p->getLeft() != NULL)
        {
            Peso(p->getLeft());
        }
        return peso;
    }



    /*H Peso(H val)
    {
        Nodo<H>* iter = search(val);
        peso = iter->getValore();
        cout << iter->getValore()<< endl;
        if (iter)
        {   
            cout <<"not NULL\n";
            while (iter->getLeft() != NULL)
            {   
                cout << "right " << iter->getValore()<< endl;
                iter = iter->getLeft();
                peso+=iter->getValore();
            }
            iter = search(val);
            while (iter->getLeft() != NULL)
            {   
                cout << "left " << iter->getValore()<< endl;
                iter = iter->getLeft();
                peso+=iter->getValore();
            }
            return peso;
        }
        return -1;
    }*/

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
                    Nodo<int>* el = albero->search(valore);
                    albero->canc(el);
                }
            }
            int pp; in >> pp;
            Nodo<int>* pe = albero->search(pp);
            out << albero->Peso(pe) << endl;
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
                double valore = stod(val);

                if (op == "ins")
                {
                    albero->insert(valore);
                }
                else if (op == "canc")
                {
                    Nodo<double>* el = albero->search(valore);
                    albero->canc(el);
                }
            }
            double pp; in >> pp;
            Nodo<double>* pe = albero->search(pp);
            out << albero->Peso(pe) << endl;
            delete albero;
        }
        
    }
    return 0;
}
