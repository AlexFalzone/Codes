int dim= 500;
int x, y;

void setup()
{
  size(500, 500);
  
  x = int(random(width));
  y = int(random(height));
  
  for (int i = 0; i < dim; i++)
  {
    fill(255,0,0);
    rect(x, y, 1, 1); 
  }
  
}

void draw()
{
  background(255);
  x = int(random(width));
  y = int(random(height));
  
  for (int i = 0; i < dim; i++)
  {
    fill(255,0,0);
    rect(x, y, 1, 1); 
  }
  
 
}
