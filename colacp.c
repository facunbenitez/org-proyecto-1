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

TNodo insertarEnNormal (TNodo nodo, int nivel, int alt){
    //Caso base, estoy en el nivel de insercion.
    //Si uno de los hijos del nodo es POS_NULA, retorno ese nodo
    //Caso contrario, retorno POS_NULA
    if(nivel==alt-1){
        if(nodo->hijo_izquierdo == POS_NULA || nodo->hijo_derecho == POS_NULA)
            return nodo;
        else
            return POS_NULA;
    }

    //Caso rec., No estoy en el nivel de insercion.
    //nodoAux sera insercionEnNormal(NI, nivel+1, alt)
    //Si nodoAux es POS_NULA le asigno a nodoAux insercionEnNormal(ND, nivel+1, alt)
    //NI es el hijo izq. del nodo. ND es el hijo der. del nodo.
    else{
        TNodo nodoAux = insertarEnNormal(nodo->hijo_izquierdo, nivel+1, alt);

        if(nodoAux == POS_NULA)
            nodoAux = insertarEnNormal(nodo->hijo_derecho, nivel+1, alt);

        return nodoAux;
    }

/*    if(nodoAux == POS_NULA)
        if(nivel < alt){
            if (nivel != (alt -1)){
                if(nodo->hijo_izquierdo != POS_NULA)
                    nodoAux = insertarEnNormal(nodo->hijo_izquierdo, nivel+1, alt, nodo);
                if(nodo->hijo_derecho != POS_NULA)
                    nodoAux = insertarEnNormal (nodo->hijo_derecho, nivel+1, alt, nodo);
            }
            else if(nivel == (alt -1)){
                if(nodo->hijo_izquierdo == POS_NULA || nodo->hijo_derecho == POS_NULA)
                    return nodo;
                else return POS_NULA;
            }
        }
    return nodoAux;*/
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
        /* ECUACION PARA HALLAR LA ALTURA
        ** 2^h -1 = cant_elems
        ** 2^h = cant_elems + 1
        ** h = log2(cant_elems + 1) */
        int alt = (log(cola->cantidad_elementos + 1) / log(2));

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

            padre = insertarEnNormal(cola->raiz, 0, alt);
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












