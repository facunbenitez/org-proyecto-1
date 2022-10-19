#include <stdio.h>
#include <stdlib.h>

#include "colacp.h";

int compara(TEntrada e1, TEntrada e2){
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

        printf("%d %d \n",nodo->entrada->clave, nodo->entrada->valor);

        if(nodo->hijo_derecho!=ELE_NULO)
            recorridoInorden(nodo->hijo_derecho);

    }
}

int main()
{
    TColaCP cola = crear_cola_cp(compara);
    TEntrada e = malloc(sizeof(TEntrada));
    TEntrada e2 = malloc(sizeof(TEntrada));
    TEntrada e3 = malloc(sizeof(TEntrada));
    TEntrada e4 = malloc(sizeof(TEntrada));

    e->clave = 111;
    e->valor = 164;

    e2->clave = 222;
    e2->valor = 238;

    e3->clave = 333;
    e3->valor = 379;

    e4->clave = 444;
    e4->valor = 412;

    cp_insertar(cola, e);
    cp_insertar(cola, e2);
    cp_insertar(cola, e3);
    cp_insertar(cola, e4);

    //printf("%i \n",cp_insertar(cola, e2));
    printf("Recorrido inorder: \n");
    recorridoInorden(cola->raiz);

    printf("Cantidad de elementos: %i \n", cola->cantidad_elementos);
    return 0;
}
