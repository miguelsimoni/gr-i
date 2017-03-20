// Secuencias del juego.

// CONSTANTES.
#define RETARDO 100


// VARIABLES GLOBALES.

mwEvent Even;

rect scrnR;

palData  RGBInfo[256], PaletaOriginal[256];

char name[20];


// FUNCONES.

// Restablecer los colores básicos de la paleta de colores.
void RestablecerPaleta(palData *Paleta)
 {
  //Black
  Paleta[ 0].palRed   = 0x0000;
  Paleta[ 0].palGreen = 0x0000;
  Paleta[ 0].palBlue  = 0x0000;
  //Blue
  Paleta[ 1].palRed   = 0x0000;
  Paleta[ 1].palGreen = 0x0000;
  Paleta[ 1].palBlue  = 0xA800;
  //Green
  Paleta[ 2].palRed   = 0x0000;
  Paleta[ 2].palGreen = 0xA800;
  Paleta[ 2].palBlue  = 0x0000;
  //Cyan
  Paleta[ 3].palRed   = 0x0000;
  Paleta[ 3].palGreen = 0xA800;
  Paleta[ 3].palBlue  = 0xA800;
  //Red
  Paleta[ 4].palRed   = 0xA800;
  Paleta[ 4].palGreen = 0x0000;
  Paleta[ 4].palBlue  = 0x0000;
  //Magenta
  Paleta[ 5].palRed   = 0xA800;
  Paleta[ 5].palGreen = 0x0000;
  Paleta[ 5].palBlue  = 0xA800;
  //Brown
  Paleta[ 6].palRed   = 0xA800;
  Paleta[ 6].palGreen = 0x5400;
  Paleta[ 6].palBlue  = 0x0000;
  //LtGray
  Paleta[ 7].palRed   = 0xA800;
  Paleta[ 7].palGreen = 0xA800;
  Paleta[ 7].palBlue  = 0xA800;
  //Gray
  Paleta[ 8].palRed   = 0x5400;
  Paleta[ 8].palGreen = 0x5400;
  Paleta[ 8].palBlue  = 0x5400;
  //LtBlue
  Paleta[ 9].palRed   = 0x5400;
  Paleta[ 9].palGreen = 0x5400;
  Paleta[ 9].palBlue  = 0xFFFF;
  //LtGreen
  Paleta[10].palRed   = 0x5400;
  Paleta[10].palGreen = 0xFFFF;
  Paleta[10].palBlue  = 0x5400;
  //LtCyan
  Paleta[11].palRed   = 0x5400;
  Paleta[11].palGreen = 0xFFFF;
  Paleta[11].palBlue  = 0xFFFF;
  //LtRed
  Paleta[12].palRed   = 0xFFFF;
  Paleta[12].palGreen = 0x5400;
  Paleta[12].palBlue  = 0x5400;
  //LtMagenta
  Paleta[13].palRed   = 0xFFFF;
  Paleta[13].palGreen = 0x5400;
  Paleta[13].palBlue  = 0xFFFF;
  //Yellow
  Paleta[14].palRed   = 0xFFFF;
  Paleta[14].palGreen = 0xFFFF;
  Paleta[14].palBlue  = 0x5400;
  //White
  Paleta[15].palRed   = 0xFFFF;
  Paleta[15].palGreen = 0xFFFF;
  Paleta[15].palBlue  = 0xFFFF;
  //Rescribir paleta
  WritePalette(0,0,255,Paleta);
 }


// Universo.
void Universo(rect espacio, int n, int fin)
 {
  int i,x,y,c;
  HideCursor();
  for(i=0;i<n;i++)
    {
     x = espacio.Xmin + rand()% (espacio.Xmax - espacio.Xmin);
     y = espacio.Ymin + rand()% (espacio.Ymax - espacio.Ymin);
     c = rand()%3;
     if(!fin)
       switch(c)
         {
          case 0: c=WHITE;
                  break;
          case 1: c=LIGHTGRAY;
                  break;
          case 2: c=DARKGRAY;
                  break;
         }
     else
       switch(c)
         {
          case 0: c=LIGHTRED;
                  break;
          case 1: c=RED;
                  break;
          case 2: c=BROWN;
                  break;
         }
     PenColor(c);
     SetPixel(x,y);
    }
  ShowCursor();
 }


