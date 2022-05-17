#include <iostream>
#include <fstream>
using namespace std;

int insertionsort(int* vett, int n){
    int i, j, tmp;
    int contatore = 0;
    for(int i = 1; i < n; i++){
        j = i;
        while(j > 0 && vett[j-1] > vett[j]){
            tmp = vett[j];
            vett[j] = vett[j-1];
            vett[j-1] = tmp;
            j--;
            contatore++;
        }
    }


    return contatore;
}


int main(){

    ifstream in("input.txt");

    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n;
        in >> n;
        int* vett = new int[n];
        for(int j = 0; j < n; j++)
            in >> vett[j];
        int contatore = insertionsort(vett, n);
        out << contatore << endl;
    
    }


    return 0;
}