// LIBRERIAS.
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include"c:\programs\metawin\metawndo.h"
#include"c:\programs\metawin\metfind.c"
#include"c:\programs\pcxlab\pcxlab.h"
#include"c:\projects\pg\boton.cpp"
#include"c:\projects\pg\nave.cpp"
#include"c:\projects\pg\record.cpp"
#include"c:\projects\pg\capsula.cpp"
#include"c:\projects\pg\asteroid.cpp"
#include"c:\projects\pg\secuen.cpp"


// CONSTANTES Y MACROS.

#define XMAX 640
#define YMAX 480

#define MAX_ESTRELLAS  200
#define MAX_ENEMIGOS   3
#define MAX_ASTEROIDES 5

#define FACIL   1      // Nivel de Difivultad: Sencillo.
#define NORMAL  2      // Nivel de Difivultad: Normal.
#define DIFICIL 3      // Nivel de Difivultad: Experto.

#define NIVEL_FINAL 3  // Número del nivel final.

#define TECLADO  0
#define RATON    1


// VARIABLES GLOBALES.

point Punto;
rect Rectangulo;
mwEvent Evento;

int Dificultad, Nivel, Control;

double Score, HiScore;

Nave Terrano, Enemigo[MAX_ENEMIGOS];

Asteroid Asteroide[MAX_ASTEROIDES];

Capsula Capsula1;

Record Jugador;


// FUNCIONES Y PROCEDIMIENTOS.

// Ayuda.
void Ayuda(void)
 {
  char NombreBoton[20]=" Aceptar";
  Boton Boton1;
  rect BotonLim;
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  Universo(Rectangulo,250,0);
  BotonLim.Xmin = 270;
  BotonLim.Xmax = 360;
  BotonLim.Ymin = 400;
  BotonLim.Ymax = 420;
  Boton1.SetBoton(NombreBoton,BotonLim,Red,LtRed);
  Boton1.Dibujar();
  MoveTo(280,90);
  DrawString("AYUDA");
  MoveTo(168,120);
  DrawString("          MOUSE = Movimientos.   ");
  MoveTo(168,140);
  DrawString("BOTON IZQUIERDO = Disparar.      ");
  MoveTo(168,160);
  DrawString("  BOTON DERECHO = Cambiar Arma.  ");
  MoveTo(168,180);
  DrawString(" TECLAS FLECHAS = Mvimientos.    ");
  MoveTo(168,200);
  DrawString("        ESPACIO = Disparar.      ");
  MoveTo(168,220);
  DrawString("              C = Cambiar Arma.  ");
  MoveTo(168,240);
  DrawString("              P = Pausa.         ");
  MoveTo(168,260);
  DrawString("            ESC = Abandoar.      ");
  MoveTo(168,280);
  DrawString("          ENTER = Jugar.         ");
  int Sw=1;
  do{
	 if(KeyEvent(False,&Evento))
	   {
		Punto.X = Evento.eventX;
		Punto.Y = Evento.eventY;
		switch(Evento.eventType)
		  {
           case evntPRESS:
                if(Boton1.Presionado(Punto,Evento))
                  Boton1.DibPres();
                break;
           case evntRELEASE:
                if(Boton1.Apuntado(Punto))
                  {
                   Sw=0;
                   Boton1.DibNoPres();
                   break;
                  }
                if(!Boton1.Apuntado(Punto))
                  Boton1.DibNoPres();
                break;
		   case evntKEYDN:
                switch(Evento.eventScan)
                  {
                   case  1: //ESC
                        Sw=0;
                        break;
                   case 28: //ENTER
                        Sw=0;
                        break;
                  }
				break;
		  }
	   }
    }while(Sw);
  Boton1.Borrar();
 }


// Aumentar puntaje.
void UpScore(int n)
 {
  Score += n;
  if(Score > HiScore)
    HiScore = Score;
 }


