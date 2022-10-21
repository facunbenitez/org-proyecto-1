#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"

const int TRUE = 1;
const int FALSE = 0;
const int CCP_NO_INI = 2;
const void* POS_NULA = NULL;
const void* ELE_NULO = NULL;

//TODO: implementar busqueda de la primer posicion valida para insertar un nuevo nodo
/*TNodo encontrarPrimerPosNula(TNodo nodo){
    if(*nodo != ELE_NULO){ //Que se almacena en direcciones de memeoria vacias?
        TNodo nIzq = encontrarPrimerPosNula(nodo * 2);
        TNodo nDer = encontrarPrimerPosNula(nodo * 2 + sizeof(struct nodo));
    }
    return *nodo;}*/

TNodo insertarEnCompleto (TNodo nodo){
    TNodo nuevoNodo = nodo;
    if(nodo->hijo_izquierdo != POS_NULA)
        nuevoNodo = insertarEnCompleto(nodo->hijo_izquierdo);
    return nuevoNodo;
}

TNodo insertarEnNormal (TNodo nodo, int nivel, int alt, TNodo nodoP){
    TNodo nodoAux = nodoP;
    if(nivel < alt && nodoAux == POS_NULA ){
        if (nivel != alt -1){
            if(nodo->hijo_izquierdo != POS_NULA)
                nodoAux = insertarEnNormal(nodo->hijo_izquierdo, nivel+1, alt, nodo );
            if(nodo->hijo_derecho != POS_NULA)
                nodoAux = insertarEnNormal (nodo->hijo_derecho, nivel+1, alt, nodo);
        }
        else{
            if(nodo->hijo_izquierdo == POS_NULA || nodo->hijo_derecho == POS_NULA)
                nodoAux = nodo;
        }
    }
    return nodoAux;
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

    nuevoNodo->hijo_izquierdo = POS_NULA;
    nuevoNodo->hijo_derecho = POS_NULA;

    //Inserto raiz, si no existe una
    if(cola->raiz==POS_NULA)
        cola->raiz = nuevoNodo;

    //Si hay raiz, busco un lugar para meter la nueva entrada
    else {

        //Reviso en que caso de insercion estoy
        int i = 1;
        int alt = 1;

        TNodo aux = cola->raiz;
        while(aux!=POS_NULA){
            alt++;
            aux = aux->hijo_izquierdo;
        }
        while(i < alt){
            i = i*2;
        }
        //Ubico el padre de mi nuevo nodo en funcion del estado de mi heap
        TNodo padre = POS_NULA;
        if(cola->cantidad_elementos + 1 == i){
            padre = (insertarEnCompleto(cola->raiz));
            padre->hijo_izquierdo = nuevoNodo;

        }

        else{
            padre = insertarEnNormal(cola->raiz, 0, alt, cola->raiz);
            printf("Hola entre xd %i\n", padre->entrada->clave);
            if(padre->hijo_izquierdo==POS_NULA)
                padre->hijo_izquierdo = nuevoNodo;
            else
                padre->hijo_derecho = nuevoNodo;
        }

        nuevoNodo->padre = padre;



        if(cola->comparador(nuevoNodo->entrada, cola->raiz->entrada)){
            //shellBurbuja(&cola->raiz);
        }
    }
    cola->cantidad_elementos++;
    return 1;
}

/* REVISAR
TEntrada cp_eliminar(TColaCP cola){
    TEntrada aRetornar = cola->raiz->entrada;

    if(cola -> cantidad_elementos == 1){
        cola -> raiz = ELE_NULO;
        cola -> cantidad_elementos = 0;
    }
    else {
        TNodo nuevaRaiz = encontrarUltimoNodo(cola->raiz);
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
*/

int cp_cantidad(TColaCP cola){
    return cola->cantidad_elementos;
}

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)){
    if(cola->raiz->hijo_izquierdo != POS_NULA)
        cp_destruirRec(cola->raiz->hijo_izquierdo, fEliminar);
    if(cola->raiz->hijo_derecho != POS_NULA)
        cp_destruirRec(cola->raiz->hijo_derecho,fEliminar);
    fEliminar(cola->raiz);
    free(cola->raiz);
    free(cola);
}

//Declarar privado
void cp_destruirRec(TNodo nodo, void(*fEliminar)(TEntrada)){
    if(nodo->hijo_izquierdo != POS_NULA)
        cp_destruirRec(nodo->hijo_izquierdo,fEliminar);
    if(nodo->hijo_derecho != POS_NULA)
        cp_destruirRec(nodo->hijo_derecho,fEliminar);
    fEliminar(nodo);
    free(nodo);
}












