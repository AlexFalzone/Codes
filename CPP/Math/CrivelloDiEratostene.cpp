#include<iostream>

void ordinamento(int a[], int dim){
    int counter = 2;
    for (int i = 0; i < dim; i++)
    {
        a[i] = counter;
        counter++;
    }
}

void CrivelloDiEratostene(int a[], int dim) {
    ordinamento(a, dim);
    for (int j = 0; j < dim; j++)
    {   
        if(a[j]==0)
        {
            continue;
        }else
        {
            for (int i = j+1; i < dim; i++)
            {
                if((a[i]%a[j]) == 0)
                {
                    a[i] = 0;
                }
            }
        }
    }    
}

void ordinamenoSuArray(int a[], int dim, int* b){
    for(int i = 0; i < dim; i++)
    {
        if(a[i] != 0)
        {
            b[i] = a[i];
        }
        else
        {
            continue;
        }
    }
}

void stampa(int a[], int dim){
    for (int i = 0; i < dim; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout<<std::endl;
}


int main(int argc, const char** argv) {
    int dim = 0;
    std::cout << "Calcolare i numeri primi tra 2 e ..." << std::endl;
    std::cin>>dim;
    
    int* array = new int[dim];
    int *b = new int[dim];

    ordinamento(array, dim);
    CrivelloDiEratostene(array, dim);
    ordinamenoSuArray(array, dim, b);
    stampa(b, dim);

    return 0;
}
