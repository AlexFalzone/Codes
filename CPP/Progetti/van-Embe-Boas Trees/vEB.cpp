#include "vEB.h"
#include<iostream>

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
        cluster = vector<van_Emde_Boas*>(num_cluster);
        
        //assegniamo a tutti i cluster la dimensione della radice quadrata di size
        for (int i = 0; i < num_cluster; i++)
        {
            cluster[i] = new van_Emde_Boas(num_cluster);
        }
    }
}


int van_Emde_Boas::successor(van_Emde_Boas* V, int x)
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
            if ( (x == 0) && (V->max == 1) )
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
        else if ( (V->min != -1) && (x < V->min) )
        {
            return V->min;
        }
        else
        {
            //assegnaimo a max_low l'elemento massimo del cluster di x
            int max_low = maximum(V->cluster[V->high(x)]);

            //se il successore (max_low) di x è all'interno del cluster di x
            if ( (max_low != -1) && (V->low(x) < max_low) )
            {
                //determiniamo il successore di x
                int offset = successor(V->cluster[V->high(x)], V->low(x));

                //ritorniamo il successore di x
                return V->index(V->high(x), offset);
            }
            else
            {   
                /*
                *   In questo caso x sarà maggiore o uguale 
                *   al massimo del suo cluster, di conseguenza
                *   dobbiamo trovare il minimo del cluster successivo
                */

                //troviamo il cluster successivo
                int succ_cluster = successor(V->summary, V->high(x));

                //se non esiste il cluster successivo, torno -1
                if (succ_cluster == -1)
                {
                    return -1;
                }
                else
                {
                    //altrimenti cerco il minimo del cluster successivo
                    int offset = minimum(V->cluster[succ_cluster]);
                    return V->index(succ_cluster, offset);
                }   
            }   
        }
    }

int van_Emde_Boas::predecessor(van_Emde_Boas* V, int x)
{
    if (universe == 2)
        {   
            /*
            *   se la dimensione è 2 e la chiave, di cui
            *   dobbiamo trovare il predecessore, è uguale a 1
            *   e il minimo di quel cluster è uguale a 0
            *   allora avremo che il predecessore della chiave
            *   sarà proprio 0, ovvero min.
            */
            if ( (x == 1) && (V->min == 0) )
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        /*
        *   se il massimo del cluster esiste 
        *   ed è minore della nostra chiave
        *   allora ritorniamo il massimo del 
        *   cluster, ovvero il predecessore di x. 
        */
        else if ( (V->max != -1) && (x > V->max) )
        {
            return V->max;
        }
        else
        {
            //assegnaimo a min_low l'elemento minimo del cluster di x
            int min_low = minimum(V->cluster[V->high(x)]);

            //se il predecessore (min_low) di x è all'interno del cluster di x
            if ( (min_low != -1) && (V->low(x) > min_low) )
            {
                //determiniamo il predecessore di x
                int offset = predecessor(V->cluster[V->high(x)], V->low(x));

                //ritorniamo il predecessore di x
                return V->index(V->high(x), offset);
            }
            else
            {   
                /*
                *   In questo caso x sarà minore o uguale 
                *   al minimo del suo cluster, di conseguenza
                *   dobbiamo trovare il massimo del cluster precedente
                */

                //troviamo il cluster successivo
                int pred_cluster = predecessor(V->summary, V->high(x));

                //se non esiste il cluster precedente, torno -1
                if (pred_cluster == -1)
                {   
                    /*
                    *   Il predecessore di x, se esiste,
                    *   non si trova nel cluster di x.
                    *   Ma se il predecessore di x è il valore
                    *   minimo nell'albero, allora il predecessore
                    *   non si trova in alcun cluster     
                    */

                    if ( (V->min != -1) && (x > V->min) )
                    {
                        return V->min;
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    //altrimenti cerco il minimo del cluster successivo
                    int offset = maximum(V->cluster[pred_cluster]);
                    return V->index(pred_cluster, offset);
                }   
            }   
        }
}   







int main(int argc, char const *argv[])
{
    van_Emde_Boas* prova = new van_Emde_Boas(10);

    std::cout << prova->maximum(prova) << std::endl;

    return 0;
}
