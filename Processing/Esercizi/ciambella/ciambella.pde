boolean ciambella = false;
float xx;
float yy;
void setup()
{
  xx = random(25, 475);
  yy = 0;
  ellipseMode(CENTER);
  size(500, 500);
}

void draw()
{
  background(255, 255, 0);
  fill(255);
  ellipse(210, height/2, 50, 50);
  ellipse(290, height/2, 50, 50);

  fill(0);
  float x = map(mouseX, 0, width, -15, 15);
  float y = map(mouseY, 0, height, -15, 15);
  ellipse(210 + x, height/2 + y, 5, 5);
  ellipse(290 + x, height/2 + y, 5, 5);

  if (ciambella == false)
  {  
    ellipse(xx, yy, 50, 50);
    yy++;

    x = map(xx, 0, width, -15, 15);
    y = map(yy, 0, height, -15, 15);

    ellipse(210 + x, height/2 + y, 5, 5);
    ellipse(290 + x, height/2 + y, 5, 5);
    
    ciambella = true;
  }
}
