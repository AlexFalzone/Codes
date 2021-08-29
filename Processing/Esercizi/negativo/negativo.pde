PImage ImO, ImN;

void setup()
{
  size(1024, 512);
  ImO = loadImage("lena.png");
  
  image(ImO, 0, 0);
  ImN = negativo(ImO);
  image(ImN, 512, 0);
}

void draw()
{
}

PImage negativo(PImage I)
{
   PImage R = I.copy();
   R.loadPixels();
   float r,g,b;
   
   for (int i = 0; i < R.pixels.length; i++)
   {
     r = 255-red(R.pixels[i]);   
     g = 255-green(R.pixels[i]); 
     b = 255-blue(R.pixels[i]); 
     R.pixels[i] = color(r,g,b);
   }
   R.updatePixels();
   
   return R;
}