// Destruccion del enemigo.
int Destruir(void)
 {
  int i, rng,  //rango de acción del arma actual.
      Destruidos = 0;
  for(i=0; i < Dificultad && Nivel%2==1 && Enemigo[i].Tipo==ENEMIGO;i++)
    {
     rng = Terrano.Arma*10 + 15;
	 if(Terrano.Coord.X >= Enemigo[i].Coord.X-rng  &&
		Terrano.Coord.X <= Enemigo[i].Coord.X+rng  &&
        Terrano.Coord.Y > Enemigo[i].Coord.Y)
       {
        Enemigo[i].Vida--;
        if(Enemigo[i].Vida==0)
          {
           Enemigo[i].Explotar();
           Enemigo[i].Coord.Y = YMAX;
           UpScore( 10*Nivel*Dificultad );
           Destruidos++;
          }
        break;
       }
    }
  for(i=0; i < Dificultad+2 && Nivel%2==0 ;i++)
    {
     rng = Terrano.Arma*10 + Asteroide[i].Tam/2;
	 if(Terrano.Coord.X >= Asteroide[i].Coord.X-rng  &&
		Terrano.Coord.X <= Asteroide[i].Coord.X+rng  &&
        Terrano.Coord.Y > Asteroide[i].Coord.Y)
       {
        Asteroide[i].Vida--;
        if(Asteroide[i].Vida==0)
          {
           Asteroide[i].Explotar();
           Asteroide[i].Coord.Y = YMAX;
           UpScore( (Asteroide[i].Tam/2)*Nivel*Dificultad );
           Destruidos++;
          }
        break;
       }
    }
  if(Nivel==NIVEL_FINAL && Enemigo[0].Tipo==NODRIZA)
    {
     rng = Terrano.Arma*10 + 30;
	 if(Terrano.Coord.X >= Enemigo[0].Coord.X-rng  &&
		Terrano.Coord.X <= Enemigo[0].Coord.X+rng  &&
        Terrano.Coord.Y > Enemigo[0].Coord.Y)
       {
        Enemigo[0].Vida--;
        int Color=Yellow;
        for(i=0; i<5 ;i++)
          {
           sound(Color*100);
           SetRect(&Rectangulo,Terrano.Coord.X-15*i,Enemigo[0].Coord.Y-8*i,
                               Terrano.Coord.X+15*i,Enemigo[0].Coord.Y+8*i);
           PenColor(Color);
           FrameOval(&Rectangulo);
           delay(5);
           PenColor(Black);
           FrameOval(&Rectangulo);
           if(Color==Yellow)
             Color=LtRed;
           else
             Color=Yellow;
          }
        if(Enemigo[0].Vida==0)
          {
           TrackCursor(False);
           for(i=0; i<5*Dificultad ;i++)
             Enemigo[0].Explotar();
           TrackCursor(True);
           UpScore( 100*Dificultad );
          }
        UpScore( 50*Dificultad );
        nosound();
       }
    }
  return Destruidos;
 }


void VisualizarEstado(int Destruidos, int Generados)
 {
  char cad[75];
  PenColor(LtBlue);
  //ventana de estado de la nave.
  SetRect(&Rectangulo,1,1,639,38);
  FrameRect(&Rectangulo);
  PenColor(Yellow);
  //visualizar vida.
  strcpy(cad,"Vidas  ");
  for(int i=0; i<=Terrano.Vida ;i++)
    strcat(cad,"@");
//  strcat(cad,itoa(Terrano.Vida,NULL,10));
  MoveTo(10,10);
  DrawString(cad);
  //visualizar arma.
  strcpy(cad,"Arma   ");
  switch(Terrano.Arma)
    {
     case 1: strcat(cad,"Laser      ");
             break;
     case 2: strcat(cad,"Laser Doble");
             break;
     case 3: strcat(cad,"Super Laser");
             break;
    }
  MoveTo(10,30);
  DrawString(cad);
  //visualizar puntaje.
  strcpy(cad,"Puntaje   ");
  strcat(cad,itoa(Score,NULL,10));
  MoveTo(170,10);
  DrawString(cad);
  //visualizar puntaje más alto.
  strcpy(cad,"Mas alto  ");
  strcat(cad,itoa(HiScore,NULL,10));
  MoveTo(170,30);
  DrawString(cad);
  //visualizar dificultad.
  strcpy(cad,"Dificultad  ");
  switch(Dificultad)
    {
     case 1: strcat(cad,"Sencillo");
             break;
     case 2: strcat(cad,"Normal  ");
             break;
     case 3: strcat(cad,"Experto ");
             break;
    }
  MoveTo(310,10);
  DrawString(cad);
  //visualizar nivel.
  strcpy(cad,"Mision      ");
  strcat(cad,itoa(Nivel,NULL,10));
  MoveTo(310,30);
  DrawString(cad);
  //visualizar enemigos destruidos.
  strcpy(cad,"Destruidos  ");
  strcat(cad,itoa(Destruidos,NULL,10));
  MoveTo(500,10);
  DrawString(cad);
  //visualizar enemigos generados.
  strcpy(cad,"Generados   ");
  strcat(cad,itoa(Generados,NULL,10));
  MoveTo(500,30);
  DrawString(cad);
 }


// Pausar el juego.
void Pausa(void)
 {
  TrackCursor(False);
  PenColor(Yellow);
  BackColor(Black);
  MoveTo(310,240);
  DrawString("PAUSA");
  int Sw=1;
  do{
     if(KeyEvent(False,&Evento))
       if(Evento.eventType == evntKEYDN)
         if(Evento.eventScan == 25)  //P
           Sw=0;
    }while(Sw);
  MoveTo(310,240);
  DrawString("     ");
  TrackCursor(True);
 }


