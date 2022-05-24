#include <stdio.h>
#include <iostream>

#include <graphics.h>


typedef struct registro
{
    struct registro *ant,*sig;
    long dir_reg;
    long dir_sig; 
}Registro;

typedef struct
{
      char nombre[20];
      long dir_atributo;
      long dir_sig;  
      char tipo;
      int longitud;
}DatosAtributo;

typedef struct atributo
{
     struct atributo *ant, *sig;
     DatosAtributo datAtrib; 
}Atributo;

typedef struct 
{
     char nombre[20];
     long dir_entidad;
     long dir_datos;
     long dir_atributo;
     long dir_PK;
     long dir_sig;
}DatosEntidad;

typedef struct entidad
{
        struct entidad *ant,*sig;
        Atributo *prim;
        Atributo *ult;
        Registro *rp;
        Registro *ru;
        DatosEntidad datEnti;
}Entidad;

typedef struct Lista
{
    long dir_primer_elemento;
    FILE *Archivo;
    Entidad *prim;  
    Entidad *ult;
}Entidades;

void inicializaListaEntidades(Entidades *arch);
void lee_texto(int x,int y,char cadena[],int numCaracteres);
void menu(Entidades arch);

void MenuArchivo(bool *archivo,Entidades *arch,int x,int y);
void nuevoArchivo(Entidades *arch);
void abrirArchivo(Entidades *arch);

void MenuEntidad(bool *agrega,Entidades *arch,int x,int y);
Entidad *creaEntidad();
void creaListaEntidades(Entidades *arch,Entidad *ent);
void agregaEntidad(Entidades *arch,Entidad *ent);
void eliminaEntidad(Entidades *arch,Entidad *ent);
Entidad *seleccionaEntidad(Entidades arch);
void dibujaEntidades(Entidades arch,bool archivo,bool agrega, bool elimina);
void dibujaEntidad(DatosEntidad dat,int x,int y);

void MenuModificaEntidad(Entidades *arch,Entidad *nuevo,int x,int y);

void MenuAtributo(bool *Atrubuto,Entidad *enti,int x,int y);
Atributo *creaAtrubuto();
void creaListaAtributos(Entidad *enti,Atributo *atri);
void agregaAtrubuto(Entidad *enti,Atributo *atri);
void eliminaAtributo(Entidad *enti,Atributo *atri);
Atributo *seleccionaAtributo(Entidad enti);
void dibujaAtributos(Entidad ent);
void dibujaAtributo(DatosAtributo atri,int x,int y);


void MenuRegistro(bool *elimina,Entidades arch,int x,int y);
Registro *creaRegistro();
void creaListaRegistro(Entidad *enti,Registro *reg);
void agregaRegistro(Entidad *enti,Registro *reg);  
void dibujaRegistros(Entidad *ent);
void dibujaRegistro(DatosAtributo atri,int x,int y);
void eliminaRegistro(Entidad *enti,Registro *reg); 
void modificaRegistro(Entidad *enti,Registro *reg);      
Registro *seleccionaRegistros(Entidad *ent);
char dialogBoxTipo();
bool dialogBoxBool();


int main( )
{
   initwindow( 900 , 600 , "WinBGIm" );
   Entidades arch;
   inicializaListaEntidades(&arch);
   srand( (unsigned)time( NULL ) );

   menu(arch);
   
   getch();
}
char dialogBoxTipo()
{
     bar(200,200,700,400);
     rectangle(200,200,700,400);
     rectangle(201,230,699,399);
     //Entero
     outtextxy(10+250,10+280,"Entero");
     rectangle(10+250,10+280,80+250,40+280);
     //Cadena
     outtextxy(10+250+150,10+280,"Cadena");
     rectangle(10+250+150,10+280,80+250+150,40+280);
     //Binario
     outtextxy(10+250+300,10+280,"Binario");
     rectangle(10+250+300,10+280,80+250+300,40+280);
     
     outtextxy(410,210,"Tipo");
     int x;
     int y;
     char op = '0';
     
     do
     {
       if(ismouseclick(WM_LBUTTONDOWN))
       {
           getmouseclick(WM_LBUTTONDOWN,x,y);
           clearmouseclick(WM_LBUTTONDOWN); 
           if(x>10+250 && y>10+280 && x<80+250 && y<40+280)
           {
                return 'E';
           }
           if(x>10+250+150 && y>10+280 && x<80+250+150 && y<40+280)
           {
                return 'C';
           }
           if(x>10+250+300 && y>10+280 && x<80+250+300 && y<40+280)
           {
                return 'B';
           }                         
       }
              
    }while(true);
}
bool dialogBoxBool()
{
     bar(200,200,700,400);
     rectangle(200,200,700,400);
     rectangle(201,230,699,399);
     //Entero
     outtextxy(10+250,10+280,"Verdadero");
     rectangle(10+250,10+280,80+250,40+280);
     
     //Binario
     outtextxy(10+250+300,10+280,"Falso");
     rectangle(10+250+300,10+280,80+250+300,40+280);
     int x;
     int y;
     
     do
     {
       if(ismouseclick(WM_LBUTTONDOWN))
       {
           getmouseclick(WM_LBUTTONDOWN,x,y);
           clearmouseclick(WM_LBUTTONDOWN); 
           if(x>10+250 && y>10+280 && x<80+250 && y<40+280)
           {
                return true;
           }
           if(x>10+250+300 && y>10+280 && x<80+250+300 && y<40+280)
           {
                return false;
           }                         
       }
              
    }while(true);
}
void inicializaListaEntidades(Entidades *arch)
{
      arch->dir_primer_elemento = -1;
      arch->Archivo = NULL;
      arch->prim = NULL;
      arch->ult = NULL;
}

void lee_texto(int x,int y,char cadena[],int numCaracteres)
{
    char tecla;     
    int contador=0;
    
    do{
          do{  
    			 setcolor(15);
    			 outtextxy(x+textwidth(cadena),y,"_");
    			 delay(50);
    			 setcolor(0);  
    			 outtextxy(x+textwidth(cadena),y,"_");
    			 delay(50);
    			 setcolor(15); 
          }while(!kbhit());
          
          tecla=getch();
          if(tecla==0)  
             tecla=getch();
            if(tecla==8 && contador > 0)
			{
				 setcolor(BLACK);
				 outtextxy(x,y,cadena);  
				 cadena[--contador]='\0'; 
				 setcolor(WHITE);
				 outtextxy(x,y,cadena);
			}
            else
			{  
              if(tecla!=13)
              {  
				 cadena[contador++]=tecla;
				 cadena[contador]='\0';
				 outtextxy(x,y,cadena);
              }
            }          
      }while(tecla!=13 && contador!=numCaracteres); 
      setcolor(WHITE);
      bar(210,5,400,20);
}

