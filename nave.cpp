// Tipo abstracto de dato que simula una nave espacial.

// Tipo de nave.
#define TERRANO 1
#define ENEMIGO 2
#define NODRIZA 3

// Tipo de arma.
#define LASER 1
#define DOBLE 2
#define SUPER 3

// Número máximo posible de vidas.
#define MAXVIDAS 4

// Máximo de puntos del bezier.
#define MAXPT 28


// TAD Nave Espacial.
class Nave
{
 private:

 point PtNave[MAXPT];

 rect Rectangulo;

 //acutaliza las coordenadas del bezier para la nave terrana.
 void SetTerrano(void)
  {
   int i=0;
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-25;  // a
   PtNave[i].X = Coord.X+ 5;  PtNave[i++].Y = Coord.Y-18;  // a,b
   PtNave[i].X = Coord.X+ 5;  PtNave[i++].Y = Coord.Y+ 2;  // b,a
   PtNave[i].X = Coord.X+14;  PtNave[i++].Y = Coord.Y+ 5;  // b
   PtNave[i].X = Coord.X+14;  PtNave[i++].Y = Coord.Y+ 5;  // b,c
   PtNave[i].X = Coord.X+14;  PtNave[i++].Y = Coord.Y+14;  // c,b
   PtNave[i].X = Coord.X+14;  PtNave[i++].Y = Coord.Y+14;  // c
   PtNave[i].X = Coord.X+14;  PtNave[i++].Y = Coord.Y+14;  // c,d
   PtNave[i].X = Coord.X+ 8;  PtNave[i++].Y = Coord.Y+16;  // d,c
   PtNave[i].X = Coord.X+ 8;  PtNave[i++].Y = Coord.Y+16;  // d
   PtNave[i].X = Coord.X+ 8;  PtNave[i++].Y = Coord.Y+16;  // d,e
   PtNave[i].X = Coord.X+ 4;  PtNave[i++].Y = Coord.Y+20;  // e,d
   PtNave[i].X = Coord.X+ 4;  PtNave[i++].Y = Coord.Y+20;  // e
   PtNave[i].X = Coord.X+ 4;  PtNave[i++].Y = Coord.Y+20;  // e,-e
   PtNave[i].X = Coord.X- 4;  PtNave[i++].Y = Coord.Y+20;  //-e,e
   PtNave[i].X = Coord.X- 4;  PtNave[i++].Y = Coord.Y+20;  //-e
   PtNave[i].X = Coord.X- 4;  PtNave[i++].Y = Coord.Y+20;  //-e,-d
   PtNave[i].X = Coord.X- 8;  PtNave[i++].Y = Coord.Y+16;  //-d,-e
   PtNave[i].X = Coord.X- 8;  PtNave[i++].Y = Coord.Y+16;  //-d
   PtNave[i].X = Coord.X- 8;  PtNave[i++].Y = Coord.Y+16;  //-d,-c
   PtNave[i].X = Coord.X-14;  PtNave[i++].Y = Coord.Y+14;  //-c,-d
   PtNave[i].X = Coord.X-14;  PtNave[i++].Y = Coord.Y+14;  //-c
   PtNave[i].X = Coord.X-14;  PtNave[i++].Y = Coord.Y+14;  //-c,-b
   PtNave[i].X = Coord.X-14;  PtNave[i++].Y = Coord.Y+ 5;  //-b,-c
   PtNave[i].X = Coord.X-14;  PtNave[i++].Y = Coord.Y+ 5;  //-b
   PtNave[i].X = Coord.X- 5;  PtNave[i++].Y = Coord.Y+ 2;  //-b,a
   PtNave[i].X = Coord.X- 5;  PtNave[i++].Y = Coord.Y-18;  // a,-b
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-25;  // a
  }


