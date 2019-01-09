#include "readelf.h"

int findSymbole(char* nom, symb* symbList, int tailleSymbList){
  int i;
  for(i = 0; i < tailleSymbList; i++){
    if(strcomp(symbList[i].nom,nom)){
      return symbList[i].valeur
    }
  }
}
int tableToDelete(int * tab){
	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));
	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	for (int i=0; i<nbEnTete; i++){
		if(strncmp(sheader[i].nom,".rel.",5) == 0){
			sheader[i]= sheader[i+1];
		}
	}
}
