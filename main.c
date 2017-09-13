#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char **argv) {
	/* i: nombre archivo
	   n: numero de procesos
	   c: cantidad de caracteres
	   p: cadena a buscar
	   d: bandera que indica si mostrar por pantalla
	*/

	char* iName;
	int nCant = 0;
	int cCant = 0;
	char* pCadena;
	int dFlag = 0;
	int index;
	int c;

	opterr = 0;
	printf("prueba\n");

	while ((c = getopt (argc, argv, "i:n:c:p:d")) != -1) {
		switch (c) {
		case 'i':
			iName = optarg;
			break;
		case 'n':
			sscanf(optarg, "%d", &nCant);
			break;
		case 'c':
			sscanf(optarg, "%d", &cCant);
			break;
		case 'p':
			pCadena = optarg;
			break;
		case 'd':
			dFlag = 1;
			break;
		case '?':
			if (optopt == 'i' || optopt == 'n' || optopt == 'c' || optopt == 'p') {
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
	printf ("iName = %s, nCant = %d, cCant = %d, pCadena = %s, dFlag = %d\n", iName, nCant, cCant, pCadena, dFlag);

	for (index = optind; index < argc; index++) {
		printf ("Non-option argument %s\n", argv[index]);
	}
	return 0;
}
