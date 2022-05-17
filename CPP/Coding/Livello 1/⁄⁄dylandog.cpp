#include<iostream>
#include<fstream>

using namespace std;

void soluzione(int* &vett, int dim, ofstream &out, int fumetto)
{   
    int sol = 0;
    for (int i = 0; i < dim; i++)
    {
        if (fumetto == vett[i])
        {   
            sol = 1;
            out << i+1 << endl;
        }
    } 
    if (sol != 1)
    {
        out << 0 << endl;
    }
}


int main(int argc, char const *argv[])
{   
    ifstream in("input.txt");
    ofstream out("output.txt");


    for (int i = 0; i < 100; i++)
    {
        int dim;
        in >> dim;

        int fumetto;
        in >> fumetto;

        int *vett = new int[dim];

        for (int j = 0; j < dim; j++)
        {
            in >> vett[j];
        }
        soluzione(vett, dim, out, fumetto);
        delete [] vett;
    }
        
    return 0;
}
