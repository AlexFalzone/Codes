#include<iostream>
#include<bitset>
#include<string>

using namespace std;

void cesar_Code(const string message, const short shift = 0)
{
    string temp_message = message;

    for (int i = 0; i < (int) message.length(); i++)
    {
        temp_message[i] = message[i] + shift;
    } 
    cout << temp_message << endl;
}

void binary_Code(const string message)
{
    string temp_message = message;
    for (int i = 0; i < (int) message.length(); i++)
    {
        cout << bitset<7>(temp_message.c_str()[i]);
    }
}

void roman_code(int message)
{
    int decimal[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    string symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int count = 0;

    while (message != 0)
    {
        while (message/decimal[count])
        {
            cout << symbol[count];
            message -= decimal[count];
        }
        count++;
    }
}





int main(int argc, char const *argv[])
{



    return 0;
}

