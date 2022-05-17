void setup()
{
  print("sono nel setup");
  frameRate(30);
  background(0);
}

void draw()
{
  println("sono nel draw " +frameCount + " frame sono passati");
  if(millis() >= 5000)
  {
    ellipse(width/2,height/2,50,50);
  }
}
