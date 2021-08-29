#include <iostream>
#include <fstream>
using namespace std;

#define MAXVECT_SIZE 10000

void Solve(int* vett, int n, ofstream &out){
	int min = 0;
	
	for(int i =  1; i < n; i++)
		if(vett[i] < vett[min])
			min = i;
	
	out << vett[min] << endl;
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i = 0; i < 100; i++){
		int* vett = new int[MAXVECT_SIZE];	//Use vector class to improve performance.
		
		string tmp; in >> tmp;
		int j = 0;
		
		while(tmp != "STOP"){
			int val = stoi(tmp);
			vett[j] = val; j++;
			in >> tmp;
		}
		
		Solve(vett, j, out);
		delete []vett;
	}
}
