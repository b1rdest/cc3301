#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pss.c"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n");
    exit(1);
  }
  //definimos variables
  char *nom_dic = argv[1];
  char *palabra = argv[2];
  char *def = argv[3];
  FILE *f = fopen(nom_dic, "r+"); //abrimos el archivo de nombre nom_dic
  //checkeamos si hay un error al abrir el archivo
  if (f == NULL) {
    perror(nom_dic);
    exit(1);
  }
  //calculamos el tamaño en lineas del archivo
  fseek(f, 0, SEEK_END);
  int lineas = ftell(f)/81;
  int pos = hash_string(palabra)%lineas; //buscamos la posicion del hash
  char *buf = malloc(81*sizeof(char)); //definmimos un buffer
  int i = 0; //iteramos sobre las lineas siguientes
  while (i < lineas) {
    fseek(f, ((pos+i)%lineas)*81, SEEK_SET);
    int cnt = fread(buf, sizeof(char), 81, f);
    if (cnt == 0) {
      printf("cnt == 0\n");
      fseek(f, 0, SEEK_SET);
      i++;
    }
    else {
      if (buf[0] != *" ") { //el espacio ya esta ocupado
        char out[81];
        strncpy(out, buf, strlen(palabra));
        if (strcmp(out, palabra) == 0) { //si la llave ya esta
          fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", palabra);
          fclose(f);
          free(buf);
          exit(1);
        }
        else {
          i++;
        }
      }
      else {
        fseek(f, ((pos+i)%lineas)*81, SEEK_SET);
        fwrite(palabra, sizeof(char), strlen(palabra), f);
        fwrite(":", sizeof(char), 1, f);
        fwrite(def, sizeof(char), strlen(def), f);
        fclose(f);
        free(buf);
        break;
      }
    }
  }
  if (i == lineas) {
    fprintf(stderr, "%s: el diccionario esta lleno\n", nom_dic);
    fclose(f);
    free(buf);
    exit(1);
  }
  return 0;
}