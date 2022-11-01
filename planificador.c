#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

int distancia(TCiudad c1, TCiudad c2){
    int x = c2->pos_x - c1->pos_x;
    int y = c2->pos_y - c1->pos_y;
    if(x<0)
        x = x*-1;
    if(y<0)
        y = y*-1;
    return x+y;
}

//SI SE USA PARA COLAMIN, LA CLAVE DE UNA ENTRADA REPRESENTA LA DISTANCIA AL ORIGEN, Y SU VALOR LA CIUDAD
//SI SE USA PARA COLAREDUCIRHORAS, LA CLAVE DE UNA ENTRADA REPRESENTA LA DISTANCIA A LA CIUDAD ACTUAL, Y SU VALOR LA CIUDAD
int comparadorMin(TEntrada e1, TEntrada e2){
    TClave clave1 = e1->clave;
    TClave clave2 = e2->clave;

    if(clave1 < clave2)
        return 1;
    else if(clave1 == clave2)
        return 0;
    else
        return -1;
}

//LA CLAVE DE UNA ENTRADA REPRESENTA LA DISTANCIA AL ORIGEN, Y SU VALOR LA CIUDAD
int comparadorMax(TEntrada e1, TEntrada e2){
    TClave clave1 = e1->clave;
    TClave clave2 = e2->clave;

    if(clave1 > clave2)
        return 1;
    else if(clave1 == clave2)
        return 0;
    else
        return -1;
}


void noEliminarEntrada(TEntrada e){
}
/*  argc = define la cantidad de parámetros por consola, más el nombre del programa
    args = es el arreglo donde se encuentran todos los parámetros por consola         */
int main(int argc, char ** args)
{
    //printf("Contenido texto: %s", args[1][0]);

    TColaCP colaMin = crear_cola_cp(comparadorMin);
    TColaCP colaMax = crear_cola_cp(comparadorMax);
    TColaCP colaReducirHoras = crear_cola_cp(comparadorMin);

    //Empieza como el 1er valor que levantamos del archivo de texto, cambia en la 3er cola recien
    TCiudad ubicacionActual;
    int horasDeManejo = 0;
    /*
        Levantamos el archivo de texto
        asignamos ubicacionActual
        para cada posicion del arreglo (a partir de la 2da)
            creamos una entrada del tipo <Distancia al origen, ciudad>
            creamos una entrada igual, pero que vamos a usar para ReducirHoras
            hacer nodos enlazados
            */

            cp_insertar(colaMin, nuevaEntrada);
            cp_insertar(colaMax, nuevaEntrada);
            cp_insertar(colaReducirHoras, nuevaEntradaRH);

        int op0 = 0;

        while(op0 == 0){
        //Preguntamos al usuario que quiere hacer

            if(/*Ingresar 0 si quiere terminar la ejecucion*/){
                if(colaMin != NULL){
                    cp_destruir(colaMin, noEliminarEntrada);
                    colaMin = NULL;
                }
                if(colaMax != NULL){
                    cp_destruir(colaMax, noEliminarEntrada);
                    colaMax = NULL;
                }
                if(colaReducirHoras != NULL){
                    cp_destruir(colaReducirHoras, noEliminarEntrada);
                    colaReducirHoras = NULL;
                }
                op0++;
                printf("Fin de la ejecucion \n");
            }

            if(/*Ingresar 1 si quiere ver ascendente*/){
            if(colaMin == NULL)
                printf("Esta operacion ya se ejecuto previamente \n");
            else{
                printf("Mostrar ascendente: \n");
                while(colaMin -> cantidad_elementos != 0){
                    TEntrada actual = cp_eliminar(colaMin);
                    printf("%s \n", *(actual->valor->nombre));
                }
                cp_destruir(colaMin, noEliminarEntrada);
                colaMin = NULL;
            }
            }

           if(/*Ingresar 2 si quiere ver descendente*/){
           if(colaMax == NULL)
                printf("Esta operacion ya se ejecuto previamente \n");
            else{
                printf("Mostrar descendente: \n");
                while(colaMax ->cantidad_elementos != 0){
                    TEntrada actual = cp_eliminar(colaMax);
                    printf("%s \n", *(actual->valor->nombre));
                }
                cp_destruir(colaMax, noEliminarEntrada);
                colaMax = NULL;
            }
           }

            if(/*Ingresar 3 si quiere reducir horas de manejo*/){
            if(colaReducirHoras == NULL)
                printf("Esta operacion ya se ejecuto previamente \n");
            else{
                printf("Mostrar descendente: \n");
                while(colaReducirHoras ->cantidad_elementos != 0){
                    TEntrada actual = cp_eliminar(colaReducirHoras);
                    printf("%s \n", *(actual->valor->nombre));
                    horasDeManejo = horasDeManejo + actual.clave;
                    ubicacionActual = actual;
                    /*  y para cada elemento de la cola, calculamos su distancia con la nueva ubicacion e insertamos en colalAUX (Hacer malloc correspondientes)
                        colaReducirHoras = colaAUX
                        removemos todos los elementos de colaAUX, pero no la destruimos*/
                }
                cp_destruir(colaReducirHoras, noEliminarEntrada);
                colaReducirHoras == NULL;
            }
            }
        }

    return 0;
}