// Juego.
int Juego()
 {
  char cad[75];
  int i, Fin, Win=-1,
      Generados=0,  //contador de enemigos generados.
      Destruidos=0, //contador de enemigos destruidos.
      ColorEnemigo[MAX_ENEMIGOS];

  point Estrella[MAX_ESTRELLAS];

  Capsula1.Estado = False;
  HideCursor();
  //inicializar coordenadas de las naves enemigas.
  for(i=0;i<MAX_ENEMIGOS;i++)
    {
     Enemigo[i].Coord.X = Punto.X = 0;
     Enemigo[i].Coord.Y = Punto.Y = YMAX;
     Enemigo[i].SetNave(Punto,1,ENEMIGO,LASER);
     ColorEnemigo[i] = 0;
    }
  //inicializar coordenadas de los asteroides.
  for(i=0;i<MAX_ASTEROIDES;i++)
    {
     Asteroide[i].Coord.X = 0;
     Asteroide[i].Coord.Y = YMAX;
    }
  //generar coordenadas de las estrellas.
  for(i=0;i<MAX_ESTRELLAS;i++)
    {
     Estrella[i].X = rand()%XMAX;
     Estrella[i].Y = rand()%(YMAX-40)+40;
    }
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  //inicializar raton como mando del juego.
  LimitMouse(20,70,XMAX-20,YMAX-30);
  Terrano.Coord.X = XMAX/2;
  Terrano.Coord.Y = YMAX-60;
  TrackCursor(False);
  MoveCursor(Terrano.Coord.X,Terrano.Coord.Y);
  TrackCursor(True);
  if(Nivel==NIVEL_FINAL)
    Fin=0;
  else
    Fin=1;
  //bucle indefinido del juego, hasta que se presione escape.
  int Sw = True;
  do{
     //avance de estrellas.
     for(i=0;i<MAX_ESTRELLAS;i++)
       {
        if(Estrella[i].Y >= 480)
          {
           Estrella[i].X = rand()%XMAX;
           Estrella[i].Y = 40;
          }
        PenColor(White);
        SetPixel(Estrella[i].X,Estrella[i].Y);
        Estrella[i].Y += 5;
        SetPixel(Estrella[i].X,Estrella[i].Y);
        PenColor(Black);
        SetPixel(Estrella[i].X,Estrella[i].Y-5);
       }
     VisualizarEstado(Destruidos,Generados);
	 if(KeyEvent(False,&Evento))
       {
        switch(Evento.eventType)
          {
		   case evntPRESS:
                switch(Evento.eventButtons)
                  {
                   case swLeft:
						Terrano.Disparar();
                        Destruidos += Destruir();
                        break;
                   case swRight:
						Terrano.CambiarArma();
                        break;
                  }
                break;
		   case evntRELEASE:
                
                break;
		   case evntKEYDN:
                switch(Evento.eventScan)
                  {
                   case  1: //ESC
                            Sw=0;
                            Win=-1;
                            goto SALIR;
                   case 25: //P
                            Pausa();
                            break;
                   case 59: //F1
                            ScreenRect(&Rectangulo);
                            EraseRect(&Rectangulo);
                            ShowCursor();
                            Ayuda();
                            HideCursor();
                            ScreenRect(&Rectangulo);
                            EraseRect(&Rectangulo);
                            break;
                   case 72: //FLECHA ARRIBA
							if(Terrano.Coord.Y > 80)
							  Terrano.Coord.Y-=20;
                            break;
                   case 80: //FLECHA ABAJO
							if(Terrano.Coord.Y < YMAX-20)
							  Terrano.Coord.Y+=20;
                            break;
                   case 75: //FLECHA IZQUIERDA
							if(Terrano.Coord.X > 20)
							  Terrano.Coord.X-=20;
                            break;
                   case 77: //FLECHA DERECHA
							if(Terrano.Coord.X < XMAX-20)
							  Terrano.Coord.X+=20;
                            break;
                   case 57: //ESPACIO
							Terrano.Disparar();
                            Destruidos += Destruir();
                            break;
                   case 46: //C
							Terrano.CambiarArma();
                            break;
                  }
				break;
		   case evntKEYUP:

				break;
		   case evntMOVE:

				break;
          }
	   }
     //dibujar nave.
	 Terrano.Borrar();
     if(Control==RATON)
       {
		Terrano.Coord.X = Evento.eventX;
		Terrano.Coord.Y = Evento.eventY;
       }
	 Terrano.Dibujar();
     if(Sw && Win<0)
       {
        Win=0;
        PenColor(White);
        MoveTo(290,240);
        DrawString("ADELANTE...");
        sleep(1);
        MoveTo(290,240);
        DrawString("           ");
       }
     //borrar naves enemigas.
     for(i=0; i<Dificultad && !Win && Nivel%2==1 ;i++)
        Enemigo[i].Borrar();
     //naves enemigas.
     for(i=0; i<Dificultad && !Win && Nivel%2==1 ;i++)
       {
        //generar nave enemiga.
        if(Enemigo[i].Coord.Y >= YMAX)
          {
           Enemigo[i].Coord.X = rand()%(XMAX-20)+10;
           Enemigo[i].Coord.Y = 65;
             Enemigo[i].Vida = 1;
           ColorEnemigo[i] = rand()%8+8;
           if(ColorEnemigo[i]==Gray)  ColorEnemigo[i]=LtGray;
           if(Destruidos<Dificultad*Nivel*10)  Generados++;
          }
        //mover nave enemiga.
        Enemigo[i].Coord.Y += 1+i;
        switch(rand()%3)
          {
           case 0: break;
           case 1: if(Enemigo[i].Coord.X < XMAX-15)
                     Enemigo[i].Coord.X += 2+i;
                   break;
           case 2: if(Enemigo[i].Coord.X > 15)
                     Enemigo[i].Coord.X -= 2-i;
                   break;
          }
        //dibujar nave enemiga.
        Enemigo[i].Dibujar(ColorEnemigo[i]);
        //disparo de nave enemiga.
       if(rand()%100==0 && Nivel==NIVEL_FINAL)
          {
           Enemigo[i].Disparar();
		   if(Enemigo[i].Coord.X >= Terrano.Coord.X-5  &&
			  Enemigo[i].Coord.X <= Terrano.Coord.X+5  &&
			  Enemigo[i].Coord.Y < Terrano.Coord.Y)
             {
			  Terrano.Explotar();
              Sw=0;
              Win=0;
             }
          }
	   }
     //choque y muerte con nave enemiga.
     for(i=0; i<Dificultad && !Win && Nivel%2==1 ;i++)
		if(Terrano.Coord.X>Enemigo[i].Coord.X-30 &&
		   Terrano.Coord.X<Enemigo[i].Coord.X+30 &&
		   Terrano.Coord.Y>Enemigo[i].Coord.Y-30 &&
		   Terrano.Coord.Y<Enemigo[i].Coord.Y+30)
          {
           Enemigo[i].Explotar();
		   Terrano.Explotar();
           Sw=0;
           Win=0;
          }
     //borrar asteroides.
     for(i=0; i<Dificultad+1 && !Win && Nivel%2==0 ;i++)
        Asteroide[i].Borrar();
     //asteroides.
     for(i=0; i<Dificultad+1 && !Win && Nivel%2==0 ;i++)
       {
        //generar asteroide.
        if(Asteroide[i].Coord.Y >= YMAX  ||  Asteroide[i].Coord.X >= XMAX  ||
           Asteroide[i].Coord.X <= 0)
          {
           if(rand()%2)
             Asteroide[i].Tam = MEDIO;
           else
             Asteroide[i].Tam = GRANDE;
           Asteroide[i].Coord.X = rand()%(XMAX-20)+10;
           Asteroide[i].Coord.Y = 45 + Asteroide[i].Tam;
           Asteroide[i].Vida = Asteroide[i].Tam/10 - 1;
           switch(rand()%3)
             {
              case 0: Asteroide[i].Dir = DIR_IZQ;
                      break;
              case 1: Asteroide[i].Dir = DIR_ABA;
                      break;
              case 2: Asteroide[i].Dir = DIR_DER;
                      break;
             }
           if(Destruidos<Dificultad*Nivel*10)  Generados++;
          }
        //mover asteroide.
        Asteroide[i].Coord.Y += 1+i;
        Asteroide[i].Coord.X += Asteroide[i].Dir;
        //dibujar asteroide.
        Asteroide[i].Dibujar();
	   }
     //choque y muerte con asteroide.
     for(i=0; i<Dificultad+1 && !Win && Nivel%2==0 ;i++)
		if(Terrano.Coord.X>Asteroide[i].Coord.X-40 &&
		   Terrano.Coord.X<Asteroide[i].Coord.X+40 &&
		   Terrano.Coord.Y>Asteroide[i].Coord.Y-40 &&
		   Terrano.Coord.Y<Asteroide[i].Coord.Y+40)
          {
           Asteroide[i].Explotar();
		   Terrano.Explotar();
           Sw=0;
           Win=0;
          }
     //generar capsula.
     if(rand()%(600/Nivel)==0 && !Capsula1.Estado)
       {
        Capsula1.Estado = True;
        switch(rand()%10)
          {
           case 0: Capsula1.Tipo = VIDA;
                   break;
           case 1: Capsula1.Tipo = ARMA;
                   break;
           case 2: Capsula1.Tipo = ARMA;
                   break;
           case 3: Capsula1.Tipo = PTOS;
                   break;
           default: break;
          }
        Capsula1.Coord.X = rand()%(XMAX-20)+10;
        Capsula1.Coord.Y = 70;
       }
     //controlar capsula.
     if(Capsula1.Estado)
       {
        Capsula1.Borrar();
        Capsula1.Coord.Y++;
        Capsula1.Dibujar();
		if(Terrano.Coord.X>Capsula1.Coord.X-15 &&
		   Terrano.Coord.X<Capsula1.Coord.X+15 &&
		   Terrano.Coord.Y>Capsula1.Coord.Y-15 &&
		   Terrano.Coord.Y<Capsula1.Coord.Y+15)
          {
           for(i=1;i<=10;i++)
             {
              sound(500*i);
              delay(5);
             }
           Capsula1.Coord.Y = YMAX;
           switch(Capsula1.Tipo)
             {
			  case VIDA: Terrano.SumarVida();
                         UpScore(200);
                         break;
			  case ARMA: Terrano.AgregarArma();
                         if(Terrano.Arma<SUPER)
                           Terrano.CambiarArma();
                         UpScore(100);
                         break;
              case PTOS: UpScore(500);
                         break;
             }
           nosound();
          }
        if(Capsula1.Coord.Y==YMAX)
          {
           Capsula1.Estado = False;
           Capsula1.Borrar();
          }
       }
     //nave enemiga final.
     if(Destruidos==Dificultad*Nivel*10 && Nivel==NIVEL_FINAL && !Fin)
       {
        if(Win==0)
          {
           for(i=0; i<20; i++)
             {
              sound(i*500);
              delay(20);
             }
           for(i=0; i<Dificultad ;i++)
             Enemigo[i].Borrar();
           Win=1;
           Enemigo[0].Coord.X = Punto.X = XMAX/2;
           Enemigo[0].Coord.Y = Punto.Y = 160;
           Enemigo[0].SetNave(Punto,Dificultad*10,NODRIZA,LASER);
           nosound();
          }
        //visualizar vida de nave enemiga final.
        strcpy(cad,"NAVE NODRIZA  ");
        for(int i=0; i<Enemigo[0].Vida ;i++)
          strcat(cad,"@");
        PenColor(Yellow);
        MoveTo(10,50);
        DrawString("                                            ");
        MoveTo(10,50);
        DrawString(cad);
        //borrar la nave enemiga final.
        Enemigo[0].Borrar();
        //mover nave enemiga final.
        switch(rand()%3)
          {
           case 0: if(Enemigo[0].Coord.X < XMAX-40)
                     Enemigo[0].Coord.X += 3;
                   break;
           case 1: break;
           case 2: if(Enemigo[0].Coord.X > 40)
                     Enemigo[0].Coord.X -= 3;
                   break;
          }
        switch(rand()%3)
          {
           case 0: if(Enemigo[0].Coord.Y < YMAX-140)
                     Enemigo[0].Coord.Y += 3;
                   break;
           case 1: break;
           case 2: if(Enemigo[0].Coord.Y > 140)
                     Enemigo[0].Coord.Y -= 3;
                   break;
          }
        //dibujar nave enemiga final.
        Enemigo[0].Dibujar(Black);
        //disparo de nave enemiga final.
        if(rand()%100==0)
          {
           Enemigo[0].Disparar();
           if(Enemigo[0].Coord.X >= Terrano.Coord.X-30  &&
              Enemigo[0].Coord.X <= Terrano.Coord.X+30  &&
              Enemigo[0].Coord.Y < Terrano.Coord.Y-80)
             {
              Terrano.Explotar();
              Win=0;
              Sw=0;
             }
          }
        //choque y muerte con nave enemiga final.
        if(Terrano.Coord.X>Enemigo[0].Coord.X-40 &&
           Terrano.Coord.X<Enemigo[0].Coord.X+40 &&
           Terrano.Coord.Y>Enemigo[0].Coord.Y-120 &&
           Terrano.Coord.Y<Enemigo[0].Coord.Y+120)
          {
           Enemigo[0].Explotar();
           Terrano.Explotar();
           Win=0;
           Sw=0;
          }
        if(Enemigo[0].Vida==0)
          {
           strcpy(cad,"            ");
           MoveTo(10,50);
           DrawString(cad);
           Win=1;
           Fin=1;
          }
       }
     //ganar la partida.
     if(Destruidos==Dificultad*Nivel*10 && Fin)
       {
        Win++;
        if(Win==1 || Win==2)
          for(i=0; i<Dificultad ;i++)
            {
             Enemigo[i].Borrar();
             Enemigo[i].Coord.Y = YMAX;
            }
          for(i=0; i<Dificultad+1 ;i++)
            {
             Asteroide[i].Borrar();
             Asteroide[i].Coord.Y = YMAX;
            }
        PenColor(White);
        MoveTo(260,220);
        DrawString("MISION COMPLETADA");
        if(Win==100)
          {
           strcpy(cad,"BONO   ");
           if(Destruidos >= Generados-Dificultad)
             {
              UpScore(Terrano.Vida*Destruidos*20);
              strcat(cad,itoa(Destruidos*20,NULL,10));
             }
           else
             {
              UpScore(Terrano.Vida*Destruidos*10);
              strcat(cad,itoa(Destruidos*20,NULL,10));
             }
          }
        if(Win>100)
          {
           PenColor(Yellow);
           MoveTo(280,240);
           DrawString(cad);
          }
        if(Win==200)
          {
           MoveTo(260,220);
           DrawString("                 ");
           MoveTo(260,240);
           DrawString("                 ");
           Sw=0;
           Win=1;
          }
       }
    }while(Sw);
SALIR:
  SetDisplay(GrafPg0);
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  ShowCursor();
  return Win;
 }


