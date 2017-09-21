#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int verificarCadena(char* linea, int pos, char* cadena) {
	/*
	  Entradas:
	  	linea: porción de línea del archivo
	  	pos: posicion de lector de la linea
	  	cadena: arreglo de chars a encontrar
	  Descripción:
	  	Esta función se encarga de buscar si se encuentra o no en una
	  	porción de línea un arreglo de chars
	  Salidas:
	  	Devuelve 1 si se encontró la cadena
	  	Devuelve 0 en caso contrario
	*/
	int cont = 0;
	int contPos = cont + pos;
	char cLinea = linea[cont];
	char cCadena = cadena[cont];
	while (cCadena != '\0') {
		if (cLinea == '\0')
		{
			return 0;
		}

		else if (linea[contPos] != cadena[cont]) {
			return 0;
		}
		cont++;
		contPos++;
		cLinea = linea[contPos];
		cCadena = cadena[cont];
	}
	return 1;
}

int verificarLinea(char* linea, char* cadena) {
	/*
	  Entradas:
	  	linea: línea del archivo
	  	cadena: arreglo de chars a encontrar
	  Descripción:
	  	Esta función se encarga de manejar el valor del contador
	  	de posición de la línea y llamar a la funcion verificarCadena
	  Salidas:
	  	Devuelve 1 si se encontró la cadena
	  	Devuelve 0 en caso contrario
	*/
	int cont = 0;
	while (linea[cont] != '\0') {
		if (verificarCadena(linea, cont, cadena)) {
			return 1;
		}
		else {
			cont++;
		}
	}
	return 0;
}


int main(int argc, char **argv) {
	/* i: nombre archivo
	   c: posicion cursor
	   p: cadena a encontrar
	   l: cantidad de lineas
	   d: identificador
	*/
	int index;
	int c;

	opterr = 0;
	/*
		En las siguientes variables se guarda el valor
		de cada una de las entradas obtenidas por la función getopt
	*/

	char* iName;
	int cPosicion;
	char* pCadena;
	int lCantidad;
	int dProceso;


	while ((c = getopt (argc, argv, "i:c:p:l:d:")) != -1) {
		switch (c) {
		case 'i':
			iName = optarg;
			break;
		case 'c':
			sscanf(optarg, "%d", &cPosicion);
			break;
		case 'p':
			pCadena = optarg;
			break;
		case 'l':
			sscanf(optarg, "%d", &lCantidad);
			break;
		case 'd':
			sscanf(optarg, "%d", &dProceso);
			break;
		case '?':
			if (optopt == 'i' || optopt == 'c' || optopt == 'p' || optopt == 'l' || optopt == 'd') {
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			}
			else if (isprint (optopt)) {
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			}
			else {
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

			}
			return 1;
		default:
			abort ();
		}

	}

	for (index = optind; index < argc; index++) {
		printf ("Non-option argument %s\n", argv[index]);
	}

	FILE* fp = fopen(iName, "r");
	if (fp == NULL) {
		printf("El archivo no existe");
		return 0;
	}
	char nombreArchivo[128] = "rp_";
	strcat(nombreArchivo, pCadena);
	strcat(nombreArchivo, "_");
	char buffer[16];
	sprintf(buffer, "%d", dProceso);
	strcat(nombreArchivo, buffer);
	strcat(nombreArchivo, ".txt");
	//Creación archivo temporal donde s eguardan los resultados
	FILE *fpOut = fopen(nombreArchivo, "w");
	if (fpOut == NULL) {
		printf("El archivo no se pudo crear");
		return 0;
	}
	fseek(fp, cPosicion, SEEK_SET);
	char linea[256];
	int lineas = lCantidad;

	//Se comienza la lectura del archivo
	while (lineas != 0) {
		fscanf(fp, "%s", linea);
		//fprintf(fpOut, "%s", linea);
		if (verificarLinea(linea, pCadena)) {
			fprintf(fpOut, "SI\n");
		}
		else {
			fprintf(fpOut, "NO\n");
		}
		lineas--;
	}


	fseek(fpOut, -1, SEEK_END);
	ftruncate(fileno(fpOut), ftell(fpOut));
	fclose(fp);
	fclose(fpOut);

	exit(0);
	return 0;
}