void menu(Entidades arch)
{	
    bool archivo = false;
    bool agrega = false;
    bool elimina = false;
    
    int x,y;
    
    do
    {
       rectangle(2,2,70,28); 
       outtextxy(10,7,"Archivo");
       setfillstyle(SOLID_FILL,0); 
       if(arch.Archivo!=NULL)
       {
          rectangle(72,2,140,28); 
          outtextxy(78,7,"Entidad");
          if(arch.prim!=NULL && arch.ult!=NULL)
          {
               rectangle(72+70,2,140+70,28); 
               outtextxy(78+70,7,"Registro");               
          }
       }
       rectangle(1,1,999,30); 
       dibujaEntidades(arch,archivo,agrega,elimina);
       if(ismouseclick(WM_LBUTTONDOWN))
       {
           getmouseclick(WM_LBUTTONDOWN,x,y);
           clearmouseclick(WM_LBUTTONDOWN); 
             
           if(x>2 && y>2 && x<70 && y<28)
           {
                  printf("Menu Archivo\n");
                  if(agrega == false && elimina ==false)
                 MenuArchivo(&archivo,&arch,x,y); 
           }
          

           if(x>72 && y>2 && x<140 && y<28)
           { 
                  printf("Menu Entidad\n");
                  if(archivo == false && elimina ==false)
                  if(arch.Archivo!=NULL == true)
                  MenuEntidad(&archivo,&arch,x,y);     
           }  
           if(x>72+70 && y>2 && x<140+70 && y<28)
           {
                 printf("Menu Registro\n"); 
                 if(archivo == false && agrega ==false)
                 MenuRegistro(&elimina,arch,x,y);
                 cleardevice();               
           }                         
       }
              
    }while(true);
}

void MenuArchivo(bool *archivo,Entidades *arch,int x,int y)
{    
    if(*archivo== false)
    { 
        rectangle(1,32,199,152);
        setfillstyle(SOLID_FILL,BLACK);
        bar(2,35,199,60);
        outtextxy(7,40,"Nuevo");      
    
        bar(2,65,199,90);
        outtextxy(7,70,"Abrir ");
        
        line(2,62,199,62);
    
        bar(2,95,199,120);
        outtextxy(7,100,"Guardar ");
        
        line(2,92,199,92);
    
        bar(2,125,199,150);
        outtextxy(7,130,"Elimina ");
        
        line(2,122,199,122);
        
        do
        {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
           getmouseclick(WM_LBUTTONDOWN,x,y);
           clearmouseclick(WM_LBUTTONDOWN); 
           *archivo=true;   
            if(x>2 && y>35 && x<199 && y<60)
            {  
                  inicializaListaEntidades(arch);
                  nuevoArchivo(arch);                      
            }
            //Abrir
            if(x>2 && y>65 && x<199 && y<90)
            {
                   abrirArchivo(arch);                                      
            }
            //Guardar
            if(x>2 && y>95 && x<199 && y<120)
            { 
                  *archivo=true;        
            }
            //Eliminar lista
            if(x>2 && y>125 && x<199 && y<150)
            {
                  *archivo=true;                     
            }   
           }     
        }while(*archivo==false);
        *archivo=false;
        setfillstyle(SOLID_FILL,BLACK);
        bar(1,32,200,153);
    }
    else
    {
        *archivo=false;
        setfillstyle(SOLID_FILL,BLACK);
        bar(1,32,200,153);
    }
}

void nuevoArchivo(Entidades *arch)
{
    arch->prim = NULL;
    arch->ult = NULL;
    arch->dir_primer_elemento = -1;
    arch->Archivo = fopen("Archivo.bet","wb");
    long as;
    if(arch==NULL)
    {
            printf("Error al crear el archivo\n");      
    } 
    else
    {
         fwrite(&(arch->dir_primer_elemento),sizeof(long),1,arch->Archivo);
         printf("Archivo creado con Exito\n"); 
         printf("Guardado %d\n",arch->dir_primer_elemento);
    }
    fclose(arch->Archivo);
    cleardevice();
}

void abrirArchivo(Entidades *arch)
{  
     arch->prim = NULL;
     arch->ult = NULL;
     arch->dir_primer_elemento = -1;
     arch->Archivo = fopen("Archivo.bet","rb");
     DatosEntidad dat;
     DatosAtributo aux;
     long dato;
     long pos =0;
     //Lee las entidades y los atributos
     if(arch->Archivo!=NULL)
     {
         fseek(arch->Archivo,0,SEEK_END);
         pos = ftell(arch->Archivo);
         fseek(arch->Archivo,0,SEEK_SET);
         fread(&arch->dir_primer_elemento,sizeof(long),1,arch->Archivo);
         fseek(arch->Archivo,arch->dir_primer_elemento,SEEK_SET);
         while(pos != ftell(arch->Archivo))
         {
             fread(&dat,sizeof(DatosEntidad),1,arch->Archivo);
             Entidad *ent = creaEntidad();
             ent->datEnti = dat;
             creaListaEntidades(arch,ent);
             if(ent->datEnti.dir_atributo!=-1)
             {
                 fseek(arch->Archivo,ent->datEnti.dir_atributo,SEEK_SET);
                 fread(&aux,sizeof(DatosAtributo),1,arch->Archivo);
                 Atributo *atri = creaAtrubuto();
                 atri->datAtrib = aux;
                 creaListaAtributos(ent,atri);
                 
                 if(atri->datAtrib.dir_sig!=-1)
                 {
                     do{
                          fseek(arch->Archivo,aux.dir_sig,SEEK_SET);
                          fread(&aux,sizeof(DatosAtributo),1,arch->Archivo);
                          Atributo *atri = creaAtrubuto();
                          atri->datAtrib = aux;
                          creaListaAtributos(ent,atri);                                                            
                     }while(aux.dir_sig!=-1); 
                 }
             }
             if(dat.dir_entidad!=-1)
             fseek(arch->Archivo,dat.dir_sig,SEEK_SET);  
         }  
         //Lee los datos o registros
         if(arch->prim!=NULL)
         {   
             Entidad *corre = arch->prim;
             while(corre)
             {
                  if(corre->datEnti.dir_datos!=-1)
                  {
                        fseek(arch->Archivo,corre->datEnti.dir_datos,SEEK_SET); 
                        Registro *reg = creaRegistro();
                        fread(&dato,sizeof(long),1,arch->Archivo);
                        reg->dir_reg = dato;
                        fread(&dato,sizeof(long),1,arch->Archivo);
                        reg->dir_sig = dato;
                        
                        
                        creaListaRegistro(corre,reg);
                        if(reg->dir_sig != -1)
                        {
                            do{
                               fseek(arch->Archivo,dato,SEEK_SET); 
                               
                               Registro *reg = creaRegistro();
                               fread(&dato,sizeof(long),1,arch->Archivo);
                               
                               
                               reg->dir_reg = dato;
                               
                               fread(&dato,sizeof(long),1,arch->Archivo);
                               
                               reg->dir_sig = dato; 
                               
                               creaListaRegistro(corre,reg);
                            }while(dato !=-1);               
                                        
                        } 
                  }            
             corre = corre->sig;            
             }                            
         }      
     }   
}

