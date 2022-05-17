#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

const int INVITATI = 100;

class Invitato
{
private:
    bool celebrita;
    int posizione;

public:
    void Inizializza(bool val, int pos) {celebrita = val; posizione = pos;}
    bool ECelebrita() {return celebrita;}
    bool conosce(Invitato);
    int RivelaPos() {return posizione;}
};

bool Invitato::conosce(Invitato a)
{
    if (a.ECelebrita())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Init(Invitato a[])
{
    srand(time(NULL));  
    int indice = rand() % INVITATI;
    cout << "Valore casuale= " << indice << endl;
    for (int i = 0; i < INVITATI; i++)
    {
        if (i == indice)
        {
            a[i].Inizializza(1,i);
        }
        else
        {
            a[i].Inizializza(0,i);
        }
    }
}

class Nodo
{
    Invitato p;
    Nodo* succ;

public:
    Nodo(Invitato x) {p = x; succ = NULL;}
    ~Nodo() {};
    Nodo* successivo() {return succ;}
    void assegnaSuccessivo(Nodo* p) {succ = p;}
};

class Pila
{
public:
    Nodo* pp;

    Pila() {pp = NULL;}
    ~Pila();
    void CancellaNodo();
    bool PilaVuota() {return pp;}
    void Push(Invitato x);
    int Pop();
    Invitato PrimoElemento(Invitato& guest);
    bool SoloUno()
    {
        if ((pp != NULL) && (pp->successivo() == NULL))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

Pila::~Pila()
{
    Nodo* pnodo;

    while (pp != 0)
    {
        pnodo = pp;
        pp = pp->successivo();
        delete pnodo;
    }
}

void Pila::Push(Invitato x)
{
    Nodo* aux = new Nodo(x);

    if (pp)
    {
        aux->assegnaSuccessivo(pp);
    }

    pp = aux;
}

void Pila::CancellaNodo()
{
    Nodo* pnodo;

    if (pp)
    {
        pnodo = pp;
        pp = pp->successivo();
        delete pnodo;
    }
}

Invitato Pila::PrimoElemento(Invitato& guest)
{
    if (pp != NULL)
    {
        return pp->this->p;
    }
}

int Pila::Pop()
{
    Invitato e;
    PrimoElemento(e);
    CancellaNodo();
    return e;
}

int main(int argc, char const *argv[])
{
    Pila p;
    Invitato A[Invitati];
    Invitato celeb;

    Init(A)
    for (int i = 0; i < INVITATI; i++)
    {
        p.push(A[i]);
    }
    celeb = A[0];
    while (!p.SoloUno())
    {
        Invitato A1,A2;

        A1 = p.Pop();
        A2 = p.Pop();
        if (A1.conosce(A2))
        {
            p.Push(A2);
            celeb = A2;
        }
        else if (A2.conosce(A1))
        {
            p.Push(A1);
            celeb = A1;
        }
    }
    cout << "La celebrità è " << celeb.RivelaPos() << endl;

    return 0;
}
