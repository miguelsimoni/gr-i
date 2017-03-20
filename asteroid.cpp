// Tipo abstracto de dato que simula un asteroide.

#define MEDIO  20
#define GRANDE 30

#define DIR_IZQ -1
#define DIR_ABA  0
#define DIR_DER  1

// TAD Asteroide.
class Asteroid
{
 private:

 rect Rectangulo;

 public:

 // Radio del asteroide.
 int Vida, Tam, Dir;

 // Coordenadas del asteroide.
 point Coord;


 // Constructor. (por defecto).
 Asteroid(void)
  {
   Coord.X = 0;
   Coord.Y = 480;
   Tam = MEDIO;
   Vida = Tam/10;
   Dir = rand()%3;
  }

 // Constructor.
 Asteroid(point c, int v, int t, int d)
  {
   Coord.X = c.X;
   Coord.Y = c.Y;
   Tam = t;
   Vida = Tam/10;
   Dir = d;
  }

 // Dibujar asteroide.
 void Dibujar(void)
  {
   SetRect(&Rectangulo,Coord.X-Tam,Coord.Y-Tam,Coord.X+Tam,Coord.Y+Tam);
   PenColor(Brown);
   PaintRoundRect(&Rectangulo,Tam+10,Tam+10);
  }

 // Borrar asteroide.
 void Borrar(void)
  {
//   SetRect(&Rectangulo,Coord.X-Tam,Coord.Y-Tam,Coord.X+Tam,Coord.Y+Tam);
   EraseRoundRect(&Rectangulo,Tam+10,Tam+10);
  }

 // Explotar asteroide.
 void Explotar(void)
  {
   int i, Color=Yellow;
   for(i=0; i<5 ;i++)
     {
      sound(Color*100);
      SetRect(&Rectangulo,Coord.X-Tam*i,Coord.Y-(Tam/2)*i,Coord.X+Tam*i,Coord.Y+(Tam/2)*i);
      PenColor(Color);
      FrameOval(&Rectangulo);
      delay(10);
      PenColor(Black);
      FrameOval(&Rectangulo);
      if(Color==Yellow)
        Color=LtRed;
      else
        Color=Yellow;
     }
   nosound();
   Borrar();
   return;
  }

};