// Juego perdido.
void GameOver(void)
 {
  HideCursor();
  PenColor(LtRed);
  BackColor(Black);
  MoveTo(280,240);
  DrawString("JUEGO PERDIDO");
  int Sw=1;
  do{
     if(KeyEvent(False,&Evento))
       if(Evento.eventType == evntKEYDN)
         Sw=0;
    }while(Sw);
  MoveTo(280,240);
  DrawString("             ");
  ShowCursor();
 }


// Menú para cambiar el nivel de dificultad.
void CambiarDificultad(void)
 {
  int Opcion=0;
  char NombreBoton[4][20]={" Sencillo"," Normal  "," Experto"," Aceptar"};
  Boton BotonMenu[4];
  rect BotonLim[4];
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  Universo(Rectangulo,250,0);
  for(int i=0,p=280; i<3 ;i++,p+=24)
    {
     BotonLim[i].Xmin =270;
     BotonLim[i].Xmax =360;
     BotonLim[i].Ymin = p+24;
     BotonLim[i].Ymax = p+20+24;
     BotonMenu[i].SetBoton(NombreBoton[i],BotonLim[i],Green,LtGreen);
     BotonMenu[i].Dibujar();
     if(Dificultad==i+1)
       BotonMenu[i].DibPres();
	}
  BotonLim[i].Xmin = 270;
  BotonLim[i].Xmax = 360;
  BotonLim[i].Ymin = 400;
  BotonLim[i].Ymax = 420;
  BotonMenu[i].SetBoton(NombreBoton[i],BotonLim[i],Red,LtRed);
  BotonMenu[i].Dibujar();
  int Sw=1;
  do{
     if(KeyEvent(False,&Evento))
       {
        Punto.X = Evento.eventX;
        Punto.Y = Evento.eventY;
        switch(Evento.eventType)
          {
           case evntPRESS:
                for(i=0;i<4;i++)
                  {
                   if(BotonMenu[i].Presionado(Punto,Evento))
                     {
                      if(i>=0 && i<=2)
                        {
                         Opcion=i;
                         switch(Opcion)
                           {
                            case 0: Dificultad=FACIL;
                                    break;
                            case 1: Dificultad=NORMAL;
                                    break;
                            case 2: Dificultad=DIFICIL;
                                    break;
                           }
                        }
                      BotonMenu[i].DibPres();
                      break;
                     }
                  }
                break;
           case evntRELEASE:
                if(BotonMenu[3].Apuntado(Punto))
                  {
                   Sw=0;
                   BotonMenu[3].DibNoPres();
                  }
                for(i=0;i<4;i++)
                  if(!BotonMenu[i].Apuntado(Punto) && Dificultad!=i+1)
                    BotonMenu[i].DibNoPres();
                break;
		   case evntKEYDN:
                switch(Evento.eventScan)
                  {
                   case  1: //ESC
                        Sw=0;
                        break;
                   case 28: //ENTER
                        Sw=0;
                        break;
                  }
				break;
		  }
	   }
    }while(Sw);
  for(i=0;i<4;i++)
    BotonMenu[i].Borrar();
  return;
 }


