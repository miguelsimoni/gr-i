// Librería General.

// TAD Botón.
class Boton
{
 private:
 // Nombre.
 char *Nombre;

 // Límites.
 rect Fondo, Limite, Selec;

 // Colores.
 int ColorBorde, ColorSelec;

 public:
 // Presion.
 int Pres;

 // Constructor (por defecto).
 Boton(void)
  {
   Nombre = new char[20];
   strcpy(Nombre," ");
   SetRect(&Fondo,8,8,22,22);
   SetRect(&Limite,10,10,20,20);
   SetRect(&Selec,12,12,18,18);
   ColorBorde = White;
   ColorSelec = LtGray;
   Pres = 0;
  }

 // Constructor.
 Boton(char *Nom, rect Lim, int CBorde, int CSelec)
  {
   Nombre = new char[20];
   strcpy(Nombre,Nom);
   DupRect(&Lim,&Limite);
   SetRect(&Fondo,Lim.Xmin-2,Lim.Ymin-2,Lim.Xmax+2,Lim.Ymax+2);
   SetRect(&Selec,Lim.Xmin+4,Lim.Ymin+3,Lim.Xmax-2,Lim.Ymax-2);
   ColorBorde = CBorde;
   ColorSelec = CSelec;
   Pres = 0;
  }

 // Destructor.
 ~Boton(void)
  {
   delete Nombre;
  }

 // Asignador.
 void SetBoton(char *Nom, rect Lim, int CBorde, int CSelec)
  {
   strcpy(Nombre,Nom);
   DupRect(&Lim,&Limite);
   SetRect(&Fondo,Lim.Xmin-2,Lim.Ymin-2,Lim.Xmax+2,Lim.Ymax+2);
   SetRect(&Selec,Lim.Xmin+4,Lim.Ymin+3,Lim.Xmax-2,Lim.Ymax-2);
   ColorBorde = CBorde;
   ColorSelec = CSelec;
  }

 // Coordenadas.
 rect Coord(void)
  {
   return Limite;
  }

 // Está presionado.
 int Presionado(point Punto, mwEvent Evento)
  {
   if(PtInRect(&Punto,&Limite,1,1) && Evento.eventButtons==swLeft)
     return 1;
   return 0;
  }

 // Punto en botón.
 int Apuntado(point Punto)
  {
   if(PtInRect(&Punto,&Limite,1,1))
     return 1;
   return 0;
  }

 // Dibujar.
 void Dibujar(void)
  {
   HideCursor();
   PenColor(Black);
   PaintRect(&Fondo);
   PenColor(ColorBorde);
   FrameRect(&Limite);
   PenColor(White);
   MoveTo(Limite.Xmin+10,Limite.Ymin+13);
   DrawString(Nombre);
   ShowCursor();
  }

 // Borrar botón.
 void Borrar(void)
  {
   HideCursor();
   PenColor(Black);
   EraseRect(&Selec);
   EraseRect(&Fondo);
   FrameRect(&Limite);
   ShowCursor();
  }

 // Dibujar presionado.
 void DibPres(void)
  {
   HideCursor();
   PenColor(ColorSelec);
   PaintRect(&Selec);
   PenColor(White);
   BackColor(ColorSelec);
   MoveTo(Limite.Xmin+10,Limite.Ymin+13);
   DrawString(Nombre);
   BackColor(Black);
   ShowCursor();
  }

 // Dibujar no presionado.
 void DibNoPres(void)
  {
   HideCursor();
   PenColor(White);
   BackColor(Black);
   EraseRect(&Selec);
   MoveTo(Limite.Xmin+10,Limite.Ymin+13);
   DrawString(Nombre);
   ShowCursor();
  }

};
