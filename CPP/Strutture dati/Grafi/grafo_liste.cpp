#include<iostream>
using namespace std;

#define W 0
#define G 1
#define B 2

template<class H>
class Nodo
{
private:
    H valore;
    Nodo<H>* succ;

public:
    Nodo(H val) :valore(val){succ = NULL;}

    Nodo<H>* getSucc() {return succ;}
    H getValore() {return valore;}

    void setSucc(Nodo<H>* zx) {succ = zx;}
    void setValore(H z) {valore = z;}
};

template<class H>
class Lista
{
private:
    Nodo<H>* testa;

public:
    Lista() {testa = NULL;}

    Nodo<H>* getTesta() {return testa;}

    void ins(H val)
    {
        Nodo<H>* nuovo = new Nodo<H>(val);
        nuovo->setSucc(getTesta());
        testa = nuovo;
    }

    Nodo<H>* search(H val)
    {   
        Nodo<H>* p;
        for (p = getTesta(); p != NULL; p = p->getSucc())
        {
            if (p->getValore() == val)
            {
                return p;
            }
        }
        return NULL;
    }

    void print()
    {
        Nodo<H>* iter = getTesta();
        while (iter != NULL)
        {
            cout << " " << iter->getValore() << "\t";
            iter = iter->getSucc();
        }
        
    }
};


template<class H>
class LGraph
{
private:
    int archi, nodi, max_nodi;
    H** matrix_index;
    Lista<int>** Adj;

    int* color;
    int* pred;
    int* dist;

    int* in;
    int* out;
    int time;

    int findIndex(H val)
    {
        for (int i = 0; i < nodi; i++)
        {
            if (*matrix_index[i] == val)
            {
                return i;
            }
        }
        return -1;
    }

    void DFS_Visit(H u)
    {
        color[u] = G;
        in[u] = time++;
        for (int i = 0; i < nodi; i++)
        {
            if (color[i] == W)
            {
                pred[i] = u;
                DFS_Visit(i);
            }
        }
        color[u] = B;
        out[u] = time++;
    }

public:
    LGraph(int dim)
    {
        max_nodi = dim;
        nodi = archi = 0;

        matrix_index = new H*[dim];
        Adj = new Lista<int>*[dim];

        for (int i = 0; i < dim; i++)
        {
            matrix_index[i] = NULL;
            Adj[i] = new Lista<int>();    
        }

        color = new int[dim];
        pred = new int[dim];
        dist = new int[dim];

        in = new int[dim];
        out = new int[dim];
        time = 0;
    }

    LGraph<H>* addNode(H n)
    {
        if (nodi < max_nodi && findIndex(n) == -1)
        {
            matrix_index[nodi] = new H(n);
            nodi++;
        }
        return this;
    }

    LGraph<H>* addEdge(H x, H y)
    {
        int i = findIndex(x);
        int j = findIndex(y);

        if ( (i != -1 && j != -1) && (!Adj[i]->search(j)) )
        {
            Adj[i]->ins(j);
            archi++;
        }
        return this;
    }

    void print()
    {
        for (int i = 0; i < nodi; i++)
        {
            cout << *matrix_index[i] << ": ";
            Adj[i]->print();
            cout << endl;
        }
    }

    void DFS() 
    {
        for (int i = 0; i < nodi; i++)
        {
            color[i] = W;
            pred[i] = -1;
        }
        time = 0;
        for (int i = 0; i < nodi; i++)
        {
            if (color[i] == W)
            {
                DFS_Visit(i);
            }
        }
    }

};


int main(int argc, char const *argv[])
{
    LGraph<char> *Gr = new LGraph<char>(9);
	Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
	Gr->addNode('8');
	
	Gr->addEdge('0','8')->addEdge('0','1');
	Gr->addEdge('1','8');
	Gr->addEdge('2','4');
	Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0');
	Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();



    return 0;
}
