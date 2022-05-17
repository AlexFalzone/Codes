PFont f;
String scrivendo = "";
String salvata = "";

void setup()
{
  size(500, 500);
  f = createFont("Colibri", 16);
}

void draw()
{
  background(255);
  int ind = 25;
  textFont(f);
  fill(0);
  text("Click sulla finestra e scrivi.\n Premi invio per salvare", ind, 40);
  text("Input: " + scrivendo, ind, 190);
  text("Testo salvato: " + salvata, ind, 230);
  
}

void keyPressed()
{
   if(key == '\n')
   {
      salvata = scrivendo;
      scrivendo = "";
   }
   else if (key == BACKSPACE && scrivendo.length() > 0 )
   {
      scrivendo = scrivendo.substring(0, scrivendo.length() - 1); 
   }
   else
   {
      scrivendo += key; 
   }
}
