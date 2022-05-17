class Caratteristiche
{
  float x, y;
  String frase;
  String Frase_Positiva;
  int dim; 
  boolean car_positiva;//vaccino
  boolean car_negativa;//infetto

  Caratteristiche(int N)
  {
    x = random(20, N-20);
    y = random(20, N-20);

    int negative = int(random(0, 7));
    switch(negative)
    {
    case 0: 
      frase = "Bill Gates";
      break;
    case 1: 
      frase = "La terra e piatta";
      break;
    case 2: 
      frase = "I soldi non fanno la felicita";
      break;
    case 3: 
      frase = "I vaccini";
      break;
    case 4: 
      frase = "Dire cose senza senso";
      break;
    case 5:
      frase = "Stickers";
      break;
    case 6:
      frase = "Farsi bannare dai gruppi";
      break;
    }
    
    int positive = int(random(0, 3));
    
    switch(positive)
    {
    case 0: 
      Frase_Positiva = "Fare After";
      break;
    case 1: 
      Frase_Positiva = "Uscire";
      break;
    case 2: 
      Frase_Positiva = "Intelligenza";
      break;
    }

    dim = int(random(70, 130));
    car_negativa = false;

    if (int(random(0, 4)) == 0)
    {
      car_positiva = true;
    } else
    {
      car_negativa = false;
    }
  }

  void dispay()
  {
    fill(255);
    rectMode(CENTER);
    rect(x, y, dim, dim);

    if (car_positiva == true)
    {
      fill(255);
      rect(x, y, dim, dim/2); 
      fill(0);
      textAlign(CENTER);
      text(Frase_Positiva, x, y, dim, dim/2);
    }

    if (car_negativa)
    { 
      fill(0);
      textAlign(CENTER);
      text(frase, x, y, dim, dim/2);
      dim -= 0.01;
    }
  }

  boolean bounce()
  {
    if (y>=height || y <=0 || x>= width || x <=0)
    {
      return true;
    } else
    {
      return false;
    }
  }

  void move()
  {
    if (int(random(0, 2)) == 0)
    {
      y += 0.5;
    } else
    {
      x += 0.5;
    }
  }

  void setColor()
  {
    car_negativa = true;
    dispay();
  }

  void run()
  {
    dispay();
    move();
  }
}
