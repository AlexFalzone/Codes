PImage im;

void setup()
{
  size(600, 600);
  im = loadImage("lena.png");
  println("Larghezza: " + im.width);
  println("Altezza: " + im.height);
}

void draw()
{
  background(0);
  image(im, 0, 0);
}

void mouseClicked()
{
  im.resize(im.width/2, im.height/2);
}

void keyTyped()
{
  if (key == 's')
  {
    println(savePath("data/lenaPiccola.png"));
    im.save(savePath("data/lenaPiccola.png"));
  }
  if (key == 'c')
  {
    println("salvo la canvas");
    saveFrame("lenaCanvas.png");
  }
}