// Abrir PCX.
void AbrirPCX(char *nombre, rect destino, int r)
 {
  int i;
  pcxHead pcxH;
  HideCursor();
  if(ReadPCXInfo(nombre,&pcxH,RGBInfo)==False)
    {
     printf("%s NO EXISTE O NO ES VALIDO\n",nombre);
     StopGraphics();
     exit(2);
    }
  WritePalette(0,0,255,RGBInfo);
  i=ReadPCX(nombre,NULL,&destino);
  if(i==False)
    {
     MoveTo(0,100);
     DrawString("ERROR AL LEER PCX");
    }
  if(r)
	RestablecerPaleta(RGBInfo);
  ShowCursor();
 }


// Presentacion principal.
void Presenta(void)
 {
  char cadena[30],*nombre;
  int cont=0,i;
  pcxHead pcxH;
  HideCursor();
  EraseRect(&scrnR);
  PenColor(Black);
  PaintRect(&scrnR);
  sleep(1);
  Universo(scrnR,250,0);
  sleep(1);
  PenColor(LtRed);
  strcpy(cadena,"T O M A S   G O M E Z");
  MoveTo(230,220);
  for(cont=0; cont<21 ;cont++)
    {
    //controlador de eventos.
	if(KeyEvent(False,&Even))
	  if(Even.eventType == evntKEYDN)
        if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
          {
           ShowCursor();
           return;
          }
     DrawChar(cadena[cont]);
     if(cadena[cont]!=' ')
       delay(500);
	}
  sleep(1);
  EraseRect(&scrnR);
  Universo(scrnR,250,0);
  PenColor(LtGreen);
  strcpy(cadena,"M I G U E L   S I M O N I");
  MoveTo(210,220);
  for(cont=0; cont<25 ;cont++)
    {
     //controlador de eventos.
	 if(KeyEvent(False,&Even))
	   if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            ShowCursor();
            return;
           }
     DrawChar(cadena[cont]);
     if(cadena[cont]!=' ')
       delay(500);
	}
  sleep(1);
  EraseRect(&scrnR);
  Universo(scrnR,250,0);
  PenColor(Yellow);
  MoveTo(230,220);
  DrawString("P R E S E N T A N");
  sleep(1);
 }


// Mostrar el nombre del juego.
void Logo(void)
 {
  AbrirPCX("tierra.pcx",scrnR,0);
  PenColor(White);
  MoveTo(280,450);
  DrawString(" ENTER/ESC ");
  do{
     //controlador de eventos.
	 if(KeyEvent(False,&Even))
	   if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            EraseRect(&scrnR);
			WritePalette(0,0,255,PaletaOriginal);
            ShowCursor();
            return;
           }
    }while(1);
 }

