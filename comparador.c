#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int verificarCadena(char* linea, int pos, char* cadena) {
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

	FILE* fp = fopen(iName, "r");
	char nombreArchivo[128] = "rc_";
	strcat(nombreArchivo, pCadena);
	strcat(nombreArchivo, "_");
	char buffer[16];
	sprintf(buffer, "%d", dProceso);
	printf("paso buffer\n");
	strcat(nombreArchivo, buffer);
	strcat(nombreArchivo, ".txt");
	FILE *fpOut = fopen(nombreArchivo, "w");
	fseek(fp, cPosicion, SEEK_SET);
	char linea[256];
	int lineas = lCantidad;

	//printf("paso archivo\n");

	while (lineas != 0) {
		fscanf(fp, "%s", linea);
		fprintf(fpOut, "%s", linea);
		if (verificarLinea(linea, pCadena)) {
			fprintf(fpOut, "    SI\n");
		}
		else {
			fprintf(fpOut, "    NO\n");
		}
		lineas--;
	}
	//printf("Termine %d\n",dProceso);
	exit(0);
	return 0;
}

