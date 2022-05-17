#include<iostream>
#include<fstream>
#include <string>

using namespace std;


void soluzione(string* &s, ofstream& out, int valore)
{   
    int primo_secondo = 0, primo_terzo = 0, secondo_terzo = 0;
    int j = 0;

    while (j != valore)
    {   
        if ( (s[0].at(j) == s[1].at(j)) && (s[1].at(j) == s[2].at(j)) )  //tutte e tre le stringhe sono uguali
        {
            primo_secondo++;
            secondo_terzo++;
            primo_terzo++;
        }
        else if (s[0].at(j) == s[1].at(j)) 
        {
            primo_secondo++;
        }
        else if (s[0].at(j) == s[2].at(j))
        {
            primo_terzo++;
        }
        else if (s[1].at(j) == s[2].at(j))
        {
            secondo_terzo++;
        }

        j++;
    }
    
    if ( (primo_secondo == valore) && (primo_terzo == valore) && secondo_terzo == valore )
    {
        out << s[0] << " " << s[1] << " "  << s[2] << endl;
    }
    else if (primo_secondo == valore)
    {
        out << s[0] << " " << s[1] << endl;
    }
    else if (primo_terzo == valore)
    {
        out << s[0] << " " << s[2] << endl;
    }
    else if (secondo_terzo == valore)
    {
        out << s[1] << " " << s[2] << endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int l = 0; l < 100; l++)
    {
        int val;
        in >> val;

        string* s = new string[3];

        for (int i = 0; i < 3; i++)
        {
            in >> s[i];
        }
        soluzione(s, out, val);
    }

    return 0;
}
    