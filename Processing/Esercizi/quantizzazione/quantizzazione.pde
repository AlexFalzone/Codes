PImage ImO, ImQ;
int livello;
void setup()
{
  livello = 2;
  ImO = loadImage("lena.png"); 
  size(1024, 512);

  image(ImO, 0, 0);
  
  ImQ = quantizza(ImO, livello);
  image(ImQ, 512, 0);
}

void draw()
{
}

PImage quantizza(PImage I, int livelli)
{
  PImage R = I.copy();
  int r = 0;

  for (int i = 0; i < R.pixels.length; i++)
  {
    r = floor((red(R.pixels[i])*livelli)/256);
    

    r = int((float(r)/(livelli-1))*255);
    

    R.pixels[i] = color(red(r),green(r),blue(r));
  }
  R.updatePixels();

  return R;
}


void keyPressed()
{
   if ( (key == '+'))
   {
      livello++;
      image(quantizza(ImO, livello), 512, 0);
   }
   if ( (key == '-') && (livello > 2))
   {
      livello--;
      image(quantizza(ImO, livello), 512, 0);
   }
}