// Menú para cambiar el control del juego.
void CambiarControl(void)
 {
  int Opcion=0;
  char NombreBoton[4][20]={" Teclado","  Raton","JoyStick"," Aceptar"};
  Boton BotonMenu[4];
  rect BotonLim[4];
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  Universo(Rectangulo,250,0);
  for(int i=0,p=280; i<3 ;i++,p+=24)
    {
     BotonLim[i].Xmin =270;
     BotonLim[i].Xmax =360;
     BotonLim[i].Ymin = p+24;
     BotonLim[i].Ymax = p+20+24;
     BotonMenu[i].SetBoton(NombreBoton[i],BotonLim[i],Brown,Yellow);
     BotonMenu[i].Dibujar();
     if(Control==i)
       BotonMenu[i].DibPres();
	}
  BotonLim[i].Xmin = 270;
  BotonLim[i].Xmax = 360;
  BotonLim[i].Ymin = 400;
  BotonLim[i].Ymax = 420;
  BotonMenu[i].SetBoton(NombreBoton[i],BotonLim[i],Red,LtRed);
  BotonMenu[i].Dibujar();
  PenColor(LtGreen);
  MoveTo(230,440);
  HideCursor();
  DrawString("JoyStick No Disponible.");
  ShowCursor();
  int Sw=1;
  do{
     if(KeyEvent(False,&Evento))
       {
        Punto.X = Evento.eventX;
        Punto.Y = Evento.eventY;
        switch(Evento.eventType)
          {
           case evntPRESS:
                for(i=0;i<4;i++)
                  {
                   if(BotonMenu[i].Presionado(Punto,Evento))
                     {
                      if(i>=0 && i<=1)
                        {
                         Opcion=i;
                         switch(Opcion)
                           {
                            case 0: Control=TECLADO;
                                    break;
                            case 1: Control=RATON;
                                    break;
                           }
                        }
                      BotonMenu[i].DibPres();
                      break;
                     }
                  }
                break;
           case evntRELEASE:
                BotonMenu[2].DibNoPres();
                if(BotonMenu[3].Apuntado(Punto))
                  {
                   Sw=0;
                   BotonMenu[3].DibNoPres();
                  }
                for(i=0;i<4;i++)
                  if(!BotonMenu[i].Apuntado(Punto) && Control!=i)
                    BotonMenu[i].DibNoPres();
                break;
		   case evntKEYDN:
                switch(Evento.eventScan)
                  {
                   case  1: //ESC
                        Sw=0;
                        break;
                   case 28: //ENTER
                        Sw=0;
                        break;
                  }
				break;
		  }
	   }
    }while(Sw);
  for(i=0;i<4;i++)
    BotonMenu[i].Borrar();
  MoveTo(240,440);
  HideCursor();
  DrawString("                       ");
  ShowCursor();
  return;
 }


