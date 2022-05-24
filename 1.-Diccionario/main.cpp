#include <stdio.h>
#include <iostream>

#include <graphics.h>

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
     long dir_sig;
}DatosEntidad;

typedef struct entidad
{
        struct entidad *ant,*sig;
        Atributo *prim;
        Atributo *ult;
        DatosEntidad datEnti;
}Entidad;

typedef struct Lista
{
    bool creada;
    long dir_primer_elemento;
    FILE *Archivo;
    Entidad *prim;  
    Entidad *ult;
}Entidades;

void inicializaListaEntidades(Entidades *arch);
void menu(Entidades arch);
void BarraHerramientas(Entidades arch);
void lee_texto(int x,int y,char cadena[],int numCaracteres);

void MenuArchivo(bool *archivo,Entidades *arch,int x,int y);
void nuevoArchivo(Entidades *arch);
void abrirArchivo(Entidades *arch);

void MenuEntidad(bool *agrega,Entidades *arch,int x,int y);
Entidad *creaEntidad();
void agregaEntidad(Entidades *arch,Entidad *ent);
void creaListaEntidades(Entidades *arch,Entidad *ent);
void eliminaEntidad(Entidades *arch,Entidad *ent);
void dibujaEntidades(Entidades arch,bool archivo,bool agrega, bool elimina);
void dibujaEntidad(DatosEntidad dat,int x,int y);
Entidad *seleccionaEntidad(Entidades arch);

void MenuModificaEntidad(Entidades *arch,Entidad *nuevo,int x,int y);

void MenuAtributo(bool *Atrubuto,Entidad *enti,int x,int y);
Atributo *creaAtrubuto();
void agregaAtrubuto(Entidad *enti,Atributo *atri);
void creaListaAtributos(Entidad *enti,Atributo *atri);
void eliminaAtributo(Entidad *enti,Atributo *atri);
void dibujaAtributos(Entidad ent);
void dibujaAtributo(DatosAtributo atri,int x,int y);
Atributo *seleccionaAtributo(Entidad enti);




int main( )
{
   initwindow( 900 , 600 , "WinBGIm" );
   Entidades arch;
   inicializaListaEntidades(&arch);
   srand( (unsigned)time( NULL ) );
   
   menu(arch);
   
   getch();
}

