#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>


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
				fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
			}
			else if (isprint (optopt)) {
				fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
			}
			else {
				fprintf (stderr, "Caracter desconocido `\\x%x'.\n", optopt);

			}
			return 1;
		default:
			abort ();
		}

	}
	printf ("iName = %s, nCant = %d, cCant = %d, pCadena = %s, dFlag = %d\n", iName, nCant, cCant, pCadena, dFlag);

	for (index = optind; index < argc; index++) {
		printf ("Argumento no existente %s\n", argv[index]);
	}
	FILE* fp = fopen(iName, "r");
	int nLineas = 0;
	char aux[256];



	while (!feof(fp)) {
		fscanf(fp, "%s", aux);
		nLineas++;
	}

	int lineasPorProceso = nLineas / nCant;

	char buff1[16];
	char buff2[16];
	char buff3[16];

	
	sprintf(buff2,"%d",lineasPorProceso);


	pid_t pid_hijo, wpid;
	int status = 0;

	int i = 0;
	for (i = 0; i < nCant - 1; i++) {
		if ((pid_hijo = fork()) == 0) {
			sprintf(buff1,"%d",i*(cCant+1)*lineasPorProceso);
			sprintf(buff3,"%d",i);
			execl("comparador", "comparador", "-i", iName, "-c", buff1, "-p", pCadena, "-l", buff2, "-d", buff3, NULL);
		}
	}

	while ((wpid = wait(&status)) > 0);

	

	//printf("Termine main\n");
	
	return 0;
}
