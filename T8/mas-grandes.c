#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pss.h"
//#include "pss.c"
       
// Defina aca la estructura para guardar nombre y tamanno
//Archivo: guarda un puntero al nombre y el tamaño
typedef struct archivo{
  char *nom;
  int size;
} Archivo;

// Agregue aca las funciones y variables globales adicionales que necesite

//queue global
Queue *global;

//Leve modificación a la función listDir.
//Añade todos los archivos a una Queue
void listDir(char *nom) {

  struct stat st_nom;
  int rc;
  rc= stat(nom, &st_nom);
  if (rc!=0) {
    exit(1);
  }
  //Inicio de la modificacion, en vez de printear el archivo, creamos un struct de tipo Archivo
  //y guardamos su nombre y tamaño
  if (S_ISREG(st_nom.st_mode)) {
    // Es un archivo regular
    Archivo *archivo = malloc(sizeof(Archivo));
    archivo->nom = strdup(nom);
    archivo->size = st_nom.st_size;
    put(global, archivo);
  }
  else if (S_ISDIR(st_nom.st_mode)) {
    // Es un directorio
    DIR *dir = opendir(nom);
    if (dir == NULL) {
      perror(nom);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir);
         entry != NULL;
         entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
      strcpy(nom_arch, nom);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      listDir(nom_arch);
      free(nom_arch);
    }
    closedir(dir);
  }
  else {
    // Podria ser un dispositivo, un link simbolico, etc.
    exit(1);
  }
}

int archivoCmp(void *ptr, int i, int j) {
  Archivo **a = ptr;
  int out = a[j]->size - a[i]->size;
  if (out == 0) { //si tienen el mismo tamaño, comparamos los nombres
    return strcmp(a[i]->nom, a[j]->nom);
  }
  return out;
}



int main(int argc, char *argv[]) {
  if (argc < 3) {
    exit(1);
  }
  global = makeQueue();
  listDir(argv[1]);
  int size = queueLength(global);
  Archivo *lista[size];
  for (int i = 0; i < size; i++) { //añadimos los elementos de la cola a una lista
    lista[i] = get(global);
  }
  sortPtrArray(&lista, 0, size-1, archivoCmp);
  //int n = queueLength(global);
  //printf("%d\n", n);
  //int n = min(atoi(argv[2]), queueLength(global));
  //int length = sizeof(lista)/sizeof(int);
  int n = atoi(argv[2]);
  //if (n > length) {
  //  n = length;
  //}
  for (int j = 0; j < n; j++) {
    printf("%s %d\n", lista[j]->nom, lista[j]->size);
  }
  for (int k = 0; k < size; k++) { //Liberamos la memoria
    free(lista[k]->nom);
    free(lista[k]);
  }
  return 0;
}
