#include<iostream>
#include<fstream>
using namespace std;

void soluzione(string a, int dim, ofstream& out)
{   
    for (int i = 0; i < dim; i++)
    {
        switch (a[i])
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            out << a[i] << "f" << a[i];
            break;
        
        default:
            out << a[i];
            break;
        }
    }
    out << " ";
}

int main(int argc, char const *argv[])
{
    ifstream in("input.txt" , ios::in);
    ofstream out("output.txt");

    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < ''; j++)
        {
            string vett; in >> vett;
            cout << vett << endl;
            soluzione(vett, vett.length(), out);
        }
        out << endl;
    }
    

    return 0;
}
