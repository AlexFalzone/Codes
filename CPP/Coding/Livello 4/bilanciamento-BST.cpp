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
    H peso;
    int valore_nodo;

    void trapianta(Nodo<H>* u, Nodo<H>* v)//rimpiazza radice u con radice v
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

    void preOrder(Nodo<H>* x)
    {   
        if (x)
        {
            cout << x->getValore() << " ";
            preOrder(x->getLeft());
            preOrder(x->getRight());
            
        }
        
    }

    void inOrder(Nodo<H>* x)
    {   
        if (x)
        {
            inOrder(x->getLeft());
            cout << x->getValore() << " ";
            inOrder(x->getRight());
        }
    }

    //inorder per la natural fill
    void _inorder(Nodo<H>* p, H* vett, int& i)
    {
        if (p)
        {
            _inorder(p->getLeft(), vett, i);
            p->setValore(vett[i]);
            i++;
            _inorder(p->getRight(), vett, i);
        }
    }

    void postOrder(Nodo<H>* x)
    {   
        if (x)
        {
            postOrder(x->getLeft());
            postOrder(x->getRight());
            cout << x->getValore() << " ";
        }
    }

    int _foglie(Nodo<H>* p)
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
                return ( _foglie( p->getLeft() ) + _foglie( p->getRight() ) );
            }
        }
    }

    int calcolaAltezza(Nodo<H>* x)  //l'altezza di un albero e la distanza dalla radice al nodo piu lontano
    {
		if(!x) return -1;//se il nodo e' nullo ritorniamo -1 perche' dobbiamo compensare la chiamata extra
		int s=calcolaAltezza(x->getLeft());//calcoliamo l'altezza del sottoalbero sinistro
		int d=calcolaAltezza(x->getRight());//calcoliamo l'altezza del sottoalbero destro
			
    	if(s>d) return 1+s;//ritorniamo il valore del sottoalbero piu' profondo +1 che sarebbe il nodo attuale
		else return 1+d;
	}

public:
    Tree() {root = NULL; peso = 0;valore_nodo = 0;}

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

    Nodo<H>* maximum(Nodo<H>* val)
    {
        Nodo<H>* max = val;
        while (max->getRight() != NULL)
        {
            max = max->getRight();
        }
        return max;
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

    Nodo<H>* successor(H v)
    {
        Nodo<H>* iter = find(v);
        
        if (iter)
        {
            Nodo<H>* y;
            if (iter->getRight() != NULL)
            {
                y = minimum(iter->getRight());
            }
            else 
            {//altrimenti se il nodo non ha figli destri
                while ( (iter->getPadre() != NULL) && (iter->getPadre()->getRight() == iter) )
                {
                    iter = iter->getPadre();
                }
                y = iter->getPadre();
            }
            return y;
        }
    }

    Nodo<H>* predecessor(H v)
    {
        Nodo<H>* iter = find(v);
        
        if (iter)
        {
            Nodo<H>* y;
            if (iter->getLeft() != NULL)
            {
                y = maximum(iter->getLeft());
            }
            else 
            {//altrimenti se il nodo non ha figli destri
                while ( (iter->getPadre() != NULL) && (iter->getPadre()->getLeft() == iter) )
                {
                    iter = iter->getPadre();
                }
                y = iter->getPadre();
            }
            return y;
        }
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

    int foglie()
    {
        return _foglie(root);
    } 

    void natural_Fill(H* vett, int& i)
    {
        _inorder(root, vett, i);
    }

    int altezza()
    {
		return calcolaAltezza(root);
	}

    void visita_preOrder()
    {
        preOrder(root);
    }

    void visita_inOrder()
    {
        inOrder(root);
    }

    void visita_postOrder()
    {
        postOrder(root);
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
            Tree<int>* al = new Tree<int>();

            for (int i = 0; i < dim; i++)
            {
                string general; in >> general;
                string operation = getOp(general);
                string valore_tmp = getVal(general);
                int valore = stoi(valore_tmp);

                if (operation == "ins")
                {
                    al->ins(valore);
                }
                else if (operation == "canc")
                {   
                    Nodo<int>* el = al->find(valore);
                    al->canc(el);
                    delete el;
                }
            }
            int k; in >> k;
            cout << "bil\n";
            cout << al->bilanciamento(k) << endl;
            cout << "fine bil\n";

            delete al;
        }
        else if (tipo == "double")
        {
            Tree<double>* al = new Tree<double>();

            for (int i = 0; i < dim; i++)
            {
                string general; in >> general;
                string operation = getOp(general);
                string valore_tmp = getVal(general);
                double valore = stod(valore_tmp);

                if (operation == "ins")
                {
                    al->ins(valore);
                }
                else if (operation == "canc")
                {   
                    Nodo<double>* el = al->find(valore);
                     al->canc(el);
                    delete el;
                }
            }
            int k; in >> k;
            cout << "bil\n";
            out << al->bilanciamento(k) << endl;
            cout << "fine bil\n";

            delete al;
        }
    }

    return 0;
}
