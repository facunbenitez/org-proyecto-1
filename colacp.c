#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"

const int TRUE = 1;
const int FALSE = 0;
const int CCP_NO_INI = 2;
const void* POS_NULA = NULL;
const void* ELE_NULO = NULL;

//TODO: implementar busqueda de la primer posicion valida para insertar un nuevo nodo
TNodo encontrarPrimerPosNula(TNodo * nodo){
    if(*nodo != ELE_NULO){ //Que se almacena en direcciones de memeoria vacias?
        TNodo nIzq = encontrarPrimerPosNula(nodo * 2);
        TNodo nDer = encontrarPrimerPosNula(nodo * 2 + sizeof(struct nodo));
    }
    return *nodo;
}

TNodo encontrarUltimoNodo(TNodo * nodo){
        TNodo nIzq = encontrarPrimerPosNula(nodo * 2);
        TNodo nDer = encontrarPrimerPosNula(nodo * 2 + sizeof(struct nodo));

    if(nDer != ELE_NULO)
        return nDer;
    else
        if(nIzq != ELE_NULO)
            return nIzq;
}

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP nuevaCola = malloc(sizeof(struct cola_con_prioridad));
    nuevaCola->cantidad_elementos = 0;
    nuevaCola->comparador = *f;
    nuevaCola->raiz = POS_NULA;
    return nuevaCola;
}

int cp_insertar(TColaCP cola, TEntrada entr){

    TNodo nuevoNodo = malloc(sizeof(struct nodo));
    nuevoNodo->entrada = entr;

    nuevoNodo->hijo_izquierdo = ELE_NULO;
    nuevoNodo->hijo_derecho = ELE_NULO;

    //Inserto raiz, si no existe una
    if(cola->raiz==ELE_NULO)
        cola->raiz = nuevoNodo;

    //Si hay raiz, busco un lugar para meter la nueva entrada
    else {

        TNodo padre = encontrarPrimerPosNula(&cola->raiz);
        nuevoNodo->padre = padre;

        if(padre->hijo_izquierdo==ELE_NULO)
            padre->hijo_izquierdo = nuevoNodo;

        else if(padre->hijo_derecho==ELE_NULO)
            padre->hijo_derecho = nuevoNodo;

        else{
            free(nuevoNodo);
            return 0;
        }

        if(cola_con_prioridad ->comparador(nuevoNodo.entrada, cola_con_prioridad.raiz.entrada))
            shellBurbuja(&cola->raiz)

    }
    cola->cantidad_elementos++;
    return 1;
}

TEntrada cp_eliminar(TColaCP cola){
    TEntrada aRetornar = cola -> raiz.entrada;

    if(cola -> cantidad_elementos == 1){
        cola -> raiz = ELE_NULO;
        cola -> cantidad_elementos = 0;
    }
    else {
        TNodo nuevaRaiz = encontrarUltimoNodo(&cola->raiz);
        TNodo hI = *(&(cola->raiz)*2);
        TNodo hD = *(&(cola->raiz)*2 + sizeof(struct nodo))
        hI.padre = nuevaRaiz;
        hD.padre = nuevaRaiz;
        cola -> raiz.entrada = ELE_NULO;
        cola -> raiz.hijo_derecho = POS_NULA;
        cola -> raiz.hijo_izquierdo = POS_NULA;
        cola -> raiz = nuevaRaiz;
        if(cola ->raiz.padre->hijo_derecho != POS_NULA)
            cola ->raiz.padre->hijo_derecho = POS_NULA;
        else
            cola ->raiz.padre->hijo_izquierdo = POS_NULA;
        cola -> raiz.padre = POS_NULA;

        //FALTA BURBUJEAR TODO.
    }

    free(sizeof(struct nodo));//PREGUNTAR SI SE HACE ACÁ O MAS ADELANTE
    return aRetornar;
}

int cp_cantidad(TColaCP cola){
    return cola->cantidad_elementos;
}

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)){
    if(cola->raiz.hijo_izquierdo != POS_NULA)
        cp_destruirRec(cola->raiz.hijo_izquierdo,*fEliminar(TEntrada));
    if(cola->raiz.hijo_derecho != POS_NULA)
        cp_destruirRec(cola->raiz.hijo_derecho,*fEliminar(TEntrada));
    fEliminar(cola->raiz);
    free(cola->raiz);
    free(cola);
}

//Declarar privado
void cp_destruirRec(*TNodo nodo, void(*fEliminar)(TEntrada)){
    if(nodo.hijo_izquierdo != POS_NULA)
        cp_destruirRec(nodo.hijo_izquierdo,*fEliminar(TEntrada));
    if(nodo.hijo_derecho != POS_NULA)
        cp_destruirRec(nodo.hijo_derecho,*fEliminar(TEntrada));
    fEliminar(nodo);
    free(nodo);
}












