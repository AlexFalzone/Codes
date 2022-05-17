#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in("input.txt", ios::in);
    ofstream out("output.txt");

    for (int j = 0; j < 100; j++)
    {
        char* iniziale = new char(5);
        char* finale = new char(5);

        for (int i = 0; i < 5; i++)//init array vocali
        {
            string vocali; in >> vocali;
            char voc_iniz = vocali[0];
            char voc_fin = vocali[2];

            iniziale[i] = voc_iniz;
            finale[i] = voc_fin;

            for (int a = 0; a < 5; a++)
            {
                cout << iniziale[a] << "\t" << finale[a] << endl;
            }
            
        }
        for (int i = 0; i != 6 ; i++)//scorrimento fino a capo
        {
            string parola; in >> parola;

            for (int k = 0; k < (int)parola.length(); k++)//scorrimento parola
            {
                for (int l = 0; l < 5; l++)//scorrimento vocali
                {
                    if (parola[k] == iniziale[l])
                    {
                        parola[k] = finale[l];
                    }
                    
                }
            }
            out << parola << " "; 
        }
        out << endl;
        delete [] iniziale;
        delete [] finale;
    }

    return 0;
}
