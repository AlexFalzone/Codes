#include "grafo_matrix.cpp"

int main(int argc, char const *argv[])
{
    cout << "Scegli il tipo:\n1)int\n2)double\n3)char\n4)bool\n";
    int tipo; cin >> tipo;

    if (tipo == 1)//int
    {   
        MGraph<int>* gr = new MGraph<int>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                int dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    int dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    int dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        }  
    }
    else if (tipo == 2) //double
    {
        MGraph<double>* gr = new MGraph<double>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                double dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    double dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    double dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        }  
    }
    else if (tipo == 3) //char
    {
        MGraph<char>* gr = new MGraph<char>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                char dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    char dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    char dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        } 
    }
    else if (tipo == 4) //bool
    {
        MGraph<bool>* gr = new MGraph<bool>(50);
        bool flag = true;
        bool vuota = true;
        while (flag == true)
        {   
            cout << "\nChe tipo di operazione vuoi fare?\n0)stampa\n1)addNode\n2)addEdge\n3)BFS\n4)DFS\n99)exit\n";
            int operazione; cin >> operazione;
            if (operazione == 0) //stampa
            {
                if (vuota == false)
                {
                    gr->print();
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 1) //addnode
            {
                cout << "\nInserisci il nodo\n";
                bool dato; cin >> dato;
                gr->addNode(dato);
                vuota = false;
            }
            else if (operazione == 2) //addedge
            {   
                if (vuota == false)
                {
                    gr->print();
                    cout << "\nInserisci i due nodi: \n";
                    bool dato1, dato2;
                    cin >> dato1 >> dato2;
                    gr->addEdge(dato1, dato2);
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
                
            }
            else if (operazione == 3) //BFS e printpath
            {   
                if (vuota == false)
                {   
                    gr->print();
                    cout << "\nDi quale nodo vuoi fare la BFS?\n";
                    bool dato_bfs; cin >> dato_bfs;
                    gr->BFS(dato_bfs);

                    /*cout << "\nVuoi stamparla?(Y/n)\n";
                    char scelta_bfs; cin >> scelta_bfs;
                    if (scelta_bfs == 'Y' || scelta_bfs == 'y') gr->printPath(dato_bfs);
                    else break;
                    cout << endl;*/
                }
                else
                {
                    cout << "\nGrafo vuoto!\n";
                }
            }
            else if (operazione == 4) //DFS e topological sort
            {
                if (vuota == false)
                {
                    gr->DFS();
                    cout << "\nVuoi svolgere anche la topological Sort?(Y/n)\n";
                    char scelta_DFS; cin >> scelta_DFS;
                    if (scelta_DFS == 'Y' || scelta_DFS == 'y') gr->topSort();
                    else break;
                }
                else
                {
                cout << "INPUT NON VALIDO!\n";                    
                }
                
            }
            else if (operazione == 99) //exit
            {
                flag = false;
            }
            else
            {
                cout << "INPUT NON VALIDO!\n";
            }   
        }  
    }
    else
    {
        cout << "INPUT NON VALIDO!\n";
    }
    
    return 0;
}