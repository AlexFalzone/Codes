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

    bool isMember(van_Emde_Boas* V, int x);

    int successor(van_Emde_Boas* V, int x);

    int predecessor(van_Emde_Boas* V, int x);

    void insert(van_Emde_Boas* V, int x);

    //delete
    void canc(van_Emde_Boas* V, int x);
};  
