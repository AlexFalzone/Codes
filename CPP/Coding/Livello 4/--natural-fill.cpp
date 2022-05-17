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
    Nodo<H>* radice;

public:
    Tree() {radice = NULL;}

    Nodo<H>* getRadice() {return radice;}


    void inserimento(H val)
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
            y->getLeft() = nuovo;
        }
        else
        {
            y->getRight() = nuovo;
        }
    }

    void visita_Inorder(Nodo<H>* p, H* vett, int& i)
    {
        if (p)
        {
            visita_Inorder(p->getLeft(), vett, i);
            p->setValore(vett[i]);
            i++;
            visita_Inorder(p->getRight(), vett, i);
        }
    }

    void Natural_Fill(H* vett, int &i)
    {
        visita_Inorder(getRadice(), vett, i);
    }

    void visita_Postorder(Nodo<H>* p, ofstream& out)
    {
        if (p)
        {
            visita_Postorder(p->getLeft(), out);
            visita_Postorder(p->getRight(), out);
            out << p->getValore() << " ";
        }
    }

    void print(ofstream& out)
    {
        visita_Postorder(getRadice(), out);
        out << endl;
    }
};


int main(int argc, char const *argv[])
{
    ifstream in("input.txt", ios::in);
    ofstream out("output.txt");

    for (int k = 0; k < 100; k++)
    {
        string tipo; in >> tipo;
        int dim; in >> dim;

        if (tipo == "int")
        { 
            Tree<int>* tree = new Tree<int>;

            for (int i = 0; i < dim; i++)
            {
                int x; in >> x;
                tree->inserimento(x);
            }

            int *vett = new int[dim];
            for (int i = 0; i < dim; i++)
            {
                int x; in >> x;
                vett[i] = x;
            }
            
            int index = 0;
            tree->Natural_Fill(vett, index);
            tree->print(out);
            delete [] vett;
            delete tree;
        }
        else if (tipo == "double")
        {
            Tree<double>* tree = new Tree<double>;

            for (int i = 0; i < dim; i++)
            {
                double x; in >> x;
                tree->inserimento(x);
            }

            double *vett = new double[dim];
            for (int i = 0; i < dim; i++)
            {
                double x; in >> x;
                vett[i] = x;
            }
            
            int index = 0;
            tree->Natural_Fill(vett, index);
            tree->print(out);
            delete [] vett;
            delete tree;
        }
    }
    

    return 0;
}
