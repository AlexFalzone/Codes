#include<iostream>

void OrdInserimento(int a[], int n){
    for(int i=1; i< n;i++)
    {   
        int j, valore =a[i];
        j = i - 1;

        while ((j >= 0) && (a[j] > valore))
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1]=valore;
    }
}

void stampa(int a[], int n){
    for (int i = 0; i < n; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char** argv) {
    int vettore[] ={12,3,6,5,131,7,43,-89,54,34,11,21,13,4,90,15,16,71,19,31};
    std::cout << "Vett iniziale:" << std::endl;
    stampa(vettore, 20);
    OrdInserimento(vettore, 20);
    std::cout << "Vett ordinato:" << std::endl;
    stampa(vettore, 20);

    return 0;
}
