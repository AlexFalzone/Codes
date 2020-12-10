float [] d = new float[10];
boolean vai = true;

void setup()
{
  size(500, 500);
  for (int i=0; i< d.length; i++)
  {
    d[i] = (i+1)*60;
  }
}

void draw()
{
  for (int i=d.length-1; i >= 0; i--)
  {
    fill(random(255), random(255), random(255));
    ellipse(width/2, height/2, d[i], d[i]);
  }

  
}
/*
void mousePressed()//variabile bool
  {
    if (mouseButton == LEFT)//int
    {
      noLoop();
    }
    if (mouseButton == RIGHT)//int
    {
       loop();
    }
  }

void mouseClicked()
{
  vai = !vai;
  if(vai)
  {
    loop();
  }
  else
  {
    noLoop();
  }
}







/*
void mousePressed()
{
}
void mouseReleased()
{
}
void mouseClicked()
{
}


void keyPressed()
{
}
void keyReleased()
{
}
void keyTyped()
{
}
*/
