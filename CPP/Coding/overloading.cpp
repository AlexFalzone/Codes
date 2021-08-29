#include<iostream>

using namespace std;

class Punto
{
private:
    double x; 
    double y;

public:
    Punto(double xx, double yy) :x(xx), y(yy) {}
    double getX() {return x;}
    double getY() {return y;}
    void setX(double xx) {x = xx;}
    void setY(double yy) {x = yy;}

    Punto operator+(const Punto& b);
    Punto& operator+=(const Punto& b);
    Punto& operator++();                    //prefissa
    Punto& operator++(int);                 //postfissa
};

Punto Punto::operator+(const Punto& b)
{
    Punto temp(0.0, 0.0);

    temp.x = this->x + b.x;
    temp.y = this->y + b.y;
    return temp;
}

Punto& Punto::operator+=(const Punto& b)
{
    x += b.x;
    y += b.y;
    return *this;
}

Punto& Punto::operator++()
{
    x++;
    y++;
    return *this;
}

Punto& Punto::operator++(int)
{
    Punto pp(this->x, this->y);
    ++(*this);
    return pp;
}

int main(int argc, char const *argv[])
{
    Punto p1(5,6);
    Punto p2(7,1);
    Punto p(0,0);

    p = p1+p2;
    cout << "p.x= " << p.getX() << "\tp.y= " << p.getY() << endl;

    p += p1;
    cout << "p.x= " << p.getX() << "\tp.y= " << p.getY() << endl;

    ++p;
    cout << "p.x= " << p.getX() << "\tp.y= " << p.getY() << endl;

    p++;
    cout << "p.x= " << p.getX() << "\tp.y= " << p.getY() << endl;


    return 0;
}
