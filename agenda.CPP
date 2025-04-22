#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <process.h>

typedef struct
   {
    char nombre[50];
    char direccion[30];
    char tel[30];
    char mail[50];
    char cum[15];
    int pos;
   } registro;

//------------------- FUNCIONES ------------------------------------------
long filesize(FILE *stream);
void writexy(char cadena[],int x,int y);
void wrotexy(char cad,int x,int y);
int  cant_reg(void);
void ayuda(void);
void menu(void);

int ver_tel(char tel[]);
int ver_direc(char dir[]);
int ver_dir(char rax[]);
int ver_mail(char mail[]);

void generar(void);
void listar(void);
void abrir(void);
void buscar(void);
void modificar (int);
void borrar(int);
void anadir(void);
void del_file(void);
void ord_nom(void);

//------------------- VARIABLES GLOBALES -----------------------------------
char path_global[50];
long length;
registro regi;
FILE *fpt,*fpt2;

//------------------- ESCRIBE UNA CADENA EN UN PUNTO INDICADO --------------
void writexy(char cadena[],int x,int y)
{
  gotoxy(x,y);
  puts(cadena);
}
//------------------- ESCRIBE UNA CHAR EN UN PUNTO INDICADO ----------------
void wrotexy(char cad,int x,int y)
{
  gotoxy(x,y);
  printf("%c", cad);
}
//-------------- VERIFICA EL NOMBRE -------------------------------------
int ver_nom(char nom[])
{
 int algo=0,k,j;

 for(j=0;j<strlen(nom);j++)
   if(isascii(nom[j]))
      break;
 for (k=j;k<strlen(nom);k++)
  if ((isalpha(nom[k]))||(nom[k]==' '))
    algo=1;
  else
   return(0);
 if (algo==1)
   return(1);

}
//-------------- VERIFICA EL TELEFONO -----------------------------------
int ver_tel(char tel[])
{
 int algo=0,k,j;

 for(j=0;j<strlen(tel);j++)
   if(isascii(tel[j]))
      break;
   if (!strcmp(tel,""))
    return(1);
 for (k=j;k<strlen(tel);k++)
  if ((isdigit(tel[k]))||(tel[k]==' '))
    algo=1;
  else
   return(0);
 if (algo==1)
   return(1);

}
//-------------- VERIFICA LA DIRECCION ----------------------------------
int ver_direc(char dir[])
{
 int algo=0,k,j;

 for(j=0;j<strlen(dir);j++)
   if(isascii(dir[j]))
      break;
 for (k=j;k<strlen(dir);k++)
  if ((isalpha(dir[k]))||(dir[k]==' ')||(isdigit(dir[k])))
    algo=1;
  else
   return(0);
 if (algo==1)
   return(1);

}
//-------------- VERIFICA EL CUMPLEA�OS ---------------------------------
int ver_cum(char cum[])
{
// const true = 1;
// const false = 0;

 int k,j;
 int ban1=false,ban2=false,ban3=false;

 for(j=0;j<strlen(cum);j++)
   if(isascii(cum[j]))
      break;
 k=j;
 if ((isdigit(cum[k])) && (isdigit(cum[k+1])) && ((cum[k+2]=='\\') ||(cum[k+2]=='/')||(cum[k+2]=='-')) && (isdigit(cum[k+3])) && (isdigit(cum[k+4])))
    ban1=true;
 else
   return(0);
 if (cum[k]>'3')
   return(0);
 else
   if ( (cum[k]=='3') && (cum[k+1]>'2') )
     return(0);
   else
     if (cum[k]<='3')
	ban2=true;
     else
	return(0);
 if (cum[k+3]>'2')
   return(0);
 else
   if ((cum[k+3]=='1') && (cum[k+4]>='2') )
     return(0);
   else
     if (cum[k+3]<='1')
       ban3=true;
     else
       return(0);
 if ((ban1 && ban2 && ban3)==true)
    return(1);
 else
    return(0);

}
//-------------- VERIFICA EL EMAIL INGRESADO ----------------------------
int ver_mail(char mail[])
{
  //const true=1;
  //const false=0;

  int bool1=false,bool2=false,bool3=false,bool4=true,i,j;

  for(j=0;j<strlen(mail);j++)
   if(isascii(mail[j]))
      break;
  if (!strcmp(mail,""))
    return(1);
  for (i=0;mail[i]!='@' && i<strlen(mail);i++)
    if (isalpha(mail[i]) || isdigit(mail[i]) || (mail[i]=='-') || (mail[i]=='_') || (mail[i]=='.') )
	bool1=true;
    else
       return(0);
  for (j=i+1;mail[j]!='.' && j<strlen(mail);j++)
    if (isalpha(mail[j]) || isdigit(mail[j]))
	bool2=true;
    else
       return(0);
  if (isalpha(mail[j+1]) && isalpha(mail[j+2]) && isalpha(mail[j+3]))
	bool3=true;
     else
	return(0);
  if (mail[j+4]=='.')
    if (isalpha(mail[j+5]) && isalpha(mail[j+6]))
	  bool4=true;
	else
	  return(0);
  if ((bool1 && bool2 && bool3 && bool4)==true)
     return(1);
   else
     return(0);
}
//--------------- VERIFICA LA DIRECCION DEL ARCHIVO ---------------------
int ver_dir(char rax[])
{
  //const true=1;
  //const false= 0;
  int bool1=false,bool2=false,bool3=false,bool4=false,k;

  for(k=0;k<strlen(rax);k++)
    if(isascii(rax[k]))
      break;
  if (isalpha(rax[k]))
      bool1=true;
  else
     return(0);
  if((rax[k+1]==':')&& ( (rax[k+2]=='\\')||(rax[k+2]=='/') ) )
      bool2=true;
  else
     return(0);
  for (k=k+3;rax[k]!='.'&&k<strlen(rax);k++)
    if(isalpha(rax[k]) || (rax[k]=='\\')||(rax[k]=='/') )
	bool3=true;
    else
       return(0);
  if (isalpha(rax[k+1]) && isalpha(rax[k+2]) && isalpha(rax[k+3]))
	bool4=true;
     else
	return(0);
  if ((bool1 && bool2 && bool3 && bool4)==true)
     return(1);
   else
     return(0);
}
//--------------- GENERA EL ARCHIVO -------------------------------------
void generar(void)

