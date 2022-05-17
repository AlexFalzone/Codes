#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void soluzione(string* &vett, int dim, ofstream& out)
{
    for (int i = 0; i < dim; i++)
    {
        out << vett[i] << " ";
    }
    out << endl;
}




int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int i = 0; i < 100; i++)
    {   
        string* vett = new string[3];

        for (int j = 0; j != 3; j++)
        {
            int d;
            in >> d;

            string s;
            in >> s;

            string tmp;
            tmp = toupper(s[0]);
            s.erase(0,1);

            vett[j] = (tmp+s);
        }
        
        soluzione(vett, 3, out);
    }
}