 //acutaliza las coordenadas del bezier para la nave enemiga.
 void SetEnemigo(void)
  {
   int i=0;
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-20;  // a
   PtNave[i].X = Coord.X+12;  PtNave[i++].Y = Coord.Y-18;  // a,b
   PtNave[i].X = Coord.X+18;  PtNave[i++].Y = Coord.Y-12;  // b,a
   PtNave[i].X = Coord.X+20;  PtNave[i++].Y = Coord.Y   ;  // b
   PtNave[i].X = Coord.X+15;  PtNave[i++].Y = Coord.Y+15;  // b,c
   PtNave[i].X = Coord.X+15;  PtNave[i++].Y = Coord.Y+15;  // c,b
   PtNave[i].X = Coord.X+12;  PtNave[i++].Y = Coord.Y+20;  // c
   PtNave[i].X = Coord.X+12;  PtNave[i++].Y = Coord.Y+20;  // c,d
   PtNave[i].X = Coord.X+ 5;  PtNave[i++].Y = Coord.Y+20;  // d,c
   PtNave[i].X = Coord.X+ 5;  PtNave[i++].Y = Coord.Y+20;  // d
   PtNave[i].X = Coord.X+ 5;  PtNave[i++].Y = Coord.Y+20;  // d,e
   PtNave[i].X = Coord.X+ 3;  PtNave[i++].Y = Coord.Y+10;  // e,d
   PtNave[i].X = Coord.X+ 3;  PtNave[i++].Y = Coord.Y+10;  // e
   PtNave[i].X = Coord.X+ 3;  PtNave[i++].Y = Coord.Y+10;  // e,-e
   PtNave[i].X = Coord.X- 3;  PtNave[i++].Y = Coord.Y+10;  //-e,e
   PtNave[i].X = Coord.X- 3;  PtNave[i++].Y = Coord.Y+10;  //-e
   PtNave[i].X = Coord.X- 3;  PtNave[i++].Y = Coord.Y+10;  //-e,-d
   PtNave[i].X = Coord.X- 5;  PtNave[i++].Y = Coord.Y+20;  //-d,-e
   PtNave[i].X = Coord.X- 5;  PtNave[i++].Y = Coord.Y+20;  //-d
   PtNave[i].X = Coord.X- 5;  PtNave[i++].Y = Coord.Y+20;  //-d,-c
   PtNave[i].X = Coord.X-12;  PtNave[i++].Y = Coord.Y+20;  //-c,-d
   PtNave[i].X = Coord.X-12;  PtNave[i++].Y = Coord.Y+20;  //-c
   PtNave[i].X = Coord.X-15;  PtNave[i++].Y = Coord.Y+15;  //-c,-b
   PtNave[i].X = Coord.X-15;  PtNave[i++].Y = Coord.Y+15;  //-b,-c
   PtNave[i].X = Coord.X-20;  PtNave[i++].Y = Coord.Y   ;  //-b
   PtNave[i].X = Coord.X-18;  PtNave[i++].Y = Coord.Y-12;  //-b,a
   PtNave[i].X = Coord.X-12;  PtNave[i++].Y = Coord.Y-18;  // a,-b
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-20;  // a
  }


