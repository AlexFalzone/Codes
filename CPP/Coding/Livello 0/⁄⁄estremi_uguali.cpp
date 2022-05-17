#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt"); 

    for (int i = 0; i < 100; i++)
    {   
        int n_volte = 0;
        
        for (int j = 0; j != 3; j++)
        {
            int d;
            in >> d;

            string s;
            in >> s;
            
            if (s[0] == s[d-1])
            {
                n_volte++;
            }
        }
        out << n_volte;
        out << endl;
    }
    

}