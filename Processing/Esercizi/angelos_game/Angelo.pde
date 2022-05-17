class Angelo
{
  PImage angelo;
  float x, y;
  float dim;

  Angelo()
  {
    angelo = loadImage("pp.jpg");
    x = width/2;
    y = height/2;
    dim = 70;
    angelo.resize(int(dim),int(dim));
  }
  
  void display()
  {
    noCursor();
    imageMode(CENTER);
    image(angelo, x, y);
  }
  
  void move()
  {
    x = mouseX;
    y = mouseY;
  }
  
  void assorbi(Caratteristiche c)
  {
    if ( (dist(c.x, c.y, x, y) < dim+30/2) && !(c.car_positiva))
    {
       c.setColor();
    }
  }
 
  void run()
  {
    display();
    move();
  }
}
