# Alberi di van Emde Boas

                                                                                                                                by Alex Falzone

- **Introduzione**:<br>Creata nel 1975 dall'informatico Peter van Emde Boas. <br>Questo albero ha la particolare caratteristica di svolgere le operazioni di search, insert, delete, minimum, maximum, successor, predecessor nel tempo O(lg lg u) dove u rappresenta la dimensione dell'universo.<br>Possiamo pensare a quest'albero come un array A (diviso in $\sqrt{u}$ parti) contenenti 0 o 1. Definito un array ***summary***[0 $\dots$ $\sqrt{u}$ - 1], dove summary[ i ] contiene 1 se e soltanto se il sottoarray A[ i\sqrt{u} \dots (i + 1)\sqrt{u} - 1 ] contiene almeno un 1. Questo sottoarray di A di $\sqrt{u}$ bit è detto i-esimo ***cluster***. 
  
  ---
  
  ---

- **Struttura albero**:<br>Indichiamo con $\sqrt[I]{u}$ la radice quadrata **inferiore**, ovvero pow(2, $\lfloor$ lg (u) / 2 $\rfloor$).<br>Mentre con $\sqrt[S]{u}$ la radice **superiore**, ovvero pow(2, $\lceil$ lg (u) / 2 $\rceil$).
  
  Denotiamo con vEB(u) un albero vEB con dimensione dell'universo pari a **u** e, a meno che u non sia uguale alla dimensione base 2, l'attributo summary punta a un albero vEB($\sqrt[S]{u}$) e l'array cluster[ 0 $\dots$ $\sqrt[S]{u}$ - 1] punta ai $\sqrt[S]{u}$ alberi vEB($\sqrt[I]{u}$).<br>Inoltre all'interno di un cluster è presente un valore **min** (non presente in alcun albero ricorsivo vEB) e un valore **max**.<br>Successivamente è necessario stabilire come accedere sia al numero di cluster di un determinato valore(x), sia alla posizione del valore(x) all'interno del cluster; Esso avviene usando rispettivamente:<br>
  
  
  
     -High(x)       =    $\lfloor$ x / $\sqrt[I]{u}$ $\rfloor$<br>   -Low(x)        =     x $\bmod$ $\sqrt[I]{u}$<br>   -Index(x , y) =     (x * $\sqrt[I]{u}$)  + y<br>Dove index(x, y) rappresenta l'indice del numero e posizione del cluster prendendo in input un cluster(x) e una posizione(y).

        


















