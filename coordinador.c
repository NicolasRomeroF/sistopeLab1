#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>


/*Funcion que copia los datos del archivo comparador en el archivo final
  junto con su resultado

  Entradas: Archivo original, archivo final, archivo parcial, cantidad de caracteres
  Salidas:  void
  */
void copiarArchivo(FILE* original, FILE* archivoC, FILE* archivoP, int cCant)
{
	
	char* linea = malloc(sizeof(char) * (cCant+10));
	char resultado[8];
	while (feof(archivoP) != 1)
	{
		fscanf(original,"%s",linea);
		fprintf(archivoC,"%s",linea);
		fscanf(archivoP, "%s", resultado);
		fprintf(archivoC,"    %s\n",resultado);

	}
	free(linea);
}

/*Funcion que junta los archivos parciales en un archivo final

  Entrada: Archivo original, cantidad total de archivos, cadena a encontrar, cantidad de caracteres
  Salida: void
  */
void juntarArchivos(FILE* original, int cantArchivos, char* pCadena, int cCant)
{
	rewind(original);
	int i;
	char buffer[16];
	char nombreC[128] = "rc_";
	strcat(nombreC, pCadena);
	strcat(nombreC, ".txt");
	FILE* archivoC = fopen (nombreC, "w");
	if (archivoC == NULL)
	{
		printf("ERROR: No se pudo crear archivo final de salida");
		return;
	}

	//Se recorren los archivos parciales y se agregan al archivo final
	for (i = 0; i < cantArchivos-1; i++)
	{
		char nombreP[128] = "rp_";
		strcat(nombreP, pCadena);
		strcat(nombreP, "_");
		sprintf(buffer, "%d", i);
		strcat(nombreP, buffer);
		strcat(nombreP, ".txt");
		printf("%s\n",nombreP);
		FILE* archivoP = fopen(nombreP, "r");
		if (archivoP == NULL)
		{
			printf("ERROR al abrir archivo parcial");
			return;
		}
		copiarArchivo(original, archivoC,archivoP,cCant);
		fclose(archivoP);
	}
	fclose(archivoC);
}

int main(int argc, char **argv) {
	/* i: nombre archivo
	   n: numero de procesos
	   c: cantidad de caracteres
	   p: cadena a buscar
	   d: bandera que indica si mostrar por pantalla
	*/

	//Aqui declaramos las variables a recibir por medio de optarg
	char* iName;
	int nCant = 0;
	int cCant = 0;
	char* pCadena;
	int dFlag = 0;
	int index;
	int c;

	opterr = 0;

	//Con este ciclo se obtienen los argumentos ingresados por consola y se asignan
	//a las variables anteriormente declaradas
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

		//Caso en que se ingrese una opcion desconocida
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

	//Se muestran por pantalla los datos ingresados.
	printf ("iName = %s, nCant = %d, cCant = %d, pCadena = %s, dFlag = %d\n", iName, nCant, cCant, pCadena, dFlag);

	//Se muestra mensaje en caso de ingresar un argumento que no existe
	for (index = optind; index < argc; index++) {
		printf ("Argumento no existente %s\n", argv[index]);
	}

	//Se abre archivo a leer
	FILE* fp = fopen(iName, "r");

	//Se muestrar en caso de no encontrar
	if(fp==NULL){
		printf("El archivo no existe");
		return 0;
	}
	int nLineas = 0;
	char aux[256];


	//Se cuenta el total de lineas para luego calcular la cantidad de lineas
	//por proceso
	while (!feof(fp)) {
		fscanf(fp, "%s", aux);
		nLineas++;
	}

	//Se calcula la cantidad de lineas a leer por proceso
	int lineasPorProceso = nLineas / nCant;

	//Dado que los argumentos deben ser strings, se declaran estas variables que 
	//contendran los argumentos a ingresar para llamar a los procesos comparadores
	char buff1[16];
	char buff2[16];
	char buff3[16];

	
	sprintf(buff2,"%d",lineasPorProceso);


	pid_t pid_hijo, wpid;
	int status = 0;

	int i = 0,auxCant;

	//En este ciclo for se crean los procesos hijos y se llama execl para ejecutar otro codigo
	//Se le pasan los parametros correspondientes
	for (i = 0; i < nCant - 1; i++) {
		if ((pid_hijo = fork()) == 0) {
			sprintf(buff1,"%d",i*(cCant+1)*lineasPorProceso);
			sprintf(buff3,"%d",i);
			execl("comparador", "comparador", "-i", iName, "-c", buff1, "-p", pCadena, "-l", buff2, "-d", buff3, NULL);
		}
		auxCant=i;
	}

	//El ultimo proceso se crea aparte en caso de que la cantidad de lineas
	//no sea divisible en la cantidad de procesos
	if((pid_hijo = fork()) == 0){
		sprintf(buff1,"%d",(auxCant+1)*(cCant+1)*lineasPorProceso);
		sprintf(buff2,"%d",nLineas-lineasPorProceso*(nCant-1));
		sprintf(buff3,"%d",(auxCant+1));
		execl("comparador", "comparador", "-i", iName, "-c", buff1, "-p", pCadena, "-l", buff2, "-d", buff3, NULL);
	}

	//Se espera que todos los procesos hijos terminen para luego juntar los archivos
	while ((wpid = wait(&status)) > 0);

	//Se juntan los archivos
	juntarArchivos(fp,nCant,pCadena,cCant);

	fclose(fp);

	//printf("Termine main\n");
	
	return 0;
}
