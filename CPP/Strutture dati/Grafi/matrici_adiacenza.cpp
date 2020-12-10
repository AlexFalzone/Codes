#include<iostream>

using namespace std;


template<class H>
class MGraph
{
private:
    int len, n, m;
    /* 	n numero di nodi effettivo, 
		m numero di archi effettivo, 
		len numero massimo di nodi
	*/
    H** k;
    int** M;

    int findIndex(H x)
    {
        for (int i = 0; i < n; i++)
        {
            if (*k[i] == x) 
            {
                return i;
            }
        }
        return -1;
    }

public:
    MGraph(int len)
    {
        this->len = len;
        n = m = 0;
        k = new H*[len];

        for (int i = 0; i < len; i++)
        {
            k[i] = NULL;
        }
        M = new int*[len];
        for (int i = 0; i < len; i++)
        {
            M[i] = new int[len];
            for (int j = 0; j < len; j++)
            {
                M[i][j] = 0;
            }
        }
    }

    MGraph<H>* addNode(H in)
    {
        if (n == len)
        {  
            return this;
        }
        if (findIndex(in) >= 0)
        {
            return this;
        }
        k[n] = new H(in);
        n++;
        return this;
    }

    MGraph<H>* addEdge(H x, H y)
    {
        int i = findIndex(x);
        int j = findIndex(y);

        if ((i < 0) || (j < 0))
        {
            return this;
        }
        if (!M[i][j])
        {
            M[i][j] = 1;
            m++;
        }
        return this;
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            cout << "(" << i << ", " << *k[i] << ")" << " : ";
            for (int j = 0; j < n; j++)
            {
                if (M[i][j])
                {
                    cout << *k[j] << " ";
                }
            }
            cout << endl;
        } 
    }
    
}; 

int main(int argc, char const *argv[])
{
    MGraph<char> *Gr = new MGraph<char>(9);

    Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
    Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
    Gr->addNode('8');
   
    Gr->addEdge('0', '8')->addEdge('0','1');
    Gr->addEdge('1', '8');
    Gr->addEdge('2', '4');
    Gr->addEdge('3', '5')->addEdge('3', '6')->addEdge('3', '7');
    Gr->addEdge('4', '0')->addEdge('4', '3');
    Gr->addEdge('5','3')->addEdge('5', '6');
    Gr->addEdge('6', '5');
    Gr->addEdge('8', '2');

    Gr->print();

    return 0;
}

