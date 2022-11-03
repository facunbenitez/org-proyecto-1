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

    if((*((int *)clave1) < (*((int *)clave2))))
        return 1;
    else if((*((int *)clave1) == (*((int *)clave2))))
        return 0;
    else
        return -1;
}

//LA CLAVE DE UNA ENTRADA REPRESENTA LA DISTANCIA AL ORIGEN, Y SU VALOR LA CIUDAD
int comparadorMax(TEntrada e1, TEntrada e2){
    TClave clave1 = e1->clave;
    TClave clave2 = e2->clave;

    if((*((int *)clave1) > (*((int *)clave2))))
        return 1;
    else if((*((int *)clave1) == (*((int *)clave2))))
        return 0;
    else
        return -1;
}


void noEliminarEntrada(TEntrada e){
}

int main(int argc, char * args[]){

    TCiudad ubicacionActual = malloc(sizeof(struct ciudad));
    TEntrada entradas[100];
    TEntrada entradasRH[100];

    FILE * archivo;
    archivo = fopen(args[1], "r");
    if(argc != 2){
        perror("Se ingreso un archivo nulo");
        exit(-1);
    }

    char cadena[300];
    int indice = 0;

    while(!feof(archivo)){
        fscanf(archivo, "%s", cadena);
        char delimitador[] = ";\n";
        char * token = strtok(cadena, delimitador);

        TCiudad aux = malloc(sizeof(struct ciudad));
        ubicacionActual -> pos_x = -1;
        ubicacionActual-> pos_y = -1;
        aux -> nombre = NULL;
        aux -> pos_x = -1;
        aux -> pos_y = -1;

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
                                TEntrada eAux = malloc(sizeof(struct entrada));
                                TEntrada eAuxRH = malloc(sizeof(struct entrada));
                                int * c1 = malloc(sizeof(int));
                                int * c2 = malloc(sizeof(int));
                                *c1 = distancia(ubicacionActual, aux);
                                *c2 = distancia(ubicacionActual, aux);
                                eAux->clave = c1;
                                eAuxRH->clave = c2;

                                eAux->valor = aux;
                                eAuxRH->valor = aux;
                                entradas[indice] = eAux;
                                entradasRH[indice] = eAuxRH;
                                indice++;
                                //Hacemos un malloc para cada ciudad de cada entrada en una variable aux.

                                aux = malloc(sizeof(struct ciudad));
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
    TCiudad ciudadNula = malloc(sizeof(struct ciudad));
    TEntrada entradaNula = malloc(sizeof(struct entrada));
    entradaNula->valor = ciudadNula;
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
                        int numaux = (*((int *)actual->clave));
                        horasDeManejo = horasDeManejo +  numaux;
                        ubicacionActual = (TCiudad) actual->valor;
                        while(cp_cantidad(colaReducirHoras) != 0)
                            cp_eliminar(colaReducirHoras);
                        for(int i = 0; i<indice; i++){

                            if(entradasRH[i] != entradaNula && entradasRH[i]->valor == ubicacionActual){
                                free(entradasRH[i]);
                                entradasRH[i] = entradaNula;
                            }
                            else if(entradasRH[i] != entradaNula){
                                int * c1 = entradasRH[i] -> clave;
                                *c1 = distancia(ubicacionActual, entradasRH[i]->valor);
                                entradasRH[i] -> clave = c1;
                            }
                        }
                        for(int i = 0; i<indice; i++){
                            if(entradasRH[i] != entradaNula){
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
        for(int j = 0; j<indice; j++){
            int hayQueLiberar = 1;
            if(entradas[j]!=NULL){
                hayQueLiberar = 0;
                if(entradasRH[j] == NULL){
                    free(((TCiudad)(entradas[j]->valor))->nombre);
                    free(entradas[j]->valor);
                }
                free(entradas[j]->clave);
                free(entradas[j]);
                entradas[j] = NULL;
            }
            if(entradasRH[j]!=entradaNula){
               if(hayQueLiberar){
                    free(((TCiudad)(entradasRH[j]->valor))->nombre);
                    free(entradasRH[j]->valor);
                }
                free(entradasRH[j]->clave);
                free(entradasRH[j]);
                entradasRH[j] = entradaNula;
            }
        }
        free(entradaNula);
        free(ciudadNula);

    return 0;
}
