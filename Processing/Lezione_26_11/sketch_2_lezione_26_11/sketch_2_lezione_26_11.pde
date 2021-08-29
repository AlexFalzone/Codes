PImage I;
float r, g, b;
color c, c1;
int vr; //variazione di rosso

void setup()
{
  I = loadImage("lena.png");
  size(512, 512);
  vr = 0;
  c = color(255,255,0);
  
  for(int i = 0; i < I.width; i++)
  {
    I.pixels[pos(i,i,I.width)] = c;
  }
}

void draw()
{
  image(I, 0, 0);
}

void keyPressed()
{
  if (key == 'r')
  {
    vr--;
  } else if (key == 'R')
  {
    vr++;
  }
  println(vr);

  I.loadPixels();
  for (int i = 0; i < I.pixels.length; i++)
  {
    c1 = I.pixels[i];
    c1 = color(red(c1) + vr, green(c1), blue(c1));
    I.pixels[i] = c1;
  }
  I.updatePixels();
}

int pos(int x, int y, int w)
{
  return (x+y*w);
}
