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
  char *ap, msg[3][256], row[256], rowTo[256];
  int size, g = 0, i, j, k, x, y, w, z, r, c, r1, r2, renglones; // para busqueda
  int a[2], b[2];                                                // tuberias
  int pid, cont;

  printf("Bienvenido al Buscador de Nombres\n\n");
  printf("Soy el PADRE (pid = %d):", getpid());
  printf("Mira el Abecedario:\n");

  for (r; r < 3; r++)
  {
    for (c; c < 9; c++)
    {
      printf("%c\t", alfa[r][c]);
    }
    printf("\n");
    c = 0;
  }

  printf("Comencemos\n");

  for (cont = 0; cont < 2; cont++)
  {
    switch (pid = fork())
    {
    case -1:
      printf("Existio un error en la creacion del HIJO %d\n", cont);
      exit(0);
      break;

    case 0:
      if (cont == 0)
      {
        printf("Soy el HIJO 1 (pid = %i)\n", getpid());
        printf("HIJO1 (pid = %i): Creando el archivo de salida ...\n", getpid());

        system("touch nombres.txt");

        printf("HIJO1 (pid = %i): Archivo de salida creado con exito!\n", getpid());
        printf("HIJO1 (pid = %i): Termine.", getpid());
        exit(0);
        break;
      }

      else
      {
        close(a[0]);
        close(b[1]);

        printf("Hola soy el segundo hijo soy %i\n", getpid());

        read(b[0], msg, 256);
        printf("Estoy leyendo\n");
        //----------------------------------------------------------------------------------------
        ap = &msg[0];
        size = strlen(msg);

        for (g; g < size; g++)
        {
          *(ap + g) = toupper(*(ap + g));
        }

        printf("La palabra es %s\n", msg);

        printf("Vamos a buscarlo:\n");
        for (i = 0; i < size; i++)
        {
          if ((*(ap + i) < 65 && *(ap + i) != 10) || *(ap + i) > 90)
          { // linea con espacio =10
            printf("Encontre un error!!\n");
            printf("Tu error es: %d\n", *(ap + i));
            printf("Termine amigo :((\n");
            exit(0);
          }

          for (j = 0; j < 3; j++)
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
        write(a[1], msg, sizeof(msg));
        printf("Termine de escribir, soy hijo 2\n");

        close(a[1]);
        close(b[0]);
        printf("Yo termine\n");

        exit(0);
        break;
      }

    default:
      close(a[1]);
      close(b[0]);

      if (cont == 0)
      {
        printf("PADRE (pid = %i): Se creo a HIJO 1\n", getpid());
        printf("PADRE (pid = %i): HIJO 1 crea el documento de salida.\n", getpid());

        wait(NULL);

        printf("PADRE (pid = %i): Llego mi HIJO 1, mi archivo de salida esta listo.\n", getpid());
      }

      else
      {
        printf("PADRE (pid = %i): Se creo a HIJO 2\n", getpid());
        printf("PADRE (pid = %i): Realizando lectura de archivo 'nombres.txt' ...\n", getpid());

        file = fopen("nombres.txt", "r");

        if (file == NULL)
        {
          printf("\t--- Error en la apertura del archivo ---\n");
          exit(0);
        }

        while (renglones < 3 && fgets(msg[renglones], sizeof(msg[0]), file) != NULL)
        {
          msg[renglones][strcspn(msg[renglones], "\r\n")] = '\0';
          renglones++;
        }

        printf("PADRE (pid = %i): El contenido del archivo es:\n\n");

        for (int r = 0; r < renglones; r++)
        {
          printf("PADRE (pid = %i): Linea %d: %s\n", r, msg[r]);
        }

        printf("\n\nPADRE (pid = %i): La lectura Termino correctamente!\n");
        fclose(file);

        printf("\n\nPADRE (pid = %i): Enviando nombres a HIJO 2!\n");

        for (r = 0; r < renglones; r++)
        {

          printf("\nPADRE (pid = %i): HIJO 2, te mando el nombre %d !\n", r);
          row[r] = msg[renglones];
          write(b[1], row, sizeof(msg));

          printf("\nPADRE (pid = %i): HIJO 2, recibo las instrucciones del nombre %d !\n", r);
          read(a[0], rowTo, 256);
          printf("\nPADRE (pid = %i): Recibi el mensaje de mi HIJO 2: \n");
        }

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
