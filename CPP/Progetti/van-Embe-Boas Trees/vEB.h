#include<cmath>
class van_Emde_Boas
{
private:
    int universe;
    int min;
    int max;

    van_Emde_Boas* cluster;
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

    //ritorna l'indice dal numero e posizione del cluster
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
    void empty_insert(int x)
    {
        min = max = x;
    }


public:
    van_Emde_Boas(int size);

    int minimum()
    {
        return min;
    }

    int maximum()
    {
        return max;
    }


    int successor(int x)
    {   
        if (universe == 2)
        {   
            /*
            *   se la dimensione è 2 e la chiave, di cui
            *   dobbiamo trovare il successore, è uguale a 0
            *   e il massimo di quel cluster è uguale a 1
            *   allora avremo che il successore della chiave
            *   sarà proprio 1, ovvero max.
            */
            if ( (x == 0) && (max == 1) )
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else if ( (min != -1) && (x < min) )
        {
            return min;
        }
        else
        {
            
        }
        
    }


};
