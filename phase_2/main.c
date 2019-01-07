#include "readelf.h"

int findSymbole(char* nom, symb* symbList, int tailleSymbList){
  int i;
  for(i = 0; i < tailleSymbList; i++){
    if(strcomp(symbList[i].nom,nom)){
      return symbList[i].valeur
    }
  }
}

int main(int argc, char const *argv[]) {
  return 0;
}
