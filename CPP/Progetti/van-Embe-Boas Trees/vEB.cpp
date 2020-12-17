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
        cluster = nullptr
    }
    else if (size > 2)
    {
        /*
        *   se la dimensione è maggiore di 2
        *   il summary e il cluster avranno dimensione 
        *   pari al ceil della radice quadrata di size.
        */

        int num_cluster = ceil(sqrt(size))

        //ogni indice del summary avrà a sua volta un van_Emde_Boas
        summary = new van_Emde_Boas*(num_cluster);

        //ogni indice del cluster avrà a sua volta un van_Emde_Boas
        cluster = new van_Emde_Boas*(num_cluster);
        
        //assegniamo a tutti i cluster la dimensione della radice quadrata di size
        for (int i = 0; i < num_cluster; i++)
        {
            cluster[i] = new van_Emde_Boas(num_cluster);
        }
    }
}

