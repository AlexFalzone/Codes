PImage Im, Imax, Imin, Imed;

void setup()
{
  size(1024, 1024);
  Im = loadImage("lena.png");
  Im.filter(GRAY);

  Imax = massimo(Im, 11);
  //Imin = minimo(Im, 11);
  //Imed = mediano(Im, 11);

  image(Im, 0, 0);
  image(Imax, 512, 0);
  image(Imin, 0, 512);
  image(Imed, 512, 512);
}

void draw()
{
}

PImage massimo(PImage I, int N)
{
  PImage R = createImage(I.width, I.height, RGB);
  PImage tmp;
  int off = N/2;
  float [] tmpF = new float[N*N];
  
  for (int x = 0; x < I.width; x++)
  {
     for (int y = 0; y < I.height; y++)
     {
        tmp  = I.get(x - off, y - off, N, N);
        tmp.loadPixels();
        
        for (int i = 0; i < tmp.pixels.length; i++)
        {
           tmpF[i] = red(tmp.pixels[i]);           
        }
        R.set(x, y, color(max(tmpF)));
     }
  }
  return R;
}


PImage minimo(PImage I, int N)
{
  PImage R = createImage(I.width, I.height, RGB);
  PImage tmp;
  int off = N/2;
  float [] tmpF = new float[N*N];
  
  for (int x = 0; x < I.width; x++)
  {
     for (int y = 0; y < I.height; y++)
     {
        tmp  = I.get(x - off, y - off, N, N);
        tmp.loadPixels();
        
        for (int i = 0; i < tmp.pixels.length; i++)
        {
           tmpF[i] = red(tmp.pixels[i]);           
        }
        R.set(x, y, color(min(tmpF)));
     }
  }
  return R;
}
