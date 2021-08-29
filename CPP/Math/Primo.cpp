/*Prende in input un intero naturale e verifica che sia maggiore di 1 e ritorna vero se il numero è primo, falso altrimenti.
La funzione implementa la ricerca di divisori sino alla √x e termina immediatamente quando trova un divisore,
oppure quando supera il valore di √x
*/

#include<iostream>

bool Primo(int n)
{
    if((n%2)==0){ std::cout<<"False"<<std::endl; }
    else if((n%3)==0){ std::cout<<"False"<<std::endl; }
    else if((n % 5) == 0) { std::cout<<"False"<<std::endl; }
    else if((n % 7) == 0) { std::cout<<"False"<<std::endl; }
    else if((n % 13) == 0) { std::cout<<"False"<<std::endl; }
    else if((n % 17) == 0) { std::cout<<"False"<<std::endl; }
    else if((n % 19) == 0) { std::cout<<"False"<<std::endl; }
    else if((n % 23) == 0) { std::cout<<"False"<<std::endl; }
    else{ std::cout<<"True"<<std::endl; }
}               

int main(int argc, char const *argv[])
{
    int x = 0;
    std::cout<<"Inserisci un numero, vedro' se esso è un numero primo:"<<std::endl;
    std::cin>>x;
    Primo(x);
    
    return 0;
}