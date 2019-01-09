#include "relocation.h"

/*int findSymbole(char* nom, symb* symbList, int tailleSymbList){
  int i;
  for(i = 0; i < tailleSymbList; i++){
    if(strcmp(symbList[i].nom,nom)){
      return symbList[i].valeur;
    }
  }
}*/

int main(int argc, char const *argv[]) {
	int taille = 2000;
	int * tab;
	if(argc < 3){
		printf("il manque un nom de fichier");
	}

	FILE *ptr = malloc(sizeof(FILE));
	ptr = fopen(argv[1],"r");
	if (ptr==NULL){
		printf("Erreur fopen");
		return -1;
	}



	tab = malloc(sizeof(int)*(taille));
	if(lireFichier(tab,ptr, &taille)){
		return -1;
	}
	afficherSection(tab);
	tableToDelete(tab,&taille);
	afficherSection(tab);


  	return 0;
}
