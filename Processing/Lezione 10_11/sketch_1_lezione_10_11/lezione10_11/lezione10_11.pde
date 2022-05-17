float [] y = new float[1000];

void setup()
{
  size(500, 500);
  noStroke();
  y = new float[width*2];
  fill( random(255), random(255), random(255), random(255) );

  for (int i = 0; i < y.length; i++)
  {
    y[i] = random(-2*height,0.1*height);
  }
  
}

void draw()
{
  background(255);
  
  for (int i = 0; i < y.length; i++)
  {
    y[i]+= 10;
    
    if(y[i] > height)
    {
      y[i] = random(-2*height, -30);
    }
    float x = i/2;
    rect(x,y[i],20,30);
  }
  
}
