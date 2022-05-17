#include<iostream>

const int MaxDimPila=100;

using namesapce std;

class pila
{
private:
    int VettorePila[MaxDimPila];
    int cima;

public:
    pila();
    void push(int x);
    int pop();
    void StampaPila();
    int PilaVuota();
    int PilaPiena();
};

pila::pila() :cima(-1) {};

int pila::PilaPiena()
{
    if (cima == (MaxDimPila - 1) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pila::PilaVuota()
{
    if (cima == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pila::push(int x)
{
    if (PilaPiena())
    {
        cout << "Pila Piena!\n";
    }
    else
    {
        cima++;
        VettorePila[cima] = x;
    }
}

int pila::pop()
{
    if (PilaVuota())
    {
        cout << "Pila vuota!\n"; 
        return -1;
    }
    else
    {
        int x = VettorePila[cima];
        cima--;
        return x;
    }
}

void pila::StampaPila()
{
    if (PilaVuota())
    {
        std::cout << "Pila Vuota!\n" << std::endl;
    }
    else
    {
        for (int i = cima; i >= 0; i--)
        {
            cout << "Posizione " << i <<" : "<< VettorePila[i]<< endl;
        } 
    }
}