void menu(Entidades arch)
{	
    bool archivo = false;
    bool agrega = false;
    bool elimina = false;
    
    int x,y;
    
    do
    {
       BarraHerramientas(arch);
       dibujaEntidades(arch,archivo,agrega,elimina);
       if(ismouseclick(WM_LBUTTONDOWN))
       {
           getmouseclick(WM_LBUTTONDOWN,x,y);
           clearmouseclick(WM_LBUTTONDOWN); 
             
           if(x>2 && y>2 && x<70 && y<28)
           {
                  if(agrega == false && elimina ==false)
                 MenuArchivo(&archivo,&arch,x,y); 
           }
          

           if(x>72 && y>2 && x<140 && y<28)
           { 
                 if(archivo == false && elimina ==false)
                 if(arch.Archivo!=NULL == true)
                  MenuEntidad(&archivo,&arch,x,y);     
           }                           
       }
              
    }while(true);
}
void BarraHerramientas(Entidades arch)
{
      rectangle(2,2,70,28); 
      outtextxy(10,7,"Archivo");
      setfillstyle(SOLID_FILL,0); 
      if(arch.Archivo!=NULL)
      {
         rectangle(72,2,140,28); 
         outtextxy(78,7,"Entidad");
         setfillstyle(SOLID_FILL,0); 
      }
      rectangle(1,1,999,30);   
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
void MenuModificaEntidad(Entidades *arch,Entidad *nuevo,int x,int y)
{
     bool salir = false;
     cleardevice();
     do{
         rectangle(1,1,999,30);
         
         rectangle(2,2,70,28); 
         outtextxy(10,7,"Nombre"); 

         rectangle(72,2,140,28); 
         outtextxy(78,7,"Dato");
         
         rectangle(72+70,2,140+70,28); 
         outtextxy(78+70,7,"Atributo");
         
         rectangle(72+70*2,2,140+70*2,28); 
         outtextxy(78+70*2,7,"Regresar");
         
         setfillstyle(SOLID_FILL,0);
          
         dibujaAtributos(*nuevo); 
         
         if(ismouseclick(WM_LBUTTONDOWN))
         {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
               if(x>2 && y>2 && x<70 && y<28)
               {
                   char cadena[20] = "\0";
                   lee_texto(285,5,cadena,15); 
                   strcpy(nuevo->datEnti.nombre,cadena);
                   bar(75,45,500,500);
                   FILE *Archivo = fopen("Archivo.bet","rb+");
                   if(Archivo!=NULL)
                   {
                        fseek(Archivo,nuevo->datEnti.dir_entidad,SEEK_SET);
                        fwrite(&nuevo->datEnti,sizeof(DatosEntidad),1,Archivo);                 
                   }
                   fclose(Archivo);               
               }  
               if(x>72 && y>2 && x<140 && y<28)
               {
               }         
               if(x>142 && y>2 && x<210 && y<28)
               { 
                   bool atri = false;
                   MenuAtributo(&atri,nuevo,x,y);
               } 
               if(x>72+70*2 && y>2 && x<140+70*2 && y<28)
               {
                    salir=true;                    
               }
         }                                   
     }while(salir==false);
     
}

void inicializaListaEntidades(Entidades *arch)
{
      arch->creada=false;
      arch->dir_primer_elemento = -1;
      arch->Archivo = NULL;
      arch->prim = NULL;
      arch->ult = NULL;
}
void nuevoArchivo(Entidades *arch)
{
    arch->creada = true;
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
}
Entidad *creaEntidad()
{
    Entidad *nuevaEntidad;
    nuevaEntidad = (Entidad*)malloc(sizeof(Entidad));
    nuevaEntidad->ant = NULL;
    nuevaEntidad->sig = NULL;
    nuevaEntidad->prim = NULL;
    strcat(nuevaEntidad->datEnti.nombre,"Entidad");
    nuevaEntidad->datEnti.dir_atributo = -1;
    nuevaEntidad->datEnti.dir_datos = -1;
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
void abrirArchivo(Entidades *arch)
{  
     arch->prim = NULL;
     arch->ult = NULL;
     arch->dir_primer_elemento = -1;
     arch->Archivo = fopen("Archivo.bet","rb");
     DatosEntidad dat;
     DatosAtributo aux;
     int x =0;
     long pos =0;
     bool salir = false;
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
     }
     
}
void agregaEntidad(Entidades *arch,Entidad *ent)
{ 
     long pos;   
     if(arch->prim == NULL && arch->ult == NULL)
     {
         FILE *Archivo = fopen("Archivo.bet","rb+"); 
         arch->prim = ent;
         arch->ult = ent;
         
         if(Archivo !=NULL)
         {   
             fseek(Archivo,0,SEEK_END);
             pos = ftell(Archivo);
             arch->dir_primer_elemento = pos;
             ent->datEnti.dir_entidad = pos; 
             fseek(Archivo,0,SEEK_SET);
             fwrite(&arch->dir_primer_elemento,sizeof(long),1,Archivo);                
             fseek(Archivo,0,SEEK_END);                              
             fwrite(&ent->datEnti,sizeof(DatosEntidad),1,Archivo);   
             printf("Entidad Agregada con exito\n");           
         }    
         else
         {
             FILE *Archivo = fopen("Archivo.bet","wb+");
             arch->prim = ent;
             arch->ult = ent; 
             if(Archivo !=NULL)
             {   
                 arch->dir_primer_elemento = sizeof(long);
                 fwrite(&arch->dir_primer_elemento,sizeof(long),1,Archivo);   
                 ent->datEnti.dir_entidad = sizeof(long);                                
                 fwrite(&ent->datEnti,sizeof(DatosEntidad),1,Archivo);   
                 printf("Se ha creado un nuevo Archivo\n");
                 printf("Entidad Agregada con exito\n");           
             }
         } 
         fclose(Archivo);              
     } 
     else
     {
         FILE *Archivo = fopen("Archivo.bet","rb+");
         if(Archivo != NULL)
         {  
             fseek(Archivo,0,SEEK_END); 
             pos = ftell(Archivo);
             arch->ult->datEnti.dir_sig = pos;
             fseek(Archivo,arch->ult->datEnti.dir_entidad,SEEK_SET);
             fwrite(&arch->ult->datEnti,sizeof(DatosEntidad),1,Archivo);
             ent->datEnti.dir_entidad = pos;
             fseek(Archivo,0,SEEK_END);
             fwrite(&ent->datEnti,sizeof(DatosEntidad),1,Archivo);  
             
             arch->ult->sig = ent;
             ent->ant = arch->ult;
             arch->ult = ent;                         
         } 
         fclose(Archivo);
     }  
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
    char cDato[10];
    setcolor(WHITE);
    itoa(dat.dir_datos,cDato,10); 
    outtextxy(105+90*x,100+80*y,cDato); 
    //Direccion entidad  
    itoa(dat.dir_entidad,cDato,10); 
    outtextxy(70+90*x,100+80*y,cDato); 
    //Direccion siguiente
    itoa(dat.dir_sig,cDato,10); 
    outtextxy(122+90*x,100+80*y,cDato); 
    
    itoa(dat.dir_atributo,cDato,10); 
    
    outtextxy(100+90*x,120+80*y,cDato);
    
    outtextxy(73+90*x,80+80*y,dat.nombre);
    
    rectangle(70+90*x,80+80*y,150+90*x,140+80*y); 
    line(70+90*x,95+80*y,150+90*x,95+80*y);   
    line(70+90*x,120+80*y,150+90*x,120+80*y);    
    line(100+90*x,95+80*y,100+90*x,120+80*y);
    line(120+90*x,95+80*y,120+90*x,120+80*y);
 
    
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
void eliminaEntidad(Entidades *arch,Entidad *ent)
{
     Entidad *aux=arch->prim;  
     FILE *Archivo = fopen("Archivo.bet","rb+");
     long dirPrim =-1;
     if(arch->prim == arch->ult)
     {
        fwrite(&dirPrim,sizeof(long),1,Archivo);                
         aux = arch->prim;
         arch->prim = NULL; 
         arch->ult = NULL;   
         free(aux);       
     }else
     if(arch->prim == ent)
     {
        fwrite(&arch->prim->sig->datEnti.dir_entidad,sizeof(long),1,Archivo); 
        arch->prim = arch->prim->sig;
        arch->prim->ant = NULL;
        ent->sig = NULL;
        free(ent);                  
     }else
     if(arch->ult == ent)
     {
         arch->ult->ant->datEnti.dir_sig=-1;   
         fseek(Archivo,arch->ult->ant->datEnti.dir_entidad,SEEK_SET);
         fwrite(&arch->ult->ant->datEnti,sizeof(DatosEntidad),1,Archivo); 
         
        arch->ult=arch->ult->ant;
        arch->ult->sig=NULL;
        ent->ant=NULL;
        free(ent);   
            
     }else
     {
               fseek(Archivo,ent->ant->datEnti.dir_entidad,SEEK_SET);
               ent->ant->datEnti.dir_sig = ent->sig->datEnti.dir_entidad;  
               fwrite(&ent->ant->datEnti,sizeof(DatosEntidad),1,Archivo); 
               ent->sig->ant = ent->ant;
               ent->ant->sig = ent->sig;
               ent->sig = NULL;
               ent->ant = NULL;
               free(ent);    
     }
     fclose(Archivo);
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

void MenuAtributo(bool *Atrubuto,Entidad *enti,int x,int y)
{
    if(*Atrubuto== false)
    {      
        setfillstyle(SOLID_FILL,BLACK);
        rectangle(140,32,199+140,122);
        bar(140,35,199+140,60);
        outtextxy(158,40,"Agrega");       
        line(140,62,199+140,62); 
        bar(140,65,199+140,90);
        outtextxy(158,70,"Modifica");
        line(140,92,199+140,92); 
        bar(140,95,199+140,120);
        outtextxy(158,100,"Elimina");
        
            
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
               getmouseclick(WM_LBUTTONDOWN,x,y);
               clearmouseclick(WM_LBUTTONDOWN); 
               *Atrubuto=true; 
                if(x>140 && y>35 && x<199+140 && y<60)
                {   
                        printf("Agrega Atrubuto\n"); 
                        agregaAtrubuto(enti,creaAtrubuto());   
                }        
                if(x>140 && y>65 && x<199+140 && y<90)
                {
                        printf("Modifica Atrubuto\n");
                        Atributo *nuevo = seleccionaAtributo(*enti);
                         if(nuevo!=NULL)
                         {
                             //MenuModificaAtrubuto(nuevo,nuevo,x,y);
                             printf("Direccion de altributo seleccionado: %d\n",nuevo->datAtrib.dir_atributo);
                         }
                         cleardevice(); 
                }
                if(x>70 && y>95 && x<269 && y<120)
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
        bar(140,30,199+145,125);
    }
    else
    {
       *Atrubuto = false;
       setfillstyle(SOLID_FILL,BLACK);
       bar(140,30,199+145,125);
    } 
}
void eliminaAtributo(Entidad *enti,Atributo *atri)
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

void agregaAtrubuto(Entidad *enti,Atributo *atri)
{ 
     long pos;   
     if(enti->prim == NULL && enti->ult == NULL)
     {
         FILE *Archivo = fopen("Archivo.bet","rb+"); 
         enti->prim = atri;
         enti->ult = atri;
         
         if(Archivo !=NULL)
         {   
             fseek(Archivo,0,SEEK_END);
             pos = ftell(Archivo);
             
             atri->datAtrib.dir_atributo = pos;  
             enti->datEnti.dir_atributo = pos;
             fseek(Archivo,enti->datEnti.dir_entidad,SEEK_SET);
             fwrite(&enti->datEnti,sizeof(DatosEntidad),1,Archivo);
             
             fseek(Archivo,0,SEEK_END);                              
             fwrite(&atri->datAtrib,sizeof(DatosAtributo),1,Archivo);  
             printf("Atributo agregado con exito\n");          
         }    
         else
             printf("No existe el archivo\n");
      
     } 
     else
     {
         FILE *Archivo = fopen("Archivo.bet","rb+");
         
         
         if(Archivo != NULL)
         {  
              
             fseek(Archivo,0,SEEK_END);
             pos = ftell(Archivo);                        
             enti->ult->datAtrib.dir_sig = pos;    
             fseek(Archivo,enti->ult->datAtrib.dir_atributo,SEEK_SET);
             fwrite(&enti->ult->datAtrib,sizeof(DatosAtributo),1,Archivo);
             
             atri->datAtrib.dir_atributo = pos; 
             
             fseek(Archivo,0,SEEK_END);                              
             fwrite(&atri->datAtrib,sizeof(DatosAtributo),1,Archivo); 
              
             printf("Atributo agregado con exito\n");  
             
             enti->ult->sig = atri;   
             atri->ant = enti->ult; 
             enti->ult = atri;  
             
         } 
         else
             printf("No existe el archivo\n");
         
         fclose(Archivo);
     }  
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
    setcolor(WHITE);
    //Nombre del Atributo
    outtextxy(73+100*x,80+80*y,atri.nombre);
    //Direccion atributo  
    itoa(atri.dir_atributo,cDato,10); 
    outtextxy(70+100*x,100+80*y,cDato); 

    //itoa(dat.dir_datos,cDato,10); 
    tipo[0] = atri.tipo;
    
    outtextxy(105+100*x,100+80*y,tipo); 
    
    
    //Direccion siguiente
    itoa(atri.dir_sig,cDato,10); 
    outtextxy(122+100*x,100+80*y,cDato); 
    
    //Longitud
    itoa(atri.longitud,cDato,10);  
    outtextxy(100+100*x,120+80*y,cDato);
    
    
    
    rectangle(70+100*x,80+80*y,150+100*x,140+80*y); 
 
    line(70+100*x,95+80*y,150+100*x,95+80*y);   
    line(70+100*x,120+80*y,150+100*x,120+80*y);
    
    line(100+100*x,95+80*y,100+100*x,120+80*y);
    line(120+100*x,95+80*y,120+100*x,120+80*y);
 
    
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
