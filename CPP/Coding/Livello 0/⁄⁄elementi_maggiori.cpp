#include<iostream>
#include<fstream>

using namespace std;

void soluzione(int* &vett, int dim, ofstream& out, int elem)
{   
    int n_volte = 0;
    for (int i = 0; i < dim; i++)
    {
        if (vett[i] > elem)
        {
            n_volte++;
        }
    }
    
    out << n_volte << " ";

    for (int j = 0; j < dim; j++)
    {
        if (vett[j] > elem)
        {
            out << vett[j] << " ";
        }
    }
    out << endl;
}


int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int i = 0; i < 100; i++)
    {   
        int d;
        in >> d;
        int *vett = new int[d];

        int elem;
        in >> elem;

        for (int j = 0; j < d; j++)
        {
            in >> vett[j];
        }
        soluzione(vett, d, out, elem);
    }
}