// Creditos.
void Creditos(void)
 {
  char NombreBoton[20]=" Aceptar";
  Boton Boton1;
  rect BotonLim;
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  Universo(Rectangulo,250,0);
  BotonLim.Xmin = 270;
  BotonLim.Xmax = 360;
  BotonLim.Ymin = 400;
  BotonLim.Ymax = 420;
  Boton1.SetBoton(NombreBoton,BotonLim,Red,LtRed);
  Boton1.Dibujar();
  PenColor(Yellow);
  MoveTo(275,90);
  DrawString("CREDITOS");
  PenColor(White);
  MoveTo(260,120);
  DrawString("TOMAS GOMEZ");
  MoveTo(255,140);
  DrawString("MIGUEL SIMONI");
  ActualizarRecord();
  VisualizarRecord();
  int Sw=1;
  do{
	 if(KeyEvent(False,&Evento))
	   {
		Punto.X = Evento.eventX;
		Punto.Y = Evento.eventY;
		switch(Evento.eventType)
		  {
           case evntPRESS:
                if(Boton1.Presionado(Punto,Evento))
                  Boton1.DibPres();
                break;
           case evntRELEASE:
                if(Boton1.Apuntado(Punto))
                  {
                   Sw=0;
                   Boton1.DibNoPres();
                   break;
                  }
                if(!Boton1.Apuntado(Punto))
                  Boton1.DibNoPres();
                break;
		   case evntKEYDN:
                switch(Evento.eventScan)
                  {
                   case  1: //ESC
                        Sw=0;
                        break;
                   case 28: //ENTER
                        Sw=0;
                        break;
                  }
				break;
		  }
	   }
    }while(Sw);
  Boton1.Borrar();
  return;
 }


