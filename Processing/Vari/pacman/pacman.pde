int dir = 1; //direzione
int a = 30; //angolo
int dira = -1;
int v = 3; //velocità
int va = v/2; //velocita spostamento bocca
int x = 60;
int r = 40; //raggio

void setup()
{
  size(500, 500);
  ellipseMode(RADIUS);
}

void draw()
{
  background(0);
  fill(255, 255, 0);

  if (dir == 1)//da sinistra a destra
  {
    arc( x, height/2, r, r, radians(a), radians(360-a) );
  }
  if (dir == -1)//da destra a sinitra
  {
    arc( x, height/2, r, r, radians(180+a), radians(360+180-a) );
  }

  fill(0);
  ellipse(x, height/2-20, 5, 5);//occhio di pacman

  if ( (x >= width-r) || (x < r) )
  {
    dir = -dir;
  }

  if (a > 30 || a <= 0)
  {
    dira = -dira;
  }
  a+=dira*va;
  x+= (dir*v);
}
