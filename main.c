#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


int main(int argc, char **argv){
	char* aName;
  	int pCant = 0;
  	int cCant;
  	char* sCadena;
  	int fFlag=0;
  	int index;
  	int c;

  	opterr = 0;


  	while ((c = getopt (argc, argv, "a:p:c:s:f")) != -1){
    		switch (c){
      			case 'a':
        			aName = optarg;
        			break;
      			case 'p':
				sscanf(optarg, "%d", &pCant);
				break;
      			case 'c':
				sscanf(optarg, "%d", &cCant);
				break;
			case 's':
				sCadena =optarg;
				break;
			case 'f':
				fFlag = 1;
				break;
      			case '?':
        			if (optopt == 'c' || optopt == 'a' || optopt == 'p' || optopt == 's'){
          				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				}
        			else if (isprint (optopt)){
          				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
          			}
        			else{
          				fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        				
				}
				return 1;
      			default:
        			abort ();
      		}

	}
  	printf ("aName = %s, pCant = %d, cCant = %d, sCadena = %s, fFlag = %d\n",aName, pCant, cCant, sCadena, fFlag);

  	for (index = optind; index < argc; index++){
    		printf ("Non-option argument %s\n", argv[index]);
	}
  	return 0;
}
