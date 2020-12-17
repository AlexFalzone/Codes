#include "vEB.h"

//costruttore
van_Emde_Boas::van_Emde_Boas(int size)
{
    universe = size;
    min = max = -1;

    if (size == 2)
    {   
        /*
        *   se la dimensione dell'albero è uguale a 2
        *   allora non avremo nessun summary e il 
        *   cluster non avrà altri elementi se non min e max
        */
        summary = nullptr;
        cluster = vector<van_Emde_Boas*>(0, nullptr);
    }
    else if (size > 2)
    {
        /*
        *   se la dimensione è maggiore di 2
        *   il summary e il cluster avranno dimensione 
        *   pari al ceil della radice quadrata di size.
        */

        int num_cluster = ceil(sqrt(size));

        //ogni indice del summary avrà a sua volta un van_Emde_Boas
        summary = new van_Emde_Boas(num_cluster);

        //ogni indice del cluster avrà a sua volta un van_Emde_Boas
        cluster = new vector<van_Emde_Boas*>(num_cluster);
        
        //assegniamo a tutti i cluster la dimensione della radice quadrata di size
        for (int i = 0; i < num_cluster; i++)
        {
            cluster[i] = new van_Emde_Boas(num_cluster);
        }
    }
}

int van_Emde_Boas::successor(int x)
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
        /*
        *   se il minimo del cluster esiste 
        *   ed è maggiore della nostra chiave
        *   allora ritorniamo il minimo del 
        *   cluster, ovvero il successore di x. 
        */
        else if ( (min != -1) && (x < min) )
        {
            return min;
        }
        else
        {
            //assegnaimo a max_low l'elemento massimo del cluster di x
            int max_low = maximum(cluster[high(x)]);

            //se il successore (max_low) di x è all'interno del cluster di x
            if ( (max_low != -1) && (low(x) < max_low) )
            {
                //determiniamo il successore di x
                int offset = successor(cluster[high(x)], low(x));

                //ritorniamo il successore di x
                return index(high(x), offset);
            }
            else
            {   
                /*
                *   In questo caso x sarà maggiore o uguale 
                *   al massimo del suo cluster, di conseguenza
                *   dobbiamo trovare il minimo del cluster successivo
                */

                //troviamo il cluster successivo
                int succ_cluster = successor(summary, high(x));

                //se non esiste il cluster successivo, torno -1
                if (succ_cluster == -1)
                {
                    return -1;
                }
                else
                {
                    //altrimenti cerco il minimo del cluster successivo
                    int offset = minimum(cluster[succ_cluster]);
                    return index(succ_cluster, offset);
                }   
            }   
        }
    }