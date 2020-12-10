#include "albero.cpp"

int main(int argc, char const *argv[])
{
    cout << "Scegli che tipo di albero vuoi creare: \n";
    cout << "1)int\n2)double\n3)char\n4)bool\n\n";
    int tipo; cin >> tipo;
    bool flag = true;
    bool vuota = true;
    
    if (tipo == 1) //int
    {
        Tree<int>* tr = new Tree<int>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                int dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    int dato_canc; cin >> dato_canc;
                    Nodo<int>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    int succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    int succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    int* vett = new int[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        int a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else if (tipo == 2)//double
    {
        Tree<double>* tr = new Tree<double>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                double dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    double dato_canc; cin >> dato_canc;
                    Nodo<double>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    double succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    double succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    double* vett = new double[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        double a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else if (tipo == 3)//char
    {
        Tree<char>* tr = new Tree<char>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                char dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    char dato_canc; cin >> dato_canc;
                    Nodo<char>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    char succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    char succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    char* vett = new char[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        char a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else if (tipo == 4)//bool
    {
        Tree<bool>* tr = new Tree<bool>();

        while (flag == true)
        {
            cout << "\n0)stampa\n1)inserimento\n2)cancellazione\n3)successore\n4)predecessore\n5)foglie\n6)natural fill\n7)altezza\n99)exit\n";
            int scelta_operazione; cin >> scelta_operazione;

            if (scelta_operazione == 0) // stampa
            {
                cout << "\n1)preOrder\n2)inOrder\n3)postOrder\n";   
                int scelta_stampa; cin >> scelta_stampa;
                switch (scelta_stampa)
                {
                    case 1:
                        tr->visita_preOrder();
                    break;
                    case 2:
                        tr->visita_inOrder();
                    break;
                    case 3:
                        tr->visita_postOrder();
                    break;

                    default:
                        cout << "\ninput non valido\n";
                    break;
                }
            }
            else if (scelta_operazione == 1) //inserimento
            {   
                cout << "\nInserisci il dato\n";
                bool dato_ins; cin >> dato_ins;
                tr->ins(dato_ins);
                vuota = false;
            }
            else if (scelta_operazione == 2) //cancellazione
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "\nInserisci il dato da cancellare\n";
                    bool dato_canc; cin >> dato_canc;
                    Nodo<bool>* el = tr->find(dato_canc);
                    tr->canc(el);
                    delete el;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 3) //successore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il successore?\n";
                    cout << endl;
                    bool succ; cin >> succ;
                    cout << tr->successor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 4) //predecessore
            {
                if (vuota == false)
                {
                    tr->visita_inOrder();
                    cout << "Di quale nodo vuoi trovare il predecessore?\n";
                    cout << endl;
                    bool succ; cin >> succ;
                    cout << tr->predecessor(succ);
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 5) //foglie
            {
                if (vuota == false)
                {
                    cout << "Foglie = " << tr->foglie() << endl;  
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 6) //natural fill
            {
                if (vuota == false)
                {
                    cout << "\nDimensione vettore = ";
                    int dim_vett; cin >> dim_vett;
                    bool* vett = new bool[dim_vett];
                    
                    for (int i = 0; i < dim_vett; i++)
                    {
                        bool a; cin >> a;
                        vett[i] = a;
                    }
                    int j = 0;
                    tr->natural_Fill(vett, j);
                    delete [] vett;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 7) //altezza
            {
                if (vuota == false)
                {
                    cout << "Altezza = " << tr->altezza() << endl;
                }
                else
                {
                    cout << "Albero vuoto!\n";
                }
            }
            else if (scelta_operazione == 99)//exit
            {
                flag = false;   
            }
            else
            {
                cout << "Operazione non valida\n";
            }
            
        }
        delete tr;

        cout << endl;
    }
    else
    {
        cout << "\nINPUT NON VALIDO!\n";
    }
    
    return 0;
}