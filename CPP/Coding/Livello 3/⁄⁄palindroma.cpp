#include <iostream>
#include <fstream>
using namespace std;

bool palindroma(string x){
    int contatore = 0;
    for(int i = 0; i < x.length(); i++)
        if(x[i] == x[x.length() - i - 1])
            contatore++;
    if(contatore == x.length() || contatore == x.length() - 2)
        return true;
    return false;
}

void vettore(string* vett, int n, ofstream &out){
    int contatore = 0;
    for(int i = 0; i < n; i++)
        if(palindroma(vett[i]))
            contatore++;
    out << contatore << " ";

    for(int i = 0; i < n; i++)
        if(palindroma(vett[i]))
            out << vett[i] << " ";
    out << endl;
}

int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n;
        in >> n;
        string* vett = new string[n];
        for(int j = 0; j < n; j++)
            in >> vett[j];
        vettore(vett, n, out);
        
    }

    return 0;
}