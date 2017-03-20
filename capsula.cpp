// Tipo abstracto de dato que simula una cápsula.

// Tipo de cápsula.
#define ARMA 1
#define VIDA 2
#define PTOS 3


// TAD Capsula.
class Capsula
{
 private:

 rect Rectangulo;

 public:

 // Tipo de capsula.
 int Tipo, Estado;

 // Coordenadas de ubicación de la capsula.
 point Coord;

 // Construcctor. (por defecto).
 Capsula(void)
  {
   Tipo = ARMA;
  }

 // Construcctor.
 Capsula(int t)
  {
   Tipo = t;
  }

 // Dibujar capsula.
 void Dibujar(void);

 // Borrar capsula.
 void Borrar(void);

};


// Dibujar capsula.
void Capsula::Dibujar(void)
 {
  PenColor(Yellow);
  SetRect(&Rectangulo,Coord.X-10,Coord.Y-10,Coord.X+10,Coord.Y+10);
  PaintOval(&Rectangulo);
  switch(Tipo)
    {
     case ARMA: PenColor(LtRed);
                break;
     case VIDA: PenColor(LtBlue);
                break;
     case PTOS: PenColor(LtGreen);
                break;
    }
  SetRect(&Rectangulo,Coord.X-8,Coord.Y-8,Coord.X+8,Coord.Y+8);
  PaintOval(&Rectangulo);
  return;
 }


// Borrar capsula.
void Capsula::Borrar(void)
 {
  SetRect(&Rectangulo,Coord.X-10,Coord.Y-10,Coord.X+10,Coord.Y+10);
  EraseOval(&Rectangulo);
  return;
 }
