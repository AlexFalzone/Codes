#include "vEB.h"

//costruttore
vEB::vEB(int size_universe)
{
  universe = size_universe;

  //caso base
  if (size_universe <= 2)
  {
    /*settiamo summary a null perchè non ci sarà 
      nessuna summary per universe <= 2
    */
    summary = nullptr;

    cluster = vector<vEB*>(size_universe, nullptr);
  }
  else
  {   
    /*per (size_universe > 2) dobbiamo creare summary e 
      cluster di dimensione pari a sqrt(size_universe) fino a quando 
      saremo nel caso base
    */
    summary = new vEB(sqrt(size_universe));
    cluster = vector<vEB*>(sqrt(size_universe), nullptr);

    //in ogni cluster creiamo un albero vEB
    for (int i = 0; i < sqrt(size_universe); i++)
    {
      cluster[i] = new vEB(sqrt(size_universe));
    }
  }    
}

bool vEB::isMember(vEB* V, int val)
{   
  /*se l'elemento è uguale al massimo o al minimo
    ritorniamo direttamente true
  */
  if ( (val == V->min) || (val == V->max) )
  {
    return true;
  }
  /*
    se ci troviamo nel caso base con (universe = 2) 
    sappiamo che esso non avrà altri elementi se non 
    min e max, di conseguenza visto che abbiamo saltato
    la prima condizione, il determinato cluster non elementi,
    quindi torniamo false
  */
  else if (V->universe == 2)
  {
    return false;
  }
  /*
    essendo (val != min) && (val != max) && (universe > 2), occorre la ricorsione 
    per cercare all'interno del cluster appropriato
  */
  else
  {
    return isMember(V->cluster[V->high(val)], V->low(val));
  } 
}

int vEB::successor(vEB* V, int x)
{   
  /*
    se stiamo cercando il successore di 0, e 1 si 
    trova nell'insime di (universe = 2) allora
    possiamo tornare direttamente 1
  */
  if (V->universe == 2)
  {
    if ( (x == 0) && (V->max == 1) )
    {
      return 1;
    }
    else
    {
      return NIL;
    }
  }
  /*
    se x è strettamente minore dell'elemento minimo
    torniamo quest'ultimo
  */
  else if ( (V->min != NIL) && (x < V->min) )
  {
    return V->min;
  }
  /*
    x sarà maggiore o uguale al valore minimo dell'albero
  */
  else
  {   
    //assegniamo a max_low l'elemento massimo nel cluster di x
    int max_low = maximum(V->cluster[V->high(x)]);
        
    /*
      verifichiamo la condizione che se il cluster di x contiene 
      qualche elemento che è maggiore di x allora sappiamo 
      che il successore si troverà nel cluster di x.
    */
    if ( (max_low != NIL) && (low(x) < max_low) )
    {
      //determiniamo dove si trova il successore di x
      int offset = successor(V->cluster[V->high(x)], V->low(x));
      return index(high(x), offset);
    }
    else
    {   
      /*
        se x è maggiore o uguale all'elemento massimo del suo cluster
        allora troviamo il minimo del cluster successivo
      */
      int succ_cluster = successor(V->summary, V->high(x));
           
      if (succ_cluster == NIL)
      {
        return NIL;
      }
      else
      {
        int offset = minimum(V->cluster[succ_cluster]);
        return index(succ_cluster, offset);
      }
    }
  }
}

int vEB::predecessor(vEB* V, int x)
{
  /*
    se stiamo cercando il predecessore di 1, e 0 si 
    trova nell'insime di (universe = 2) allora
    possiamo tornare direttamente 0
  */
  if (V->universe == 2)
  {
    if ( (x == 1) && (V->max == 0) )
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }
  /*
    se x è strettamente maggiore dell'elemento massimo
    torniamo quest'ultimo
  */
  else if ( (V->max != NIL) && (x > V->max) )
  {
    return V->max;
  }
  /*
    x sarà minore o uguale al valore massimo dell'albero
  */
  else
  {   
    //assegniamo a max_low l'elemento massimo nel cluster di x
    int min_low = minimum(V->cluster[V->high(x)]);
        
  /*
    verifichiamo la condizione che se il cluster di x contiene 
    qualche elemento che è minore di x allora sappiamo 
    che il predecessore si troverà nel cluster di x.
    */
    if ( (min_low != NIL) && (low(x) > min_low) )
    {
      //determiniamo dove si trova il predecessore di x
      int offset = predecessor(V->cluster[V->high(x)], V->low(x));
      return index(high(x), offset);
    }
    else
    {   
      /*
        se x è il minimo dell'albero
        il predecessore non si troverà in nessun cluster
        */
        int pred_cluster = predecessor(V->summary, V->high(x));
          
      if (pred_cluster == NIL)
      {   
        if ( (V->min != NIL) && (x > V->min) )
        {
          return V->min;
        }
        else
        {
          return NIL;
        }
      }
      else
      {
        int offset = maximum(V->cluster[pred_cluster]);
        return index(pred_cluster, offset);
      }
    }
  }
}

void vEB::insert(vEB* V, int x)
{ 
  //se l'albero è vuoto 
  if (V->min == NIL)
  {
    /*
      richiamiamo empty_insert
      che aggiunge a min e a max
      il valore da inserire
    */
    empy_insert(V, x);
  }
  //se l'elemento da inserire è minore del minimo
  else if (x < V->min)
  {
    /*
      scambiamo x con min e di conseguenza
      nella nostra x troveremo il valore originale di min.
      Che andremo a posizionare nel cluster corretto
    */
    swap(x, V->min);
    
    if (V->universe > 2)
    {
      //se il cluster dove andra x (ovvero il min originale) è vuoto
      if ( minimum(V->cluster[V->high(x)]) == NIL )
      {
        //inseriamo il numero di cluster di x nel summary
        insert(V->summary, V->high(x));
        
        //inseriamo x (ovvero il min originale) in un cluster vuoto
        empy_insert(V->cluster[V->high(x)], low(x));
      }
      //se il cluster di x (ovvero il min originale) NON è vuoto
      else
      {
        /*
          inseriamo x nel suo cluster
          non occorre aggiornare il summary, in quanto il numero
          di cluster di x è gia membro del summary
        */
        insert(V->cluster[V->high(x)], low(x));
      }
    }
    if (x > V->max)
    {
      V->max = x;
    }
  }
}

