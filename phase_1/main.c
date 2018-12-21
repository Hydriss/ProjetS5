#include "readelf.h"

int main(int argc, char * argv[]){
	int taille = 2000;
	int * tab;
	if(argc < 3){
		printf("il manque un nom de fichier");
	}
	char * file = NULL;

	if(argv[1][0] == '-' && argv[1][1] != 'x'){
		file = argv[2];
	}
	else{
		file = argv[3];
	}

	FILE *ptr = malloc(sizeof(FILE));
	ptr = fopen(file,"r");
	if (ptr==NULL){
		printf("Erreur fopen");
		return -1;
	}



	tab = malloc(sizeof(int)*(taille));
	if(lireFichier(tab,ptr, &taille)){
		return -1;
	}
	if(argv[1][0] == '-'){
		switch (argv[1][1]) {
			case 'h':
				afficherEntete(tab);
				break;
			case 'S' :
				afficherSection(tab);
				break;
			case 'x':
				afficherDetailSection(tab,argv[2]);
				break;
			case 's':
				afficherSymbole(tab);
				break;
			case 'r' :
				afficherRelocationTable(tab);
				break;
			default :
				afficherEntete(tab);
				afficherSection(tab);
		}
	} else {
		printf("erreur sur les parametres");
	}


	fclose(ptr);
	return 0;
}