// Menú principal de opciones.
int MenuPrincipal(void)
 {
  int Opcion=5;
  char NombreBoton[6][20]={"  Jugar"," Opciones"," Control","  Ayuda"," Creditos","  Salir"};
  Boton BotonMenu[6];
  rect BotonLim[6];
  ScreenRect(&Rectangulo);
  EraseRect(&Rectangulo);
  Universo(Rectangulo,250,0);
  for(int i=0,p=280; i<6 ;i++,p+=24)
	{
	 BotonLim[i].Xmin =270;
	 BotonLim[i].Xmax =360;
	 BotonLim[i].Ymin = p;
	 BotonLim[i].Ymax = p+20;
	 BotonMenu[i].SetBoton(NombreBoton[i],BotonLim[i],Blue,LtBlue);
	 BotonMenu[i].Dibujar();
	}
  char MayorPuntaje[22];
  strcpy(MayorPuntaje,"Mayor Puntaje: ");
  strcat(MayorPuntaje,itoa(HiScore,NULL,10));
  PenColor(Yellow);
  MoveTo(250,440);
  HideCursor();
  DrawString(MayorPuntaje);
  ShowCursor();
  int Sw=1;
  do{
	 if(KeyEvent(False,&Evento))
	   {
		Punto.X = Evento.eventX;
		Punto.Y = Evento.eventY;
		switch(Evento.eventType)
		  {
           case evntPRESS:
                for(i=0;i<6;i++)
                  {
                   if(BotonMenu[i].Presionado(Punto,Evento))
                     {
                      Opcion=i;
                      BotonMenu[i].Pres = 1;
                      BotonMenu[i].DibPres();
                      break;
                     }
                  }
                break;
           case evntRELEASE:
                for(i=0;i<6;i++)
                  {
                   if(BotonMenu[i].Apuntado(Punto) && BotonMenu[i].Pres==1)
                     {
                      Sw = 0;
                      BotonMenu[i].DibNoPres();
                      break;
                     }
                  }
                for(i=0;i<6;i++)
                  if(!BotonMenu[i].Apuntado(Punto))
                    BotonMenu[i].DibNoPres();
                break;
		   case evntKEYDN:
                switch(Evento.eventScan)
                  {
                   case  1: //ESC
                        Sw=0;
                        break;
                   case 28: //ENTER
                        Opcion=0;
                        Sw=0;
                        break;
                  }
				break;
		  }
	   }
    }while(Sw);
  for(i=0;i<6;i++)
    BotonMenu[i].Borrar();
  MoveTo(250,440);
  DrawString("                    ");
  return Opcion;
 }