// Introduccion del juego.
void Intro(void)
 {
  int cont=0,linea=0;
  char historia[30][60]={"E N   U N   F U T U R O   M U Y ,  M U Y   L E J A N O ",
                         "  L A   R A Z A   H U M A N A   H A    L O G R A D O   ",
                         "  L A   M A Y O R   P R O E Z A   D E   T O D A   S U  ",
                         "                    H I S T O R I A                    ",
                         " L A   C O N Q U I S T A   Y   C O L O N I Z A C I O N ",
                         "    D E   C A S I   T O D A   L A   G A L A X I A      ",
                         "                                                       ",
                         "   E N   S U   A F A N   P O R   E L   D O M I N I O   ",
                         "          T O T A L   D E L   U N I V E R S O          ",
                         "   C O M E N Z O   L A   E X P L O R A C I O N   D E   ",
                         "           U N A   L E J A N A   G A L A X I A         ",
                         "    T O P A N D O S E   C O N   U N   S I S T E M A    ",
                         "   P A R E C I D O   A L   S I S T E M A   S O L A R   ",
                         "       - E L   S I S T E M A   P E N G A M I C O -     ",
                         "C O N S T R U Y E N D O   Y   E S T A B L E C I E N D O",
                         "         E N   U N A   D E    S U S   L U N A S        ",
                         "                    - S P Y R A -                      ",
                         "   U N A   I N M E N S A   B A S E   E S P A C I A L   ",
                         "                                                       ",
                         "L A M E N T A B L E M E N T E   A L L I   H A B I T A N",
                         "     U N A   R A Z A  A L I E N I G E N A   M U Y      ",
                         "                       H O S T I L                     ",
                         "           - L O S   S A L G A D I N H O S -           ",
                         "       Q U E   I N D I G N A D O S   P O R   L A       ",
                         "    O S A D I A   D E   L O S   T E R R I C O L A S    ",
                         "    D E   I N V A D I R   S U   T E R R I T O R I O    ",
                         "           L E S   H A N   D E C L A R A D O           ",
                         "                  L A    G U E R R A                   "};
  HideCursor();
  PenColor(Black);
  PaintRect(&scrnR);
  while(cont<648)
    {
     MoveTo(100,400);
     ScrollRect(&scrnR,0,-2);
     PenColor(LtBlue);
     if(cont % 15 == 0 && linea < 30)
       {
        DrawText(historia[linea],0,60);
		Universo(scrnR,60,0);
        linea++;
       }
     cont++;
     //controlador de eventos.
	 if(KeyEvent(False,&Even))
	   if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            ShowCursor();
            return;
           }
    }
  ShowCursor();
 }


// Historia de la primera misión.
void Mision1(void)
 {
  rect area, cuadroDialogo;
  pcxHead pcxHeader;
  int i,x,y,cont,cont2;
  char texto1[12][45]={" Se ha detectado una nave espacial en las    ",
                       " proximidades de la base espacial ECO ubicada",
                       " en Spyra, una luna en el sistema pengamico. ",
                       " provocando  un clima de  tension entre sus  ",
                       " habitantes...                               ",
  /*segundo pcx -L5-*/ " En vista de la situacion, el transbordador  ",
                       " espacial MEGAN que se encuentra cerca de las",
                       " coordenadas detectadas por la base espacial,",
                       " envia de inmediato una nave a investigar.   ",
                       " La nave enviada reporta que es una nave     ",
                       " nodriza Salgadinho, justamente antes de     ",
                       " empezar a ser atacada por los enemigos.     "};
  HideCursor();
  PenColor(Black);
  PaintRect(&scrnR);
  SetRect(&area,120,60,520,360);  // area establecida para el pcx junto al texto.
  AbrirPCX("base03.pcx",area,0);
  sleep(1);
  SetRect(&cuadroDialogo,120,360,520,440);
  PenColor(Black);
  PaintRect(&cuadroDialogo);
  y=370;
  for(cont=0;cont<12;cont++)
    {
     x=130;
     for(cont2=0;cont2<45;cont2++)
       {
        MoveTo(x,y);
        PenColor(White);
        DrawChar(texto1[cont][cont2]);
        x=x+8;
        delay(RETARDO);
        //controlador de eventos.
		if(KeyEvent(False,&Even))
		  if(Even.eventType == evntKEYDN)
            if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
              {
               EraseRect(&scrnR);
			   WritePalette(0,0,255,PaletaOriginal);
               ShowCursor();
               return;
              }
       }
     delay(RETARDO);
     y=y+15;
     if(y>440)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        y=370;
       }
     if(cont==4)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        PaintRect(&area);
        AbrirPCX("espa02.pcx",area,0);
        y=370;
       }
     //controlador de eventos.
	 if(KeyEvent(False,&Even))
	   if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            EraseRect(&scrnR);
            WritePalette(0,0,255,PaletaOriginal);
            ShowCursor();
            return;
           }
    }
  EraseRect(&scrnR);
  WritePalette(0,0,255,PaletaOriginal);
  ShowCursor();
 }


