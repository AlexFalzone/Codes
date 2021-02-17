PImage Im, Imr, Imp;
float mseO, mseR, mseP;
float psnrO, psnrR, psnrP;

void setup()
{
  Im = loadImage("lena.png");
  size(1536, 512);
  background(0);

  Imr = Im.copy();
  Imr.resize(256, 256);
  Imr = replication2x(Imr);

  Imp = Im.copy();
  Imp.resize(256, 256);
  Imp.resize(512, 512);

  mseO = MSE(Im, Im);
  mseR = MSE(Im, Imr);
  mseP = MSE(Im, Imp);

  psnrO = PSNR(Im, Im);
  psnrR = PSNR(Im, Imr);
  psnrP = PSNR(Im, Imp);

  println("MSE con se stessa: " + mseO);
  println("MSE processing: " + mseP);
  println("MSE replication: " + mseR);

  println("PSNR con se stessa: " + psnrO);
  println("PSNR processing: " + psnrP);
  println("PSNR replication: " + psnrR);

  image(Im, 0, 0);
  image(Imr, 512, 0);
  image(Imp, 1024, 0);
}

void draw()
{
}

PImage replication2x(PImage I)
{
  PImage R = createImage(2*I.width, 2*I.height, RGB); 

  for (int x = 0; x < I.width; x++)
  {
    for (int y = 0; y < I.height; y++)
    {
      R.set(2*x, 2*y, I.get(x, y));

      R.set(2*x+1, 2*y, I.get(x, y));
      R.set(2*x, 2*y+1, I.get(x, y));
      R.set(2*x+1, 2*y+1, I.get(x, y));
    }
  }
  return R;
}


float MSE( PImage I1, PImage I2)
{
  float res = 0;

  I1.loadPixels();
  I2.loadPixels();

  for (int i = 0; i < I1.pixels.length; i++)
  {
    res += pow(blue(I1.pixels[i]) - blue(I2.pixels[i]), 2);
    res += pow(red(I1.pixels[i]) - red(I2.pixels[i]), 2);
    res += pow(green(I1.pixels[i]) - green(I2.pixels[i]), 2);
  }

  res = res/I1.pixels.length;
  return res;
}

float PSNR( PImage I1, PImage I2)
{
  float res = 0;
  float mse = MSE(I1, I2);

  res = 10*log((255*255)/mse)/log(10);

  return res;
}