{
  char path[60],aux_nom[50],op,cont=0;

  clrscr();
  printf("INGRESE DIRECTORIO:  ");
  gets(path);
  if (ver_dir(path)) 
   {
	 printf("INGRESE LOS DATOS");
	 printf("\nNombre: ");
	 fflush(stdin);
	 gets(aux_nom);
	 strupr(aux_nom);
	 while (!ver_nom(aux_nom))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nNombre: ");
	     fflush(stdin);
	     gets(aux_nom);
	   }
	 while (strcmp(aux_nom ,""))
	 {
	   fflush(stdin);
	   strcpy(regi.nombre,aux_nom);
	   printf("\nDireccion: ");
	   fflush(stdin);
	   gets(regi.direccion);
	   while (!ver_direc(regi.direccion))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nDireccion: ");
	     fflush(stdin);
	     gets(regi.direccion);
	   }
	   printf("\nTelefono: ");
	   fflush(stdin);
	   gets(regi.tel);
	   while (!ver_tel(regi.tel))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nTelefono: ");
	     fflush(stdin);
	     gets(regi.tel);
	   }
	   printf("\nE-Mail: ");
	   fflush(stdin);
	   gets(regi.mail);
	   while (!ver_mail(regi.mail))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nE-Mail: ");
	     fflush(stdin);
	     gets(regi.mail);
	   }
	   printf("\nCumplea�os: ");
	   fflush(stdin);
	   gets(regi.cum);
	   while (!ver_cum(regi.cum))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nCumplea�os: ");
	     fflush(stdin);
	     gets(regi.cum);
	   }
	   strupr(regi.nombre);
	   strupr(regi.mail);
	   strupr(regi.direccion);
	   regi.pos=cont+1;
	   cont++;
	   fpt=fopen(path,"ab");
	   fwrite(&regi,sizeof regi,1,fpt);
	   fclose(fpt);
	   printf("\n\nDESEA INGRESAR MAS DATOS? S=Si/N=No:  ");
	   op=getche();
	   op=toupper(op);
	   if (op!='S')
	      break;
	   printf("\nNombre: ");
	   fflush(stdin);
	   gets(aux_nom);
	   while (!ver_nom(aux_nom))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nNombre: ");
	     fflush(stdin);
	     gets(aux_nom);
	     strupr(aux_nom);
	     if (strcmp(aux_nom,""))
	       break;
	   }
	}
       strcpy(path_global,path);
    }
   else
     {
	printf("EL DIRECTORIO NO ESTA LISTO");
	getch();
     }
     clrscr();
}
//--------------- SUBMENU -----------------------------------------------
void submenu(void)
{
  int j,pos;
  char op2;                                                

  scanf("%d",&pos);
//  if (!isdigit(pos))
 //   return;
  clrscr();
  writexy("��������������������ͻ",1,1);
  writexy("�  1. -> Modificar   �",1,2);
  writexy("�  2. -> Borrar      �",1,3);
  writexy("��������������������ͼ",1,4);
  printf("ELIJA UNA OPCION:  ");
  op2=getche();
  fclose(fpt);
  switch (op2)
  {
   case '1': modificar(pos);
	     break;
   case '2': borrar(pos);
	     break;
  }

}
//------------------ LISTA LA AGENDA ------------------------------------
void listar(void)
{
  int i=1;
  char op;

  if (!strcmp(path_global,""))
    {
      writexy("ABRA LA AGENDA",32,16);
      //delay(2000);
    }
  else
  {
     fpt=fopen(path_global,"rb");
     clrscr();
     while (length!=filesize(fpt))
     {
       fread(&regi, sizeof regi, 1, fpt);
       printf("%d\n",regi.pos);
       fflush(stdin);
       printf("Nombre: %s \n",regi.nombre);
       if (strcmp(regi.tel,""))
	  printf("Telefono: %s \n",regi.tel);
       else
	  printf("Telefono: NO TIENE \n");
       printf("Direccion: %s \n",regi.direccion);
       if (strcmp(regi.mail,""))
	  printf("E-Mail: %s\n",regi.mail);
       else
	  printf("E-Mail: NO TIENE \n");
       if (strcmp(regi.cum,""))
	  printf("Cumplea�os: %s \n",regi.cum);
       else
	  printf("Cumplea�os: NO TIENE \n");
       i++;
       if (i==5)
	 {
	   printf("Presione una tecla para continuar...");
	   op=getche();
	   if(op==27)
		submenu();
	   i=1;
	   clrscr();
	 }
     }
     if (i!=1)
       {
	 printf("Presione una tecla para continuar...");
	 op=getche();
	 if(op==27)
	     submenu();
       }
  fclose(fpt);
  }
 clrscr();
}
//---------------------- ??? --------------------------------------------
long filesize(FILE *stream)
{
   long curpos;

   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return curpos;
}
//--------------------- ABRE EL ACHIVO ----------------------------------
void abrir(void)
{
  clrscr();
  printf("INGRESE DIRECTORIO:  ");
  gets(path_global);
  if (!strcmp(path_global,""))
  {
    printf("INGRESE UN DIRECTORIO VALIDO:  ");
    gets(path_global);
    if ((fpt=fopen(path_global,"rb")) == NULL)
    {
      printf("NO SE ENCONTRO EL ARCHIVO");
      getch();
    }
  }
  else
  {
    if ((fpt=fopen(path_global,"rb")) == NULL)
    {
      writexy("NO SE ENCONTRO EL ARCHIVO",25,6);
      getch();
    }
  }
  fflush(stdin);
  clrscr();
}
//---------------------- BUSCA UN "STRING" EN EL ARCHIVO ----------------
void buscar(void)
{
  //const true=1;
  //const false=0;

  char clave[25],op;
  int ban,bar,i=1;

  if (!strcmp(path_global,""))
    {
     writexy("ABRA LA AGENDA",32,16);
     //delay(2000);
    }
  else
    {
      do {
	clrscr();
	fpt=fopen(path_global,"rb");
	printf("INGRESE PALABRA CLAVE:  ");
	gets(clave);
	fflush(stdin);
	while (!ver_direc(clave))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     fflush(stdin);
	     gets(clave);
	   }
	strupr(clave);
	clrscr();
	bar=false;
	while (length!=filesize(fpt))
	  {
	    ban=false;
	    fread(&regi, sizeof regi, 1, fpt);
	    if ((memchr(regi.nombre,*clave, strlen(regi.nombre))) && (ban==false))
	      {
		printf("%d\n",regi.pos);
		printf("NOMBRE:  %s\n",regi.nombre);
		printf("Direccion:   %s\n",regi.direccion);
		if (strcmp(regi.tel,""))
		  printf("Telefono: %s \n",regi.tel);
		else
		  printf("Telefono: NO TIENE \n");
		if (strcmp(regi.mail,""))
		  printf("E-Mail: %s\n",regi.mail);
		else
		  printf("E-Mail: NO TIENE \n");
		if (strcmp(regi.cum,""))
		  printf("Cumplea�os: %s \n",regi.cum);
		else
		  printf("Cumplea�os: NO TIENE \n");
		ban=true;
		bar=true;
		i++;
	      }
	    if ((memchr(regi.direccion,*clave, strlen(regi.direccion))) && (ban==false))
	      {
		printf("%d\n",regi.pos);
		printf("DIRECCION:  %s\n",regi.direccion);
		printf("Nombre: %s\n",regi.nombre);
		if (strcmp(regi.tel,""))
		  printf("Telefono: %s \n",regi.tel);
		else
		  printf("Telefono: NO TIENE \n");
		if (strcmp(regi.mail,""))
		  printf("E-Mail: %s\n",regi.mail);
		else
		  printf("E-Mail: NO TIENE \n");
		if (strcmp(regi.cum,""))
		  printf("Cumplea�os: %s \n",regi.cum);
		else
		  printf("Cumplea�os: NO TIENE \n");
		ban=true;
		bar=true;
		i++;
	      }
	    if ((memchr(regi.tel,*clave, strlen(regi.tel))) && (ban==false))
	      {
		printf("%d\n",regi.pos);
		printf("TELEFONO:  %s\n",regi.tel);
		printf("Nombre:  %s\n",regi.nombre);
		printf("Direccion:  %s\n",regi.direccion);
		if (strcmp(regi.mail,""))
		  printf("E-Mail: %s\n",regi.mail);
		else
		  printf("E-Mail: NO TIENE \n");
		if (strcmp(regi.cum,""))
		  printf("Cumplea�os: %s \n",regi.cum);
		else
		  printf("Cumplea�os: NO TIENE \n");
		ban=true;
		bar=true;
		i++;
	      }
	    if ((memchr(regi.mail,*clave, strlen(regi.mail))) && (ban==false))
	      {
		printf("%d\n",regi.pos);
		printf("E-MAIL:   %s\n",regi.mail);
		printf("Nombre:   %s\n",regi.nombre);
		printf("Direccion:  %s\n",regi.direccion);
		if (strcmp(regi.tel,""))
		  printf("Telefono: %s \n",regi.tel);
		else
		  printf("Telefono: NO TIENE \n");
		if (strcmp(regi.cum,""))
		  printf("Cumplea�os: %s \n",regi.cum);
		else
		  printf("Cumplea�os: NO TIENE \n");

		ban=true;
		bar=true;
		i++;
	      }
	    if ((memchr(regi.cum,*clave, strlen(regi.cum))) && (ban==false))
	      {
		printf("%d\n",regi.pos);
		printf("CUMPLEA�OS:   %s\n",regi.cum);
		printf("Nombre:   %s\n",regi.nombre);
		printf("Direccion:  %s\n",regi.direccion);
		if (strcmp(regi.tel,""))
		  printf("Telefono: %s \n",regi.tel);
		else
		  printf("Telefono: NO TIENE \n");
		if (strcmp(regi.cum,""))
		  printf("Cumplea�os: %s \n",regi.cum);
		else
		  printf("Cumplea�os: NO TIENE \n");
		ban=true;
		bar=true;
		i++;
	      }
	    if (i==5)
	      {
		printf("Presione una tecla para continuar...");
		op=getche();
		printf("\n\n");
		if (op==27)
		  submenu();
		i=1;
	      }
	  }
       if (i!=1)
       {
	 printf("Presione una tecla para continuar...");
	 op=getche();
	 if(op==27)
	     submenu();
       }
       fclose(fpt);
       if (bar==false)
	 printf("NO SE ENCONTRO NINGUN REGISTRO CON EL CARACTER '%s' \n",clave);
       printf("\nDESEA REALIZAR OTRA BUSQUEDA? S=Si/N=No:  ");
       op=getche();
       op=toupper(op);
      } while (op=='S');
    }
   clrscr();
}
//---------------------- MODIFICA UN CAMPO DE UN REGISTRO ------------
void modificar (int ind)
{
  char pal[50],op;
  registro r;
  fpos_t pos;

  fflush(stdin);
  fpt=fopen(path_global,"rb+");
  fseek(fpt,(ind-1) * sizeof regi,SEEK_CUR);
  fgetpos(fpt,&pos);
  fread(&regi, sizeof regi, 1, fpt);
  r=regi;
  printf("\n1)  Nombre: %s \n",regi.nombre);
  printf("2)  Telefono: %s \n",regi.tel);
  printf("3)  Direccion: %s \n",regi.direccion);
  printf("4)  E-Mail: %s\n",regi.mail);
  printf("5)  Cumplea�os: %s\n",regi.cum);
  printf("\nELIJA EL CAMPO A MODIFICAR:   ");
  op=getche();
  switch (op)
  {
  case '1':{    printf("\nPALABRA A SUSTITUIR:   ");
	      gets(pal);
	      strupr(pal);
	while (!ver_nom(pal))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nPALABRA A SUSTITUIR:   ");
	     fflush(stdin);
	     gets(pal);
	   }
	   strupr(pal);
	   strcpy(r.nombre,pal);
	   fsetpos(fpt,&pos);
	   fwrite(&r, sizeof r, 1, fpt);
	   break;
	}
  case '2':
	 {      printf("\nPALABRA A SUSTITUIR:   ");
	      gets(pal);
	      strupr(pal);
	   while (!ver_tel(pal))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nPALABRA A SUSTITUIR:   ");
	     fflush(stdin);
	     gets(pal);
	   }
	   strupr(pal);
	   strcpy(r.tel,pal);
	   fsetpos(fpt,&pos);
	   fwrite(&r, sizeof r, 1, fpt);
	   break;
	 }
  case '3':
	 {    printf("\nPALABRA A SUSTITUIR:   ");
	    gets(pal);
	    strupr(pal);
	   while (!ver_direc(pal))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nPALABRA A SUSTITUIR:   ");
	     fflush(stdin);
	     gets(pal);
	   }
	   strupr(pal);
	   strcpy(r.direccion,pal);
	   fsetpos(fpt,&pos);
	   fwrite(&r, sizeof r, 1, fpt);
	   break;
	 }
  case '4':
	 {     printf("\nPALABRA A SUSTITUIR:   ");
	     gets(pal);
	     strupr(pal);
	   while (!ver_mail(pal))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nPALABRA A SUSTITUIR:   ");
	     fflush(stdin);
	     gets(pal);
	   }
	   strupr(pal);
	   strcpy(r.mail,pal);
	   fsetpos(fpt,&pos);
	   fwrite(&r, sizeof r, 1, fpt);
	   break;
	 }
  case '5':    printf("\nPALABRA A SUSTITUIR:   ");
	 {   gets(pal);
	     strupr(pal);
	   while (!ver_cum(pal))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nPALABRA A SUSTITUIR:   ");
	     fflush(stdin);
	     gets(pal);
	   }
	   strupr(pal);
	   strcpy(r.cum,pal);
	   fflush(stdin);
	   fsetpos(fpt,&pos);
	   fwrite(&r, sizeof r, 1, fpt);
	   break;
	 }
   default :
    {
      printf("\n\n EL CARACTER %c NO ES VALIDO\n\n",op);
      printf("Presione una tecla para continuar...");
      op=getche();
    }
  }
 fclose(fpt);
}
//------------------- BORRA UN REGISTRO ------------------------------------
void borrar(int ind)
{
  char op,dir[20];
  registro r;
  int inc_=0;

  fflush(stdin);
  fseek(fpt,(ind-1) * sizeof regi,SEEK_CUR);
  fread(&regi, sizeof regi, 1, fpt);
  printf("\n1)  Nombre: %s \n",regi.nombre);
  printf("2)  Telefono: %s \n",regi.tel);
  printf("3)  Direccion: %s \n",regi.direccion);
  printf("4)  E-Mail: %s\n",regi.mail);
  printf("5)  Cumplea�os: %s\n",regi.cum);
  printf("�DESEA ELIMINAR EL REGISTRO S=Si/N=No?:  ");
  op=getche();
  op=toupper(op);
  if (op=='S')
   {
     fclose(fpt);
     strcpy(dir,"C:\\FILE.DAT");
     fpt2=fopen(dir,"wb");
     fpt=fopen(path_global,"rb");
     while (length!=filesize(fpt))
      {
	fread(&regi, sizeof regi, 1, fpt);
	if(ind!=regi.pos)
	  {
	   if(ind!=regi.pos)
	    {
	     if (inc_==1)
	       regi.pos=regi.pos-1;
	     fwrite(&regi, sizeof regi, 1, fpt2);
	    }
	  }
	else
	   inc_=1;
      }
    remove(path_global);
    fcloseall();
    rename(dir,path_global);
   }
}
//--------------------- ORDENAR X NOMBRE ---------------------------------
void ord_nom(void)
{
  FILE *fpt2;
  registro r,reg;
  fpos_t pos1,pos2,pos_aux;
  int i=1;
  char op;

  if (!strcmp(path_global,""))
    {
     writexy("ABRA LA AGENDA",32,16);
     //delay(2000);
    }
  else
    {  clrscr();
       fpt=fopen(path_global,"rb");
       fpt2=fopen("C:\\FILEPOS.DAT","wb");
       while (length!=filesize(fpt))
       {
	 fread(&regi, sizeof regi, 1, fpt);
	 fwrite(&regi, sizeof regi, 1, fpt2);
       }
       fcloseall();
       fpt2=fopen("C:\\FILEPOS.DAT","r+b");
       fgetpos(fpt2,&pos1);
       fflush(fpt);
       fflush(fpt2);
       fflush(stdin);
       pos_aux=sizeof(registro);
       fread(&regi, sizeof regi, 1, fpt2);
       r=regi;
       while (length!=pos1)
       {
	  while (length!=filesize(fpt2))
	  {
	    fgetpos(fpt2,&pos2);
	    fread(&regi, sizeof regi, 1, fpt2);
	    if (strcmp(r.nombre,regi.nombre) > 0 )
	    {
	      r=regi;
	      fsetpos(fpt2, &pos1);
	      fread(&regi, sizeof regi, 1, fpt2);
	      fsetpos(fpt2, &pos2);
	      fwrite(&regi, sizeof regi, 1, fpt2);
	      fsetpos(fpt2, &pos1);
	      fwrite(&r, sizeof r, 1, fpt2);
	    }
	  }
	  pos1=pos1+pos_aux;
	  fsetpos(fpt2,&pos1);
	  fread(&regi, sizeof regi, 1, fpt2);
	  r=regi;
       }
       rewind(fpt2);
       while (length!=filesize(fpt2))
       {
	 fread(&regi, sizeof regi, 1, fpt2);
	 printf("%d\n",regi.pos);
	 fflush(stdin);
	 printf("Nombre: %s \n",regi.nombre);
	 printf("Telefono: %s \n",regi.tel);
	 printf("Direccion: %s \n",regi.direccion);
	 printf("E-Mail: %s\n",regi.mail);
	 printf("Cumplea�os: %s \n",regi.cum);
	 i++;
	 if (i==5)
	 {
	   printf("Presione una tecla para continuar...");
	   op=getche();
	   if(op==27)
		submenu();
	   i=1;
	   clrscr();
	 }
       }
       if (i!=5)
       {
	 printf("Presione una tecla para continuar...");
	 op=getche();
	 if(op==27)
	     submenu();
       }
       fclose(fpt2);

    }
  clrscr();
}
//---------------------- CUENTA LOS REGISTROS DEL ARCHIVO ----------------
int cantreg(void)
{
   long curpos;
   fpos_t pos1;

   fpt=fopen(path_global,"rb");
   curpos = sizeof(registro);
   fseek(fpt, 0L, SEEK_END);
   fgetpos(fpt, &pos1);
   curpos = (pos1/curpos);
   fclose(fpt);
   return (curpos);
}
//---------------------- A�ADE UN REGISTRO -------------------------------
void anadir(void)
{
  char aux_nom[50],op;
  int cant_reg;

  if (!strcmp(path_global,""))
    {
     writexy("ABRA LA AGENDA",32,16);
     //delay(2000);
    }
  else
    {    clrscr();
	 cant_reg=cantreg();
	 printf("INGRESE LOS DATOS");
	 printf("\nNombre: ");
	 fflush(stdin);
	 gets(aux_nom);
	 strupr(aux_nom);
	 while (!ver_nom(aux_nom))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nNombre: ");
	     fflush(stdin);
	     gets(aux_nom);
	   }
	 while (strcmp(aux_nom ,""))
	 {
	   fflush(stdin);
	   strcpy(regi.nombre,aux_nom);
	   printf("\nDireccion: ");
	   fflush(stdin);
	   gets(regi.direccion);
	   while (!ver_direc(regi.direccion))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nDireccion: ");
	     fflush(stdin);
	     gets(regi.direccion);
	   }
	   printf("\nTelefono: ");
	   fflush(stdin);
	   gets(regi.tel);
	   while (!ver_tel(regi.tel))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nTelefono: ");
	     fflush(stdin);
	     gets(regi.tel);
	   }
	   printf("\nE-Mail: ");
	   fflush(stdin);
	   gets(regi.mail);
	   while (!ver_mail(regi.mail))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nE-Mail: ");
	     fflush(stdin);
	     gets(regi.mail);
	   }
	   printf("\nCumplea�os: ");
	   fflush(stdin);
	   gets(regi.cum);
	   while (!ver_cum(regi.cum))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nTelefono: ");
	     fflush(stdin);
	     gets(regi.cum);
	   }
	   strupr(aux_nom);
	   strupr(regi.cum);
	   strupr(regi.mail);
	   strupr(regi.direccion);
	   regi.pos=cant_reg+1;
	   cant_reg++;
	   fpt=fopen(path_global,"ab");
	   fwrite(&regi,sizeof regi,1,fpt);
	   fclose(fpt);
	   printf("\n\nDESEA INGRESAR MAS DATOS? S=Si/N=No:  ");
	   op=getch();
	   toupper(op);
	   if (op!='S')
	      break;
	   printf("\nNombre: ");
	   fflush(stdin);
	   gets(aux_nom);
	   while (!ver_nom(aux_nom))
	   {
	     printf("EL INGRESO DE DATOS NO ES VALIDO");
	     printf("\nNombre: ");
	     fflush(stdin);
	     gets(aux_nom);
	     strupr(aux_nom);
	     if (strcmp(aux_nom,""))
	       break;
	   }
	 }

    }
  clrscr();
}
//--------------------- BORRA EL ARCHIVO ---------------------------------
void del_file(void)
{
  char op;

  if (!strcmp(path_global,""))
    {
      writexy("ABRA LA AGENDA",32,16);
      //delay(2000);
    }
  else
    {
      writexy("�DESEA ELIMINAR EL ARCHIVO S=Si/N=No?",2,19);
      op=getche();
      if (toupper(op)=='S')
	{
	  remove(path_global);
	  strcpy(path_global,"");
	  writexy("EL ARCHIVO SE ELIMINO ",2,21);
	  //delay(2000);
       }
    }
  clrscr();
}
//----------------------- AYUDA -----------------------------------------
void ayuda(void)
{
clrscr();
printf(">>> AYUDA <<<\n");
printf("�������������\n\n");
printf("CREAR: Permite ingresar los datos de las personas que desea agregar a la agenda.");
printf("ABRIR: Abre el archivo de la agenda.\n");
printf("LISTAR: Muestra en pantalla los datos de las personas.\n");
printf("BUSCAR: Mediante esta opcion usted puede realizar una busqueda\n");
printf("A�ADIR: Abre la agenda para agregar mas datos\n");
printf("ORDENAR: Ordena la agenda por nombre.\n");
printf("BORRAR: Elimina la agenda.\n\n");
printf("MODIFICAR DATOS: Permite modificar los datos que han sido ingresados.\n");
printf("BORRAR DATOS: Mediante esta funcion se borra un registro de la agenda.\n");
printf("ESTAS DOS OPCIONES ESTAN DISPONIBLES AL LISTAR LA AGENDA, BUSCAR U ORDENAR.\n");
printf("CUANDO DICE \"Presione una tecla para continuar...\".\n");
printf("SE APRETA ESCAPE LUEGO EL NUMERO DE REGISTRO Y DESPUES ENTER.\n\n");
printf("FORMATO DE REGISTRO\n");
printf("NOMBRE: PEPE\nTELEFONO: 41568251\nDIRECCION: AV EVERGREEN 111\nE-MAIL: PEPE._-@NOSE.COM\nCUMPLEA�OS: 05/04  DD/MM \n\n");
printf("Presione una tecla para continuar ... ");
fflush(stdin);
getch();
clrscr();
}
//---------------------- MENU -------------------------------------------
void menu(int opc)
{
    switch (opc)
    {
      case 7: generar();    break;
      case 8: abrir();      break;
      case 9: listar();     break;
      case 10: buscar();    break;
      case 11: anadir();    break;
      case 12: ord_nom();   break;
      case 13: del_file();  break;
      case 14: exit(0);     break;
     }
}

