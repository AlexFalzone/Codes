#include<iostream>

void scambia(int &a, int&b){
    int aux = a;
    a = b;
    b = aux;
}

void OrdScambio(int a[], int n){
    for(int i=0; i< n-1;i++){
        for(int j=i+1;j<n;j++){
            if(a[i] > a[j]){
                scambia(a[i],a[j]);
            }
        }
    }
}

void stampa(int a[], int n){
    for (size_t i = 0; i < n; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char** argv) {
    int vettore[] ={12,3,6,5,131,7,43,-89,54,34,11,21,13,4,90,15,16,71,19,31};
    std::cout << "Vett iniziale:" << std::endl;
    stampa(vettore, 20);
    OrdScambio(vettore, 20);
    std::cout << "Vett ordinato:" << std::endl;
    stampa(vettore, 20);

    return 0;
}