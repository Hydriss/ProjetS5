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
  int tab[10] = {0,1,2,3,4,5,6,7,8,9};
  int taille = 10;
  remplaceParZero(tab,0,9);
  for(int i = 0; i < taille;i++){
    printf("%d,",tab[i]);
  }
    printf("\n");
  return 0;
}
