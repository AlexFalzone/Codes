#include<cmath>
#include<vector>
using namespace std;

class van_Emde_Boas
{
private:
    int universe;
    int min;
    int max;

    vector<van_Emde_Boas*> cluster;
    van_Emde_Boas* summary;


    //ritorna il numero di cluster di x
    int high(int x)
    {
        int lower_square = pow(2, floor(log2(universe)/2));
        return floor(x / lower_square);
    }

    //ritorna la posizione di x all'interno del suo cluster
    int low(int x)
    {
        int lower_square = pow(2, floor(log2(universe)/2));
        return (x % lower_square);
    }

    /*
    *   ritorna l'indice del numero e posizione del cluster
    *   prendendo in input un cluster (x) e una posizione (y)
    */
    int index(int x, int y)
    {
        int lower_square = pow(2, floor(log2(universe)/2));
        return ( (x*lower_square) + y);
    }

    bool isMember(van_Emde_Boas* V, int x)
    {
        /*
        *   se x è uguale al massimo o al minimo
        *   ritorniamo true.
        */
        if ( (x == V->min) || (x == V->max) ) 
        {
            return true;
        }
        /*
        *   Se la dimensione dell'universo è 2
        *   ed abbiamo saltato il primo caso, allora 
        *   x non sarà nè il min nè il max.
        *   Quindi torniamo false.
        */
        else if (V->universe == 2)
        {
            return false;
        }
        //  Cerchiamo ricorsivamente x nei nostri casi base.
        else
        {
            return isMember(V->cluster[V->high(x)], V->low(x));
        }
    }

    /*
    *   se l'albero è vuoto inseriamo il nostro 
    *   elemento (x) come minimo e massimo 
    *   del cluster padre
    */
    void empty_insert(van_Emde_Boas* V, int x)
    {
        V->min = V->max = x;
    }

    void swap(int &a, int&b)
    {
        int aux = a;
        a = b;
        b = aux;
    }

public:
    //costruttore
    van_Emde_Boas(int size);

    int minimum(van_Emde_Boas* V);

    int maximum(van_Emde_Boas* V);

    int successor(van_Emde_Boas* V, int x);

    int predecessor(van_Emde_Boas* V, int x);

    void insert(van_Emde_Boas* V, int x);

};  
