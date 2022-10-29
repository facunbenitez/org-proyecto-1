#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"

const int TRUE = 1;
const int FALSE = 0;
const int CCP_NO_INI = 2;
const void* POS_NULA = NULL;
const void* ELE_NULO = NULL;

//HACER PRIVADO
TNodo insertarEnCompleto (TNodo nodo){
    TNodo nuevoNodo = nodo;
    if(nodo->hijo_izquierdo != POS_NULA)
        nuevoNodo = insertarEnCompleto(nodo->hijo_izquierdo);
    return nuevoNodo;
}

//HACER PRIVADO
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
}

//HACER PRIVADO
TNodo buscarMenor(TColaCP cola, TNodo nodo){
    TNodo nEntradaMenor = nodo;
    TNodo nMenorIzq = nodo->hijo_izquierdo;
    TNodo nMenorDer = nodo->hijo_derecho;

    if(nMenorIzq != POS_NULA)
        nMenorIzq = insertarEnCompleto(nodo->hijo_izquierdo);
    if(nMenorDer != POS_NULA)
        nMenorDer = insertarEnCompleto(nodo->hijo_derecho);

    //CASO 1: TIENE LOS 2 HIJOS. HAY QUE COMPARAR LAS ENTRADAS ENTRE SI Y LUEGO COMPARAR CON LA DEL PADRE
    if(nMenorDer != POS_NULA && nMenorIzq != POS_NULA){
        TNodo menorHijo = POS_NULA;
        if((cola->comparador(nMenorIzq->entrada, nMenorDer->entrada)) == TRUE)
            menorHijo = nMenorIzq;
        else
            menorHijo = nMenorDer;

        if((cola->comparador(menorHijo->entrada, nEntradaMenor->entrada)) == TRUE)
            nEntradaMenor = menorHijo;
    }
    else{
        //CASO 2: TIENE UN SOLO HIJO. HAY QUE COMPARAR LA ENTRADA DIRECTAMENTE CON LA DEL PADRE
        if(nMenorIzq != POS_NULA){
            if((cola->comparador(nMenorIzq->entrada, nEntradaMenor->entrada)) == TRUE)
            nEntradaMenor = nMenorIzq;
        }
        if(nMenorDer != POS_NULA){
            if((cola->comparador(nMenorDer->entrada, nEntradaMenor->entrada)) == TRUE)
            nEntradaMenor = nMenorDer;
        }
    }
    return nEntradaMenor;
}

//HACER PRIVADO
void burbujeoArriba(TColaCP cola, TNodo nodo){
    if(cola->raiz != nodo){
       TEntrada aux = nodo->entrada;
       nodo->entrada = nodo->padre -> entrada;
       nodo->padre -> entrada = aux;
       burbujeoArriba(cola, nodo->padre);
    }
}

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP nuevaCola = malloc(sizeof(struct cola_con_prioridad));
    nuevaCola->cantidad_elementos = 0;
    nuevaCola->comparador = *f;
    nuevaCola->raiz = POS_NULA;
    return nuevaCola;
}

//HACER PRIVADO
int altura(TColaCP cola){
    return (log(cola->cantidad_elementos + 1) / log(2));
}

//HACER PRIVADO
int cantParaLlenar(TColaCP cola){
    int i = 2;
    /* ECUACION PARA HALLAR LA ALTURA
    ** 2^h -1 = cant_elems
    ** 2^h = cant_elems + 1
    ** h = log2(cant_elems + 1) */
    int alt = (log(cola->cantidad_elementos + 1) / log(2));

    for(int j = 1; j<alt; j++){
        i = i*2;
    }
    i--;
    printf("Altura: %d, i: %d, cantidad_elems: %d\n", alt, i, cola->cantidad_elementos);
    return i;
}

//HACER PRIVADO
TNodo buscarDerecha(TNodo n){
    if(n->hijo_derecho != POS_NULA)
        return buscarDerecha(n->hijo_derecho);
    else
        return n;
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

        //Ubico el padre de mi nuevo nodo en funcion del estado de mi heap
        TNodo padre = POS_NULA;
        if(cantParaLlenar(cola)==cola->cantidad_elementos){
            padre = (insertarEnCompleto(cola->raiz));
            padre->hijo_izquierdo = nuevoNodo;

        }

        else{

            padre = insertarEnNormal(cola->raiz, 0, altura(cola));
            if(padre->hijo_izquierdo==POS_NULA)
                padre->hijo_izquierdo = nuevoNodo;
            else
                padre->hijo_derecho = nuevoNodo;
        }

        nuevoNodo->padre = padre;

        if((cola->comparador(nuevoNodo->entrada, cola->raiz->entrada)) == TRUE)
            burbujeoArriba(cola, nuevoNodo);
    }
    cola->cantidad_elementos++;
    return 1;
}


TEntrada cp_eliminar(TColaCP cola){
    TEntrada aRetornar = cola->raiz->entrada;

    if(cola -> cantidad_elementos == 1){
        cola -> raiz = ELE_NULO;
        cola -> cantidad_elementos = 0;
    }
    else {
        //BUCAMOS EL NODO QUE SERÁ NUESTRA NUEVA RAIZ (ultimo nodo insertado)

        TNodo ultimoNodo = POS_NULA;
        if(cola->cantidad_elementos == cantParaLlenar(cola))
            ultimoNodo = (buscarDerecha(cola->raiz));
        else{
            ultimoNodo = insertarEnNormal(cola->raiz, 0, altura(cola));
        }

        printf("antes de borrar %d\n", ultimoNodo->entrada->clave);
        //ASIGNAMOS NUESTRA NUEVA RAIZ Y ELIMINAMOS EL NODO QUE NOS SOBRA EN LA HEAP

        cola->raiz->entrada = ultimoNodo->entrada;
        ultimoNodo->entrada = ELE_NULO;
        if(ultimoNodo->padre->hijo_derecho != POS_NULA)
            ultimoNodo->padre->hijo_derecho = POS_NULA;
        else
            ultimoNodo->padre->hijo_izquierdo = POS_NULA;
        free(ultimoNodo);//PREGUNTAR SI SE HACE ACÁ O MAS ADELANTE
        cola -> cantidad_elementos--;

        printf("antes de burbujear\n");
        //EVALUAMOS SI HAY QUE BURBUJEAR
        TNodo nodoMenor = buscarMenor(cola, cola->raiz);
        if((cola->comparador(nodoMenor->entrada, cola->raiz->entrada)) == TRUE)
            burbujeoArriba(cola, nodoMenor);

        }
    return aRetornar;
}


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















