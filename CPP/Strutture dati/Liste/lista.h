#include<iostream>

using namespace std;

enum stato_pila {OK, PIENA, VUOTA};


template<class T>
class ListaSemplice
{   
private:
    int lunghezza;
    T* tabella;
    int cima;
    stato_pila stato;
    void CancellaNodo();

public:
    ListaSemplice(int lungh = 10);
    ~ListaSemplice() {delete [] tabella;}
    void Push(T);
    T Pop();
    int num_elementi();
    void visualizza();
    int leggi_lunghezza() {return lunghezza;}


};

template<class T>
ListaSemplice<T>::ListaSemplice(int lungh)
{
    lunghezza = lungh;
    tabella = new T[lunghezza];
    cima = -1;
    stato = VUOTA;
}

template<class T>
void ListaSemplice<T>::Push(T x)
{
    if (stato != PIENA)
    {
        tabella[++cima] = x;
    }
    else
    {
        cout << "Pila Piena!\n";
    }
    if (cima == lunghezza)
    {
        stato = PIENA;
    }
    else
    {
        stato = OK;
    }
}

template<class T>
T ListaSemplice<T>::Pop()
{
    T elem = 0;
    if (stato != VUOTA)
    {
        elem = tabella[cima--];
    }
    else
    {
        cout << "Pila vuota!\n";
    }
    if (cima == -1)
    {
        stato = VUOTA;
    }
    else
    {
        stato = OK;
    }
    return elem;
}

template<class T>
void ListaSemplice<T>::visualizza()
{
    for (int i = cima; i >= 0; i--)
    {
        cout << "[" << tabella[i] << "]" << endl; 
    }
} 

template<class T>
int ListaSemplice<T>::num_elementi()
{
    return (cima+1);
}

int main(int argc, char const *argv[])
{
    ListaSemplice<int> stack(6);

    stack.Push(4);
    stack.Push(7);
    stack.Push(87);
    cout << "Numero elementi: " << stack.num_elementi() << endl;
    stack.visualizza();
    stack.Pop();
    stack.visualizza();

    return 0;
}