void MenuEntidad(bool *agrega,Entidades *arch,int x,int y)
{
    if(*agrega== false)
    {      
        setfillstyle(SOLID_FILL,BLACK);
        bar(70,35,269,60);
        outtextxy(80,40,"Agrega Entidad"); 
        bar(70,65,269,90);
        outtextxy(80,70,"Modifica Entidad");
        bar(70,95,269,120);
        outtextxy(80,100,"Elimina Entidad");
        line(70,62,269,62);
        rectangle(70,32,269,122);
        line(70,92,269,92);
            
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
               *agrega=true; 
                if(x>70 && y>35 && x<269 && y<60)
                {   
                        printf("Agrega Entidad\n"); 
                        agregaEntidad(arch,creaEntidad());   
                }        
                if(x>70 && y>65 && x<269 && y<90)
                {
                        printf("Modifica Entidad\n");
                        Entidad *nuevo = seleccionaEntidad(*arch);
                         if(nuevo!=NULL)
                         {
                             MenuModificaEntidad(arch,nuevo,x,y);
                         }
                         cleardevice(); 
                }
                if(x>70 && y>95 && x<269 && y<120)
                {
                         printf("Elimina Entidad\n"); 
                         Entidad *nuevo = seleccionaEntidad(*arch);
                         if(nuevo!=NULL)
                         {
                            eliminaEntidad(arch,nuevo);         
                         }
                         cleardevice();  
                }
            }
        }while(*agrega == false);
        *agrega = false; 
        setfillstyle(SOLID_FILL,BLACK);
        bar(70,30,199+75,130);
    }
    else
    {
       *agrega = false;
       setfillstyle(SOLID_FILL,BLACK);
       bar(65,32,199+70,130);
    } 
}

Entidad *creaEntidad()
{
    Entidad *nuevaEntidad;
    nuevaEntidad = (Entidad*)malloc(sizeof(Entidad));
    nuevaEntidad->ant = NULL;
    nuevaEntidad->sig = NULL;
    nuevaEntidad->prim = NULL;
    nuevaEntidad->ult = NULL;
    nuevaEntidad->rp = NULL;
    nuevaEntidad->ru = NULL;
    strcat(nuevaEntidad->datEnti.nombre,"Entidad");
    nuevaEntidad->datEnti.dir_atributo = -1;
    nuevaEntidad->datEnti.dir_datos = -1;
    nuevaEntidad->datEnti.dir_PK = -1;
    nuevaEntidad->datEnti.dir_entidad = -1;
    nuevaEntidad->datEnti.dir_sig = -1;
    return nuevaEntidad;        
}

void creaListaEntidades(Entidades *arch,Entidad *ent)
{    
     if(arch->prim == NULL && arch->ult == NULL)
     {
         arch->prim = ent;
         arch->ult = ent;                         
     } 
     else
     {  
         arch->ult->sig = ent;
         ent->ant = arch->ult;
         arch->ult = ent;                         
     }  
}

void agregaEntidad(Entidades *arch,Entidad *ent)
{ 
     long pos;   
     outtextxy(145,7,"Nombre: ");
     char cadena[20] = "\0";
     lee_texto(205,7,cadena,15); 
     strcpy(ent->datEnti.nombre,cadena);
     cleardevice();
     if(arch->prim == NULL && arch->ult == NULL)
     {
         arch->Archivo = fopen("Archivo.bet","rb+"); 
         arch->prim = ent;
         arch->ult = ent;
         
         if(arch->Archivo !=NULL)
         {   
             fseek(arch->Archivo,0,SEEK_END);
             pos = ftell(arch->Archivo);
             arch->dir_primer_elemento = pos;
             ent->datEnti.dir_entidad = pos; 
             fseek(arch->Archivo,0,SEEK_SET);
             fwrite(&arch->dir_primer_elemento,sizeof(long),1,arch->Archivo);                
             fseek(arch->Archivo,0,SEEK_END);                              
             fwrite(&ent->datEnti,sizeof(DatosEntidad),1,arch->Archivo);   
             printf("Entidad Agregada con exito\n");           
         }    
         else
         {
             arch->Archivo = fopen("Archivo.bet","wb+");
             arch->prim = ent;
             arch->ult = ent; 
             if(arch->Archivo !=NULL)
             {   
                 arch->dir_primer_elemento = sizeof(long);
                 fwrite(&arch->dir_primer_elemento,sizeof(long),1,arch->Archivo);   
                 ent->datEnti.dir_entidad = sizeof(long);                                
                 fwrite(&ent->datEnti,sizeof(DatosEntidad),1,arch->Archivo);   
                 printf("Se ha creado un nuevo Archivo\n");
                 printf("Entidad Agregada con exito\n");           
             }
         } 
         fclose(arch->Archivo);              
     } 
     else
     {
         arch->Archivo = fopen("Archivo.bet","rb+");
         if(arch->Archivo != NULL)
         {  
             fseek(arch->Archivo,0,SEEK_END); 
             pos = ftell(arch->Archivo);
             arch->ult->datEnti.dir_sig = pos;
             fseek(arch->Archivo,arch->ult->datEnti.dir_entidad,SEEK_SET);
             fwrite(&arch->ult->datEnti,sizeof(DatosEntidad),1,arch->Archivo);
             ent->datEnti.dir_entidad = pos;
             fseek(arch->Archivo,0,SEEK_END);
             fwrite(&ent->datEnti,sizeof(DatosEntidad),1,arch->Archivo);  
             
             arch->ult->sig = ent;
             ent->ant = arch->ult;
             arch->ult = ent;                         
         } 
         fclose(arch->Archivo);
     }  
}

void eliminaEntidad(Entidades *arch,Entidad *ent)
{
     Entidad *aux=arch->prim;  
     arch->Archivo = fopen("Archivo.bet","rb+");
     long dirPrim =-1;
     if(arch->prim == arch->ult)
     {
         fwrite(&dirPrim,sizeof(long),1,arch->Archivo);                
         aux = arch->prim;
         arch->prim = NULL; 
         arch->ult = NULL;   
         free(aux);       
     }else
     if(arch->prim == ent)
     {
        fwrite(&arch->prim->sig->datEnti.dir_entidad,sizeof(long),1,arch->Archivo); 
        arch->dir_primer_elemento = arch->prim->sig->datEnti.dir_entidad; 
        arch->prim = arch->prim->sig;
        arch->prim->ant = NULL;
        ent->sig = NULL;
        free(ent);                  
     }else
     if(arch->ult == ent)
     {
         arch->ult->ant->datEnti.dir_sig=-1;   
         fseek(arch->Archivo,arch->ult->ant->datEnti.dir_entidad,SEEK_SET);
         fwrite(&arch->ult->ant->datEnti,sizeof(DatosEntidad),1,arch->Archivo); 
         
        arch->ult=arch->ult->ant;
        arch->ult->sig=NULL;
        ent->ant=NULL;
        free(ent);   
            
     }else
     {
               fseek(arch->Archivo,ent->ant->datEnti.dir_entidad,SEEK_SET);
               ent->ant->datEnti.dir_sig = ent->sig->datEnti.dir_entidad;  
               fwrite(&ent->ant->datEnti,sizeof(DatosEntidad),1,arch->Archivo); 
               ent->sig->ant = ent->ant;
               ent->ant->sig = ent->sig;
               ent->sig = NULL;
               ent->ant = NULL;
               free(ent);    
     }
     fclose(arch->Archivo);
}

