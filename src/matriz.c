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


int main(){
	char *nombre = NULL;
	nombre = "B.txt";
	leerDimensiones(nombre,&n,&m);
	char *filas[n];
	tomarMatriz(nombre,filas);
	int matriz[n][m];
	rellenarMatriz(matriz,filas);
	imprimirMatriz(matriz);
	return 0;
}

void leerDimensiones(char *nombre,int *n, int *m){
	FILE* fichero;
	fichero = fopen(nombre,"r");
	if (fichero == NULL){
		//fputs("no existe tal matriz\n",strerr);
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
