#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

// #include <string.h>

int main()
{
  char alfa[3][9] = {{'A','B','C','D','E','F','G','H','I'},{'J','K','L','M','N','O','P','Q','R'},{'S','T','U','V','W','X','Y','Z'}};
  char numbers[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  char *ap, l[256];

  char aBuscar;
  int size, g = 0, i, j, k, x, y, w, z, r1, r2;

  
  printf("Vamos a buscar\n");
  printf("Ingresa una palabra en mayuscula: \n");
  fgets(l, 256, stdin);
  
  ap = &l[0];
  size = strlen(l);

for(g;g<size;g++){
  *(ap+g)= toupper(*(ap+g));
}

printf("La palabra es %s\n", l);






  printf("Vamos a buscarlo:\n");
  for (i = 0; i < size; i++)
  {
    if((*(ap+i)<65 && *(ap+i) != 10) || *(ap+i)>90 ){ // linea con espacio =10
      printf("Encontre un error!!\n");
      printf("Tu error es: %d\n",*(ap+i));
      printf("Termine amigo :((\n");
      exit(0);
    }

    for (j = 0; j < 3; j++)
    {
      for(k = 0; k < 9; k++){
        if (alfa[j][k] == *(ap + i)&& i == 0){
          printf("La palabra comienza con el indice: [%d][%d]\n", j,k);
          x= j;
          y = k;
        }
        else{
          if(alfa[j][k] == *(ap + i)){
            printf("Para ir de %c a %c\n", *(ap+(i-1)),*(ap+i));
            w = j;
            z = k;


            r1 = x-w;

              if(r1 == 0){
                printf("En el mismo renglon\n");
              }else if(r1<0){
                printf("Bajar %g fila(s)\n", fabs(r1));
              } else{
                printf("Subes %d fila(s)\n", r1);
              }

              x = w;


            r2 = y-z;

              if(r2==0){
                printf("En la misma columna\n");
              }else if(r2<0){
                printf("Derecha %g columna(s)\n", fabs(r2));
              } else{
                printf("Izquierda %d columna()s\n", r2);                
              }


              y = z;

            printf("La letra en el indice: [%d][%d]\n", j,k);

          }
        }
      }
      k = 0;
    }
    j = 0;
  }
i=0;



}