Entidad *seleccionaEntidad(Entidades arch)
{
     int x=0;
     int y=0;
     bool salir=false;
     cleardevice();
     outtextxy(5,5,"Selecciona la Entidad");
     dibujaEntidades(arch,false,false,false);
     do{
        if(ismouseclick(WM_LBUTTONDOWN))
        {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
            int xx=0;
            int yy=0;
            Entidad *nuevo = arch.prim;
            while(nuevo)
            {
                  if(x>70+90*xx && y>80+80*yy && x<150+90*xx && y<140+80*yy)
                  {
                      return nuevo;
                  }
                  nuevo = nuevo->sig;   
                  xx+=1;  
                  if(xx==8)
                  {
                      xx=0;
                      yy+=1;    
                  }       
            } 
            return NULL;
               
        } 
    }while(true);
}

void dibujaEntidades(Entidades arch,bool archivo,bool agrega, bool elimina)
{
     if(archivo == false && agrega == false && elimina == false)
     {
         if(arch.Archivo !=NULL)
         { 
             outtextxy(10,50,"Cabecera");
             rectangle(11,45,70,70);  
             line(40,70,40,90); 
             line(40,90,70,90); 
             char cDato[10];
             itoa(arch.dir_primer_elemento,cDato,10);
             outtextxy(100,50,cDato); 
         }
        Entidad *nuevo = arch.prim;
        int x=0;
        int y=0;
        while(nuevo)
        {
              dibujaEntidad(nuevo->datEnti,x,y);
              nuevo = nuevo->sig;   
              x+=1;  
              if(x==8)
              {
                  x=0;
                  y+=1;    
              }       
        } 
    }    
}
void dibujaEntidad(DatosEntidad dat,int x,int y)
{
    char cDato[10]; //oliis oliiiiiiiiisssssssssss

    setcolor(WHITE);
    itoa(dat.dir_datos,cDato,10); 
    outtextxy(95+90*x,100+80*y,cDato); 
    //Direccion entidad  
    itoa(dat.dir_entidad,cDato,10); 
    outtextxy(70+90*x,100+80*y,cDato); 
    //Direccion siguiente
    itoa(dat.dir_sig,cDato,10); 
    outtextxy(122+90*x,100+80*y,cDato); 
    
    itoa(dat.dir_atributo,cDato,10); 
    outtextxy(100+90*x,120+80*y,cDato);
    
    outtextxy(73+90*x,80+80*y,dat.nombre);
    
    
    //Direccion al indice del PK
    itoa(dat.dir_PK,cDato,10); 
    outtextxy(122+90*x,120+80*y,cDato); 
    
    rectangle(70+90*x,80+80*y,150+90*x,140+80*y); 
    line(70+90*x,95+80*y,150+90*x,95+80*y);   
    line(70+90*x,120+80*y,150+90*x,120+80*y);    
    line(95+90*x,95+80*y,95+90*x,120+80*y);
    line(120+90*x,95+80*y,120+90*x,140+80*y);

    if(dat.dir_datos != -1)
    { 
        setfillstyle(8,GREEN);
        floodfill(73+90*x,83+80*y,WHITE);
        floodfill(73+90*x,100+80*y,WHITE);
        floodfill(73+90*x,123+80*y,WHITE);
        floodfill(125+90*x,100+80*y,WHITE);
    }
    
    if(dat.dir_sig!=-1)
    {
        setcolor(YELLOW);
        line(150+90*x,110+80*y,160+90*x,110+80*y);
        if(x==7)
        {
          line(160+90*x,110+80*y,160+90*x,150+80*y);
          line(160+90*x,150+80*y,9*x,150+80*y);
          line(9*x,150+80*y,9*x,185+80*y);
          line(9*x,185+80*y,10*x,185+80*y);
        }
    }
}

void MenuModificaEntidad(Entidades *arch,Entidad *nuevo,int x,int y)
{
     bool salir = false;
     cleardevice();
     do{
         rectangle(1,1,999,30);
         
         rectangle(2,2,70,28); 
         outtextxy(10,7,"Atributo"); 

         rectangle(72,2,140,28); 
         outtextxy(78,7,"Regresar");
         
         
         setfillstyle(SOLID_FILL,0);         
         dibujaAtributos(*nuevo); 
         if(ismouseclick(WM_LBUTTONDOWN))
         {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
               if(x>2 && y>2 && x<70 && y<28)
               {
                   bool atri = false;
                   MenuAtributo(&atri,nuevo,x,y);           
               }  
               if(x>72 && y>2 && x<140 && y<28)
               {
                       salir=true; 
               }         
         }                                   
     }while(salir==false);
}

void MenuAtributo(bool *Atrubuto,Entidad *enti,int x,int y)
{
    if(*Atrubuto== false)
    {      
        setfillstyle(SOLID_FILL,BLACK);
        
        rectangle(1,32,199,122);
        bar(2,35,199,60);
        outtextxy(7,40,"Agrega Atributo");      
        line(2,62,199,62);
        bar(2,65,199,90);
        outtextxy(7,70,"Modifica Nombre");
        line(2,92,199,92);  
        bar(2,95,199,120);
        outtextxy(7,100,"Elimina Atributo");
        
          
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
               *Atrubuto=true; 
                if(x>2 && y>35 && x<199 && y<60)
                {   
                        printf("Agrega Atrubuto\n"); 
                        agregaAtrubuto(enti,creaAtrubuto());   
                }        
                if(x>2 && y>65 && x<199 && y<90)
                {
                        printf("Modifica Atrubuto\n");
                        Atributo *nuevo = seleccionaAtributo(*enti);
                         if(nuevo!=NULL)
                         {
                              char cadena[20] = "\0";
                              lee_texto(285,5,cadena,15); 
                              strcpy(nuevo->datAtrib.nombre,cadena);
                              bar(75,45,500,500);
                              
                               FILE *Archivo = fopen("Archivo.bet","rb+");
                               if(Archivo!=NULL)
                               {
                                    fseek(Archivo,nuevo->datAtrib.dir_atributo,SEEK_SET);
                                    fwrite(&nuevo->datAtrib,sizeof(DatosAtributo),1,Archivo);                 
                               }
                               fclose(Archivo); 
                         }
                         cleardevice(); 
                }
                if(x>2 && y>95 && x<199 && y<120)
                {
                         printf("Elimina Atrubuto\n"); 
                         Atributo *nuevo = seleccionaAtributo(*enti);
                         if(nuevo!=NULL)
                         {
                             eliminaAtributo(enti,nuevo);
                             printf("Direccion de altributo seleccionado: %d\n",nuevo->datAtrib.dir_atributo);
                         }
                         cleardevice(); 
                }
            }
        }while(*Atrubuto == false);
        *Atrubuto = false; 
        setfillstyle(SOLID_FILL,BLACK);
        bar(1,32,200,125);
    }
    else
    {
       *Atrubuto = false;
       setfillstyle(SOLID_FILL,BLACK);
       bar(1,32,200,125);
    } 
}

