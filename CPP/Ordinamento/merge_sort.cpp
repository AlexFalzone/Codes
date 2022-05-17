#include<iostream>

#define DIM 20

void merge(int a[], int left, int center, int right)
{
    int i = left, j = center+1, k = left;
    int b[DIM];

    while ( (i<=center)&&(j<=right))
    {
        if(a[i]<=a[j])
        {
            b[k]=a[i]; 
            i++;
        }
        else
        {
            b[k]=a[j]; 
            j++;
        }
        k++;
    }

    while (i<=center)
    {
        b[k]=a[i];
        i++;
        k++;
    }
    while (j<=right)
    {
        b[k]=a[j];
        j++;
        k++;
    }
    for (k = left; k < right; k++)
    {
        a[k]=b[k];
    }
}

void mergesort(int a[], int left, int right)
{
    if(left < right)
    {
        int center = (left+right)/2;
        mergesort(a, left, center);
        mergesort(a, center+1, right);
        merge(a,left,center,right);
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
    mergesort(vettore, 0, DIM-1);
    std::cout << "Vettore ordinato:" << std::endl;
    stampa(vettore, 20);

    return 0;
}
