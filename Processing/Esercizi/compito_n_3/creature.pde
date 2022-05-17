class creature
{  
  float x, y;
  int energia;

  creature(float x, float y, int energia)
  {
    this.x = x;
    this.y = y;
    this.energia = energia;
  }

  void display()
  {
    fill(255, 255, 0);
    noStroke();
    ellipse(x, y, 6, 6);
  }

  void move()
  {
    x = int(random(2, 10));
    y = int(random(2, 10));
    energia -= 5;
  }

  void run()
  {
    display();
    move();
  }
}
