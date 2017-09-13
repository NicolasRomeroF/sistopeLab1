#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int verificarCadena(char* cadenaAux, char* cadena) {
	int cont = 0;
	char c = 0;
	while (c != '\0') {
		if (cadenaAux[cont] != cadena[cont]) {
			return 0;
		}
		cont++;
	}
	return 1;
}

int verificarLinea(char* linea, char* cadena) {
	int cont = 0;
	while (linea[cont] != '\0') {
		if (verificarCadena(linea, cadena)) {
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
	printf ("iName = %s, cPosicion = %d, pCadena = %s, lCantidad = %d, dProceso = %d\n", iName, cPosicion, pCadena, lCantidad, dProceso);

	for (index = optind; index < argc; index++) {
		printf ("Non-option argument %s\n", argv[index]);
	}

	/*
	char* file = argv[0];
	FILE *fp = fopen(file, "r");
	char* sPos = argv[1];
	int pos = atoi(sPos);
	char *cadena;
	strcpy(cadena, argv[2]);
	char* sLineas = argv[3];
	int lineas = atoi(sLineas);
	char* ID = argv[4];
	char *nombreArchivo = "rc_";
	strcat(nombreArchivo, cadena);
	strcat(nombreArchivo, ID);
	strcat(nombreArchivo, ".txt");
	FILE *fpOut = fopen(nombreArchivo, "w");
	fseek(fp, pos, SEEK_SET);
	int contador = 0;
	char * linea;
	*/
	/*
	while (lineas != 0) {
		fscanf(fp, "%s", linea);
		fprintf(fpOut, "%s", linea);
		if (verificarLinea(linea, cadena)) {
			fprintf(fpOut, "    SI\n");
		}
		else {
			fprintf(fpOut, "    NO\n");
		}
		lineas--;
	}
	*/
}