Atributo *creaAtrubuto()
{
  Atributo *nuevo;
  nuevo = (Atributo*)malloc(sizeof(Atributo)); 
  nuevo->ant = NULL;
  nuevo->sig = NULL;
  nuevo->datAtrib.dir_atributo = -1;
  nuevo->datAtrib.dir_sig = -1;
  nuevo->datAtrib.tipo = 'E';
  strcat(nuevo->datAtrib.nombre,"Atributo1"); 
  nuevo->datAtrib.longitud=4;
  return nuevo;
}

void creaListaAtributos(Entidad *enti,Atributo *atri)
{
     if(enti->prim == NULL && enti->ult == NULL)
     {
         enti->prim = atri;
         enti->ult = atri;
     }
     else
     {
         enti->ult->sig = atri;
         atri->ant = enti->ult;
         enti->ult = atri;
     }   
}

void agregaAtrubuto(Entidad *enti,Atributo *atri)
{
     if(enti->datEnti.dir_datos == -1)
     {
         outtextxy(145,7,"Nombre: ");
         char Nombre[20] = "\0";
         char Tipo[0] ; 
         lee_texto(205,7,Nombre,15); 
         strcpy(atri->datAtrib.nombre,Nombre);
         bar(145,5,500,25);

         atri->datAtrib.tipo = dialogBoxTipo();
         cleardevice();
         
         if(atri->datAtrib.tipo == 'C')
         {
            outtextxy(145,7,"Tamaño: ");
            char Longitud[1] ;
            lee_texto(150,7,Tipo,2);                       
            atri->datAtrib.longitud=atoi(Tipo);                         
                                
         }else
         if(atri->datAtrib.tipo == 'B')
         atri->datAtrib.longitud = 1;
            
         if(enti->prim == NULL && enti->ult == NULL)
         {
             FILE *Archivo = fopen("Archivo.bet","rb+"); 
             enti->prim = atri;
             enti->ult = atri;
             
             if(Archivo !=NULL)
             {   
                 fseek(Archivo,0,SEEK_END);
                 atri->datAtrib.dir_atributo = ftell(Archivo);
                 
                 fwrite(&atri->datAtrib,sizeof(DatosAtributo),1,Archivo);
                  
                 enti->datEnti.dir_atributo = atri->datAtrib.dir_atributo;
                 fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);
                 fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);
    
                 printf("Atributo agregado con exito primer atributo\n");          
             }    
             else
                 printf("No existe el archivo\n");
             fclose(Archivo);
         } 
         else
         {
             FILE *Archivo = fopen("Archivo.bet","rb+");
             if(Archivo != NULL)
             {  
                  
                 fseek(Archivo,0,SEEK_END);
                 atri->datAtrib.dir_atributo = ftell(Archivo);                                        
                 fwrite(&atri->datAtrib,sizeof(DatosAtributo),1,Archivo);                                  
                 enti->ult->datAtrib.dir_sig = atri->datAtrib.dir_atributo;    
                 fseek(Archivo,enti->ult->datAtrib.dir_atributo,SEEK_SET);
                 fwrite(&enti->ult->datAtrib,sizeof(DatosAtributo),1,Archivo);    
                 printf("Atributo agregado con exito al final\n");                   
                 enti->ult->sig = atri;   
                 atri->ant = enti->ult; 
                 enti->ult = atri;                   
             } 
             else
                 printf("No existe el archivo\n");            
             fclose(Archivo);
         }  
     }
     else
     {
         outtextxy(500,100,"La entidad ya no puede ser modificada");   
         getch();
     }
}

void eliminaAtributo(Entidad *enti,Atributo *atri)
{
     if(enti->datEnti.dir_datos == -1)
     {
         Atributo *aux=enti->prim;  
         FILE *Archivo = fopen("Archivo.bet","rb+");
    
         if(enti->prim == enti->ult)
         {
             enti->datEnti.dir_atributo = -1;
             fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);  
             fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);                
             aux = enti->prim;
             enti->prim = NULL; 
             enti->ult = NULL;   
             free(aux);       
         }else
         if(enti->prim == atri)
         {
            enti->datEnti.dir_atributo = enti->prim->sig->datAtrib.dir_atributo;
            fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);
            fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);
            enti->prim = enti->prim->sig;
            enti->prim->ant = NULL;
            atri->sig = NULL;
            free(atri);                  
         }else
         if(enti->ult == atri)
         { 
            enti->ult->ant->datAtrib.dir_sig = -1;
            fseek(Archivo,enti->ult->ant->datAtrib.dir_atributo,SEEK_SET);
            fwrite(&enti->ult->ant->datAtrib,sizeof(DatosAtributo),1,Archivo);             
            enti->ult=enti->ult->ant;
            enti->ult->sig=NULL;
            atri->ant=NULL;
            free(atri);   
                
         }else
         {
              atri->ant->datAtrib.dir_sig = atri->sig->datAtrib.dir_atributo;
              fseek(Archivo,atri->ant->datAtrib.dir_atributo,SEEK_SET);
              fwrite(&atri->ant->datAtrib,sizeof(DatosAtributo),1,Archivo);
           atri->sig->ant = atri->ant;
           atri->ant->sig = atri->sig;
           atri->sig = NULL;
           atri->ant = NULL;
           free(atri);    
         }
         fclose(Archivo);
    }
    else
    {
        outtextxy(500,100,"La entidad ya no puede ser modificada");   
        getch();
    }     
}
Atributo *seleccionaAtributo(Entidad enti)
{
     int x=0;
     int y=0;
     bool salir=false;
     cleardevice();
     outtextxy(5,5,"Selecciona el Atributo");
     dibujaAtributos(enti);
     do{
        if(ismouseclick(WM_LBUTTONDOWN))
        {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
            int xx=0;
            int yy=0;
            Atributo *nuevo = enti.prim;
            while(nuevo)
            {
                  if(x>70+90*xx && y>80+80*yy && x<150+90*xx && y<140+80*yy)
                  {
                      return nuevo;
                  }
                  nuevo = nuevo->sig;   
                  yy+=1;  
                  if(yy==8)
                  {
                      yy=0;
                      xx+=1;    
                  }       
            } 
            return NULL;             
        } 
    }while(true);
}

void dibujaAtributos(Entidad ent)
{
    Atributo *nuevo = ent.prim;
    int x = 0;
    int y = 0;
    rectangle(10,40,200,65);
    outtextxy(15,45,"Entidad: ");
    outtextxy(75,45,ent.datEnti.nombre);
    
    while(nuevo)
    {
          dibujaAtributo(nuevo->datAtrib,x,y);
          nuevo = nuevo->sig;   
          y+=1;  
          if(y==6)
          {
              y=0;
              x+=1;   
          }       
    }       
}

