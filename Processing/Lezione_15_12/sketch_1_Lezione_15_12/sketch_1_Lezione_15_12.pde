PImage Im, In3, In5, Il, Is, Isx, Ir;
//in sequenza 
//immagine originale, immagine n3-box, immagine n5-box, immagine lapaciano,
//immagine sharpening, immagine sobel x

float n3 = 1/9.0;
float [][] nbox3 = {  {n3, n3, n3},
                      {n3, n3, n3},
                      {n3, n3, n3}  };

float n5 = 1/25.0;
float [][] nbox5 = {  {n5, n5, n5, n5, n5},
                      {n5, n5, n5, n5, n5},
                      {n5, n5, n5, n5, n5}  };                      
                      
float [][] lapl = { {-1, 0, -1},
                    {0, 4, 0},
                    {-1, 0, -1} };                    
               
float [][] sobX = { {-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1} };                   
                    
float [][] sharp = { {-1, 0, -1},
                    {0, 5, 0},
                    {-1, 0, -1} };                 

float [][] random = { {3, 3, 4},
                    {0, 0, 3},
                    {-4, 2, -1} };


void setup()
{
  size(1024, 1024);
  Im = loadImage("lena.png");
  Im.filter(GRAY);
  In3 = converti( convoluzione(Im, nbox3) );
  In5 = converti( convoluzione(Im, nbox5) );
  Il = converti( convoluzione(Im, lapl) );
  Is = converti( convoluzione(Im, sharp) );
  Isx = converti( convoluzione(Im, sobX) );
  Ir = converti( convoluzione(Im, random) );
  
  image(Im, 0, 0);
  image(In3, 512, 0);
  image(Is, 0, 512);
  image(Ir, 512, 512);
}

void draw()
{
}

float [][] convoluzione(PImage I, float [][] K)
{
  float [][] R = new float [I.height][I.width];
  
  int N = K[0].length;
  int M = K.length;
  PImage temp;
  float res;
  
  for (int x = 0; x < I.width; x++)
  {
    for (int y = 0; y < I.height; y++)
    {
       temp = I.get(x - N/2, y-M/2, N, M);
       res = 0; 
       
       for (int p = 0; p < N; p++)
       {
         for (int q = 0; q < M; q++)
         {
            res = res + red(temp.get(p,q)) * K[q][p];
         }
       }
       R[y][x] = res;
    }
  }
  
  return R;
}


PImage converti(float [][] F)
{
  PImage R = createImage(F[0].length, F.length, RGB);
  float res = 0;
  
  for (int x = 0; x < R.width; x++)
  {
    for (int y = 0; y < R.height; y++)
    {
      res = constrain(F[y][x], 0, 255);
      R.set(x, y, color(res));
    }
  }
  return R;
}
