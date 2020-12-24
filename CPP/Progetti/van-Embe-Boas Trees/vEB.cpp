#include "vEB.h"
#include<iostream>
using namespace std;

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
        cluster = vector<van_Emde_Boas*>(num_cluster, nullptr);
        
        //assegniamo a tutti i cluster la dimensione della radice quadrata di size
        for (int i = 0; i < num_cluster; i++)
        {
            cluster[i] = new van_Emde_Boas(num_cluster);
        }
    }
}

int van_Emde_Boas::maximum(van_Emde_Boas* V)
{
    return V->max;
}

int van_Emde_Boas::minimum(van_Emde_Boas* V)
{
    return V->min;
}

bool van_Emde_Boas::isMember(van_Emde_Boas* V, int x)
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

int van_Emde_Boas::successor(van_Emde_Boas* V, int x)
    {   
        if (V->universe == 2)
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
    if (V->universe == 2)
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
                return 0;
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

void van_Emde_Boas::insert(van_Emde_Boas* V, int x)
{   
    //Se non esiste il minimo, allora l'albero è vuoto.
    if (V->min == -1)
    {
        //Di conseguenza inseriamo la chiave come min e max.
        empty_insert(V, x);
    }
    else 
    {   
        if (x < V->min)
        {
            /*
            *   Se la chiave da inserire è minore
            *   del minimo, scambiamo entrambi.
            *   Di conseguenza indicheremo con x il minimo
            *   originale (quello che andremo a sistemare
            *   nel cluster appropriato) e con V->min la chiave
            *   originale posizionata come min
            */
            swap(V->min, x);
        }
        if (V->universe > 2)
        {   
            //Determianiamo se il cluster dove andrà x è vuoto.
            if (minimum(V->cluster[V->high(x)]) == -1)
            {   
                /*
                *   Se il cluster è vuoto, inseriamo il
                *   numero di cluster di x nel summary.
                */
                insert(V->summary, V->high(x));

                //e inseriamo, nel cluster vuoto, x.
                empty_insert(V->cluster[V->high(x)], V->low(x));
            }
            else
            {   
                /*
                *   se il cluster non è vuoto, inseriamo x 
                *   nel cluster appropriato.
                */
                insert(V->cluster[V->high(x)], V->low(x));
            }
        }

        if (x > V->max)
        {
            V->max = x;
        }
    }
    
}

void van_Emde_Boas::canc(van_Emde_Boas* V, int x)
{   
    /*
    *   Se l'albero (o un determinato cluster) ha una sola chiave
    *   essa sarà quella che vogliamo eliminare,
    *   di conseguenza settiamo min e max a -1.
    */
    if (V->min == V->max)
    {   
        V->max = V->min = -1;
    }

    /*
    *   Se l'albero (o un determinato cluster) ha dimensione 2 
    *   ma piu' chiavi (infatti abbiamo saltato il primo if).
    */
    else if (V->universe == 2)
    {   
        //Se la chiave da eliminare ha indice 0.
        if (x == 0)
        {
            //Allora settiamo il minimo al successore di x.
            V->min = 1;
        }
        else
        {
            //In questo caso la chiave da eliminare è 1.
            V->min = 0;
        }

        /*
        *   Settiamo min = max perchè adesso l'albero 
        *   (o un determinato cluster) avrà un solo elemento.
        */
        V->max = V->min;
    }
    //Abbiamo due o piu' elementi.
    else 
    {   
        //Se l'elemento da cancellare è il minimo di un cluster.
        if (x == V->min)
        {   
            /*
            *   Troviamo il numero del cluster che contiene
            *   il piu' piccolo elemento diverso da min .
            */
            int first_cluster = minimum(V->summary);

            //Impostiamo x al piu' piccolo elemento di tale cluster.
            x = V->index(first_cluster, minimum(V->cluster[first_cluster]));

            V->min = x;
        }

        /*
        *   Cancelliamo x, sia che x sia il valore
        *   originariamente passato sia che x sia l'elemento
        *   che deve diventare il nuovo minimo.
        */
        canc(V->cluster[V->high(x)], V->low(x));

        //Dopo l'eliminazione di x il suo cluster potrebbe essere vuoto.
        if (minimum(V->cluster[V->high(x)]) == -1)
        {   
            //Se lo è eliminiamo il numero di cluster dal summary.
            canc(V->summary, V->high(x));

            //Se stiamo eliminando l'elemento massimo.
            if (x == V->max)
            {   
                /*
                *   Impostiamo summary_max al numero
                *   del cluster non vuoto con il numero 
                *   piu' grande.
                */
                int summary_max = maximum(V->summary);

                //Se tutti i cluster sono vuoti.
                if (summary_max == -1)
                {   
                    /*
                    *   L'unico elemento sarà min.
                    *   Di conseguenza diverrà anche 
                    *   il max.
                    */
                    V->max = V->min;
                }
                else
                {   
                    /*
                    *   Altrimenti impostiamo max al massimo elemento
                    *   nel cluster con il numero piu' grande.
                    */
                    V->max = V->index(summary_max, maximum(V->cluster[summary_max]));
                }
            }
        }
        /*
        *   Se il cluster (dopo l'eliminazione di x)
        *   non è vuoto potrebbe essere necessario
        *   aggiornare max. Nel caso l'aggiorna prendendo
        *   il massimo dal cluster appropriato.
        */
        else if (x == V->max)
        {   
            V->max = V->index(V->high(x), maximum(V->cluster[V->high(x)]));
        }
    }
    
}


int main(int argc, char const *argv[])
{   
    van_Emde_Boas* prova = new van_Emde_Boas(100);
    
    prova->insert(prova, 1);
    prova->insert(prova, 2);
    prova->insert(prova, 3);
    prova->insert(prova, 4);
    prova->insert(prova, 5);
    prova->insert(prova, 6);
    prova->insert(prova, 7);
    prova->insert(prova, 8);
    prova->insert(prova, 9);
    prova->insert(prova, 10);


    cout << "\nPrima dell'eliminazione" << endl;
    cout << "masssimo = " << prova->maximum(prova) << endl;
    cout << "minimo = " << prova->minimum(prova) << endl;
    cout << "Successore di 8 = " << prova->successor(prova, 8) << endl;
    cout << "Predecessore di 8 = " << prova->predecessor(prova, 8) << endl;

    prova->canc(prova, 9);
    prova->canc(prova, 7);
    prova->canc(prova, 10);

    cout << "\nDopo dell'eliminazione" << endl;
    cout << "masssimo = " << prova->maximum(prova) << endl;
    cout << "minimo = " << prova->minimum(prova) << endl;
    cout << "Successore di 8 = " << prova->successor(prova, 8) << endl;
    cout << "Predecessore di 8 = " << prova->predecessor(prova, 8) << endl;

    return 0;
}