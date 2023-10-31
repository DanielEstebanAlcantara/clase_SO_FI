/*
Integrantes:
  -Alcantara Paleo Daniel Esteban
  -Beltrán Hernández Nathan
  -Ovando Nader Carlos Enrique
  -Trigueros López Héctor Adrián
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
///////////////////////////

int main()
{
  FILE *file;

  char alfa[3][9] = {{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}, {'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'}, {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};
  // msg separa por renglones, row para lectura, rowTo para escritura
  char *ap, msg[3][256], row[256] = {0}, rowTo[256] = {0};
  int size, g = 0, i, j, k, x, y, w, z, r, c, r1, r2, renglones; // para busqueda
  int a[2], b[2];                                                // tuberias
  int pid, cont;

  printf("\n***** Bienvenido al Buscador de Nombres *****\n\n");
  printf("Soy el PADRE (pid = %d):\n\n", getpid());
  printf("Mira el Abecedario:\n");

  for (r = 0; r < 3; r++)
  {
    for (c = 0; c < 9; c++)
    {
      printf("%c\t", alfa[r][c]);
    }
    printf("\n");
    c = 0;
  }

  printf("\n\nComencemos:\n\n");
  // conteo para los hijos
  for (cont = 0; cont < 2; cont++)
  {
    switch (pid = fork())
    {
    case -1: // error
      printf("Existio un error en la creacion del HIJO %d\n", cont);
      exit(0);
      break;

    case 0: // hijo 1
      if (cont == 0)
      {
        printf("Soy el HIJO 1 (pid = %i)\n", getpid());
        printf("HIJO1 (pid = %i): Creando el archivo de salida ...\n", getpid());

        system("touch nombres.txt");

        printf("HIJO1 (pid = %i): Archivo de salida creado con exito!\n", getpid());
        printf("HIJO1 (pid = %i): Termine.\n", getpid());
        exit(0);
        break;
      }

      else
      {
        // el padre lee y los escribe en el pipe
        // el hijo espero o lee
        close(a[0]);
        close(b[1]);

        printf("Soy el HIJO 2 (pid = %i)\n", getpid());
        printf("HIJO2 (pid = %d):Voy a leer lo que dice mi PADRE (pid = %d)\n", getpid(), getppid());

        // if(row == )

        read(b[0], row, 256);
        printf("Estoy leyendo\n");
        //----------------------------------------------------------------------------------------
        /*                     SE USA UN APUNTADOR A EL ARREGLO QUE RECIBE LO QUE ENVIA EL PADRE        */
        ap = &row[0];
        size = strlen(row);
        /*                CONVERSION A MAYUSCULAS                      */
        for (g; g < size; g++)
        {
          *(ap + g) = toupper(*(ap + g));
        }

        printf("La palabra es %s\n", row); //// MUESTRA LA PALABRA

        printf("Vamos a buscarlo:\n");
        for (i = 0; i < size; i++)
        {
          if ((*(ap + i) < 65 && *(ap + i) != 10) || *(ap + i) > 90)
          { // linea con espacio =10
            printf("Encontre un error!!\n");
            printf("Tu error es: %d\n", *(ap + i));
            printf("--- Termina la ejecucion ---\n");
            exit(0);
          }
          /*   BUSQUEDA EN EL ABECEDARIO       */
          for (j = 0; j < 3; j++) /*           POR CADA OPCION DE PRINTF QUE SE GENERE DEBERA REGRESARSE AL PADRE POR EL PIPE      */
          {
            for (k = 0; k < 9; k++)
            {
              if (alfa[j][k] == *(ap + i) && i == 0)
              {
                printf("La palabra comienza con el indice: [%d][%d]\n", j, k);
                x = j;
                y = k;
              }
              else
              {
                if (alfa[j][k] == *(ap + i))
                {
                  printf("Para ir de %c a %c\n", *(ap + (i - 1)), *(ap + i));
                  w = j;
                  z = k;

                  r1 = x - w;

                  if (r1 == 0)
                  {
                    printf("En el mismo renglon\n");
                  }
                  else if (r1 < 0)
                  {
                    printf("Bajar %g fila(s)\n", fabs(r1));
                  }
                  else
                  {
                    printf("Subes %d fila(s)\n", r1);
                  }

                  x = w;

                  r2 = y - z;
                  if (r2 == 0)
                  {
                    printf("En la misma columna\n");
                  }
                  else if (r2 < 0)
                  {
                    printf("Derecha %g columna(s)\n", fabs(r2));
                  }
                  else
                  {
                    printf("Izquierda %d columna()s\n", r2);
                  }

                  y = z;
                  printf("La letra en el indice: [%d][%d]\n", j, k);
                }
              }
            }
            k = 0;
          }
          j = 0;
        }
        i = 0;
        //----------------------------------------------------------------------------------------
        // fgets(msg, 256, stdin);
        write(a[1], rowTo, sizeof(rowTo));
        printf("Termine de escribir, soy hijo 2\n");

        close(a[1]); // los pipes que ya utilizó
        close(b[0]);
        printf("Yo termine\n");

        exit(0);
        break;
      }

    default:       /*                PADRE                             */
      close(a[1]); // cierra los que no utilizará
      close(b[0]);

      if (cont == 0)
      { /////////////////  DEL PADRE AL HIJO 1 ///////////////////////////////////////
        printf("PADRE (pid = %i): Se creo a HIJO 1\n", getpid());
        printf("PADRE (pid = %i): HIJO 1 crea el documento de salida.\n", getpid());
        printf("PADRE (pid = %i): Esperando a que HIJO 1 termine ...\n", getpid());

        wait(NULL); // primero ejecuta los pintf

        printf("PADRE (pid = %i): Llego mi HIJO 1, mi archivo de salida esta listo.\n\n", getpid());
      }
      else
      { /////// DEL PADRE AL HIJO 2////////////////////////////////////////////////////////////////
        /*         CREACION DE PIPES              */
        // verificar que el pipe se hayan creado
        if (pipe(a) == -1)
        {
          printf("\n--- Error al crear el pipe (a) ----\n");
          exit(0);
        }

        if (pipe(b) == -1)
        {
          printf("\n--- Error al crear el pipe (b) ----\n");
          exit(0);
        }

        /*              LECTURA DE ARCHIVOS                    */
        printf("PADRE (pid = %i): Se creo a HIJO 2\n", getpid());
        printf("PADRE (pid = %i): Realizando lectura de archivo 'nombres.txt' ...\n", getpid());

        file = fopen("nombres.txt", "r");

        if (file == NULL)
        {
          printf("\t--- Error en la apertura del archivo ---\n");
          exit(0);
        }
        /*             SE TOMAN LOS NOMBRES DEL ARCHIVO Y SE ENLISTAN EN ARREGLO BIDIMENSIONAL       */
        while (renglones < 3 && fgets(msg[renglones], sizeof(msg[0]), file) != NULL) // lee compara que no tenga más de 3 renglones
        {
          msg[renglones][strcspn(msg[renglones], "\r\n")] = '\0'; // quita valor de salto de linea
          renglones++;
        }

        printf("PADRE (pid = %i): El contenido del archivo es:\n\n", getpid());

        for (int r = 0; r < renglones; r++)
        {
          printf("PADRE (pid = %i): Linea %d: %s\n", getpid(), r, msg[r]);
        }

        printf("\n\nPADRE (pid = %i): La lectura Termino correctamente!\n", getpid());
        fclose(file);

        printf("\n\nPADRE (pid = %i): Enviando nombres a HIJO 2:\n", getpid());

        for (r = 0; r < renglones; r++)
        {

          printf("\nPADRE (pid = %i): HIJO 2, te mando el nombre %d !\n", getpid(), r);
          strcpy(row, msg[r]);
          // row[r] = msg[renglones];
          write(b[1], row, sizeof(msg));

          printf("\nPADRE (pid = %i): HIJO 2, recibo las instrucciones del nombre %d !\n", getpid(), r);
          read(a[0], rowTo, 256);
          printf("\nPADRE (pid = %i): Recibi el mensaje de mi HIJO 2: \n", getpid());
          printf("%s", rowTo);
        }

        close(a[0]);
        close(b[1]);
        /*                     CIERRE DE PADRE, Y PIPES                               */
        printf("Ahora si son todos!!");
      }

      // printf("Yo tambien ya termine hijos\n");
      break;
    }
  }

  // wait(NULL);
  printf("\nTerminamos\n");

  return 0;
}
