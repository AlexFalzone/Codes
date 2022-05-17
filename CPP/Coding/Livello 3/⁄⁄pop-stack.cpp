#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class H>
class Nodo{
    protected:
        H elemento;
        Nodo<H>* succ;
    public:
        Nodo(H _el): elemento(_el){
            this->succ = NULL;
        }

        //Get
        H getElemento(){return elemento;}
        Nodo<H>* getSucc(){return succ;}

        //Set
        void setSucc(Nodo<H>* succ){this->succ = succ;}
};

template <class H>
class Stack{
    protected:
        Nodo<H>* testa;
    public:
        Stack(){this->testa = NULL;}
        ~Stack();
        void Push(H);
        void Pop();
        void print(ofstream&);
};

template <class H> Stack<H>::~Stack(){
    Nodo<H>* iter = testa;
    Nodo<H>* tmp;

    while(iter != NULL){
        tmp = iter->getSucc();
        delete iter;
        iter = tmp;
    }
}

template <class H> void Stack<H>::Push(H x){
    Nodo<H>* nuovo = new Nodo<H>(x);

    nuovo->setSucc(testa);
    testa = nuovo;
}

template <class H> void Stack<H>::Pop(){
    if(testa != NULL){
        Nodo<H>* tmp = testa;
        testa = testa->getSucc();
        delete tmp;
    }
}

template <class H> void Stack<H>::print(ofstream &out){
    Nodo<H>* iter = testa;

    while(iter != NULL){
        out << iter->getElemento() << " ";
        iter = iter->getSucc();
    }
    out << endl;
}

int main(){
    
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        cout << type << endl;
        int n; in >> n;

        if(type == "int"){
            Stack<int>* t = new Stack<int>();
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
                
                if(tmp == "pop")
                    t->Pop();
                else{
                    string _value = tmp.substr(1, tmp.length());
                    int val = stoi(_value);
                    t->Push(val);
                }
            }
            t->print(out);
            delete t;
        }
        else if(type == "double"){
            Stack<double>* t = new Stack<double>();
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
                
                if(tmp == "pop")
                    t->Pop();
                else{
                    string _value = tmp.substr(1, tmp.length());
                    double val = stod(_value);
                    t->Push(val);
                }
            }
            t->print(out);
            delete t;
        }
        else if(type == "bool"){
            Stack<bool>* t = new Stack<bool>();
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
              
                if(tmp == "pop")
                    t->Pop();
                else{
                    string _value = tmp.substr(1, tmp.length());
                    bool val = stoi(_value);
                    t->Push(val);
                }
            }
            t->print(out);
            delete t;
        }
        else if(type == "char"){
            Stack<char>* t = new Stack<char>();
            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
                
                if(tmp == "pop")
                    t->Pop();
                else{
                    string val = tmp.substr(1, tmp.length());
                    t->Push(val[0]);
                }
            }
            t->print(out);
            delete t;
        }
        
    }
}