#include<iostream>
#include<fstream>
using namespace std;

#define DIM 10

template<class H>
void scambia(H& a, H& b)
{
    H aux = a;
    a = b;
    b = aux;
}

template<class H>
void insertion_Sort(H* a, int dim)
{
    int i,j;
    H valore;
    for (int i = 0; i < dim; i++)
    {   
        j = i-1;
        valore = a[i];

        while ((j >= 0) && (a[j] > valore))
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = valore;
    }
}

template<class H>
void bubble_Sort(H *a, int dim)
{
    bool flag = true;
    for (int i = 0; i < dim-1 && flag; i++)
    {
        flag = false;
        for (int j = 0; j < dim-i-1; j++)
        {
            if (a[j] > a[j+1])
            {
                flag = true;
                scambia(a[j], a[j+1]);
            }
        }
    }
}

template<class H>
void swapSort(H* a, int dim)
{
	int i,j; 
	for (i=0;i<dim-1;i++) 	
    {
		for (j=i+1; j<dim; j++) 
        {
		    if (a[i] > a[j])
            {
			    scambia(a[i],a[j]);
            }
        }
    }
}


template<class H>
void merge(H* a, int left, int center, int right)
{
    int i = left, j = center+1, k = left;
    H b[DIM];

    while (i <= center && j <= right)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    while (i<=center)
    {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j<=right)
    {
        b[k] = a[j];
        j++;
        k++;
    }
    for (k = left; k < right; k++)
    {
        a[k] = b[k];
    }
}

template<class H>
void mergeSort(H* a, int left, int right)
{
    if (left < right)
    {   
        int center = (left+right)/2;
        mergeSort(a, left, center);
        mergeSort(a, center+1, right);
        merge(a, left, center, right);
    }
}


template<class H>
int partition(H* a, int p, int r)
{
    int pivot = a[r]; //settiamo il pivot all'ultimo elemento dell'array
    int i = p-1;
    
    for (int j = p; j < r; j++)
    {
        if (a[j] <= pivot)
        {
            scambia(a[i],a[j]);
            i++;
        }
    }
    scambia(a[i+1],a[r]);
    return i+1;
}

template<class H>
void quickSort(H* a, int sinistra, int destra)
{
    if (sinistra < destra)
    {
        int centro = partition(a, sinistra, destra);
        quickSort(a, sinistra, centro-1);
        quickSort(a, centro+1, destra);
    }
}

template<class H>
void quickSort(H* a, int dim)
{
    quickSort(a,0,dim-1);
}


template<class H>
int ricerca_binaria(H* a, H chiave, int sin, int des)
{
    if (sin == des)
    {
        if (chiave = a[sin])
        {
            return sin;
        }
        else
        {
            return -1;
        }
    }
    int centro = (sin+des)/2;
    if (chiave <= a[centro])
    {
        return ricerca_binaria(a, chiave, sin, centro);
    }
    else
    {
        return ricerca_binaria(a, chiave, centro+1, des);
    }
}

template<class H>
void stampa(H a[], int dim){
    for (int i = 0; i < dim; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}



