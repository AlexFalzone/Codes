#include<cmath>
using namespace std;

class vEB
{
private:
    int universe;
    int min;
    int max;

    vEB* cluster;
    vEB* summary;

    /*ritorna i (ln(u)/2) bit piu significativi di x
      che rappresentano il numero di cluster di x
    */
    int high(int x)
    {
        int lower_sqrt = pow( 2, floor(log2(universe) / 2) );
        return floor(x / lower_sqrt);
    }

    /*ritorna i (ln(u)/2) bit meno significativi di x
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
    vEB(); //costruttore
    
    ~vEB(); //distruttore

};



int main(int argc, char const *argv[])
{
    
    return 0;
}
