size(480, 480);
background(255);
noStroke();

int r = 40;
int colore = 0;
int tmp = 0;
for (int y = 0; y <= height; y+=r)
{
  colore = tmp;
  for (int x = 0; x <= width; x+=r)
  {
    fill(colore);
    rect(x, y, r, r);

    if (x == r)
    {
      tmp = colore;
    }
    colore += 12;
    println(colore);
    println(tmp);
  }
  
}
