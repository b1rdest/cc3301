//Tarea 1 CC3301 Diego Vergara V.

#include <stdio.h>

#include "suma.h"

Bcd sumaBcd(Bcd x, Bcd y) {
    Bcd carryover = 0;
    Bcd resultado = 0;
    int mask = 0x0F;
    for(int i = 0; i < 16; i++){
        //podemos aplicar una mascara para extraer cada decimal
        //usamos 0x0...0F = 0b0...01111, lo cual nos permite extraer los ultimos 4 bits
        //luego, shifteamos cuatro espacios hacia la derecha para conseguir el siguiente digito
        int xshift = x >> 4*i;
        int yshift = y >> 4*i;
        xshift = xshift & mask;
        yshift = yshift & mask;
        Bcd z = xshift + yshift + carryover;
        if (z >= 10){ //Si la suma de dos digitos es mayor o igual a 10, se suma 1 al siguiente (accarreo)
            z = z - 10;
            carryover = 1;
        }
        //rearmamos el numero en BCD
        else {
            carryover = 0;
        }
        resultado = resultado | (z << 4*i);
    } //Si el carryover se pasa de los 16 bits, entonces se desborda
    if (carryover == 1){
        resultado = 0xFFFFFFFFFFFFFFFF;
    }
    return resultado;
}