 //acutaliza las coordenadas del bezier para la nave nodriza.
 void SetNodriza(void)
  {
   int i=0;
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-20;  // a
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-20;  // a,b
   PtNave[i].X = Coord.X+20;  PtNave[i++].Y = Coord.Y-30;  // b,a
   PtNave[i].X = Coord.X+20;  PtNave[i++].Y = Coord.Y-40;  // b
   PtNave[i].X = Coord.X+20;  PtNave[i++].Y = Coord.Y-30;  // b,c
   PtNave[i].X = Coord.X+20;  PtNave[i++].Y = Coord.Y-80;  // c,b
   PtNave[i].X = Coord.X+20;  PtNave[i++].Y = Coord.Y-70;  // c
   PtNave[i].X = Coord.X+24;  PtNave[i++].Y = Coord.Y-80;  // c,d
   PtNave[i].X = Coord.X+36;  PtNave[i++].Y = Coord.Y-80;  // d,c
   PtNave[i].X = Coord.X+40;  PtNave[i++].Y = Coord.Y-80;  // d
   PtNave[i].X = Coord.X+36;  PtNave[i++].Y = Coord.Y   ;  // d,e
   PtNave[i].X = Coord.X+36;  PtNave[i++].Y = Coord.Y   ;  // e,d
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y+10;  // e
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y+10;  // e,-e
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y+10;  //-e,e
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y+10;  //-e
   PtNave[i].X = Coord.X-36;  PtNave[i++].Y = Coord.Y   ;  //-e,-d
   PtNave[i].X = Coord.X-36;  PtNave[i++].Y = Coord.Y   ;  //-d,-e
   PtNave[i].X = Coord.X-40;  PtNave[i++].Y = Coord.Y-80;  //-d
   PtNave[i].X = Coord.X-36;  PtNave[i++].Y = Coord.Y-80;  //-d,-c
   PtNave[i].X = Coord.X-24;  PtNave[i++].Y = Coord.Y-80;  //-c,-d
   PtNave[i].X = Coord.X-20;  PtNave[i++].Y = Coord.Y-70;  //-c
   PtNave[i].X = Coord.X-20;  PtNave[i++].Y = Coord.Y-80;  //-c,-b
   PtNave[i].X = Coord.X-20;  PtNave[i++].Y = Coord.Y-30;  //-b,-c
   PtNave[i].X = Coord.X-20;  PtNave[i++].Y = Coord.Y-40;  //-b
   PtNave[i].X = Coord.X-20;  PtNave[i++].Y = Coord.Y-30;  //-b,a
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-20;  // a,-b
   PtNave[i].X = Coord.X   ;  PtNave[i++].Y = Coord.Y-20;  // a
  }


 public:

 // Características.
 int Vida, Tipo, Arma, NumArmas;

 // Coordenadas.
 point Coord;


 // Constructor. (por defecto).
 Nave(void)
  {
   Coord.X = 0;
   Coord.Y = 0;
   Vida = 1;
   Tipo = ENEMIGO;
   NumArmas = Arma = LASER;
   SetEnemigo();
   SetRect(&Rectangulo,Coord.X-20,Coord.Y-20,Coord.X+20,Coord.Y+20);
  }

 // Constructor.
 Nave(point c, int v, int t)
  {
   Coord.X = c.X;
   Coord.Y = c.Y;
   Vida = v;
   Tipo = t;
   NumArmas = Arma = LASER;
  }

 // Asignar proiedades a la nave.
 void SetNave(point c, int v, int t, int a)
  {
   Coord.X = c.X;
   Coord.Y = c.Y;
   Vida = v;
   Tipo = t;
   NumArmas = Arma = a;
  }

 // Sumar vida extra.
 void SumarVida(void)
  {
   if(Vida<MAXVIDAS)
	 Vida++;
  }

 // Agregar arma a la nave.
 void AgregarArma(void)
  {
   if(NumArmas<SUPER)
	 NumArmas++;
  }

 // Cambiar Arma.
 void CambiarArma(void)
  {
   if(NumArmas>Arma)
     Arma++;
   else
     Arma=LASER;
  }

 // Dibujar la nave espacial.
 void Dibujar(void);

 // Dibujar la nave espacial enemiga.
 void Dibujar(int Color);

 // Borrar la nave espacial.
 void Borrar(void);

 // Disparo de la nave espacial.
 void Disparar(void);

 // Explosion de la nave espacial.
 void Explotar(void);

};


