#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "estructuras.h"
//Datos Globales

#define READ 0
#define WRITE 1

int n; //medidas de la matriz
int m;
MATRIZ arregloDeMatriz[26]; //arreglo de estructuras del tipo  matriz que contiene todas las matrices que son utilizables (donde A se asigna a la pos 0 y Z a la 25)

//Cabeceras de las funciones implementadas
void rellenarMatriz(char *nombre, int indiceLocal);
int seleccionarMatriz(char *letra);
void obtenerMedidas(char *nombre);
void imprimir(int indiceLocal);
void guardar(int indiceLocal,char *nombre);

int verificarConstante(char constante);

//Función principal del programa
//Se define un comando  de ejecución que  permite  el ingreso de los comandos 
//Luego se separan los elementos capturados en el comando para dedicir que acciones realizar
//Se define una sentencia if para cada comando ejecutable
int main(int argc, char const *argv[]){
	int i, primerArgumento, segundoArgumento, tercerArgumento;
    int hijopapa[2];
	printf("Bienvenido: \n");
	int condicionEjecucion = 0;
	while (condicionEjecucion == 0){ //condicion  periodica de ejecucion
		int indice, indice2;
		char comando[25];
		char *aux = NULL ;    //punteros auxiliares para capturar los comando ingresados durante la ejecucion
		char *aux2 = NULL ;	
		char *aux3 = NULL;
		char *trozo = NULL;
		fgets(comando, 25, stdin);	//Se captura el comando
		trozo = strtok(comando," \n"); 
		primerArgumento = 0;
		segundoArgumento = 0;
		tercerArgumento = 0;		
		while( trozo != NULL ) { //while para guardar los componentes del comando en sus respectivos auxiliares
			aux3 = trozo;
			if(segundoArgumento == 1){
				aux2 = trozo;		
			}
			if(primerArgumento == 0){	
				aux = trozo;
				aux2 = trozo;						
			}
			trozo = strtok( NULL, " \n");
			primerArgumento++;			
			segundoArgumento++;
			
	    }
	    aux = strtok(aux," "); //Se usan el procedimiento strtok para eliminar caracteres innecesarios en los auxiliares, por ejemplo los 								   //espacios o saltos de linea.
		printf("2p1: ->%s<-,p2 = ->%s<-,p3: ->%s<-\n",aux,aux2,aux3);
			
	    if(strcmp(aux,"load")==0){ //sentencias if que describen el comportamiento de los comandos ejecutados
	    	aux3 = strtok(aux3,"\"");
	    	obtenerMedidas(aux3);
	    	indice = seleccionarMatriz(aux2);
	    	arregloDeMatriz[indice].estado = 1;
	    	strcpy(arregloDeMatriz[indice].archivo,aux3);
	    	arregloDeMatriz[indice].nlocal = n;
	    	arregloDeMatriz[indice].mlocal = m;
	    	rellenarMatriz(aux3,indice);
	    }
	   	else if(strcmp(aux,"print")==0){
			indice = seleccionarMatriz(aux2);
			if(arregloDeMatriz[indice].estado == 1){
					imprimir(indice);
			}
			else{
				printf("NO disponible para utilizar!\n");
			}
		}
		else if(strcmp(aux,"clear")==0){
			indice = seleccionarMatriz(aux2);
			if (arregloDeMatriz[indice].estado==1){
				arregloDeMatriz[indice].estado = 0;
			}
			else{
				printf("La matriz estaba limpia\n");
			}
		}
		else if(strncmp(aux,"exit",4)==0){
			printf("Adios\n");
			condicionEjecucion = 1;
		}
		else if(strcmp(aux,"save")==0){
			aux3 = strtok(aux3,"\"");
			indice = seleccionarMatriz(aux2);
			guardar(indice,aux3);
		}
		else if (strncmp(aux,aux3,1)!=0 && strlen(aux)==strlen(aux3) && strncmp(aux2,"=trans",6)!=0){
			if(strcmp(aux2,"=")==0){
				indice = seleccionarMatriz(aux);
				indice2 = seleccionarMatriz(aux3);
				if (arregloDeMatriz[indice].estado == 1 && arregloDeMatriz[indice2].estado == 1){
					arregloDeMatriz[indice].nlocal = arregloDeMatriz[indice2].nlocal;
					arregloDeMatriz[indice].mlocal = arregloDeMatriz[indice2].mlocal;
					arregloDeMatriz[indice].matriz = arregloDeMatriz[indice2].matriz;	
				}
				else{
					printf("Codigo incorrecto\n");
				}			
			}
			else{
			}
		}
		else if( (strlen(aux3)==3 && strlen(aux2)==1 && strlen(aux)==1) ||
				 (seleccionarMatriz(aux) != -1 && seleccionarMatriz(aux3) != -1 && strncmp(aux2,"=trans",6) == 0) ){
			if (strncmp(aux2,"=trans",6) != 0){
				int indiceAux1, indiceAux2, indiceAux3,cons;
				char string1[10];
				char string2[10];
				char string3[10];
				char string4[10];
				char string5[10];
				char string6[10];
				strcpy(string3, aux3);
				strcpy(string2, strtok(string3,"ABCDEFGHIIJKLMNOPQRSTUVWXYZ123456789"));
				strcpy(string1,strtok(string3,"-*+"));
				char *puntero3 = &aux3[2];
				char *puntero1 = string1;
				char *puntero2 = string2;
				indiceAux1 = seleccionarMatriz(aux);
				indiceAux2 = seleccionarMatriz(puntero1);
				indiceAux3 = seleccionarMatriz(puntero3);
				strcpy(string4,arregloDeMatriz[indiceAux1].archivo);
				strcpy(string5,arregloDeMatriz[indiceAux2].archivo);
				strcpy(string6,arregloDeMatriz[indiceAux3].archivo);
				if( (verificarConstante(puntero3[0])) == 1){
					cons = atoi(puntero3);
				} 
				if(strcmp(puntero2,"+")==0){
					char* arg_list[] = {
					"./suma",
					string4,
					string5,
					string6,
					"ls",
					"-al",
					NULL};
					char respuesta[12];
    				pipe(hijopapa);
    				int pid = fork();
					if(pid<0){
						printf("ERROR DEL FORK\n");
					}
					else if(pid == 0){ //HIJO
		    			dup2(hijopapa[1],STDOUT_FILENO);
		    			close(hijopapa[0]);
		    			execvp ("./suma", arg_list);
		    			exit(EXIT_FAILURE);
					}
					else{ //PADRE
						
						read(hijopapa[READ], respuesta, 12);
						arregloDeMatriz[indiceAux1].estado = 1;
						obtenerMedidas(respuesta);
						arregloDeMatriz[indiceAux1].nlocal = n;
						arregloDeMatriz[indiceAux1].mlocal = m;
						strcpy(arregloDeMatriz[indiceAux1].archivo,respuesta);
						rellenarMatriz(respuesta,indiceAux1);
						guardar(indiceAux1,arregloDeMatriz[indiceAux1].archivo);
					}
				}
				else if (strcmp(puntero2,"-")==0){
					char* arg_list[] = {
					"./resta",
					string4,
					string5,
					string6,
					"ls",
					"-al",
					NULL};
					char respuesta[12];
    				pipe(hijopapa);
    				int pid = fork();
					if(pid<0){
						printf("ERROR DEL FORK\n");
					}
					else if(pid == 0){ //HIJO
		    			dup2(hijopapa[1],STDOUT_FILENO);
		    			close(hijopapa[0]);
		    			execvp ("./resta", arg_list);
		    			exit(EXIT_FAILURE);
					}
					else{ //PADRE	
						
						read(hijopapa[READ], respuesta, 12);
						arregloDeMatriz[indiceAux1].estado = 1;
						obtenerMedidas(respuesta);
						arregloDeMatriz[indiceAux1].nlocal = n;
						arregloDeMatriz[indiceAux1].mlocal = m;
						rellenarMatriz(respuesta,indiceAux1);
						guardar(indiceAux1,arregloDeMatriz[indiceAux1].archivo);
					}
				}
				else if ((strcmp(puntero2,"*"))==0 && ((verificarConstante(puntero3[0]))) == 1){
					char* arg_list[] = {
					"./cons",
					string4,
					string5,
					puntero3,
					"ls",
					"-al",
					NULL};
					char respuesta[12];
    				pipe(hijopapa);
    				int pid = fork();
					if(pid<0){
						printf("ERROR DEL FORK\n");
					}
					else if(pid == 0){ //HIJO
		    			dup2(hijopapa[1],STDOUT_FILENO);
		    			close(hijopapa[0]);
		    			execvp ("./cons", arg_list);
		    			exit(EXIT_FAILURE);
					}
					else{ //PADRE

						read(hijopapa[READ], respuesta, 12);
						arregloDeMatriz[indiceAux1].estado = 1;
						obtenerMedidas(respuesta);
						arregloDeMatriz[indiceAux1].nlocal = n;
						arregloDeMatriz[indiceAux1].mlocal = m;
						rellenarMatriz(respuesta,indiceAux1);
						guardar(indiceAux1,arregloDeMatriz[indiceAux1].archivo);	
					}
				}
				else if (strcmp(puntero2,"*")==0){
					char* arg_list[] = {
					"./multiplo",
					string4,
					string5,
					string6,
					"ls",
					"-al",
					NULL};
					char respuesta[12];
    				pipe(hijopapa);
    				int pid = fork();
					if(pid<0){
						printf("ERROR DEL FORK\n");
					}
					else if(pid == 0){ //HIJO
		    			dup2(hijopapa[1],STDOUT_FILENO);
		    			close(hijopapa[0]);
		    			execvp ("./multiplo", arg_list);
		    			exit(EXIT_FAILURE);
					}
					else{ //PADRE

						read(hijopapa[READ], respuesta, 12);
						arregloDeMatriz[indiceAux1].estado = 1;
						obtenerMedidas(respuesta);
						arregloDeMatriz[indiceAux1].nlocal = n;
						arregloDeMatriz[indiceAux1].mlocal = m;
						rellenarMatriz(respuesta,indiceAux1);
						guardar(indiceAux1,arregloDeMatriz[indiceAux1].archivo);	
					}
				}
			}
			else{
				int indiceAUX = seleccionarMatriz(aux);
				int indiceAUX2 = seleccionarMatriz(aux3);
				char string7[10];
				char string8[10];
				strcpy(string7,arregloDeMatriz[indiceAUX].archivo);
				strcpy(string8,arregloDeMatriz[indiceAUX2].archivo);
				char* arg_list[] = {
				"./trans",
				string7,
				string8,
				"ls",
				"-al",
				NULL};
				pipe(hijopapa);
    			int pid = fork();
				if(pid<0){
					printf("ERROR DEL FORK\n");
				}
				else if(pid == 0){ //HIJO
	    			dup2(hijopapa[WRITE],STDOUT_FILENO);
	    			execvp ("./trans", arg_list);
	    			exit(EXIT_FAILURE);
				}
				else{ //PADRE	
					char respuesta[12];
					close(hijopapa[WRITE]);
					read(hijopapa[READ], respuesta, 12);
					strcpy(arregloDeMatriz[indiceAUX].archivo,respuesta);
					arregloDeMatriz[indiceAUX].estado = 1;
					obtenerMedidas(respuesta);
					arregloDeMatriz[indiceAUX].nlocal = n;
					arregloDeMatriz[indiceAUX].mlocal = m;
					rellenarMatriz(respuesta,indiceAUX);
				}
			}
		}
		else{
			printf("Comando invalido\n");
		}
	}

}

