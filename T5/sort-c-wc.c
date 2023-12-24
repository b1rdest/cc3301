//Tarea 5 CC3301 Diego Vergara V.

#include <string.h>
#include <stdio.h>

int strCmp(char *s1, char *s2) {
    char c1;
    char c2;

    for (;;) {
      c1= *s1;
      c2= *s2;

      if (c1==0)
        break;

      if (c1!=c2)
        break;

      s1++;
      s2++;
    }

    return c1 - c2;
}

//funcion para contar las palabras de un string
int words(char *a) {
  int words = 0;
  int i = 0;
  int espacio = 1;
  while (a[i] != '\0') {
    if (a[i] == ' ') {
      espacio = 1;
    }
    else if (espacio) {
      espacio = 0;
      words++;
    }
    i++;
  }
  return words;
}

//funcion para encontrar el minimo de un array de ints
int * min(int *a, int n, int length) {
  int *numero = &a[length - n];
  for (int i = length - n + 1; i < length; i++) {
    if (*numero > a[i]) {
      numero = &a[i];
    }
  }
  return numero;
}

void sort(char **a, int n) {
  //programamos un selectionsort
  //n es el tamaño del arreglo
  //creamos un arreglo que guarda la cantidad de palabras de cada string
  int palabras[n];
  int i = 0;
  while (i < n) {
    palabras[i] = words(a[i]);
    i++;
  }
  //luego, ordenamos las palabras usando selectionsort en los valores de palabras
  i = 0;
  while(i < n) {
    int pos = min(palabras, n-i, n)- palabras;
    char *temp = a[i];
    a[i] = a[pos];
    a[pos] = temp;
    int temp2 = palabras[i];
    palabras[i] = palabras[pos];
    palabras[pos] = temp2;
    i++;
  }
}

/*
void sort(uint nums[], int n) // registros a0, a1
uint *p = nums; // p está en sp+56
uint *ult = &nums[n-1]; // ult esta en sp+52
a1 (n) es el tamaño del arreglo
nums está en dirección sp+48
p está en registro t0

*/