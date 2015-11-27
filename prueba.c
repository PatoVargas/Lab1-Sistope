#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variables globales

int n;
int m;

//cabeceras
void leerDimensiones(char *nombre,int *n, int *m);
void tomarMatriz(char *nombre,char *fila[]);
void rellenarMatriz(int matriz[][m], char *filas[]);
void imprimirMatriz(int matriz[][m]);

int main(int argc, char *argv[])
{
	int estado = 0;	
	char comando[20];
	FILE *archivo;
	int primerArgumento,segundoArgumento,tercerArgumento;
	char separador[] = " \n";
	char *trozo = NULL;
	int matrizA[n][m];
	int matrizB[n][m];		
	while(estado == 0){
		char *aux = NULL ;
		char *aux2 = NULL ;	
		char *aux3 = NULL;
		fgets(comando, 20, stdin);
        	trozo = strtok( comando, separador);              
		primerArgumento = 0;
		segundoArgumento = 0;
		tercerArgumento = 0;		
		while( trozo != NULL ) {
			aux3 = trozo;
			if(segundoArgumento == 1){
				aux2 = trozo;		
			}
			if(primerArgumento == 0){	
				aux = trozo;					
			}
			trozo = strtok( NULL, separador);
			segundoArgumento++;
			primerArgumento++;
	    	}
		printf("aux: %s -\n",aux);
		printf("aux2: %s -\n",aux2);
		printf("aux3: %s -\n",aux3);
		if(strncmp(aux,"load",4)==0){
                        aux3 = strtok(aux3,"\"");
			leerDimensiones(aux3,&n,&m);
			char *filas[n];
			tomarMatriz(aux3,filas);			
			if(strncmp(aux2,"A",1)==0){
				rellenarMatriz(matrizA,filas);
			}
			else if(strncmp(aux2,"B",1)==0){				
				rellenarMatriz(matrizB,filas);
			}		
		}
		else if(strncmp(aux,"save",4)==0){
			printf("GUARDAR\n");
		}
		else if(strncmp(aux,"print",5)==0){
                        aux2 = strtok( aux2, " ");			
			if(strncmp(aux2,"A",1)==0){
				imprimirMatriz(matrizA);
			}
			else if(strncmp(aux2,"B",1)==0){
				imprimirMatriz(matrizB);
			}
			else{
				printf("%s NO!\n",aux2);			
			}
		}
		else if(strncmp(aux,"clear",5) == 0){
			printf("limpiando la matriz %s\n",aux2);		
		}
		else if(strncmp(aux,"exit",4) == 0){
			return 0;		
		}	
		else{
			printf("Comando invalido\n");
		}	      	
	}
	return 0;
}

void leerDimensiones(char *nombre,int *n, int *m){
	FILE* fichero;
	fichero = fopen(nombre,"r");
	if (fichero == NULL){
		printf("no existe tal matriz\n");
		exit(1);	
	}
	else{
		fscanf(fichero,"%d\n",n);
		fscanf(fichero,"%d\n",m);
	}
	fclose(fichero);
}

void tomarMatriz(char *nombre,char *fila[]){
	FILE* fichero;
	int cont = 0;
	char linea[255];
	fichero = fopen(nombre,"r");
	if (fichero == NULL){
		//fputs("no existe tal matriz\n",strerr);
		exit(1);	
	}
	else{
		fgets(linea,255,fichero);
		fgets(linea,255,fichero);
		while(!feof(fichero)){
			fila[cont] = (char *)malloc(100*sizeof(char));
			fgets(linea,255,fichero);
			strcpy(fila[cont],linea);
			cont++;
		}
	}
	fclose(fichero);
}


void rellenarMatriz(int matriz[][m], char*array[]){
	int i = 0;
	int j = 0;
	char *token = NULL;
	int cont = 0;
	while(cont < n){
		token = strtok(array[cont]," ");
		matriz[i][j] = atoi(token);
		j++;
		while ((token = strtok(NULL," \n")) != NULL) {
			matriz[i][j] = atoi(token);
			j++;
			
		}
		
		i++;
		j = 0;
		cont++;
	}
	
}

void imprimirMatriz(int matriz[][m]){
	int i = 0;
	int j = 0;
	for (i = 0; i < n;i++){
		for(j=0;j<m;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}