void dibujaAtributo(DatosAtributo atri,int x,int y)
{
    char cDato[10];
    char tipo[0];
    tipo[0] = atri.tipo;  
    setcolor(WHITE);
    //Nombre del Atributo
    outtextxy(73+100*x,80+80*y,atri.nombre);
    //Direccion atributo  
    itoa(atri.dir_atributo,cDato,10); 
    outtextxy(70+100*x,100+80*y,cDato);  
    outtextxy(105+100*x,100+80*y,tipo);  
    //Direccion siguiente
    itoa(atri.dir_sig,cDato,10); 
    outtextxy(122+100*x,100+80*y,cDato); 
    
    //Longitud
    itoa(atri.longitud,cDato,10);  
    outtextxy(70+100*x,120+80*y,cDato);

    line(105+100*x,130+80*y,115+100*x,130+80*y);
        
    //Direccion al rregistro
    outtextxy(122+100*x,120+80*y,"Dir");
    
    rectangle(70+100*x,80+80*y,150+100*x,140+80*y); 
 
    line(70+100*x,95+80*y,150+100*x,95+80*y);   
    line(70+100*x,120+80*y,150+100*x,120+80*y);
    
    line(100+100*x,95+80*y,100+100*x,140+80*y);
    line(120+100*x,95+80*y,120+100*x,140+80*y);
     
    if(atri.dir_sig!=-1)
    {
        setcolor(YELLOW);
        if(y==5)
        {
             line(150+90*x,110+80*y,160+90*x,110+80*y);
             line(160+90*x,110+80*y,160+90*x,22*y); 
             line(160+90*x,22*y,170+90*x,22*y); 
        }else
        {
             line(150+100*x,110+80*y,155+100*x,110+80*y);  
             line(155+100*x,110+80*y,155+100*x,150+80*y);
             line(65+100*x,150+80*y,155+100*x,150+80*y);
             line(65+100*x,150+80*y,65+100*x,189+80*y);
             line(65+100*x,189+80*y,70+100*x,189+80*y);
        }
    }
}


Registro *creaRegistro()
{
      Registro *nuevoRegistro = (Registro*)malloc(sizeof(Registro));
      nuevoRegistro->ant=NULL;
      nuevoRegistro->sig = NULL;
      nuevoRegistro->dir_reg = -1;
      nuevoRegistro->dir_sig = -1;
      printf("Registro creado con exito\n");
      return nuevoRegistro;         
}
void creaListaRegistro(Entidad *enti,Registro *reg)
{                     
     if(enti->rp == NULL && enti->ru == NULL)
     {
         enti->rp = reg;
         enti->ru = reg;
     }
     else
     {
         enti->ru->sig = reg;
         reg->ant = enti->ru;
         enti->ru = reg;
     }   
}

