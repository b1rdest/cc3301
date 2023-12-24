//Tarea 2 CC3301 Diego Vergara V.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat) {
  char *s = str; //puntero hacia el primer character de str
  char *s1 = str; //puntero auxiliar
  while (*s1 != 0) {
    char *s2 = s1; //puntero auxiliar
    char *p = pat; //puntero hacia el primer character de pat
    int j = 0; //contador
    int k = 1; //booleano
    while ((*p != 0) & k) { //buscamos el patrón
      k = (*s2 == *p);
      s2++;
      p++;
      j++;
    }
    if (k) { //caso en que se encuentra el patrón (k = 1)
      s1 = s1 + j; //nos "saltamos" n espacios, para saltarnos el patrón
    }
    else {
      *s = *s1; //escribimos todos los caracteres, excepto los saltados
      s++;
      s1++;
    }
  }
  *s = 0; //finalizamos el string
}

char *eliminados(char *str, char *pat) {
  char *sc = str; //puntero hacia el primer character de str
  int i = 0;  //contador para iterar
  int contador = 0; //cantidad de chars del string resultante

  while (*sc != 0) {
    char *s2 = sc; //puntero auxiliar
    char *p = pat; //puntero hacia el primer character de pat
    int j = 0; //contador auxiliar
    int k = 0; //booleano que indica si se encontro el patron
    while (*p != 0) { //buscamos el patrón
      k = (*s2 == *p);
      if (!k){
        break;
      }
      s2++;
      p++;
      j++; 
    }
    if (k) { //caso en que se encuentra el patrón (k = 1)
      sc = sc + j; //nos "saltamos" n espacios, para saltarnos el patrón
    }
    else {
      contador = contador + 1;
      sc++;
      i++;
    }
  }
  char *out = malloc(contador+1); //alocamos memoria

  //ahora, hacemos un proceso idéntico a la Parte A, pero en vez de
  //sobreescribir el string, escribimos uno nuevo (out) con los chars
  //correspondientes

  char *s1 = str; //puntero auxiliar
  char *iout = out; //puntero para el string out
  i = 0;
  while (i < contador) {
    char *s2 = s1; //puntero auxiliar
    char *p = pat; //puntero hacia el primer character de pat
    int j = 0; //contador
    int k = 0; //booleano
    while ((*p != 0)) { //buscamos el patrón
      k = (*s2 == *p);
      if (!k) {
        break;
      }
      s2++;
      p++;
      j++;
    }
    if (k) { //caso en que se encuentra el patrón (k = 1)
      s1 = s1 + j; //nos "saltamos" n espacios, para saltarnos el patrón
    }
    else {
      *iout = *s1; //escribimos todos los caracteres, excepto los saltados
      iout++;
      s1++;
      i++;
    }
  }
  *iout = 0;
  return out;
}
