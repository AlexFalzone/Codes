#include<iostream>
#include<fstream>
using namespace std;


int fibonacci(int a)
{   
    int primo =0, secondo = 1, tmp;
    if (a <= 1)
    {
        return a;
    }
    for (int i = 2; i <= a; i++)
    {
        tmp = primo;
        primo = secondo;
        secondo = primo + tmp;
    }
    return secondo;
}


int main(int argc, char const *argv[])
{
    ifstream in("input.txt", ios::in);
    ofstream out("output.txt");    

    for (int j = 0; j < 100; j++)
    {
        int num; in >> num;
        cout << num << endl;
        int fib = fibonacci(num);

        out << fib << endl;
    }
    

    return 0;
}
