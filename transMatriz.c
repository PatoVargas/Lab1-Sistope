#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "estructuras.h"

#define READ 0
#define WRITE 1
int n; //medidas de la matriz
int m;
MATRIZ arregloDeMatriz[2]; //arreglo de estructuras del tipo  matriz que contiene todas las matrices que son utilizables (donde A se asigna a la pos 0 y Z a la 25)

//Cabeceras de las funciones implementadas
void rellenarMatriz(char *nombre, int indiceLocal);
int seleccionarMatriz(char *letra);
void obtenerMedidas(char *nombre);
void imprimir(int indiceLocal);
void guardar2(MATRIZ resultante);

int main(int argc, char const *argv[]){
	char matrizDestino[25];
	char primerOperando[25];
	strcpy(matrizDestino,argv[1]);
	strcpy(primerOperando,argv[2]);
	obtenerMedidas(primerOperando);
	arregloDeMatriz[0].nlocal = n;
	arregloDeMatriz[0].mlocal = m;
	rellenarMatriz(primerOperando,0);
	MATRIZ resultado;
	if(arregloDeMatriz[0].nlocal != 0){
		int i,j,k;
		resultado.nlocal = arregloDeMatriz[0].mlocal;
		resultado.mlocal = arregloDeMatriz[0].nlocal;
		resultado.estado = 1;
		resultado.matriz = (int**)(malloc( sizeof(int*) * resultado.nlocal));
        for (i=0;i<resultado.mlocal;i++){
             resultado.matriz[i] = (int*)( malloc( sizeof(int) * resultado.mlocal));
        }
		for(i=0;i<resultado.mlocal;i++){
			for(j=0;j<resultado.nlocal;j++){
				resultado.matriz[i][j] = arregloDeMatriz[0].matriz[j][i];
			}
		}
    	guardar2(resultado);
	}
	else{
		printf("LAS MATRICES DEBEN SER DE DIMENSIONES MXN Y NXP RESPECTIVAMENTE\n");
	}
    write(STDOUT_FILENO, "auxiliar.txt", 12);
	return 0;	
}

void obtenerMedidas(char *nombre){
	FILE * file;
    file = fopen(nombre, "r");
    if(file == NULL){ // Error al abrir el archivo
        printf("Error: No se ha podido abrir el archivo de entrada.\n");
    }
    else{ // Apertura de archivo correcta
        int i, j;//n filas, m columnas
        // Leemos matriz de entrada

        fscanf(file, "%d", &n);
        fscanf(file, "%d", &m);
        fclose(file);
    }
}

//rellenarMatriz
void rellenarMatriz(char *nombre, int indiceLocal){
	FILE * file;
    file = fopen(nombre, "r");
    if(file == NULL){ // Error al abrir el archivo
        printf("Error: No se ha podido abrir el archivo de entrada.\n");
    }
    else{ // Apertura de archivo correcta
        int i, j;//n filas, m columnas
        // Leemos matriz de entrada

        fscanf(file, "%d", &n);
        fscanf(file, "%d", &m);
        arregloDeMatriz[indiceLocal].matriz = (int**)(malloc( sizeof(int*) * n));
        for (i=0;i<n;i++){
             arregloDeMatriz[indiceLocal].matriz[i] = (int*)( malloc( sizeof(int) * m));
        }
 
        for (i=0;i<n;i++){
            for (j=0;j<m;j++){
                fscanf(file, "%d", &arregloDeMatriz[indiceLocal].matriz[i][j]);
            }
        }
        fclose(file);
    }
}
//Funcion para imprimir la matriz
void imprimir(int indiceLocal){
	int i,j;
    for(i=0;i<arregloDeMatriz[indiceLocal].nlocal ;i++){
        for(j=0;j<arregloDeMatriz[indiceLocal].mlocal;j++){
        	printf("%i ",arregloDeMatriz[indiceLocal].matriz[i][j]);
        }
        printf("\n");
    }
}

//Funcion para escribir una determinada matriz en algun archivo de texto
void guardar2(MATRIZ resultante){
	int i,j;
	if(resultante.estado == 1){
		FILE * file;
    	file = fopen("auxiliar.txt", "w+");
    	fprintf(file, "%i",resultante.nlocal);
    	fprintf(file, "\n");
    	fprintf(file, "%i",resultante.mlocal);   	
    	fprintf(file, "\n");
    	for(i=0;i<resultante.nlocal;i++){
        	for(j=0;j<resultante.mlocal;j++){
        		fprintf(file,"%i ",resultante.matriz[i][j]);
        	}
        	if(i != resultante.nlocal-1){
        		fprintf(file,"\n");
    		}
    	}
		fclose ( file );
	}
	else{
		printf("NO SE GUARDO\n");
	}
}
