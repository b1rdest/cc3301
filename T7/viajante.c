//Tarea 7 Diego Vergara V. CC3301-1

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double distancia(int z[], int n, double **m) { //por alguna razón, si usaba dist no me funcionaba, así que copié la función de test-viajante.c
  //, la pegué y le puse otro nombre.
  double d= m[z[n]][0];    // distancia de z[n] a 0
  for (int i=0; i<n; i++) {
      d += m[z[i]][z[i+1]];
  }
  return d;
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
  double min = DBL_MAX;
  int pids[p];
  int fds[p][2];
  for (int i = 0; i < p; i++) { //creamos los pipes
    pipe(fds[i]);
  }
  for (int k = 0; k < p; k++) { //iteramos sobre la cantidad de cores
    int child = fork();
    if (child == 0) { //estamos en el k-ésimo hijo
      close(fds[k][0]);
      srandom(getUSecsOfDay()*getpid());
      viajante(z, n, m, nperm/n);
      write(fds[k][1], &z[0], (n+1)*sizeof(int));
      exit(0);
    }
    else { //estamos en el padre
      close(fds[k][1]);
      pids[k] = child;
      int out[n+1];
      leer(fds[k][0], &out[0], (n+1)*sizeof(int));
      close(fds[k][0]);
      waitpid(pids[k], NULL, 0);
      double d = distancia(out, n, m);
      if (d<min) { // si distancia es menor que la que se tenía hasta el momento
        min= d; // d es la nueva menor distancia
        printf("%f", min);
        for (int j= 0; j<=n; j++)
          z[j]= out[j]; // guarda ruta que recorre la menor distancia en parámetro z
      }
    }
  }
  return min;

  // Complete esta funcion
  // Puede invocar a su version secuencial: viajante
  // Use la funcion leer para que el padre reciba la ruta del hijo.
  // Use fork() para crear p nuevos procesos.  El padre solo obtiene los
  // resultados de los procesos hijos a traves de pipes, entierra a los
  // los hijos y calcula el resultado final.
  // Despues de invocar fork() agregue: srandom(getUSecsOfDay()*getpid());
  // Esto es para que cada proceso genere secuencias de numeros aleatorios
  // diferentes.
}
