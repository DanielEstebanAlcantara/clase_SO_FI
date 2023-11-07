/*
Equipo: 10
Alcantara Paleo Daniel Esteban
Beltran Hernandez Nathan
Ovando Nader Carlos Enrique
Trigueros Lopez Hector Adrian
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

int main()
{
  FILE *fileIn;
  FILE *fileOut;
  char alfa[3][9] = {{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}, {'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'}, {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}};
  char *ap, row[256], rowTo[256], row1[256], rowTo2[256];
  int size, g = 0, i, j, k, x, y, w, z, r, c, r1, r2, renglones;
  int a[2], b[2];
  int pid, cont;

  printf("\n\t\t***** Bienvenido al Buscador de Nombres *****\n\n");
  printf("Soy el PADRE (pid = %d):\n\n", getpid());
  printf("Mira el Abecedario:\n");

  for (r = 0; r < 3; r++)
  {
    printf("\t");
    for (c = 0; c < 9; c++)
    {
      printf("%c\t", alfa[r][c]);
    }
    printf("\n");
    c = 0;
  }

  /*
  Se cran los pipes
  pipe(a) crea el primer pipe y establece la comunicación entre el proceso padre y el hijo1.
  pipe(b) crea el segundo pipe y establece la comunicación entre el proceso padre y el hijo2.
  */
  if (pipe(a) == -1 || pipe(b) == -1)
  {
    printf("\n--- Error al crear el pipe (a) ----\n");
    exit(0); // si no se crean los pipes se detiene la ejecución del programa
  }

  printf("\n\nComencemos:\n\n");

  // para crear los hijos
  for (cont = 0; cont < 2; cont++)
  {
    switch (pid = fork())
    /*
    si pid = -1 error
        pid = 0 proceso hijo
        pid >0 proceso padre default
    */
    {
    case -1:
      printf("\t\t----- Existio un error en la creacion del HIJO %d ------\n", cont);
      exit(0);
      break;

    case 0:
      if (cont == 0) // es el primer proceso
      {
        printf("Soy el HIJO 1 (pid = %i)\n", getpid());
        printf("HIJO1 (pid = %i):\n\tCreando el archivo de salida ...\n", getpid());

        system("touch output.txt"); // crea el archivo de salida

        printf("HIJO1 (pid = %i):\n\tArchivo de salida creado con exito!\n", getpid());
        printf("HIJO1 (pid = %i):\n\tTermine Padre.\n", getpid());
        exit(0);
        break;
      }

      else
      {
        // Cerrando los pipes
        close(a[0]); // comunicación desde el proceso padre hacia este hijo.
        close(b[1]); // comunicación desde este hijo hacia el proceso padre

        printf("Soy el HIJO 2 (pid = %i)\n", getpid());
        printf("HIJO2 (pid = %d):\n\tVoy a leer lo que dice mi PADRE (pid = %d)\n", getpid(), getppid());

        while (read(b[0], row1, 256) > 0) // almacena el mensaje en row1(funciona como un buffer) y verifica que los bytes leidos sean mayores a 0, ews decir, recibió un mensaje
        // si devuleve 0 entonces el pipe se cerró
        {
          printf("HIJO2 (pid = %d):\n\tRecibi el nombre, padre: %s\n", getpid(), row1);

          /*
          sew copia el mensaje a una variable temporal
          */
          char temp[256];
          strcpy(temp, row1);

          ap = &temp[0]; // ap apunta al primer caracter de la cadena temp
          size = strlen(temp);

          /*

          */
          sprintf(rowTo, "%d", size);            // size se hace cadena se almacena en rowTo
          write(a[1], rowTo, strlen(rowTo) + 1); // se manda el tamaño en un mensaje al proceso padre con el pipe a[1

          read(b[0], row1, 256); // recibe mensaje del padre
          printf("HIJO2 (pid = %d):\n\t?Continuo padre?: %s\n", getpid(), row1);

          /*
          Combierte a mayusculas la cadena
          */
          for (g = 0; g < size; g++)
          {
            *(ap + g) = toupper(*(ap + g));
          }

          printf("HIJO2 (pid = %d):\n\tVamos a buscar la palabra:\n", getpid());

          for (i = 0; i < size; i++) // recorre cada caracter de la cadena
          {
            /*
            Para ver si un caraacter es válido o no
            Comprueba que el caracter no este por de bajo de 'A' en ASCII 65, si sí, entonces no es válido
            verifica si el carácter no es un carácter de nueva línea (10), retorno de carro (13) o espacio en blanco (32). No serían válidos
            Si es mayor de 90 ('Z') entonces no cumple
            */
            if ((*(ap + i) < 65 && *(ap + i) != 10 && *(ap + i) != 13 && *(ap + i) != 32) || *(ap + i) > 90)
            {
              printf("\t\t----- Encontre un error -----\n");
              printf("\t\t*** Tu error es: %d ***\n", *(ap + i));
              printf("\t\t----- Termina la ejecucion -----\n");
              exit(0);
            }

            for (j = 0; j < 3; j++) // recorre las filas
            {
              for (k = 0; k < 9; k++) // recorre las columnas
              // determinan la posición de un caracter
              {
                /*
                 se comparan los elementos de la matriz alfa con un carácter específico que se encuentra en la cadena temp. La lógica se utiliza para determinar si el carácter actual en temp coincide con un carácter en la matriz alfa. Si hay una coincidencia, se registran las coordenadas (j y k) en la matriz alfa donde se encontró el carácter en temp.
                */
                if (alfa[j][k] == *(ap + i) && i == 0) // si es el primer caracter
                {
                  printf("HIJO2 (pid = %d):\n\tLa palabra comienza con el indice: [%d][%d]\n", getpid(), j, k);

                  sprintf(rowTo, "La palabra comienza con el indice: [%d][%d]\n", j, k); // Esto proporciona información sobre la posición inicial del nombre en la matriz.
                  write(a[1], rowTo, strlen(rowTo) + 1);                                 // envía la cadena al proceso padre
                  read(b[0], row1, 256);                                                 // para leer la cadena enviada por el hijo 2
                  printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);

                  sprintf(rowTo, "\n");
                  write(a[1], rowTo, strlen(rowTo) + 1);
                  read(b[0], row1, 256);
                  printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);

                  x = j;
                  y = k;
                }
                else // si no coinicide o no es el primero
                {
                  if (alfa[j][k] == *(ap + i)) // si coinicide, ya no es el primero
                  {
                    printf("HIJO2 (pid = %d):\n\tPara ir de %c a %c\n", getpid(), *(ap + (i - 1)), *(ap + i));
                    w = j;
                    z = k;

                    /* diferencia entre las coordenadas de las filas x(fila del carácter actual)
                      y w(fila del carácter anterior )
                      si r1 negativo cuantas filas bajar
                      si r1 positivo cuantsa filas subir
                    */
                    r1 = x - w;

                    if (r1 == 0) // mismo caracter
                    {
                      printf("HIJO2 (pid = %d):\n\tEn el mismo renglon\n", getpid());
                      sprintf(rowTo, "En el mismo renglon\n");

                      write(a[1], rowTo, strlen(rowTo) + 1);
                      read(b[0], row1, 256);
                      printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);
                    }
                    else if (r1 < 0) // menor a 0 bajar y r1 tiene almacenado el nuemro de filas
                    {
                      printf("HIJO2 (pid = %d):\n\tBajar %g fila(s)\n", getpid(), fabs(r1));
                      sprintf(rowTo, "Bajar %g fila(s)\n", abs(r1));

                      write(a[1], rowTo, strlen(rowTo) + 1);
                      read(b[0], row1, 256);
                      printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);
                    }
                    else // mayor a 0 sube r1 numero de filas
                    {
                      printf("HIJO2 (pid = %d):\n\tSubes %d fila(s)\n", getpid(), r1);
                      sprintf(rowTo, "Subes %d fila(s)\n", r1);

                      write(a[1], rowTo, strlen(rowTo) + 1);
                      read(b[0], row1, 256);
                      printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);
                    }

                    x = w; // ahora x es la fila en la que se encontraba el caracter anterior

                    /*
                    r2 determina cuantas columnas debe moverse
                    si r2 < 0 hacia la derecha
                    si r2 > 0 hacia la izquierda
                    */
                    r2 = y - z;  // columas, "y" es la columna actual; "z" columna del caracter anterior
                    if (r2 == 0) // misma columna
                    {
                      printf("HIJO2 (pid = %d):\n\tEn la misma columna\n", getpid());
                      sprintf(rowTo, "En la misma columna\n");

                      write(a[1], rowTo, strlen(rowTo) + 1);
                      read(b[0], row1, 256);
                      printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);
                    }
                    else if (r2 < 0) // derecha
                    {
                      printf("HIJO2 (pid = %d):\n\tDerecha %g columna(s)\n", getpid(), fabs(r2));
                      sprintf(rowTo, "Derecha %g columna(s)\n", abs(r2));

                      write(a[1], rowTo, strlen(rowTo) + 1);
                      read(b[0], row1, 256);
                      printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);
                    }
                    else // izquierda r2 > 0
                    {

                      printf("HIJO2 (pid = %d):\n\tIzquierda %d columna(s)\n", getpid(), r2);
                      sprintf(rowTo, "Izquierda %d columna(s)\n", r2);
                      write(a[1], rowTo, strlen(rowTo) + 1);
                      read(b[0], row1, 256);
                      printf("HIJO2 (pid = %d):\n\tContinuo, padre: %s", getpid(), row1);
                    }

                    y = z; // y ahora tiene la posición del caracter anterior
                    printf("HIJO2 (pid = %d):\n\tLa letra en el indice: [%d][%d]\n", getpid(), j, k);
                  }
                }
              }
              /*
              reinicio de variables k, j e i para los bucles y seguir con el siguiente caracter
              */
              k = 0;
            }
            j = 0;
          }
          i = 0;
        }
        // cierre de pipes
        close(a[0]);
        close(b[1]);
        printf("HIJO2 (pid = %d):\n\tTermine, adios padre.\n", getpid());

        exit(0);
        break;
      }
    default:
      /*
      Default maneja la lógica del proceso padre, que se encarga de leer nombres del archivo "nombres.txt", enviarlos al hijo 2 para su procesamiento, recibir las respuestas del hijo 2 e imprimir la información en el archivo de salida.
      */
      if (cont == 0) // con el hijo 1
      {
        printf("PADRE (pid = %i):\n\tSe creo a HIJO 1\n", getpid());
        printf("PADRE (pid = %i):\n\tHIJO 1 crea el documento de salida.\n", getpid());
        printf("PADRE (pid = %i):\n\tEsperando a que HIJO 1 termine ...\n", getpid());

        wait(NULL);

        printf("PADRE (pid = %i):\n\tLlego mi HIJO 1, mi archivo de salida esta listo.\n\n", getpid());
      }
      else // con el hijo 2
      {
        close(a[1]);
        close(b[0]);

        printf("PADRE (pid = %i):\n\tSe creo a HIJO 2\n", getpid());
        printf("PADRE (pid = %i):\n\tRealizando lectura de archivo 'nombres.txt' ...\n", getpid());

        fileIn = fopen("nombres.txt", "r");
        if (fileIn == NULL)
        {
          printf("\t\t----- Error en la apertura del archivo -----\n");
          exit(0);
        }

        fileOut = fopen("output.txt", "w");
        if (fileOut == NULL)
        {
          printf("\t\t----- Error en la apertura del archivo -----\n");
          exit(0);
        }

        r = 0;

        while (fgets(row, 265, fileIn) != NULL)
        /*
        Se leen las lineas del archivo nombres.txt
          fgets se utiliza para leer una línea completa del archivo fileIn. La línea se almacena en la variable row. La longitud máxima que puede leerse es de 265 caracteres
        */
        {
          printf("\nPADRE (pid = %i):\n\tHIJO 2, te envio el nombre %d:\n", getpid(), r);

          printf("\t\t%s\n", row);           // imprime el nombre leido
          write(b[1], row, strlen(row) + 1); // se envia al proceso padre

          printf("PADRE (pid = %i):\n\tEsperando respuesta de mi hijo 2:\n", getpid());
          read(a[0], rowTo2, 256); // se recibe mensaje del hijo

          int numero = rowTo2[0] - '0';

          numero = numero - 2;

          sprintf(row, "Continua hijo1\n");
          write(b[1], row, strlen(row) + 1);

          /*
          Se escribe dentro del archivo de salida.
          */
          for (int v = 0; v < numero; v++)
          {
            read(a[0], rowTo2, 256);
            printf("PADRE (pid = %i):\n\tTengo la respuesta 1, hijo: %s\n", getpid(), rowTo2);
            printf("PADRE (pid = %i):\n\tContinua hijo 2.\n", getpid());
            sprintf(row, "Continua hijo 2\n");
            write(b[1], row, strlen(row) + 1);

            fprintf(fileOut, "1) Renglon: %s", rowTo2); // se escribe en el archivo de salida

            read(a[0], rowTo2, 256);
            printf("PADRE (pid = %i):\n\tTengo la respuesta 2, hijo: %s\n", getpid(), rowTo2);
            printf("PADRE (pid = %i):\n\tContinua hijo 2.\n", getpid());
            sprintf(row, "Continua hijo3\n");
            write(b[1], row, strlen(row) + 1);

            fprintf(fileOut, "2) Columna: %s", rowTo2);

            printf("PADRE (pid = %i):\n\tLa siguiente letra.\n", getpid());
          }
          printf("PADRE (pid = %i):\n\tTerminamos con el nombre %d\n", getpid(), r);
          r++;
        }

        printf("\n\nPADRE (pid = %i): La lectura Termino correctamente!\n", getpid());

        fclose(fileIn);
        fclose(fileOut);

        close(a[0]);
        close(b[1]);
      }
      break;
    }
  }

  printf("\n\n\t\t----- FIN DE LA EJECUCION -----\n");
  return 0;
}
