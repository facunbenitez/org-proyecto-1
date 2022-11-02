#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char * args[]){

    TCiudad ubicacionActual = malloc(sizeof(ubicacionActual));
    TEntrada entradas[100];
    TEntrada entradasRH[100];
    ///HAY QUE HACER MALLOC DE LOS ARREGLOS? PROBLEMAS A LA HORA DE HACER FREE

    FILE * archivo;
    archivo = fopen(args[1], "r");
    if(archivo == NULL){
        perror("Se ingreso un archivo nulo");
        exit(-1);
    }

    char cadena[300];
    fscanf(archivo, "%s", cadena); ///CONSULTAR SI ES LO MEJOR O SI DEBERIAMOS USAR OTRA FUNCION
    char delimitador[] = ";\n";
    char * token = strtok(cadena, delimitador);
    TCiudad aux = malloc(sizeof(aux));
    TCiudad aux2 = malloc(sizeof(aux2));
    ubicacionActual -> pos_x = -1;
    ubicacionActual-> pos_y = -1;
    aux -> nombre = NULL;
    aux -> pos_x = -1;
    aux -> pos_y = -1;
    aux2 -> nombre = NULL;
    aux2 -> pos_x = -1;
    aux2 -> pos_y = -1;
    int indice = 0;

    if(token!= NULL){
        while(token != NULL){
            //1er caso, seteamos la ubicacion actual
            if(ubicacionActual->pos_x == -1 || ubicacionActual->pos_y == -1){
                if(ubicacionActual->pos_x == -1)
                    ubicacionActual->pos_x = atoi(token);
                else{
                    if(ubicacionActual->pos_x != -1 && ubicacionActual->pos_y == -1)
                        ubicacionActual->pos_x = atoi(token);
                }
            }
            //2do caso, construimos una nueva entrada
            else{
                if(aux->nombre == NULL)
                    strcpy(aux->nombre, token);
                else{
                    if(aux->pos_x == -1)
                        aux->pos_x = atoi(token);
                    else{
                        if(aux->pos_y == -1){
                            aux->pos_y = atoi(token);
                            //Una vez que seteamos todos los valores de una ciudad, creamos la
                            //entrada y la ubicamos en las colecciones de entradas.
                            TEntrada eAux = malloc(sizeof(eAux));
                            TEntrada eAuxRH = malloc(sizeof(eAuxRH));
                            eAux->clave = (int) distancia(ubicacionActual, aux);
                            eAuxRH->clave = (int) distancia(ubicacionActual, aux);
                            eAux->valor = aux;
                            eAuxRH->valor = aux;
                            entradas[indice] = eAux;
                            entradasRH[indice] = eAuxRH;
                            indice++;
                            aux = aux2;
                        }
                    }
                }

            }
            token = strtok(NULL, delimitador);
        }
    }

    int horasDeManejo = 0;
    int op0 = 0;
    printf("Si desea finalizar la ejecucion, inserte 0 \n");
    printf("Si desea mostrar ascendente, inserte 1 \n");
    printf("Si desea mostrar descendente, inserte 2 \n");
    printf("Si desea reducir horas de manejo, inserte 3 \n");

    TColaCP colaMin;
    TColaCP colaMax;
    TColaCP colaReducirHoras;
    int opcion = -1;

        while(op0 == 0){
        printf("Indique la opcion deseada: ");
        scanf("%i", &opcion );
        printf("\n");


            if(opcion == 0){
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

            if(opcion == 1){
            if(colaMin == NULL)
                printf("Esta operacion ya se ejecuto previamente \n");
            else{
                colaMin = crear_cola_cp(comparadorMin);
                for(int i = 0; i < indice; i++)
                    cp_insertar(colaMin, entradas[i]);
                printf("Mostrar ascendente: \n");
                while(colaMin -> cantidad_elementos != 0){
                    TEntrada actual = cp_eliminar(colaMin);
                    printf("%s \n", ((TCiudad) actual->valor)->nombre);
                }
                cp_destruir(colaMin, noEliminarEntrada);
                colaMin = NULL;
            }
            }

           if(opcion == 2){
           if(colaMax == NULL)
                printf("Esta operacion ya se ejecuto previamente \n");
            else{
                colaMax = crear_cola_cp(comparadorMax);
                for(int i = 0; i < indice; i++)
                    cp_insertar(colaMax, entradas[i]);
                printf("Mostrar descendente: \n");
                while(colaMax ->cantidad_elementos != 0){
                    TEntrada actual = cp_eliminar(colaMax);
                    printf("%s \n", ((TCiudad) actual->valor)->nombre);
                }
                cp_destruir(colaMax, noEliminarEntrada);
                colaMax = NULL;
            }
           }

            if(opcion == 3){
            if(colaReducirHoras == NULL)
                printf("Esta operacion ya se ejecuto previamente \n");
            else{
                colaReducirHoras = crear_cola_cp(comparadorMin);
                for(int i = 0; i < indice; i++)
                    cp_insertar(colaReducirHoras, entradasRH[i]);
                printf("Mostrar descendente: \n");
                while(colaReducirHoras ->cantidad_elementos != 0){
                    TEntrada actual = cp_eliminar(colaReducirHoras);
                    printf("%s \n", ((TCiudad) actual->valor)->nombre);
                    horasDeManejo = horasDeManejo + actual->clave;
                    ubicacionActual = (TCiudad) actual->valor;
                    while(cp_cantidad(colaReducirHoras) != 0)
                        cp_eliminar(colaReducirHoras);
                    for(int i = 0; i<indice; i++){
                        if(entradasRH[i]->valor == ubicacionActual){
                            free(entradasRH[i]->clave);
                            free(entradasRH[i]);
                            entradasRH[i] = NULL;
                        }
                        if(entradasRH[i] != NULL){
                            entradasRH[i] -> clave = (int) distancia(ubicacionActual, aux);
                        }
                    }
                    for(int i = 0; i<indice; i++){
                        if(entradasRH[i] != NULL){
                            cp_insertar(colaReducirHoras, entradasRH[i]);
                        }
                    }
                }
                cp_destruir(colaReducirHoras, noEliminarEntrada);
                colaReducirHoras = NULL;
            }
            }
        }
        free(ubicacionActual);
        free(aux2);
        free(aux);
        ///PREGUNTAR SI HAY QUE HACER FREE DE ENTRADASRH (Problemas de referencias)
        for(int j = 0; j<indice; j++){
            free(entradas[j]->clave);
            free(entradas[j]->valor);
            free(entradas[j]);
        }
        ///PREGUNTAR ERRORES RELATIVOS A TCLAVE A LA HORA DE ASIGNARLO

    return 0;
}
