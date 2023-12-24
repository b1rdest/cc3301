//Tarea 3 CC3301-1 Primavera 2023 - Diego Vergara V.

#include <stddef.h>
#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {
  //Primero, checkeamos que la raíz no sea NULL
  if (t == NULL) {
    return;
  }
  //recorremos el árbol en Inorden, es decir, partimos por el nodo izquierdo
  asignarPrev(t->izq, pprev);
  //asignamos el nuevo prev
  t->prev = *pprev;
  //luego, cuando estamos en la raíz, asignamos el prev si este no es null
  if (*pprev != NULL) {
    (t->prev)->prox = t;
  }
  //nuevamente actualizamos prev
  *pprev = t;
  //asignamos prox como NULL temporalmente, se actualiza sólo si no es el último nodo
  t->prox = NULL;
  //Luego, recorremos el árbol en Inorden
  asignarPrev(t->der, pprev);
}