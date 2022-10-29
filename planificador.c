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

void recorridoInorden(TNodo nodo){
    if(nodo!=ELE_NULO){

        if(nodo->hijo_izquierdo!=ELE_NULO)
            recorridoInorden(nodo->hijo_izquierdo);

        printf("%d %d \n",(int*)nodo->entrada->clave, (int*)nodo->entrada->valor);

        if(nodo->hijo_derecho!=ELE_NULO)
            recorridoInorden(nodo->hijo_derecho);

    }
}

void eliminarEntrada(TEntrada e){
    free(e);
}
/*  argc = define la cantidad de parámetros por consola, más el nombre del programa
    args = es el arreglo donde se encuentran todos los parámetros por consola         */
int main(int argc, char ** args)
{
    //printf("Contenido texto: %s", args[1][0]);

    TColaCP cola = crear_cola_cp(comparadorMin);
    TEntrada e = malloc(sizeof(TEntrada));
    TEntrada e2 = malloc(sizeof(TEntrada));
    TEntrada e3 = malloc(sizeof(TEntrada));
    TEntrada e4 = malloc(sizeof(TEntrada));
    TEntrada e5 = malloc(sizeof(TEntrada));
    TEntrada e6 = malloc(sizeof(TEntrada));
    TEntrada e7 = malloc(sizeof(TEntrada));
    TEntrada e8 = malloc(sizeof(TEntrada));
    TEntrada e9 = malloc(sizeof(TEntrada));

    e->clave = (int*)1;
    e->valor = (int*)1;

    e2->clave = (int*)2;
    e2->valor = (int*)2;

    e3->clave = (int*)3;
    e3->valor = (int*)3;

    e4->clave = (int*)4;
    e4->valor = (int*)4;

    e5->clave = (int*)5;
    e5->valor = (int*)5;

    e6->clave = (int*)6;
    e6->valor = (int*)6;

    e7->clave = (int*)7;
    e7->valor = (int*)7;

    e8->clave = (int*)8;
    e8->valor = (int*)8;

    e9->clave = (int*)9;
    e9->valor = (int*)9;

    cp_insertar(cola, e);
    cp_insertar(cola, e2);

    cp_insertar(cola, e3);
    cp_insertar(cola, e4);
    cp_insertar(cola, e5);

    cp_insertar(cola, e6);
    cp_insertar(cola, e7);
    cp_insertar(cola, e8);
    cp_insertar(cola, e9);


    printf("La raiz ACTUAL es: %i\n", cola->raiz->entrada->clave);
    //printf("%i \n",cp_insertar(cola, e2));
    printf("Recorrido inorder: \n");
    recorridoInorden(cola->raiz);

    for(int i = 0; i<3; i++){
        printf("\n");
        cp_eliminar(cola);

        printf("La raiz ACTUAL es: %i\n", cola->raiz->entrada->clave);
        printf("Cantidad de elementos: %i \n", cola->cantidad_elementos);

        recorridoInorden(cola->raiz);
    }

    cp_destruir(cola, eliminarEntrada);

    printf("Fin del programa\n");
    return 0;
}