// Historia de la segunda misión.
void Mision2(void)
 {
  rect area, cuadroDialogo;
  pcxHead pcxHeader;
  int x,y,cont,cont2;
  char texto1[8][45]={" La guerra espacial termino por destruir la  ",
                      " Luna SPYRA, dejando en su lugar un vasto    ",
                      " recuerdo de esta...                         ",
                      " Al tratar de escapar, la nave terrana se    ",
                      " tropieza con un inmenso campo de asteroides.",
  /*segundo pcx -2-*/ " Los SALGADINHOS estan sumamente molestos,   ",
                      " con grandes ganas de vengarse de la raza    ",
                      " humana...                                   ",};
  HideCursor();
  PenColor(Black);
  PaintRect(&scrnR);
  SetRect(&area,120,60,520,360);  // area establecida para el pcx junto al texto.
  AbrirPCX("explo04.pcx",area,0);
  sleep(1);
  SetRect(&cuadroDialogo,120,360,520,440);
  PenColor(Black);
  PaintRect(&cuadroDialogo);
  y=370;
  for(cont=0;cont<8;cont++)
    {
     x=130;
     for(cont2=0;cont2<45;cont2++)
       {
        MoveTo(x,y);
        PenColor(White);
        DrawChar(texto1[cont][cont2]);
        x=x+8;
        delay(RETARDO);
        //controlador de eventos.
		if(KeyEvent(False,&Even))
		  if(Even.eventType == evntKEYDN)
            if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
              {
               EraseRect(&scrnR);
               WritePalette(0,0,255,PaletaOriginal);
               ShowCursor();
               return;
              }
       }
     delay(RETARDO);
     y=y+15;
     if(y>440)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        y=370;
       }
     if(cont==4)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        PaintRect(&area);
        AbrirPCX("espa05.pcx",area,0);
        y=370;
       }
     //controlador de eventos.
	 if(KeyEvent(False,&Even))
	   if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            EraseRect(&scrnR);
            WritePalette(0,0,255,PaletaOriginal);
            ShowCursor();
            return;
           }
    }
  EraseRect(&scrnR);
  WritePalette(0,0,255,PaletaOriginal);
  ShowCursor();
 }


