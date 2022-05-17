#include<iostream>

using namespace std;

void scambia(int&a , int&b)
{
    int aux = a;
    a = b;
    b = aux;
}

void OrdScambia(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (a[i] > a[j] )
            {
                scambia(a[i], a[j]);
            }
        }   
    }
}

void OrdScambiaRicorsivo(int a[], int n)
{
    for (int j = 1; j < n; j++)
    {
        if (a[0] > a[j])
        {
            scambia(a[0], a[j]);
        }
    }
    for (int i = 1; i < n; i++)
    {
        OrdScambiaRicorsivo(a+i,n-1);
    }
}

int main(int argc, char const *argv[])
{
    int vettore[10] = {11,4,7,6,234,77,45,1,19,3};

    for (int i = 0; i < 10; i++)
    {
        cout << vettore[i] << " ";
    }

    cout << endl;

    OrdScambiaRicorsivo(vettore, 10);

    for (int i = 0; i < 10; i++)
    {
        cout << vettore[i] << " ";
    }
    

    return 0;
}
