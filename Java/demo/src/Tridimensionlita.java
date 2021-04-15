package Codes.Java;

import java.text.DecimalFormat;

public class Tridimensionlita
{
    /**
     * Calcola la distanza dell'origine alla cord (x,y,z)
     * @param x asse
     * @param y asse
     * @param z asse
     * @return ritorna la distanza dall'origine al punto (x,y,z). Esito non negativo
     */
    public double distanza(double x, double y, double z)
    {
        return Math.sqrt(x*x + y*y + z*z);
    }

    /**
     * Formatta un valore double cosi che abbia un singolo valore
     * dopo la virgola.
     * Se il contenuto dopo la parte decimale è 0 viene ritornata
     * una stringa del suo contenuto
     * @param input il valore da formattare
     * @return String rappresentante 'input' 
     */
    public String formato(double input)
    {
        DecimalFormat df = new DecimalFormat("0.##");
        return df.format(input);
    }
}