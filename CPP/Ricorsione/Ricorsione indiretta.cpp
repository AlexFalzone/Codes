#include<iostream>

void A(int);
void B(int);

void A(int c){
    if(c>5) B(c);
    std::cout << c << " ";
}

void B(int c){
    A(--c);
}

int main(int argc, char const *argv[])
{
    A(25);
    return 0;
}

