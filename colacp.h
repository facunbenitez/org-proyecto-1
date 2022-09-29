#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

const int TRUE;
const int FALSE;
const int CCP_NO_INI;
const void* POS_NULA;
const void* ELE_NULO;

typedef void* TClave;
typedef void* TValor;

typedef struct entrada{
    TClave clave;
    TValor valor;
} * TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
}* TNodo;

typedef struct cola_con_prioridad {
    int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada, TEntrada);
} * TColaCP;

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

int cp_insertar(TColaCP cola, TEntrada entr);

TEntrada cp_eliminar(TColaCP cola);

int cp_cantidad(TColaCP cola);

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada));

int f(TEntrada, TEntrada);

int fEliminar(TEntrada);

#endif
