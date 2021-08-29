PImage Im, Is, Ie;
float[] H1, H2;

void setup()
{
  Im = loadImage("lena.png");
  Im.filter(GRAY);
  size(1536, 512);

  Is = stretching(Im);
  //H1 = istogramma(Im);
  //H2 = istogramma(Is);
  //Ie = equalizza(Im);

  image(Im, 0, 0);
  image(Is, 512, 0);
  //image(Ie, 1024, 0);

  //println(H1[0]);
  //println(H2[0]);
}

PImage stretching(PImage I)
{
  PImage R = I.copy();
  float max, min;

  R.loadPixels();
  max = red(R.pixels[0]);
  min = red(R.pixels[0]);

  for (int i = 1; i < R.pixels.length; i++)
  {
    if ( red(R.pixels[i]) > max)
    {
      max = red(R.pixels[i]);
    }
    if ( red(R.pixels[i]) < min)
    {
      min = red(R.pixels[i]);
    }
  }

  for (int i = 0; i < R.pixels.length; i++)
  {
    R.pixels[i] = color( 255*red(R.pixels[i]) - min)/(max - min);
  }
  R.updatePixels();
  return R;
}


float[] istogramma(PImage I)
{
  float[] H = new float[256];

  for (int i = 0; i < 256; i++)
  {
    H[i] = 0;
  }

  I.loadPixels();
  for ( int i = 0; i < I.pixels.length; i++)
  {
    H[(int(red(I.pixels[i])))]++;
  }
  
  for (int i = 0; i< 256; i++)
  {
    H[i] = H[i]/I.pixels.length;
  }
  return H;
}
