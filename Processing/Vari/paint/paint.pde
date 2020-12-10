float x;
float y;

void setup()
{
  size(500, 500);
  stroke(255, 0, 0);
  stroke(10);
  background(255);
}

void draw()
{
  if (mousePressed)
  {
    line(pmouseX, pmouseY, mouseX, mouseY);
  }
}
