void setup()
{
  size(500, 500);
}

void draw()
{
  background(100);
  fill(255);
  ellipse(width/2, height/2, 50, 50);
  fill(0);
  
  float x = map(mouseX, 0, width, -15, 15);
  float y = map(mouseY, 0, height, -15, 15);
  ellipse(width/2+x, height/2+y, 5, 5);
  
}


/*
void setup()
{
  size(240, 120);
}

void draw()
{
  background(255);
  for(int x = 20; x < width; x+= 20)
  {
     float rum = map(mouseX, 0, width, 0, 12);
     float rumi = random(-rum, +rum);
     float rumf = random(-rum, +rum);
     line(x+rumi, 20, x+rumf, 100);
  }
  
}*/
