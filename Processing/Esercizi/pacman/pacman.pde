int dirx = 1; //direzionex    1 = destra, -1 = sinistra
int diry = 1; //direzioney    1 = sopra, -1 = sotto
int a = 30; //angolo
int dira = -1;
int v = 3; //velocità
int va = v/2; //velocita spostamento bocca
int x = 60;
int y = 60;
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
  
  printX();
  printY();
  
  moveX();
  moveY();


  fill(0);
  ellipse(x, height/2-20, 5, 5);//occhio di pacman
  
}

//metodo W A S D
void keyReleased()
{
  if (key == 'a' || key == 'a')//destra
  {
    dirx = -1;
  }
  if (key == 'd' || key == 'd')//sinistra
  {
    dirx = +1;
  }
  if (key == 'w' || key == 'w')//sopra
  {
    diry = 1;
  }
  if (key == 's' || key == 's')//sotto
  {
    dirx = -1;
  }
}       

void printX()
{
  if (dirx == 1)//da sinistra a destra
  {
    arc(width/2, height/2, r, r, radians(a), radians(360-a) );
  }
  if (dirx == -1)//da destra a sinitra
  {
    arc(width/2, height/2, r, r, radians(180+a), radians(360+180-a) );
  }
}

void printY()
{
   if (diry == 1)//da sotto a sopra
   {
     arc(width/2, height/2, r, r, radians(90+a), radians(360+90-a));
   }
   if (diry == -1)//da sopra a sotto
   {
     arc(width/2, height/2, r, r, radians(270+a), radians(360+270-a));
   }
}


void moveX()
{
  if (x >= width-r || x < r)//se arriva al borso destro || al bordo sinistro
  {
    dirx = -dirx;
  }

  if (a > 30 || a <= 0)
  {
    dira = -dira;
  }
  a+=dira*va;
  x+= dirx;
}


void moveY()
{
  if (y >= height-r || diry < r)//se arriva al bordo superiore o inferiore
  {
    diry = -diry;
  }

  if (a > 30 || a <= 0)
  {
    dira = -dira;
  }
  a+=dira*va;
  y+= diry;
}
