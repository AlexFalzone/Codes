int r = 30;
int dir = 1;
int x;
int y;

void setup()
{
  size(500, 500);
  ellipseMode(RADIUS);
  x=width/2;
  y = height/2;
}

void draw()
{
  background(125);
  float d =  dist(mouseX, mouseY, x, y);

  if (r >= width/2 || r < 30)
  {
    dir = -dir;
  }

  if (d<r)
  {
    r+=dir;
    fill(0);
  } else
  {
    fill(255);
  }
  ellipse(x, y, r, r);
}
