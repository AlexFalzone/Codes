#include<iostream>

int power(int x, int n){
    int y = 0;
    if (n==0)
    {
        return 1;

    }else if ((n%2) != 0){  //dispari
        y = power(x,(n-1)/2);
        return x*y*y;

    }else{                  //pari
       y = power(x,n/2);
       return y*y; 
    }
}

int main(int argc, const char** argv) {
    int e = 0, n=0;

    std::cout << "Inserisci il numero e l'esponente:" << std::endl;
    std::cin>>n;
    std::cin>>e;
    power(n,e);

    return 0;
}