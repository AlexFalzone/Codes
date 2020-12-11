#include<cmath>
#include<vector>
using namespace std;

class vEB
{
private:
    int universe;
    int min;
    int max;

    vector<vEB*> cluster;
    vEB* summary;

    /*
      ritorna i (ln(u)/2) bit piu significativi di x
      che rappresentano il numero di cluster di x
    */
    int high(int x)
    {
        int lower_sqrt = pow( 2, floor(log2(universe) / 2) );
        return floor(x / lower_sqrt);
    }

    /*
      ritorna i (ln(u)/2) bit meno significativi di x
      che rappresentano la posizione di x all'interno del suo cluster
    */
    int low(int y)
    {
        int lower_sqrt = pow( 2, floor(log2(universe) / 2) );
        return y % lower_sqrt;
    }

    //costruisce il numero dell'elemento da a x a y
    int index(int x, int y)
    {
        int lower_sqrt = pow( 2, floor(log2(universe) / 2) );
        return x*lower_sqrt + x;
    }

    int minimum(vEB* V)
    {
        return V->min;
    }

    int maximum(vEB* V)
    {
        return V->max;
    }

public:
    //costruttore
    vEB(int size_universe); 
    
    //distruttore
    ~vEB(); 

    bool isMember(vEB* V, int val);

    /*
      Trova il successore.
      Esso puo trovarsi o nello stesso cluster di val o nel cluster successivo. 
    */
    int successor(vEB* V, int val);

    /*
      Trova il predecessore.
      Esso puo trovarsi o nello stesso cluster di val o nel cluster precedente. 
    */
    int predecessor(vEB* V, int val);

};



