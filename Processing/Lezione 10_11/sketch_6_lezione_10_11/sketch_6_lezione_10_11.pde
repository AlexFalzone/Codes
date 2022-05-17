int a = 0;

void setup()
{
  size(500,500);
  
}

void draw()
{
    background(0);
    translate(width/2, height/2);
    fill(255,255,0);
    ellipse(0,0,30,30);
    rotate( millis() * 0.001 * TWO_PI/10);
    
    translate(80,0);
    rotate( millis() * 0.001 * TWO_PI);
    fill(255);
    noStroke();
    ellipseMode(CENTER);
    ellipse(0,0,40,40);
    
    strokeWeight(5);
    stroke(255,0,0);
    line(0,0,40,0);
}
