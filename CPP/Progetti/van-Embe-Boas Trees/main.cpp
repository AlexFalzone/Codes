#include "vEB.cpp"
#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int universe = 10;
    cout << "ciao0" << endl;
    vEB* prova = new vEB(universe);
    prova->insert(prova, 3);
    prova->insert(prova, 5);
    prova->insert(prova, 10);
    prova->insert(prova, 8);
    prova->insert(prova, 1);
    prova->insert(prova, 20);
    prova->insert(prova, 13);
    cout << "ciao1" << endl;
    cout << "successore di 8 = " << prova->successor(prova, 8);
    cout << prova->isMember(prova, 2);
    cout << prova->isMember(prova, 3);
    cout << "predecessore di 8 = " << prova->predecessor(prova, 8);
    cout << "ciao2" << endl;
    return 0;
}
