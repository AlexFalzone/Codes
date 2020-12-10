#include<iostream>

void scambia(int &a, int&b){
    int aux = a;
    a = b;
    b = aux;
}

void BubbleSort(int a[], int n){
    bool flag=true;

    for(int i=0; i< n-1 && flag;i++)
    {   
        flag = false;
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j] > a[j+1])
            {   
                flag = true;
                scambia(a[j],a[j+1]);
            }
        }
    }
}

void stampa(int a[], int n){
    for (size_t i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char** argv) {
    int vettore[] ={12,3,6,5,131,7,43,-89,54,34,11,21,13,4,90,15,16,71,19,31};
    std::cout << "Vettore iniziale:" << std::endl;
    stampa(vettore, 20);
    BubbleSort(vettore, 20);
    std::cout << "Vettore ordinato:" << std::endl;
    stampa(vettore, 20);

    return 0;
}