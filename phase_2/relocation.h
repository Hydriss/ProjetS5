#ifndef __RELOCATION_H__
#define __RELOCATION_H__
#include "../phase_1/readelf.h"

void tableToDelete(int * tab,int * taille);
int decoupeTab(int * tab, int tailleTab, int offset, int tailleDecoupe, int numeroSection);
void remplaceParZero(int * tab, int offset, int tailleRemplace);
void ecrireInt(int * tab, int index, int a);

#endif
