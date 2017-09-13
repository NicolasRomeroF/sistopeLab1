#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int verificarCadena(char* cadenaAux, char* cadena){
	int cont=0;
	char c=0;
	while(c!='\0'){
		if(cadenaAux[cont]!=cadena[cont]){
			return 0;
		}
		cont++;
	}
	return 1;
}
int verificarLinea(char* linea, char* cadena){
	int cont=0;
	while(linea[cont]!='\0'){
		if(verificarCadena(linea,cadena)){
			return 1;
		}
		else{
			cont++;
		}
	}
}


int main(int argc, char **argv){
	char* file = argv[0];
	FILE *fp = fopen(file,"r");
	char* sPos = argv[1];
	int pos = atoi(sPos);
	char *cadena;
	strcpy(cadena,argv[2]);
	char* sLineas = argv[3];
	int lineas=atoi(sLineas);
	char* ID= argv[4];
	char *nombreArchivo="rc_";
	strcat(nombreArchivo,cadena);
	strcat(nombreArchivo,ID);
	strcat(nombreArchivo,".txt");
	FILE *fpOut=fopen(nombreArchivo,"w");
	fseek(fp,pos,SEEK_SET);
	int contador=0;
	char * linea;
	while(lineas!=0){
		fscanf(fp,"%s",linea);
		fprintf(fpOut,"%s",linea);
		if(verificarLinea(linea,cadena)){
			fprintf(fpOut,"    SI\n");
		}
		else{
			fprintf(fpOut,"    NO\n");
		}
		lineas--;
	}
}

