// Manejo del archivo de records de los jugadores.


#define RECORD_FILE "RECORD.DAT"

typedef struct { char Nombre[11];
                 double  Puntaje;
               } Record;


// Anexar nuevo record al archivo de records.
int NuevoRecord(char Nombre[11], double Score)
 {
  Record Jugador;
  FILE *Aptfile;     //apuntador al archivo de acceso de directo.
  if( ( Aptfile=fopen(RECORD_FILE,"r+") ) == NULL )
     return 0;
  else
    {
     strcpy(Jugador.Nombre,Nombre);
     Jugador.Puntaje= Score;
     fseek(Aptfile, 5 * sizeof(Record), SEEK_SET);
     fwrite(&Jugador,sizeof(Record),1,Aptfile);
    }
  fclose(Aptfile);
  return 1;
 }


// Actualizar el archivo RECORD.DAT.
int ActualizarRecord(void)
 {
  int i=0, j=0;
  FILE *Aptfile;     // Apuntador al archivo de acceso de directo.
  Record Jugador1, Jugador2, Jugador3;
  if( ( Aptfile=fopen(RECORD_FILE,"r+") ) == NULL )
     return 0;
  else
    {
     for(i=0; i<6 ;i++)
       {
        fseek(Aptfile, i * sizeof(Record), SEEK_SET);
        fread(&Jugador1,sizeof(Record),1,Aptfile);
        for(j=i+1; j<6 ;j++)
           {
            fseek(Aptfile, j * sizeof(Record), SEEK_SET);
            fread(&Jugador2,sizeof(Record),1,Aptfile);
            if(Jugador2.Puntaje > Jugador1.Puntaje)
              {
               strcpy(Jugador3.Nombre,Jugador1.Nombre);
               strcpy(Jugador1.Nombre,Jugador2.Nombre);
               strcpy(Jugador2.Nombre,Jugador3.Nombre);
               Jugador3.Puntaje = Jugador1.Puntaje;
               Jugador1.Puntaje = Jugador2.Puntaje;
               Jugador2.Puntaje = Jugador3.Puntaje;
               fseek(Aptfile, i * sizeof(Record), SEEK_SET);
               fwrite(&Jugador1,sizeof(Record),1,Aptfile);
               fseek(Aptfile, j * sizeof(Record), SEEK_SET);
               fwrite(&Jugador2,sizeof(Record),1,Aptfile);
              }   
           }
       }
    }
  fclose(Aptfile);
  return 1;
 }

// Visualizar los records de los jugadores -> archivo: RECORD.DAT.
int VisualizarRecord(void)
 {
  FILE *Aptfile;     // Apuntador al archivo de acceso de directo.
  Record Jugador;    // Registro para grabar datos del jugador.
  if( ( Aptfile=fopen(RECORD_FILE,"r") ) == NULL )
    return 0;
  else
    {
     PenColor(Yellow);
     MoveTo(240,220);
     DrawString("MEJORES PUNTAJES");
     MoveTo(190,250);
     DrawString("Lugar");
     MoveTo(275,250);
     DrawString("Nombre");
     MoveTo(380,250);
     DrawString("Puntaje");
     PenColor(White);
     for(int i=0; i<5 ;i++)
       {
        fseek(Aptfile, i * sizeof(Record), SEEK_SET);
        fread(&Jugador,sizeof(Record),1,Aptfile);
        MoveTo(205,250+(i+1)*20);
        DrawString(itoa(i+1,NULL,10));
        MoveTo(260,250+(i+1)*20);
        DrawString(Jugador.Nombre);
        MoveTo(390,250+(i+1)*20);
        DrawString(itoa(Jugador.Puntaje,NULL,10));
       }
    }
  fclose(Aptfile);
  return 1;
 }


// Consultar archivo de records.
double GetHiScore(void)
 {
  FILE *Aptfile;     // Apuntador al archivo de acceso de directo.
  Record Jugador;    // Registro para grabar datos del jugador.
  if( ( Aptfile=fopen(RECORD_FILE,"r") ) == NULL )
    return 0;
  else
    {
     fseek(Aptfile, 0 * sizeof(Record), SEEK_SET);
     fread(&Jugador,sizeof(Record),1,Aptfile);
     fclose(Aptfile);
     return Jugador.Puntaje;
    }
 }


// Consultar archivo de records.
int ConsultarRecord(double Score)
 {
  FILE *Aptfile;     // Apuntador al archivo de acceso de directo.
  Record Jugador;    // Registro para grabar datos del jugador.
  if( ( Aptfile=fopen(RECORD_FILE,"r") ) == NULL )
    return 0;
  else
    {
     fseek(Aptfile, 4 * sizeof(Record), SEEK_SET);
     fread(&Jugador,sizeof(Record),1,Aptfile);
     if(Score > Jugador.Puntaje)
       return 1;
    }
  fclose(Aptfile);
  return 0;
 }


// Inicializar archivo de records.
int InitRecord(void)
 {
  FILE *Aptfile;     // Apuntador al archivo de acceso de directo.
  Record Jugador;    // Registro para grabar datos del jugador.
  if( ( Aptfile=fopen(RECORD_FILE,"w") ) == NULL )
    return 0;
  else
    {
     for(int i=0; i<=5 ;i++)
       {
        printf("%d Nombre: ",i);
        gets(Jugador.Nombre);
        Jugador.Puntaje= i*1000;
        fseek(Aptfile, i * sizeof(Record), SEEK_SET);
        fwrite(&Jugador,sizeof(Record),1,Aptfile);
       }
    }
  fclose(Aptfile);
  return 1;
 }
