#include<iostream>
#include<fstream>

using namespace std;

void soluzione(int *&vett, int n, ofstream& out)
{
    for (int i = 0; i < n; i++)
    {
        if ( (vett[i] % 2) != 0)
        {
            out << vett[i] << " ";
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
        int n;
        in >> n;
        int* vett = new int[n];

        for (int j = 0; j < n; j++)
        {
            in >> vett[j];
        }
        soluzione(vett, n, out);

        delete [] vett;
    }

    return 0;
}
