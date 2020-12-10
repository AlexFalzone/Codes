#include<iostream>
using namespace std;

#define W 0
#define G 1
#define B 2
#define inf 99999999

class Coda
{
private:
    int* arr; 
    int testa;
    int fine;
    int dim;

public:
    Coda(int dim)
    {
        this->dim = dim;
        testa = fine = -1;
        arr = new int[dim];
    }

    bool codaPiena() 
    {
        return (fine+1)%dim == testa;
    }  

    bool codaVuota()
    {
        return (testa == -1);
    }

    void enqueue(int val)
    {
        if (!codaPiena())
        {
            fine = (fine+1)%dim;
            arr[fine] = val;
            if (testa == -1)
            {
                testa = 0;
            }
        }
    }

    int dequeue()
    {
        if (!codaVuota())
        {
            int x = arr[testa];
            if (testa == fine)
            {
                testa = fine = -1;
            }
            else
            {
                testa = (testa+1)%dim;
            }
            return x;
        }
        return -1;
    }

};

template<class H>
class MGraph
{
private:
    int archi, nodi, max_nodi;
    int current_root;
    int** M; //matrice adiacenza
    H** matrix; //matrice indici

    int* color;
    int* pred;
    int* dist;
    int* rad;

    int* in;
    int* out;
    int time;


    int findIndex(H val)
    {
        for (int i = 0; i < nodi; i++)
        {
            if (*matrix[i] == val)
            {
                return i;
            }
        }
        return -1;
    }

    void _bfs(int v)
    {
        for (int i = 0; i < nodi; i++)
        {
            color[i] = W;
            dist[i] = inf;
            pred[i] = -1;
        }
        color[v] = G;
        dist[v] = 0;
        pred[v] = -1;
        Coda* coda = new Coda(nodi);
        coda->enqueue(v);
        while (!coda->codaVuota())
        {
            int x = coda->dequeue();
            for (int i = 0; i < nodi; i++)
            {
                if (M[x][i] == 1 && color[i] == W)
                {
                    color[i] = G;
                    dist[i] = dist[x] +1;
                    pred[i] = x;
                    coda->enqueue(i);
                }
            }
            color[x] = B;
        }
        for(int i=0; i<nodi; i++) 
        {
			cout << "[" << i << "]->";
			if(dist[i]==inf) cout << "inf." << endl;
			else cout << dist[i] << endl;
		}
		cout << endl;
    }

    int DFS_Visit(int v)
    {
        color[v] = G;
        in[v] = time++;
        rad[v] = current_root;
        int cycle = 0;
        for (int i = 0; i < nodi; i++)
        {
            if (M[v][i] == 1)
            {
                if (color[i] == W)
                {
                    pred[i] = v;
                    cycle |= DFS_Visit(i);
                }
                if (color[i] == G)
                {
                    cycle = 1;
                }
            }
        }
        color[v] = B;
        out[v] = time++;
        return cycle;
    }

    void sort(int *a, int n, int *k) {
			for(int i=1; i<n; i++) {
				int j = i-1;
				while(j>=0 && k[a[j+1]]>k[a[j]]) {
					int t = a[j+1];
					a[j+1] = a[j];
					a[j] = t;
					j--;
				}
			}
		}

    /*void _printPath(int x)
    {
        if (x == -1)
        {
            return;
        }
        if (pred[x] == -1)
        {
            cout << *matrix[x] << " ";
        }
        else 
        {
			_printPath(pred[x]);
			cout << "->" << *matrix[x] << " "; 
		}
    }*/

public:
    MGraph(int dim)
    {
        max_nodi = dim;
        archi = nodi = 0;
        M = new int*[dim];
        matrix = new H*[dim];

        for (int i = 0; i < dim; i++)
        {
            matrix[i] = NULL;
            M[i] = new int[dim];
            for (int j = 0; j < dim; j++)
            {
                M[i][j] = 0;
            }
        }

        color = new int[dim];
        pred = new int[dim];
        dist = new int[dim];
        rad = new int[dim];

        in = new int[dim];
        out = new int[dim];
    }

    MGraph<H>* addNode(H val)
    {
        int x = findIndex(val);
        if ( (nodi < max_nodi) && (x == -1) )
        {
            matrix[nodi] = new H(val);
            nodi++;
        }
        return this;
    }

    MGraph<H>* addEdge(H u, H v)
    {
        int i = findIndex(u);
        int j = findIndex(v);
        if (i != -1 && j != -1 && M[i][j] == 0)
        {
            M[i][j] = 1;
            archi++;
        }
        return this;
    }

    void print()
    {
        for (int i = 0; i < nodi; i++)
        {
            cout << *matrix[i] << " : ";
            for (int j = 0; j < nodi; j++)
            {
                if (M[i][j])
                {
                    cout << *matrix[j] << "\t";
                }
            }
            cout << endl;
        }
    }

    void BFS(H val)
    {
        int i = findIndex(val);
        if (i != -1)
        {
            _bfs(i);
        }
    }

    /*void printPath(H val)
    {
        int i=findIndex(val);
		if (i>=0)
        {
            _printPath(i);
		}
		cout << endl;
    }*/
    
    int DFS()
    {
        for (int i = 0; i < nodi; i++)
        {
            color[i] = W;
            pred[i] = -1;
            rad[i] = 0;
        }
        time = 0;
        int cycle = 0;
        for (int i = 0; i < nodi; i++)
        {
            if (color[i] == W)
            {   
                current_root = i;
                cycle |= DFS_Visit(i);
            } 
        }
        for (int i = 0; i < nodi; i++)
        {
            cout << "(" << *matrix[i] << "," << in[i] << "," << out[i] << ")" << endl; 
        }
        return cycle;
    }

    void topSort()
    {
        int cycle = DFS();
        if (cycle)
        {
            cout << "Il grafo contiene un ciclo\n";
            return;
        }
        int* s = new int[nodi];
        for (int i = 0; i < nodi; i++)
        {
            s[i] = i;
            sort(s,nodi,out);
        }
        for (int i = 0; i < nodi; i++)
        {
            cout << "(" << in[i] << ", " << out[i] << ") ";
        }
        cout << endl;
    }
};

//Da aggiungere:
//scc


//Aggiunti:
//nodi
//archi
//stampa
//bfs
//printpath
//dfs
//top-sort



