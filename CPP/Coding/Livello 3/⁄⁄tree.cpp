#include<iostream>
#include<fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template<class H>
class Nodo
{
private:    
    H valore;
    Nodo<H>* padre;
    Nodo<H>* left;
    Nodo<H>* right;

public:
    Nodo(H val) 
    {   
        valore = val;
        padre = left = right = NULL;
    }

    //valore
    H getValore() {return valore;}
    void setValore(H val) {valore = val;}

    //padre
    Nodo<H>* getPadre() {return padre;}
    void setPadre(Nodo<H>* val) {padre = val;}

    //left
    Nodo<H>* getLeft() {return left;}
    void setLeft(Nodo<H>* val) {left = val;}

    //right
    Nodo<H>* getRight() {return right;}
    void setRight(Nodo<H>* val) {right = val;}
};

template<class H>
class BST
{
private:
    Nodo<H>* radice;

public:
    BST() {radice = NULL;}

    Nodo<H>* getRadice() {return radice;}

    void visitaPreOrder(Nodo<H>* p)
    {
        if (p)
        {
            out << p->getValore() << " ";
            visitaPreOrder( p->getLeft());
            visitaPreOrder( p->getRight());
        }
    }


    void visitaInOrder(Nodo<H>* p)
    {   
        if (p)
        {
            visitaInOrder(p->getLeft());
            out << p->getValore() << " ";
            visitaInOrder(p->getRight());    
        }
    }


    void visitaPostOrder(Nodo<H>* p)
    {
        if (p)
        {
            visitaPostOrder(p->getLeft());
            visitaPostOrder(p->getRight());
            out << p->getValore() << " ";
        }

    }


    void insert(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);

        Nodo<H>* x = radice;
        Nodo<H>* y = NULL;

        while (x != NULL) //scorriamo albero fino alla fine
        {
            y = x;

            if ( val <= ( x->getValore() ) )
            {
                x = x->getLeft();
            }
            else
            {
                x = x->getRight();
            }
        }

        nuovo->setPadre(y);

        if (y == NULL) //albero vuoto
        {
            radice = nuovo;
        }
        else if ( val <= ( y->getValore() ) )
        {
            y->setLeft(nuovo);
        }
        else
        {
            y->setRight(nuovo);
        } 
    }

    void stampa(string tipo)
    {
        Nodo<H>* iter = radice;

        if (tipo == "inorder")
        {
            visitaInOrder(iter);
        }
        else if (tipo == "postorder")
        {
            visitaPostOrder(iter);
        }
        else if (tipo == "preorder")
        {
            visitaPreOrder(iter);
        }
    }
};

int main(int argc, char const *argv[])
{
    

    for (int i = 0; i < 100; i++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;
        string order; in >> order;

        if (tipo == "int")
        {
            BST<int>* tree = new BST<int>;

            for (int i = 0; i < dim; i++)
            {
                int x; in >> x;
                tree->insert(x);
            }
            tree->stampa(order);
            out << endl;
            delete tree;
        }   
        else if (tipo == "double")
        {
            BST<double>* tree = new BST<double>;

            for (int i = 0; i < dim; i++)
            {
                double x; in >> x;
                tree->insert(x);
            }
            tree->stampa(order);
            out << endl;
            delete tree;
        }
        else if (tipo == "bool")
        {
            BST<bool>* tree = new BST<bool>;

            for (int i = 0; i < dim; i++)
            {
                bool x; in >> x;
                tree->insert(x);
            }
            tree->stampa(order);
            out << endl;
            delete tree;
        }
        else if (tipo == "char")
        {
            BST<char>* tree = new BST<char>;

            for (int i = 0; i < dim; i++)
            {
                char x; in >> x;
                tree->insert(x);
            }
            tree->stampa(order);
            out << endl;
            delete tree;
        }
    }
    

    return 0;
}
