#include <iostream>

#define DIM 20

int ricerca_binaria(int a[], int chiave, int sin, int des)
{
    if(sin==des)
    {
        if(chiave==a[sin])
        {
            return sin;
        }
        else
        {
            return -1;
        }
    }
    int centro = (sin+des)/2;
    if(chiave<=a[centro])
    { 
        return ricerca_binaria(a,chiave,sin,centro);
    }
    else
    {
        return ricerca_binaria(a,chiave,centro+1,des);
    }
    
}

void stampa(int a[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char **argv)
{
    int vettore[] = {2, 3, 6, 7, 8, 10, 13, 19, 24, 34, 35, 39, 41, 43, 50, 55, 56, 71, 79, 81};
    int chiave, pos;
    
    std::cout << "Inserire un intero da cercare:" << std::endl;
    std::cin>>chiave;
    pos = ricerca_binaria(vettore,chiave,0,DIM-1);

    if(pos+1)
    {
        std::cout<<"L'elemento cercato in pos " << pos 
        << std::endl;
    }
    else
    {
        std::cout<<"Elemento non presente."<<std::endl;
    }
    

    return 0;
}
