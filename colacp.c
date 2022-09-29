#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP nuevaCola = malloc(sizeof(struct cola_con_prioridad));
    nuevaCola->cantidad_elementos = 0;
}







