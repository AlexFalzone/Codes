package Codes.Java;

public class main 
{
    public static void main(String[] args) 
    {
        double x,y,z;
        
        x = 5.4;
        y = 10.3;
        z = 3.17;
        
        Tridimensionlita c = new Tridimensionlita();
        System.out.println("Esito: " + c.formato(c.distanza(x,y,z)));
    }   
}
