#include <iostream>
#include <fstream>
using namespace std;


string diametro(string* vett, int n){
    string max = vett[0];
    for(int i = 1; i < n; i++){
        if(max.length() < vett[i].length())
            max = vett[i];
        else if(max.length() == vett[i].length()){
            bool state = false;
            int j = 0;
            while(!state){
                if(max[j] == vett[i][j])
                    j++;
                else if(max[j] > vett[i][j])
                    state = true;
                else{
                    max = vett[i];
                    state = true;
                }
            }
        }
    }

    return max;
}


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n;
        in >> n;
        string* vett = new string[n];
        for(int j = 0; j < n; j++){
            in >> vett[j];
        }
        out << diametro(vett, n) << endl;
    }

    in.close();
    out.close();

    return 0;
}