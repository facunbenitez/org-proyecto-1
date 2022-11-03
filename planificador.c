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

    /*FILE * archivo;
    archivo = fopen(args[1], "r");
    if(archivo == NULL){
        perror("Se ingreso un archivo nulo");
        exit(-1);
    }*/

    char cadena[300] = "1;1\nSaliquelo;2;2\nBahia Blanca;4;4\nTrenque Lauquen;4;0\nCarhue;0;3";
    printf("La cadena es: [ %s ]\n", cadena);
    //fscanf(archivo, "%s", cadena);
    ///CONSULTAR SI ES LO MEJOR O SI DEBERIAMOS USAR OTRA FUNCION
    char delimitador[] = ";\n";
    char * token = strtok(cadena, delimitador);

    TCiudad aux = malloc(sizeof(aux));
    ubicacionActual -> pos_x = -1;
    ubicacionActual-> pos_y = -1;
    aux -> nombre = NULL;
    aux -> pos_x = -1;
    aux -> pos_y = -1;
    int indice = 0;

    if(token!= NULL){
        while(token != NULL){


            //1er caso, seteamos la ubicacion actual
            if(ubicacionActual->pos_x == -1 || ubicacionActual->pos_y == -1){
                int ret = atoi(token);
                if(ubicacionActual->pos_x == -1)
                    ubicacionActual->pos_x = ret;
                else{
                    if(ubicacionActual->pos_x != -1 && ubicacionActual->pos_y == -1)
                        ubicacionActual->pos_y = ret;
                }

            }
            //2do caso, construimos una nueva entrada
            else{
                if(aux->nombre == NULL){
                    char * s = token;
                    strcpy(s, token);
                    aux->nombre = s;
                }
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
                            //Hacemos un malloc para cada ciudad de cada entrada en una variable aux.
                            aux = malloc(sizeof(aux));
                            aux -> nombre = NULL;
                            aux -> pos_x = -1;
                            aux -> pos_y = -1;
                        }
                    }
                }

            }

            token = strtok(NULL, delimitador);
        }
    }
    printf("Ub actual: %f, %f\n", ubicacionActual->pos_x, ubicacionActual->pos_y);
    for(int i = 0; i<indice; i++){
        printf("Entrada %i : %s\n",i,((TCiudad)(entradas[i]->valor))->nombre);
    }
    int horasDeManejo = 0;
    int op0 = 0;
    printf("Si desea finalizar la ejecucion, inserte 0 \n");
    printf("Si desea mostrar ascendente, inserte 1 \n");
    printf("Si desea mostrar descendente, inserte 2 \n");
    printf("Si desea reducir horas de manejo, inserte 3 \n");

    TColaCP colaMin = crear_cola_cp(comparadorMin);
    TColaCP colaMax = crear_cola_cp(comparadorMax);
    TColaCP colaReducirHoras = crear_cola_cp(comparadorMin);
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
                    printf("Reduciendo horas de manejo...: \n");
                    while(cp_cantidad(colaReducirHoras) != 0){
                        TEntrada actual = cp_eliminar(colaReducirHoras);
                        printf("%s \n", ((TCiudad) actual->valor)->nombre);
                        horasDeManejo = horasDeManejo + actual->clave;
                        ubicacionActual = (TCiudad) actual->valor;
                        while(cp_cantidad(colaReducirHoras) != 0)
                            cp_eliminar(colaReducirHoras);
                            /***/
                        for(int i = 0; i<indice; i++){

                            if(entradasRH[i] !=NULL && entradasRH[i]->valor == ubicacionActual){
                                free(entradasRH[i]);
                                entradasRH[i] = NULL;
                            }
                            else if(entradasRH[i] != NULL){
                                entradasRH[i] -> clave = (int) distancia(ubicacionActual, entradasRH[i]->valor);
                            }
                        }
                            /***/
                        for(int i = 0; i<indice; i++){
                            if(entradasRH[i] != NULL){
                                cp_insertar(colaReducirHoras, entradasRH[i]);

                            }
                        }
                    }
                    printf("Total recorrido %i \n", horasDeManejo);
                    cp_destruir(colaReducirHoras, noEliminarEntrada);
                    colaReducirHoras = NULL;
                }
            }
        }
        free(ubicacionActual);
        free(aux);

        ///PREGUNTAR SI HAY QUE HACER FREE DE ENTRADASRH (Problemas de referencias)
        for(int j = 0; j<indice; j++){
            if(entradas[j]!=NULL){
                if(entradas[j]->valor!=NULL)
                    free(entradas[j]->valor);
                free(entradas[j]);
            }

            ///PREGUNTAR POR QUE SE ROMPE ACA (SUPONEMOS PROBLEMAS EN MANEJO DE MEMORIA)
            if(entradasRH[j]!=NULL){
                free(entradasRH[j]);
            }
        }


        ///PREGUNTAR ERRORES RELATIVOS A TCLAVE A LA HORA DE ASIGNARLO
    return 0;
}