void main(void)
 {
  char NombreJugador[11];
  clrscr();
  if(InitGraphics(VESA640x480X))
	{
	 cout << "Error al inicializar modo gr fico." << endl << endl;
	 exit(0);
	}
  SetDisplay(GrafPg0);
  ReadPalette(0,0,255,PaletaOriginal);  //copia de la paleta original.
  ScreenRect(&scrnR);  //definir pantalla completa.
  InitMouse(MsDriver);
  CursorStyle(2);
  CursorColor(Black,White);
  EventQueue(True);
  Presenta();
  Intro();
  Logo();
  ShowCursor();
  TrackCursor(True);
  Dificultad=NORMAL;
  Score=0;
  HiScore=GetHiScore();
  Control=RATON;
  int Opcion;
  do{
     Opcion=MenuPrincipal();
     switch(Opcion)
       {
        case 0: Score=0;
                Nivel=1;
                Punto.X = XMAX/2;
                Punto.Y = YMAX-60;
				Terrano.SetNave(Punto,2,TERRANO,LASER);
                Mision1();
                do{
                   switch(Juego())
                     {
                      case -1: //abortar misión.
                               Nivel=NIVEL_FINAL+1;
							   Terrano.Vida=0;
                               break;
                      case  0: //misión perdida.
							   Terrano.Vida--;
							   if(Terrano.Vida < 0)
                                 GameOver();
                               break;
                      case  1: //misión exitosa.
                               Nivel++;
                               switch(Nivel)
                                 {
                                  case 2: Mision2();
                                          break;
                                  case 3: Mision3();
                                          break;
                                 }
                               if(Nivel==NIVEL_FINAL+1)
                                 Final();
                               break;
                     }
				  }while(Terrano.Vida>=0 && Nivel<=NIVEL_FINAL);
                if(ConsultarRecord(Score))
                  {
                   HideCursor();
                   PenColor(White);
                   MoveTo(560,10);
                   DrawString("<- Nombre");
                   StopEvent();
                   gets(NombreJugador);
                   NuevoRecord(NombreJugador,Score);
                   EventQueue(True);
                   ShowCursor();
                   Creditos();
                  }
                HideCursor();
                TrackCursor(False);
                MoveCursor(XMAX/2,YMAX/2);
                Logo();
                TrackCursor(True);
                ShowCursor();
                break;
        case 1: CambiarDificultad();
                break;
        case 2: CambiarControl();
                break;
        case 3: Ayuda();
                break;
        case 4: Creditos();
                break;
        case 5: break;
	   }
    }while(Opcion!=5);
  StopEvent();
  TrackCursor(False);
  HideCursor();
  StopMouse();
  SetDisplay(TextPg0);
  StopGraphics();
  clrscr();
  cout << "Gracias por jugar Misión GR-I..." << endl << endl;
 }
