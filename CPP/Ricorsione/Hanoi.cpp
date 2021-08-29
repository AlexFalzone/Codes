#include<iostream>

using namespace std;

void Hanoi(char iniziale, char centrale, char finale, int n){
    if(n==1){
        cout << "Muovo il disco 1 dal piatto " << iniziale <<
            " al piatto " << finale << endl;
    }else{
        Hanoi(iniziale,finale, centrale, n-1);
        cout << "Muovo il disco " << n << 
            " dal piatto " << iniziale << 
            " al piatto " << finale << endl;
        Hanoi(centrale, iniziale, finale, n-1);
    }
}

int main(int argc, char const *argv[])
{   
    int n;

    cout << "Inserire un intero positivo: ";
    cin >> n;
    cout << "Con " << n << 
        " dischi la sequenza di operazione è \n";
    Hanoi('A','B','C',n);

    return 0;
}
