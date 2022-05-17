#include<iostream>
#include<fstream>
using namespace std;


int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int j = 0; j < 100; j++)
    {
        int dim; in >> dim;

        for (int i = 0; i < dim; i++)
        {
            int op1; in >> op1;
            char segno; in >> segno;
            int op2; in >> op2;

            if (segno == '+')
            {
                out << op1+op2<< " ";
            }
            else if (segno == '-')
            {
                out << op1-op2 << " ";
            }
            else if (segno == '*')
            {
                out << op1*op2 << " ";
            }
        }
        out << endl;
    }
    

    return 0;
}