void agregaRegistro(Entidad *enti,Registro *reg)
{        
     if(enti->rp == NULL && enti->ru == NULL)
     {
         FILE *Archivo = fopen("Archivo.bet","rb+"); 
         enti->rp = reg;
         enti->ru = reg;
         
         if(Archivo !=NULL)
         {   
             fseek(Archivo,0,SEEK_END);
             reg->dir_reg = ftell(Archivo);
             
             
             fwrite(&reg->dir_reg ,sizeof(long),1,Archivo);
             fwrite(&reg->dir_sig,sizeof(long),1,Archivo);
             enti->datEnti.dir_datos = reg->dir_reg;
              
             Atributo *corre = enti->prim;
             
             /*Se guardan todos los datos que esten en los atributos*/
             while(corre)
             { 
                 cleardevice();
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='C')
                 {
                         rectangle(200,200,700,400);
                         rectangle(201,230,699,399);
                         outtextxy(410,210,corre->datAtrib.nombre);
                         
                       fseek(Archivo,0,SEEK_END);                 
                       char cadena[corre->datAtrib.longitud];
                       lee_texto(10+250,10+280,cadena,corre->datAtrib.longitud);  
                       fwrite(&cadena,sizeof(cadena),1,Archivo);                                    
                 }else
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='E')
                 {                      
                         rectangle(200,200,700,400);
                         rectangle(201,230,699,399);
                         outtextxy(410,210,corre->datAtrib.nombre);
                       
                       fseek(Archivo,0,SEEK_END);   
                       char cadena[corre->datAtrib.longitud];
                       lee_texto(10+250,10+280,cadena,corre->datAtrib.longitud);
                       int entero = atoi(cadena);  
                       fwrite(&entero,sizeof(int),1,Archivo);                                    
                 }else
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='B')
                 { 
                       fseek(Archivo,0,SEEK_END);    
                       bool entero = dialogBoxBool();  
                       fwrite(&entero,sizeof(bool),1,Archivo);                                    
                 }
                        
                 corre = corre->sig;            
             }
             fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);
             fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);

             printf("Registro agregado con exito primer atributo\n");          
         }    
         else
             printf("No existe el archivo\n");
         fclose(Archivo);
     } 
     else
     {
         FILE *Archivo = fopen("Archivo.bet","rb+");
         if(Archivo != NULL)
         {  
              
             fseek(Archivo,0,SEEK_END);
             reg->dir_reg = ftell(Archivo);   
                             
             fwrite(&reg->dir_reg,sizeof(long),1,Archivo);
             fwrite(&reg->dir_sig,sizeof(long),1,Archivo);
             enti->ru->dir_sig = reg->dir_reg;
             
              /*Se guardan todos los datos que esten en los atributos */
             Atributo *corre = enti->prim;
             while(corre)
             { 
                 cleardevice();
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='C')
                 {
                         rectangle(200,200,700,400);
                         rectangle(201,230,699,399);
                         outtextxy(410,210,corre->datAtrib.nombre);    
                                      
                       char cadena[corre->datAtrib.longitud];
                       lee_texto(10+250,10+280,cadena,sizeof(cadena));  
                       fwrite(&cadena,sizeof(cadena),1,Archivo);                                    
                 }else
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='E')
                 {
                       rectangle(200,200,700,400);
                       rectangle(201,230,699,399);
                       outtextxy(410,210,corre->datAtrib.nombre);
                       char cadena[corre->datAtrib.longitud];
                       lee_texto(10+250,10+280,cadena,corre->datAtrib.longitud);
                       int entero = atoi(cadena);  
                       fwrite(&entero,sizeof(int),1,Archivo);                                    
                 }else
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='B')
                 {
                      outtextxy(410,210,corre->datAtrib.nombre);
                       int entero = dialogBoxBool();  
                       fwrite(&entero,sizeof(bool),1,Archivo);                                    
                 }
                        
                 corre = corre->sig;            
             }              
                
             fseek(Archivo,enti->ru->dir_reg,SEEK_SET);
             printf("Direccion del ultimo registro %d\n",enti->ru->dir_reg);
             fwrite(&enti->ru->dir_reg,sizeof(long),1,Archivo);
             fwrite(&enti->ru->dir_sig,sizeof(long),1,Archivo);
 
             printf("Registro agregado con exito al final\n"); 
             
             enti->ru->sig = reg;   
             reg->ant = enti->ru; 
             enti->ru = reg;  
         } 
         else
             printf("No existe el archivo\n"); 
         fclose(Archivo);
     } 
}
void MenuRegistro(bool *elimina,Entidades arch,int x,int y)
{
    if(*elimina== false)
    {      
        setfillstyle(SOLID_FILL,BLACK);
        
        rectangle(140,32,199+140,150);
        setfillstyle(SOLID_FILL,BLACK);
        
        
        bar(140,35,199+140,60);
        outtextxy(158,40,"Agrega Registro");      
    
        bar(140,65,199+140,90);
        outtextxy(158,70,"Visualiza Registro");
        line(140,62,199+140,62);

        bar(140,95,199+140,120);
        outtextxy(158,100,"Elimina Registro");
        line(140,92,199+140,92);  
        
        bar(140,125,199+140,150);
        outtextxy(158,130,"Modifica Registro");
        line(140,122,199+140,122);  
          
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
               *elimina=true; 
                if(x>140 && y>35 && x<199+140 && y<60)
                {  
                     Entidad *nuevo = seleccionaEntidad(arch);
                     if(nuevo!=NULL)
                     {
                         if(nuevo->prim != NULL && nuevo->ult != NULL)
                         {
                              agregaRegistro(nuevo,creaRegistro());          
                         }else
                         {
                               printf("No existen atributos en la entidad\n");
                         }
                     }                 
                }
                if(x>140 && y>65 && x<199+140 && y<90)
                { 
                     Entidad *nuevo = seleccionaEntidad(arch);
                     if(nuevo!=NULL)
                     {
                          if(nuevo->datEnti.dir_datos!=-1)
                             dibujaRegistros(nuevo);  
                          else
                              {
                                   printf("La entidad no tiene registros");                   
                              }      
                     }
                }
                //Elimina registro
                if(x>140 && y>95 && x<199+140 && y<120)
                {
                                      
                       printf("Elimina Registro\n");
                       Entidad *nuevo = seleccionaEntidad(arch);
                         if(nuevo!=NULL)
                         {
                             Registro *reg = seleccionaRegistros(nuevo);
                             if(reg!=NULL)
                             eliminaRegistro(nuevo,reg);
                         }
                         cleardevice();        
                }
                //Modifica registro
                if(x>140 && y>125 && x<199+140 && y<150)
                {                
                       printf("Modifica Registro\n");
                       Entidad *nuevo = seleccionaEntidad(arch);
                         if(nuevo!=NULL)
                         {
                             Registro *reg = seleccionaRegistros(nuevo);
                             if(reg!=NULL)
                             modificaRegistro(nuevo,reg);
                         }
                         cleardevice();     
                }
            }
        }while(*elimina == false);
        *elimina = false; 
        setfillstyle(SOLID_FILL,BLACK);
        bar(140,35,199+140,90);
    }
    else
    {
       *elimina = false;
       setfillstyle(SOLID_FILL,BLACK);
       bar(140,65,199+140,90);
    } 
}
void dibujaRegistros(Entidad *ent)
{
     system("cls");   
     cleardevice();
     FILE *Archivo = fopen("Archivo.bet","rb");
     long dir;
     long dato;
     bool bol;
     int numAtri =0;
     int x,y; 
     int i,j;
     Atributo *atriCore = ent->prim;
     Registro *reg = ent->rp;
     Atributo *atri = ent->prim;

      
    while(atriCore)
    {
           numAtri+=1;
            atriCore = atriCore->sig;
    }
    atriCore = ent->prim; 
    x=850/(numAtri);
    i=j=0;
    y=30;
    while(atriCore)
    {
           outtextxy(25+x*i,30+y*j,atriCore->datAtrib.nombre);
           rectangle(25+x*i,30+y*j,25+x+x*i,30+y+y*j);   
           setfillstyle(8,GREEN);
           floodfill(26+x*i,31+y*j,WHITE);
           atriCore = atriCore->sig;
           i+=1;
    } 

     if(Archivo!=NULL)
     {
          while(reg)
          { 
             Atributo *atri = ent->prim;
             dir = reg->dir_reg;
             fseek(Archivo,dir,SEEK_SET);
             
             fread(&dir,sizeof(long),1,Archivo);      
             fread(&dir,sizeof(long),1,Archivo);
             i=0; 
             while(atri)
             {
                 if(atri->datAtrib.tipo == 'C')
                 {
                     char caracter[atri->datAtrib.longitud];
                     fread(&caracter,sizeof(caracter),1,Archivo); 
                     outtextxy(25+x*i,60+y*j,caracter);
                     rectangle(25+x*i,60+y*j,25+x+x*i,60+y+y*j);                
                 }else
                 if(atri->datAtrib.tipo == 'E')
                 {
                     fread(&dato,sizeof(long),1,Archivo);
                     char nuevo[3];  itoa(dato,nuevo,10);
                     outtextxy(25+x*i,60+y*j,nuevo);
                     rectangle(25+x*i,60+y*j,25+x+x*i,60+y+y*j);                  
                 }else
                 if(atri->datAtrib.tipo == 'B')
                 {
                     fread(&bol,sizeof(bool),1,Archivo);
                     if(bol == 1)
                     outtextxy(25+x*i,60+y*j,"Verdadero");
                     else
                     outtextxy(25+x*i,60+y*j,"Falso");
                     rectangle(25+x*i,60+y*j,25+x+x*i,60+y+y*j);                        
                 } 
                    atri = atri->sig;
                    i+=1;
              }
             reg = reg->sig;
             j+=1;
         }
         
     }
     fclose(Archivo); 
     getch();
}
Registro *seleccionaRegistros(Entidad *ent)
{
     system("cls");  
     FILE *Archivo = fopen("Archivo.bet","rb");
     long dir;
     long dato;
     bool bol;
     int numAtri =0;
     int x,y;
     int x1,y1; 
     int i,j;
     Atributo *atriCore = ent->prim;
     Registro *reg = ent->rp;
     Atributo *atri = ent->prim;

     cleardevice();
    while(atriCore)
    {
           numAtri+=1;
            atriCore = atriCore->sig;
    }
    atriCore = ent->prim; 
    x=850/(numAtri);
    i=j=0;
    y=30;
    while(atriCore)
    {
           outtextxy(25+x*i,30+y*j,atriCore->datAtrib.nombre);
           rectangle(25+x*i,30+y*j,25+x+x*i,30+y+y*j);   
           setfillstyle(8,GREEN);
           floodfill(26+x*i,31+y*j,WHITE);
           atriCore = atriCore->sig;
           i+=1;
    } 

     if(Archivo!=NULL)
     {
          while(reg)
          { 
             Atributo *atri = ent->prim;
             dir = reg->dir_reg;
             fseek(Archivo,dir,SEEK_SET);
             
             fread(&dir,sizeof(long),1,Archivo);      
             fread(&dir,sizeof(long),1,Archivo);
             i=0; 
             while(atri)
             {
                 if(atri->datAtrib.tipo == 'C')
                 {
                     char caracter[atri->datAtrib.longitud];
                     fread(&caracter,sizeof(caracter),1,Archivo); 
                     outtextxy(25+x*i,60+y*j,caracter);
                     rectangle(25+x*i,60+y*j,25+x+x*i,60+y+y*j);                
                 }else
                 if(atri->datAtrib.tipo == 'E')
                 {
                     fread(&dato,sizeof(long),1,Archivo);
                     char nuevo[3];  itoa(dato,nuevo,10);
                     outtextxy(25+x*i,60+y*j,nuevo);
                     rectangle(25+x*i,60+y*j,25+x+x*i,60+y+y*j);                  
                 }else
                 if(atri->datAtrib.tipo == 'B')
                 {
                     fread(&bol,sizeof(bool),1,Archivo);
                     if(bol == 1)
                     outtextxy(25+x*i,60+y*j,"Verdadero");
                     else
                     outtextxy(25+x*i,60+y*j,"Falso");
                     rectangle(25+x*i,60+y*j,25+x+x*i,60+y+y*j);                        
                 } 
                    atri = atri->sig;
                    i+=1;
              }
             reg = reg->sig;
             j+=1;
         }
         fclose(Archivo); 
     }
    do{
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x1,y1);
            clearmouseclick(WM_LBUTTONDOWN); 
            int yy=30;
            int j=0;
            Registro *reg = ent->rp;
            while(reg)
            {
                  if(x1>30 && y1>60+yy*j && x1<850 && y1<60+yy+yy*j)
                  {
                     fclose(Archivo); 
                     return reg;
                  }
                  reg = reg->sig;
                  j+=1;
            } 
            return NULL;   
        } 
    }while(true);
    getch();
}
void eliminaRegistro(Entidad *enti,Registro *reg)
{
     if(enti->datEnti.dir_datos != -1)
     {
          Registro *aux=enti->rp;  
         FILE *Archivo = fopen("Archivo.bet","rb+");
    
         if(enti->rp == enti->ru)
         {
             enti->datEnti.dir_datos = -1;
             fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);  
             fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);              
             aux = enti->rp;
             enti->rp = NULL; 
             enti->ru = NULL;          
         }else
         if(enti->rp == reg)
         {
            enti->datEnti.dir_datos = enti->rp->sig->dir_reg;
            fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);
            fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);
            enti->rp = enti->rp->sig;
            enti->rp->ant = NULL;
            reg->sig = NULL;
            free(reg);                  
         }else
         if(enti->ru == reg)
         { 
            enti->ru->ant->dir_sig = -1;
            fseek(Archivo,enti->ru->ant->dir_reg,SEEK_SET);
            
            fwrite(&enti->ru->ant->dir_reg ,sizeof(long),1,Archivo);
            fwrite(&enti->ru->ant->dir_sig,sizeof(long),1,Archivo);   
                    
            enti->ru=enti->ru->ant;
            enti->ru->sig=NULL;
            reg->ant=NULL;//No se porque los comente checar
            free(reg);   
                
         }else
         {
              reg->ant->dir_sig = reg->sig->dir_reg;
              fseek(Archivo,reg->ant->dir_reg,SEEK_SET);
              fwrite(&reg->ant->dir_reg ,sizeof(long),1,Archivo);
              fwrite(&reg->ant->dir_sig,sizeof(long),1,Archivo); 
              
              reg->sig->ant = reg->ant;
              reg->ant->sig = reg->sig;
              reg->sig = NULL;
              reg->ant = NULL;
              free(reg);    
         }
         fclose(Archivo);                         
                                   
     }else
     {
        outtextxy(500,100,"No existen registros");   
        getch();     
     }  
}
void modificaRegistro(Entidad *enti,Registro *reg)
{
     cleardevice();
     dibujaAtributos(*enti);
     Atributo *nuevo = seleccionaAtributo(*enti);
     if(nuevo!=NULL)
     {
         long tam;
         char tipo;
         long dir;
         char nombre[20];
         FILE *Archivo = fopen("Archivo.bet","rb");
         
         
         if(Archivo != NULL)
         {    
             fseek(Archivo,reg->dir_reg,SEEK_SET);  
                             
             fread(&dir,sizeof(long),1,Archivo);
             fread(&dir,sizeof(long),1,Archivo);
    
             Atributo *corre = enti->prim;
             while(corre)
             { 
                 cleardevice();
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='C')
                 {
                     if(corre == nuevo)
                     {
                         tam = corre->datAtrib.longitud;
                         tipo = 'C';  
                         dir = ftell(Archivo); 
                         strcpy(nombre,corre->datAtrib.nombre); 
                         printf("Cadena\n");  
                     }
                       char cadena[corre->datAtrib.longitud]; 
                       fread(&cadena,sizeof(cadena),1,Archivo); 
                                                         
                 }else
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='E')
                 {
                     if(corre == nuevo)
                     {
                         tam = corre->datAtrib.longitud;
                         tipo = 'E';  
                         dir = ftell(Archivo);
                         strcpy(nombre,corre->datAtrib.nombre);    
                         printf("Entero\n");  
                     }
                       int entero;  
                       fread(&entero,sizeof(int),1,Archivo);  
                                                        
                 }else
                 if(corre !=NULL)
                 if(corre->datAtrib.tipo =='B')
                 {
                     if(corre == nuevo)
                     {
                         tam = corre->datAtrib.longitud;
                         tipo = 'B';  
                         dir = ftell(Archivo);
                         strcpy(nombre,corre->datAtrib.nombre); 
                         printf("Boleano\n");      
                     }
                       int boleano;  
                       fread(&boleano,sizeof(bool),1,Archivo);  
                                                        
                 }                    
                 corre = corre->sig;            
             } 
             fclose(Archivo);
         } 
         fclose(Archivo);                
         Archivo = fopen("Archivo.bet","rb+");   
         if(Archivo!=NULL)
         {
             fseek(Archivo,dir,SEEK_SET);
             if(tipo == 'C')
             {
                  rectangle(200,200,700,400);
                  rectangle(201,230,699,399);
                  outtextxy(410,210,nombre);    
                                          
                  char cadena[tam];
                  lee_texto(10+250,10+280,cadena,sizeof(cadena));  
                  fwrite(&cadena,sizeof(cadena),1,Archivo);   
             }
             else
             if(tipo == 'E')
             {
                  rectangle(200,200,700,400);
                  rectangle(201,230,699,399);
                  outtextxy(410,210,nombre);
 
                  char cadena[tam];
                  lee_texto(10+250,10+280,cadena,tam);
                  int entero = atoi(cadena);  
                  fwrite(&entero,sizeof(int),1,Archivo);
             }
             else
             if(tipo == 'B')
             {
                  outtextxy(410,210,nombre);
                  int entero = dialogBoxBool();  
                  fwrite(&entero,sizeof(bool),1,Archivo);    
             }  
             fclose(Archivo);                             
         }  
     }
}


