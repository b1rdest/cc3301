#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat){
  char *check = str;  // para recorrer la palabra que quiero revisar
  char *copy = str;   // para escribir   // pal patron que quiero eliminar

  while(*check != 0){
    printf("%s\n", "asd");
    char *aux = pat; 
    printf("%s\n", "c");
    if(*check != *aux){
      *copy = *check;
      copy++;
      check++;
      aux = pat;  // not sure 
      printf("%c\n", *copy);
    }
    else{
      char *copyauxiliar = copy;
      int hay_patron = 1;
      int counter = 0;
      while(*aux){
        printf("%s\n", "a");
        if(*copyauxiliar == *aux){
          counter += 1;
          copyauxiliar++;
          aux++;
          printf("%s\n", "d");
        }
        else{
          printf("%s\n", "e");
          hay_patron = 0;
          copy += counter;
          break;
        }
      }
      if(hay_patron == 1){
        printf("%s\n", "f");
        check += counter;
        printf("%s\n", "g");
      }
    }
  printf("*copy1 = %c\n", *copy);
  }
  printf("%s\n", "asdf");
  *copy = 0;
  printf("*copy2 = %c\n", *copy);
}





char *eliminados(char *str, char *pat) {
  char *check = str;  // para recorrer la palabra que quiero revisar
  char *aux = pat;    // pal patron que quiero eliminar
  int max_len = 0;
  char *ptr = str;

  while(*ptr){
    max_len++;
    ptr++;
  }

  char *result = (char *)malloc(max_len +1);
  char *copy = result;
  
  while(*check != 0){
    if(*check != *aux){
      *copy = *check;
      copy++;
      check++;
    }
    else{
      int hay_patron = 1;
      int counter =0;
      char *checkauxiliar = check;
      while(*aux){
        if(*checkauxiliar != *aux){
          hay_patron = 0;
          break;
        }
        checkauxiliar++;
        aux++;
        counter += 1;
      }
      aux = pat;
      if(hay_patron == 1){
        check = check+ counter;
      }
      else {
        *copy = *check;
        copy++;
        check++;
      }
    }
  }
  *copy = 0;
  return result;
}

int main() {
 char *xd = "aaa";
  eliminar(xd, "a");
  //printf("resultado: %s\n",eliminados("","aaa"));
  printf(xd);
  return 0;
}

  // contar el largo del resultado, hacer un malloc con esa cantidad
  // hacer algo identico a la parte A

  // usar dos veces eliminar modificado
  // la primera en vez de ir reemplazando vas contando cuantas veces está el patrón
  // en medio haces Malloc

  // despues haces el mismo procedimiento pero copiando en el nuevo string creado con malloc
//}


//    void eliminar(char *str, char *pat) {
//      char  *copy = str;
//      char *check = str;
//      char *aux = pat;
//      while(*copy != 0){
//        if(aux != check){
//          *copy = *str;
//          copy++;
//          check++;
//          if(aux != pat){
//            aux = pat;
//          }
//        }
//        if(aux == check){
//          

//        }




//      }



  // idea: usar punteros auxiliares 
  // un puntero escribiendo (copy)
  // un puntero que vaya recorriendo la palabra que quiero revisar (check)
  // otro puntero que recorra el patrón que quiero eliminar (aux)

  // al principio comparamos aux con check, 
  // si no son iguales no he encontrado el patron -> puntero copy copia el elemento y sigue a la siguiente letra junto con check
  // y auxiliar tiene que volver al primer caracter del patron en caso de ser movido

  // en el caso de encontrar una coincidencia (check == aux)
  // dejamos copia donde está y avanzamos colo con revisar y auxiliar (para comprobar si es el patrón completo)
  // si no lo es -> sigo con el procedimiento de antes
  // si encuentra el patrón entero -> me salto el espacio del patrón y comenzar a copiar desde lo que viene después del patron

//}