// Dibujar nave espacial.
void Nave::Dibujar(void)
 {
  SetTerrano();
  PenColor(White);
  PaintBezier(PtNave,MAXPT);
  PenColor(Blue);
  FrameBezier(PtNave,MAXPT);
  PenColor(Red);
  SetRect(&Rectangulo,Coord.X+14,Coord.Y,Coord.X+20,Coord.Y+28);
  PaintRoundRect(&Rectangulo,5,5);
  SetRect(&Rectangulo,Coord.X-14,Coord.Y,Coord.X-20,Coord.Y+28);
  PaintRoundRect(&Rectangulo,5,5);
  PenColor(LtRed);
  SetRect(&Rectangulo,Coord.X-6,Coord.Y-2,Coord.X+6,Coord.Y+15);
  PaintOval(&Rectangulo);
  PenColor(Blue);
  SetRect(&Rectangulo,Coord.X-5,Coord.Y+3,Coord.X+5,Coord.Y+14);
  PaintOval(&Rectangulo);
  return;
 }

// Dibujar nave espacial enemmiga (de distintos colores).
void Nave::Dibujar(int Color)
 {
  if(Tipo==ENEMIGO)
    {
     SetEnemigo();
     PenColor(Color);
     PaintBezier(PtNave,MAXPT);
     PenColor(Color-8);
     if(Color==LtGray)  PenColor(Color+1);
     FrameBezier(PtNave,MAXPT);
     PenColor(Gray);
     SetRect(&Rectangulo,Coord.X-12,Coord.Y-10,Coord.X+12,Coord.Y+5);
     PaintOval(&Rectangulo);
     PenColor(Blue);
     SetRect(&Rectangulo,Coord.X-10,Coord.Y-5,Coord.X+10,Coord.Y+5);
     PaintOval(&Rectangulo);
    }
  else
    {
     SetNodriza();
     PenColor(Green);
     PaintBezier(PtNave,MAXPT);
     SetRect(&Rectangulo,Coord.X-30,Coord.Y,Coord.X+30,Coord.Y+80);
     PaintOval(&Rectangulo);
     PenColor(Red);
     SetRect(&Rectangulo,Coord.X-15,Coord.Y-50,Coord.X+15,Coord.Y);
     PaintOval(&Rectangulo);
     SetRect(&Rectangulo,Coord.X-40,Coord.Y+20,Coord.X-10,Coord.Y+60);
     PaintOval(&Rectangulo);
     SetRect(&Rectangulo,Coord.X+10,Coord.Y+20,Coord.X+40,Coord.Y+60);
     PaintOval(&Rectangulo);
    }
  return;
 }

// Borrar la nave espacial.
void Nave::Borrar(void)
 {
  if(Tipo==NODRIZA)
    SetRect(&Rectangulo,Coord.X-60,Coord.Y-80,Coord.X+60,Coord.Y+80);
  else
    SetRect(&Rectangulo,Coord.X-21,Coord.Y-30,Coord.X+21,Coord.Y+30);
  EraseRect(&Rectangulo);
  return;
 }