// Historia de la tercera misión.
void Mision3(void)
 {
  rect area, cuadroDialogo;
  pcxHead pcxHeader;
  int i,x,y,cont,cont2;
  char texto1[9][45]={" Los Salgadinhos al verse derrotados en su   ",
                      " propio sistema, quieren vengarse a como de  ",
                      " lugar, por lo que emprenden un ataque masivo",
                      " junto con un gran grupo de rebeldes enemigos",
  /*segundo pcx -L3-*/" hacia nuestro sistema solar para acabar con ",
                      " la raza humana de una vez por todas...      ",
  /*tercer pcx -L5-*/ " En vista de la situacion, en la tierra se   ",
                      " preparan y lanzan un contrataque con el     ",
                      " objetivo de eliminar la amenaza salgadinha. ",};
  HideCursor();
  PenColor(Black);
  PaintRect(&scrnR);
  SetRect(&area,120,60,520,360);  // area establecida para el pcx junto al texto.
  AbrirPCX("alien01.pcx",area,0);
  sleep(1);
  SetRect(&cuadroDialogo,120,360,520,440);
  PenColor(Black);
  PaintRect(&cuadroDialogo);
  y=370;
  for(cont=0;cont<9;cont++)
    {
     x=130;
     for(cont2=0;cont2<45;cont2++)
       {
        MoveTo(x,y);
        PenColor(White);
        DrawChar(texto1[cont][cont2]);
        x=x+8;
        delay(RETARDO);
        //controlador de eventos.
        if(KeyEvent(False,&Even))
          if(Even.eventType == evntKEYDN)
            if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
              {
               EraseRect(&scrnR);
               WritePalette(0,0,255,PaletaOriginal);
               ShowCursor();
               return;
              }
       }
     delay(RETARDO);
     y=y+15;
     if(y>440)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        y=370;
       }
     if(cont==3)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        PaintRect(&area);
        AbrirPCX("satur.pcx",area,0);
        y=370;
       }
     //controlador de eventos.
     if(KeyEvent(False,&Even))
       if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            EraseRect(&scrnR);
            WritePalette(0,0,255,PaletaOriginal);
            ShowCursor();
            return;
           }
     if(cont==5)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        PaintRect(&area);
        AbrirPCX("argus.pcx",area,0);
        y=370;
       }
     //controlador de eventos.
	 if(KeyEvent(False,&Even))
	   if(Even.eventType == evntKEYDN)
         if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
           {
            EraseRect(&scrnR);
            WritePalette(0,0,255,PaletaOriginal);
            ShowCursor();
            return;
           }    
    }
  EraseRect(&scrnR);
  WritePalette(0,0,255,PaletaOriginal);
  ShowCursor();
 }


// Final del juego.
void Final(void)
 {
  rect area, cuadroDialogo;
  pcxHead pcxHeader;
  int i,x,y,cont,cont2;
  char texto1[7][45]={" Los Salgadinhos y rebeldes fueron derrotados",
                      " viendose obligados a huir a su sistema...   ",
  /*segundo pcx -L1-*/" Se ha restaurado la paz en la galaxia...    ",
  /*tercer pcx -L2- */" La raza humana todavia sigue viva           ",
                      " aprendiendo una gran leccion que nunca      ",
                      " debera olvidar.........................     ",
                      "                                             "};
  HideCursor();
  PenColor(Black);
  PaintRect(&scrnR);
  SetRect(&area,120,60,520,360);  // area establecida para pcx junto al texto.
  AbrirPCX("adios.pcx",area,0);
  sleep(1);
  SetRect(&cuadroDialogo,120,360,520,440);
  PenColor(Black);
  PaintRect(&cuadroDialogo);
  y=370;
  for(cont=0;cont<7;cont++)
    {
     x=130;
     for(cont2=0;cont2<45;cont2++)
       {
        MoveTo(x,y);
        PenColor(White);
        DrawChar(texto1[cont][cont2]);
        x=x+8;
        delay(RETARDO);
        //controlador de eventos.
        if(KeyEvent(False,&Even))
          if(Even.eventType == evntKEYDN)
        if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
          {
           EraseRect(&scrnR);
           WritePalette(0,0,255,PaletaOriginal);
           ShowCursor();
           return;
          }
       }
     delay(RETARDO);
     y=y+15;
     if(y>440)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        y=370;
       }
     if(cont==1)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        PaintRect(&area);
        AbrirPCX("paz08.pcx",area,0);
        y=370;
       }
     if(cont==2)
       {
        sleep(1);
        PenColor(Black);
        PaintRect(&cuadroDialogo);
        PaintRect(&area);
        AbrirPCX("paz09.pcx",area,0);
        y=370;
       }
     //controlador de eventos.
     if(KeyEvent(False,&Even))
       if(Even.eventType == evntKEYDN)
     if(Even.eventScan == 1 || Even.eventScan == 28)  //ESC o ENTER
       {
        EraseRect(&scrnR);
        WritePalette(0,0,255,PaletaOriginal);
        ShowCursor();
        return;
       }
    }
  EraseRect(&scrnR);
  WritePalette(0,0,255,PaletaOriginal);
  ShowCursor();
 }
