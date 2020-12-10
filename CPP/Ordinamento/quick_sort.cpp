#include<iostream>

#define DIM 20

void scambia(int &a, int&b){
    int aux = a;
    a = b;
    b = aux;
}

int partition(int a[], int p, int r)
{
    int pivot=a[r];
    std::cout << "p=" <<  pivot << std::endl;
    int i=p-1;
    for (int j = p; j < r; j++)
    {
        if(a[j]<=pivot)
        {
            i++;
            scambia(a[i],a[j]);
        }
    }
    scambia(a[i+1],a[r]);
    return i+1;
}

void quicksort(int a[],int sinistra, int destra)
{
    if(sinistra<destra)
    {
        int q=partition(a,sinistra,destra);
        quicksort(a,sinistra,q-1);
        quicksort(a,q+1,destra);
    }
}

void stampa(int a[], int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char** argv) {
    int vettore[] ={12,3,6,5,131,7,43,-89,54,34,11,21,13,4,90,15,16,71,19,31};
    std::cout << "Vettore iniziale:" << std::endl;
    stampa(vettore, 20);
    quicksort(vettore, 0, DIM-1);
    std::cout << "Vettore ordinato:" << std::endl;
    stampa(vettore, 20);

    return 0;
}
