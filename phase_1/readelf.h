#ifndef __READELF_H__
#define __READELF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char * nom;
	int nom_off;
	int type;
	char * flags;
	int adresse;
	int off;
	int size;
	int link;
	int info;
	int addralign;
	int entsize;
}sh;

typedef struct {
	int idNom;
	char * nom;
	int valeur;
	int tail;
	int type;
	int lien;
	int ndx;
}symb;

void afficherRelocationTable(int * tab);

void afficherSymbole(int * tab);

void getContenueSection(symb * symboles, int * tab, int offsetNom, int debut_symtab, int size, int fin_symtab);

char * getSymboleLien(int lien);

char * getSymboleType(int type);

void afficherDetailSection(int * tab, char * para);

void DetailSection(int * tab, char * para, int * debut, int * fin);

int getNumSection(char * para, sh * sheader, int nbEnTete);

void afficherSection(int * tab);

void getEnTeteSection(sh * sheader, int * tab,int nbEnTete,int offsetsec,int e_shstrndx);

char * readFlags(int flags);

char * getnom(int offset,int offset_nom,int * tab);

void afficherEnTeteSection(char *nom,int type,char * flags,int adresse,int off,int size,int link,int info,int addralign,int entsize);

void afficherEntete(int * tab);

int lireFichier(int * tab, FILE * ptr, int * taille);

#endif
