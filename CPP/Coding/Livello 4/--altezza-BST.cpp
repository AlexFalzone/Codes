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

    Nodo<H>* &getPadre() {return padre;}
    Nodo<H>* &getRight() {return right;}
    Nodo<H>* &getLeft() {return left;}
    H &getValore() {return valore;}

};

template<class H>
class BST
{
private:
    Nodo<H>* radice;

    int calcolaAltezza(Nodo<H>* x)
    {
		if(!x) return 0;//se il nodo e' nullo ritorniamo -1 perche' dobbiamo compensare la chiamata extra
		int s=calcolaAltezza(x->getLeft());//calcoliamo l'altezza del sottoalbero sinistro
		int d=calcolaAltezza(x->getRight());//calcoliamo l'altezza del sottoalbero destro
		
		if(s>d) return 1+s;//ritorniamo il valore del sottoalbero piu' profondo +1 che sarebbe il nodo attuale
		else return 1+d;
	}

public:
    BST() {radice = NULL;}

    int altezza()
    {
		return calcolaAltezza(radice);
	}

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
        nuovo->getPadre() = y;
        if (y== NULL)
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

    void Trapianta(Nodo<H>*u, Nodo<H>* v)
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

        if (v != NULL)
        {
            v->getPadre() = u->getPadre();
        }
    }

    void Cancella(Nodo<H>* iter)
    {
        Nodo<H>* y;
        if (iter->getLeft() == NULL)
        {
            Trapianta(iter, iter->getRight());
        }
        else if (iter->getRight() == NULL)
        {
            Trapianta(iter, iter->getLeft());
        }
        else
        {
            y = Minimo(iter->getRight());
            if (y->getPadre() != iter)
            {
                Trapianta(y, y->getRight());
                y->getRight() = iter->getRight();
                y->getRight()->getPadre() = y;
            }
            Trapianta(iter, y);
            y->getLeft() = iter->getLeft();
            y->getLeft()->getPadre() = y;
        }
        delete iter;
    }

    Nodo<H>* Find(H val)
    {
        Nodo<H>* iter = radice;

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
    return s.substr(getDuePunti(s)+1, s.length());
}



int main(int argc, char const *argv[])
{
    ifstream in("input.txt", ios::in);
    ofstream out ("output.txt");

    for (int j = 0; j < 100; j++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;

        if (tipo == "int")
        {
            BST<int>* tree = new BST<int>;

            for (int i = 0; i < dim; i++)
            {
                string x; in>>x;
                string op = getOp(x);
                string val = getVal(x);
                int valore = stoi(val);

                if (op == "canc")
                {   
                    Nodo<int>* el = tree->Find(valore);
                    tree->Cancella(el);
                }
                else if (op == "ins")
                {
                    tree->insert(valore);
                }
            }
            out << tree->altezza() << endl;
            delete tree;
        }
        else if (tipo == "double")
        {
            BST<double>* tree = new BST<double>;

            for (int i = 0; i < dim; i++)
            {
                string x; in>>x;
                string op = getOp(x);
                string val = getVal(x);
                double valore = stod(val);

                if (op == "canc")
                {   
                    Nodo<double>* el = tree->Find(valore);
                    tree->Cancella(el);
                }
                else if (op == "ins")
                {
                    tree->insert(valore);
                }
            }
            out << tree->altezza() << endl;
            delete tree;
        }
        
    }
    

    return 0;
}
