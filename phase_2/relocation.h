#ifndef __RELOCATION_H__
#define __RELOCATION_H__
#include "../phase_1/readelf.h"

int tableToDelete(int * tab);
int decoupeTab(int * tab, int tailleTab, int offset, int tailleDecoupe);
void remplaceParZero(int * tab, int offset, int tailleRemplace);

#endif