int verificarCaracter(char caracter){


}

int verificarConstante(char constante){
	if(constante >= '0' && constante <= '9') return 1; //true
	return 0; //false

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
        //printf("Error: No se ha podido abrir el archivo de entrada.\n");
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
void guardar(int indiceLocal,char *nombre){
	int i,j;
	if(arregloDeMatriz[indiceLocal].estado == 1){
		FILE * file;
    	file = fopen(nombre, "w+");
    	fprintf(file, "%i",arregloDeMatriz[indiceLocal].nlocal);
    	fprintf(file, "\n");
    	fprintf(file, "%i",arregloDeMatriz[indiceLocal].mlocal);   	
    	fprintf(file, "\n");
    	for(i=0;i<arregloDeMatriz[indiceLocal].nlocal;i++){
        	for(j=0;j<arregloDeMatriz[indiceLocal].mlocal;j++){
        		fprintf(file,"%i ",arregloDeMatriz[indiceLocal].matriz[i][j]);
        	}
        	fprintf(file,"\n");
    	}
		fclose ( file );
	}
	else{
		printf("NO SE GUARDO\n");
	}
}

//funcion que establece que matriz es utiliza el usuario, una para cada caso (de la A a la Z) 
int seleccionarMatriz(char *letra){
	int i;
	if(strcmp(letra,"A")==0){
		return 0;	
	}
	else if(strcmp(letra,"B")==0){
		return 1;
	}
	else if(strcmp(letra,"C")==0){
		return 2;

	}
	else if(strcmp(letra,"D")==0){
		return 3;
	}
	else if(strcmp(letra,"E")==0){
		return 4;
	}
	else if(strcmp(letra,"F")==0){
		return 5;
	}
	else if(strcmp(letra,"G")==0){
		return 6;
	}
	else if(strcmp(letra,"H")==0){
		return 7;
	}
	else if(strcmp(letra,"I")==0){
		return 8;
	}
	else if(strcmp(letra,"J")==0){
		return 9;
	}
	else if(strcmp(letra,"K")==0){
		return 10;
	}
	else if(strcmp(letra,"L")==0){
		return 11;
	}
	else if(strcmp(letra,"M")==0){
		return 12;
	}
	else if(strcmp(letra,"N")==0){
		return 13;
	}
	else if(strcmp(letra,"O")==0){
		return 14;
	}
	else if(strcmp(letra,"P")==0){
		return 15;
	}
	else if(strcmp(letra,"Q")==0){
		return 16;
	}
	else if(strcmp(letra,"R")==0){
		return 17;
	}
	else if(strcmp(letra,"S")==0){
		return 18;
	}
	else if(strcmp(letra,"T")==0){
		return 19;
	}
	else if(strcmp(letra,"U")==0){
		return 20;
	}
	else if(strcmp(letra,"V")==0){
		return 21;
	}
	else if(strcmp(letra,"W")==0){
		return 22;
	}
	else if(strcmp(letra,"X")==0){
		return 23;
	}
	else if(strcmp(letra,"Y")==0){
		return 24;
	}
	else if(strcmp(letra,"Z")==0){
		return 25;
	}
	else{
		return -1;
	}
}
