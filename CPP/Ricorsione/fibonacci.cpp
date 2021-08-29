#include<iostream>

using namespace std;

unsigned long fibonacci_ricorsivo(unsigned long a){
    if (a==0 || a==1)
    {
        return a;
    }
    else
    {
        return fibonacci_ricorsivo(a-1) + fibonacci_ricorsivo(a-2);
    } 
}



int main(int argc, char const *argv[])
{
    unsigned long risultato, num;

    cout << "Inserisci un intero:"<<endl;
    cin>>num;

    risultato = fibonacci_ricorsivo(num);

    cout << "Fibonacci("<<num<<")=" << risultato;


    /*ITERATIVO
    int x = 0;
    std::cout << "Inserisci valore: ";
    std::cin>>x;

    fibonacci_iterativo(x);*/

    return 0;
}
