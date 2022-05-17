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
class BST
{
private:
    Nodo<H>* radice;
    int livello;
    H peso;

    void preOrder(Nodo<H>* p)
    {   
        if (p)
        {
            cout << p->getValore() << " ";
            preOrder(p->getLeft());
            preOrder(p->getRight());
        }
    }

    void inOrder(Nodo<H>* p)
    {
        if (p)
        {
            inOrder(p->getLeft());
            cout << p->getValore() << " ";
            inOrder(p->getRight());
        }
    }
    
    void Inorder(Nodo<H>* p, H* vett, int& i)
    {
        if (p)
        {
            Inorder(p->getLeft(), vett, i);
            p->setValore(vett[i]);
            i++;
            Inorder(p->getRight(), vett, i);
        }
    }

    void postOrder(Nodo<H>*  p)
    {
        if (p)
        {
            postOrder(p->getLeft());
            postOrder(p->getRight());
            cout << p->getValore() << " ";   
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

public:
    BST() {radice = NULL, livello = 0, peso = 0;}

    void insert(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->getLeft() = nuovo->getRight() = NULL;
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
        if (y==NULL)
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

    Nodo<H>* Massimo(Nodo<H>* z)
    {
        Nodo<H>* max = z;
        while (max->getRight() != NULL)
        {
            max = max->getRight();
        }
        return max;
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
            Trapianta(z,z->getRight());
        }
        else if (z->getRight() == NULL)
        {
            Trapianta(z,z->getLeft());
        }
        else
        {
            y = Minimo(z->getRight());
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

    void visitaPreOrder() {preOrder(radice);}
    void visitaInOrder() {inOrder(radice);}
    void visitaPostOrder() {postOrder(radice);}

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

    int profondita(H val)    //e' la distanza da un nodo alla radice, ovvero la sua altezza sostanzialmente
    {                                   
		Nodo<H>* tmp=search(val);
		if(tmp)
        {
			int x=0;
			while(tmp->getPadre() != NULL)
            {
				tmp=tmp->getPadre();
				x++;
			}
			return x;
		}
		return -1;
    }

    int altezza()
    {
		return calcolaAltezza(radice);
	}

    Nodo<H>* successore(H v)
    {   
        Nodo<H>* val = search(v);
        if (val->getRight() != NULL)
        {
            return Minimo(val->getRight());
        }
        Nodo<H>* y = val->getPadre();
        while ((y->getRight() != NULL) && (val == y->getRight()))
        {
            val = y;
            y = y->getPadre();
        }
        return y;
    }

    Nodo<H>* predecessore(H v)
    {
        Nodo<H>* val = search(v);
        if (val->getLeft() != NULL)
        {
            return Massimo(val->getLeft());
        }
        Nodo<H>* y = val->getPadre();
        while ((y->getLeft() != NULL) && (val == y->getLeft()))
        {
            val = y;
            y = y->getPadre();
        }
        return y;
    }

    int livello_chiave(H val)
    {   
        Nodo<H>* iter = radice;
        livello = 0;
        while ( (iter != NULL) && (val != iter->getValore()) )
        {
            if (val < iter->getValore())
            {
                iter = iter->getLeft();
                livello += 1;
            }
            else
            {
                iter = iter->getRight();
                livello += 1;
            }
        }
        return livello;
    }

    void Natural_Fill(H* vett, int &i)
    {
        Inorder(radice, vett, i);
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

    int getFoglie() {return foglie(radice);}

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
    int i = 0;
    int vett[] = {8, 13, 14, 18, 22, 27, 32, 35, 36, 41};
    BST<int>* tree = new BST<int>();
    tree->insert(291);tree->insert(210);tree->insert(158);tree->insert(11);tree->insert(44);tree->insert(34);tree->insert(25);tree->insert(118);tree->insert(167);tree->insert(189);
    tree->Natural_Fill(vett, i);
    tree->visitaInOrder();
    
    

    return 0;
}
