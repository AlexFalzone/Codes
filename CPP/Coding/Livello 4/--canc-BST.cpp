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
    Nodo(H val) {padre = right = left = NULL; valore = val;}

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

    void inserimento(H val)
    {
        Nodo<H>* x = radice;
        Nodo<H>* y = NULL;
        Nodo<H>* nuovo = new Nodo<H>(val);
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
            y->getLeft() = nuovo;
        }
        else
        {
            y->getRight() = nuovo;
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
        else if (u == u->getPadre()->getLeft() )
        {
            u->getPadre()->getLeft() = v;
        }
        else
        {
            u->getPadre()->getRight() = v;
        }
        
        if (v != NULL)
        {
            v->setPadre( u->getPadre() );
        }
    }

    void Cancella(Nodo<H>* z)
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

    void visita_Inorder(Nodo<H>* p, ofstream& out)
    {
        if (p)
        {
            visita_Inorder(p->getLeft(), out);
            out << p->getValore() << " ";
            visita_Inorder(p->getRight(), out);
        }
        
    }

    void visita_PostOrder(Nodo<H>* p, ofstream& out)
    {
        if (p)
        {
            visita_PostOrder(p->getLeft(), out);
            visita_PostOrder(p->getRight(), out);
            out << p->getValore() << " ";
        }
    }

    void visita_Preorder(Nodo<H>* p, ofstream& out)
    {
        if (p)
        {
            out << p->getValore() << " ";
            visita_Preorder(p->getLeft(), out);
            visita_Preorder(p->getRight(), out);
        }
    }
    
    void print(ofstream& out, int x)
    {
        if (x == 0)//preorder
        {
            visita_Preorder(radice, out);
        }
        else if (x == 1)//inorder
        {
            visita_Inorder(radice, out);
        }
        else if (x == 2)//postorder
        {
            visita_PostOrder(radice, out);
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
        string stampa; in >> stampa;

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
                    albero->inserimento(valore);
                }
                else if (op == "canc")
                {
                    Nodo<int>* el = albero->cerca(valore);
                    albero->Cancella(el);
                }
            }
            if (stampa == "preorder")
            {
                albero->print(out, 0);
            }
            else if (stampa == "inorder")
            {
                albero->print(out, 1);
            }
            else if (stampa == "postorder")
            {
                albero->print(out, 2);
            }
            out << endl;
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
                    albero->inserimento(valore);
                }
                else if (op == "canc")
                {
                    Nodo<double>* el = albero->cerca(valore);
                    albero->Cancella(el);
                }
            }
            if (stampa == "preorder")
            {
                albero->print(out, 0);
            }
            else if (stampa == "inorder")
            {
                albero->print(out, 1);
            }
            else if (stampa == "postorder")
            {
                albero->print(out, 2);
            }
            out << endl;
            delete albero;
        }
        else if (tipo == "char")
        {
            tree<char>* albero = new tree<char>;

            for (int i = 0; i < dim; i++)
            {
                string x; in >> x;
                string op = getOp(x);
                string val = getVal(x);
                char valore = val[0];

                if (op == "ins")
                {
                    albero->inserimento(valore);
                }
                else if (op == "canc")
                {
                    Nodo<char>* el = albero->cerca(valore);
                    albero->Cancella(el);
                }
            }
            if (stampa == "preorder")
            {
                albero->print(out, 0);
            }
            else if (stampa == "inorder")
            {
                albero->print(out, 1);
            }
            else if (stampa == "postorder")
            {
                albero->print(out, 2);
            }
            out << endl;
            delete albero;
        }
        else if (tipo == "bool")
        {
            tree<bool>* albero = new tree<bool>;

            for (int i = 0; i < dim; i++)
            {
                string x; in >> x;
                string op = getOp(x);
                string val = getVal(x);
                bool valore = stoi(val);

                if (op == "ins")
                {
                    albero->inserimento(valore);
                }
                else if (op == "canc")
                {
                    Nodo<bool>* el = albero->cerca(valore);
                    albero->Cancella(el);
                }
            }
            if (stampa == "preorder")
            {
                albero->print(out, 0);
            }
            else if (stampa == "inorder")
            {
                albero->print(out, 1);
            }
            else if (stampa == "postorder")
            {
                albero->print(out, 2);
            }
            out << endl;
            delete albero;
        }
    }
    

    return 0;
}