int main(void)
{

int pos=7,k=18;
char aux;

  clrscr();
 do {
  writexy("Esc=SALIR    F1=AYUDA                       UTILICE LAS FLECHAS PARA DESPLAZARSE",1,1);
  writexy("������������������������ͻ",5,4);
  writexy("�  MENU                  �",5,5);
  writexy("������������������������͹",5,6);
  writexy("�  I.    ->   Crear      �",5,7);
  writexy("�  II.   ->   Abrir      �",5,8);
  writexy("�  III.  ->   Listar     �",5,9);
  writexy("�  IV.   ->   Buscar     �",5,10);
  writexy("�  V.    ->   A�adir     �",5,11);
  writexy("�  VI.   ->   Ordenar    �",5,12);
  writexy("�  VII.  ->   Borrar     �",5,13);
  writexy("�  VIII. ->   Salir      �",5,14);
  writexy("������������������������͹",5,15);
  writexy("�                        �",5,16);
  writexy("������������������������ͼ",5,17);
  gotoxy(7,16);
  printf("%s",path_global);
  switch(pos)
  {
  case 7 : gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Crear ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Crear ");
	   break;
  case 8 : gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Abrir ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Abrir ");
	   break;
  case 9 : gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Listar ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Listar ");
	   break;
  case 10: gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Buscar ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Buscar ");
	   break;
  case 11: gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" A�adir ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" A�adir ");
	   break;
  case 12: gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Ordenar ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Ordenar ");
	   break;
  case 13: gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Borrar ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Borrar ");
	   break;
  case 14: gotoxy(k,pos);
	   textcolor(CYAN);
	   textbackground(BLACK);
	   cprintf(" Salir ");
	   aux=getch();
	   textcolor(7);
	   gotoxy(k,pos);
	   cprintf(" Salir ");
	   break;
  }
  switch(aux)
  {
  case 0x48 : pos=pos-1;
	      if(pos==6)
		pos=18;
	      break;
  case 0x50 : pos=pos+1;
	      if(pos==15)
		pos=4;
	      break;
  case 0x0d : menu (pos); break;
  case 0x3b : ayuda(); break;
  }
 } while (aux!=27);
}  						       //by XQ2  1337-1453//
