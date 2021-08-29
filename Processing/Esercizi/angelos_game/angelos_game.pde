Angelo A;
ArrayList<Caratteristiche> C;
int numCaratteristiche;
int N;

void setup()
{
  size(1000, 1000);
  N = 1000;
  numCaratteristiche = 10;
  A = new Angelo();
  C = new ArrayList<Caratteristiche>(numCaratteristiche);
}

void draw()
{
  background(0);
  for (Caratteristiche c : C)
  {
    c.run();
  }

  for (int i = 0; i < C.size(); i++)
  {
    A.assorbi(C.get(i));
    if (C.get(i).bounce())
    {
      C.remove(i);
    }
  }

  A.run();
}

void keyPressed() {
  if (key == 'R' || key == 'r') 
  {
    setup();
  }
  
  if (key == 'a' || key == 'A')
  {
    Caratteristiche c = new Caratteristiche(N);
    C.add(c);
  }
}
