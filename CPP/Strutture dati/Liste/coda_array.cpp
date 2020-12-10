#include<iostream>

using namespace std;

const int Max = 10;

class Coda
{
private:
    int VettoreCoda[Max];
    int testa;
    int fine;
    int num_elementi;

public:
    Coda();
    void Enqueque(int x);
    int Dequeque();
    void StampaCoda();
    int Testa() {return testa;}
    int CodaVuota() {return (num_elementi == 0);}
    int CodaPiena() {return (num_elementi==Max);}
};

Coda::Coda() :testa(0), fine(-1), num_elementi(0) {};

void Coda::Enqueque(int x)
{
    if (CodaPiena())
    {
        cout << "Coda piena!\n";
    }
    else
    {
        fine = (fine + 1) % Max; 
        VettoreCoda[fine] = x;
        num_elementi++;    
    }
}

int Coda::Dequeque()
{
    int x;

    if (CodaVuota())
    {
        cout << "Coda vuota!\n";
        return -1;
    }
    else
    {
        x = VettoreCoda[testa];
        testa = (testa + 1) % Max;
        num_elementi--;
        return x;
    }
}

void Coda::StampaCoda()
{
    int i = testa;
    int x = 0;

    if (CodaVuota())
    {
        cout << "Coda vuota!\n";
    }
    else
    {
        while ((i%Max) != fine)
        {
            cout << "Posizione " << x << ": " << VettoreCoda[i%Max] << endl;
            x++; 
            i++;
        }
        cout << "Posizione " << x << ": " << VettoreCoda[i%Max] << endl;
    }
}

int main(int argc, char const *argv[])
{
    Coda coda;

    int x = coda.Dequeque();

    for (int i = 0; i < Max; i++)
    {
        coda.Enqueque((i + 1) * 10);
    }

    cout << endl;

    coda.StampaCoda();
    
    coda.Enqueque(4);

    for (int i = 0; i < Max-1; i++)
    {
        coda.Dequeque((i + 1) * 10);
    }
    cout << endl;

    return 0;
}