// Disparo de la nave espacial.
void Nave::Disparar(void)
 {
  if(Tipo==TERRANO)
    {
     switch(Arma)
       {
        case 1: PenColor(LtRed);
                SetRect(&Rectangulo,Coord.X-3,Coord.Y-30,Coord.X+3,Coord.Y-25);
                PaintOval(&Rectangulo);
                MoveTo(Coord.X,Coord.Y-25);
                LineTo(Coord.X,40);
                break;
        case 2: PenColor(LtGreen);
                SetRect(&Rectangulo,Coord.X-20,Coord.Y-5,Coord.X-15,Coord.Y);
                PaintOval(&Rectangulo);
                SetRect(&Rectangulo,Coord.X+20,Coord.Y-5,Coord.X+15,Coord.Y);
                PaintOval(&Rectangulo);
                MoveTo(Coord.X-17,Coord.Y);
                LineTo(Coord.X-17,40);
                MoveTo(Coord.X+17,Coord.Y);
                LineTo(Coord.X+17,40);
                break;
        case 3: PenColor(LtCyan);
                SetRect(&Rectangulo,Coord.X-3,Coord.Y-30,Coord.X+3,Coord.Y-25);
                PaintOval(&Rectangulo);
                SetRect(&Rectangulo,Coord.X-20,Coord.Y-5,Coord.X-15,Coord.Y);
                PaintOval(&Rectangulo);
                SetRect(&Rectangulo,Coord.X+20,Coord.Y-5,Coord.X+15,Coord.Y);
                PaintOval(&Rectangulo);
                MoveTo(Coord.X,Coord.Y-20);
                LineTo(Coord.X,40);
                MoveTo(Coord.X-17,Coord.Y);
                LineTo(Coord.X-17,40);
                MoveTo(Coord.X+17,Coord.Y);
                LineTo(Coord.X+17,40);
                break;
       }
     for(int i=1;i<=5;i++)
       {
        sound(300*i*Arma);
        delay(5);
       }
     PenColor(Black);
     switch(Arma)
       {
        case 1: MoveTo(Coord.X,Coord.Y-20);
                LineTo(Coord.X,40);
                break;
        case 2: MoveTo(Coord.X-17,Coord.Y);
                LineTo(Coord.X-17,40);
                MoveTo(Coord.X+17,Coord.Y);
                LineTo(Coord.X+17,40);
                break;
        case 3: MoveTo(Coord.X,Coord.Y-20);
                LineTo(Coord.X,40);
                MoveTo(Coord.X-17,Coord.Y);
                LineTo(Coord.X-17,40);
                MoveTo(Coord.X+17,Coord.Y);
                LineTo(Coord.X+17,40);
                break;
       }
    }
  if(Tipo==ENEMIGO)
    {
     SetRect(&Rectangulo,Coord.X-5,Coord.Y+5,Coord.X+5,Coord.Y+15);
     PenColor(LtRed);
     PaintOval(&Rectangulo);
     delay(10);
     PenColor(LtRed);
     MoveTo(Coord.X,Coord.Y+20);
     LineTo(Coord.X,480);
     for(int i=1;i<=5;i++)
       {
        sound(500*i);
        delay(5);
       }
     PenColor(Black);
     MoveTo(Coord.X,Coord.Y+20);
     LineTo(Coord.X,480);
    }
  if(Tipo==NODRIZA)
    {
     PenColor(LtRed);
     SetRect(&Rectangulo,Coord.X-40,Coord.Y+20,Coord.X-10,Coord.Y+60);
     PaintOval(&Rectangulo);
     SetRect(&Rectangulo,Coord.X+10,Coord.Y+20,Coord.X+40,Coord.Y+60);
     PaintOval(&Rectangulo);
     delay(20);
     PenColor(LtRed);
     SetRect(&Rectangulo,Coord.X-40,Coord.Y+40,Coord.X-10,480);
     PaintRect(&Rectangulo);
     SetRect(&Rectangulo,Coord.X+10,Coord.Y+40,Coord.X+40,480);
     PaintRect(&Rectangulo);
     for(int i=1;i<=5;i++)
       {
        sound(500*i);
        delay(5);
       }
     PenColor(Black);
     SetRect(&Rectangulo,Coord.X-40,Coord.Y+40,Coord.X-10,480);
     EraseRect(&Rectangulo);
     SetRect(&Rectangulo,Coord.X+10,Coord.Y+40,Coord.X+40,480);
     EraseRect(&Rectangulo);
    }
  nosound();
  return;
 }


// Explosion de la nave espacial.
void Nave::Explotar(void)
 {
  int i, Color=Yellow;
  for(i=0; i<5 ;i++)
    {
     sound(Color*100);
     SetRect(&Rectangulo,Coord.X-15*i,Coord.Y-8*i,Coord.X+15*i,Coord.Y+8*i);
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
  if(Tipo==NODRIZA)
    {
     for(i; i<=10 ;i++)
       {
        sound(Color*100);
        SetRect(&Rectangulo,Coord.X-15*i,Coord.Y-8*i,Coord.X+15*i,Coord.Y+8*i);
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
    }
  Borrar();
  nosound();
  return;
 }
