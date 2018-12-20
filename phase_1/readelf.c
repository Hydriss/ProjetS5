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
} symb;

int lireFichier(int * tab, FILE * ptr, int * taille){
	char c;
	unsigned int i = 0;
	while (!feof(ptr)){
		c = fgetc(ptr);
		if(i >= *taille){
			*taille += 10;
			tab = realloc(tab, sizeof(int)*(*taille));
			if(tab == NULL){
				printf("erreur de reallocation");
				return 1;
			}
		}
		printf("%d : %x\n ",i,c);
		tab[i] = c;
		tab[i] = tab[i] & 0x000000ff;
		i++;
	}
	return 0;
}

void afficherEntete(int * tab){
	int i;
	printf("\nclass : ");
	for(i = 1; i <=3;i++){
		printf("%c",tab[i]);
	}
	switch (tab[4]) {
		case 0:
			printf("NONE");
			break;
		case 1:
			printf("32");
			break;
		case 2:
			printf("64");
			break;
		default :
			printf("invalid");
	}
	printf("\ndata : ");
	switch (tab[5]) {
		case 0:
			printf("dataNONE");
			break;
		case 1:
			printf("dataLSB");
			break;
		case 2:
			printf("dataMSB");
			break;
		default :
			printf("invalid");
	}
	printf("\n");
	printf("version : %d",tab[6]);
	printf("\n");
	printf("ABI : ");
	switch (tab[7]) {
		case 0:
			printf("UNIX System V");
			break;
		case 1:
			printf("HP-UX");
			break;
		case 2:
			printf("NetBSD");
			break;
		case 3:
			printf("Linux");
			break;
		case 6:
			printf("Sun Solaris");
			break;
		case 7:
			printf("IBM AIX");
			break;
		case 8:
			printf("SGI Irix");
			break;
		case 9:
			printf("FreeBSD");
			break;
		case 10:
			printf("Compaq TRU64");
			break;
		case 11:
			printf("Novell Modesto");
			break;
		case 12:
			printf("OpenBSD");
			break;
		case 64:
			printf("ARM EABI");
			break;
		case 97:
			printf("ARM");
			break;
		case 255:
			printf("Standalone");
			break;
		default:
			printf("???");

	}
	printf("\n");
	printf("Version ABI : 0x%x\n",tab[8]);
	printf("type : ");
	switch (tab[16]) {
		case 0:
			printf("not file type");
			break;
		case 1:
			printf("relocatable file");
			break;
		case 2:
			printf("executable file");
			break;
		case 3:
			printf("shared object file");
			break;
		case 4:
			printf("corefile");
			break;
		case 0xff00:
			printf("Processor-scpecifique");
			break;
		case 0xffff:
			printf("Processor-scpecifique");
			break;
		default :
			printf("???");
	}
	printf("\n");
	printf("type machine: ");
	switch (tab[18]) {
		case 0:
			printf("aucune");
			break;
		case 2:
			printf("SPARC");
			break;
		case 3:
			printf("intel 80386");
			break;
		case 4:
			printf("Motorola 68000");
			break;
		case 7:
			printf("Intel i860");
			break;
		case 8:
			printf("MIPS I");
			break;
		case 19:
			printf("Intel i960");
			break;
		case 20:
			printf("PowerPC");
			break;
		case 40:
			printf("ARM");
			break;
		case 50:
			printf("Intel IA64");
			break;
		case 62:
			printf("x64");
			break;
		default :
			printf("???");
	}
	printf("\n");
	printf("version : %s",(!tab[20])? "Aucune" : "Actuelle");
	printf("\n");
	printf("adresse d'entree : 0x%x\n",((tab[24] << 0) + (tab[25] << 8) + (tab[26] << 16) + (tab[27] << 24)));
	int offsetprg = (tab[28] << 0) + (tab[29] << 8) + (tab[30] << 16) + (tab[31] << 24);
	printf("offset des entetes de programme : %d\n",offsetprg);
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	printf("offset des entetes de sections : %d\n",offsetsec);
	printf("fanions : 0x%x\n",((tab[36] << 0) + (tab[37] << 8) + (tab[38] << 16) + (tab[39] << 24)));
	printf("taille de cette entete : %d\n",((tab[40] << 0) + (tab[41] << 8)));
	printf("taille de l'entete du programme : %d\n",((tab[42] << 0) + (tab[43] << 8)));
	printf("nombre d'entete du programme : %d\n",((tab[44] << 0) + (tab[45] << 8)));
	printf("taille des entetes de sections : %d\n",((tab[46] << 0) + (tab[47] << 8)));
	printf("nombres d'entetes de sections : %d\n",((tab[48] << 0) + (tab[49] << 8)));
	printf("table d'index des chaines d'entete de sections : %d\n",((tab[50] << 0) + (tab[51] << 8)));
}

void afficherEnTeteSection(char *nom,int type,char * flags,int adresse,int off,int size,int link,int info,int addralign,int entsize){
	printf("\t-nom : %s\n",nom);
	printf("\t-type : ");
	switch (type) {
		case  0 :
			printf("NULL");
			break;
		case  1 :
			printf("PROGBITS" );
			break;
		case  2:
			printf("SYMTAB");
			break;
		case  3 :
			printf("STRTAB");
			break;
		case  4 :
			printf("RELA" );
			break;
		case  5 :
			printf("HASH");
			break;
		case  6 :
			printf("DYNAMIC" );
			break;
		case  7 :
			printf("NOTE");
			break;
		case  8 :
			printf("NOBITS" );
			break;
		case  9:
			printf("REL");
			break;
		case  10 :
			printf("SHLIB" );
			break;
		case  11 :
			printf("DYNSYM" );
			break;
		case  0x70000000 :
			printf("LOPROC");
			break;
		case   0x7fffffff  :
			printf("HIPROC" );
			break;
		case  0x80000000:
			printf("LOUSER" );
			break;
		case  0xffffffff :
			printf("HIUSER" );
			break;
		case 0x70000003:
			printf("ARM_ATTRIBUTES" );
			break;
		default :
			printf("type inconnu" );
	}
	printf("\n\t-flags : %s",flags);
	printf("\n");
	printf("\t-adresse: %x\n\t-off: %x\n\t-size: %x\n\t-link: %d\n\t-info: %d\n\t-addralign: %d\n\t-entsize: %d\n",adresse,off,size,link,info,addralign,entsize);
}

char * getnom(int offset,int offset_nom,int * tab){
	char * nom;
	int offset_C = offset + offset_nom;

	nom = malloc(sizeof(char)*50);
	int i=0;
	while (tab[offset_C+i]!=0){
		nom[i] = tab[offset_C+i];
		i++;
	}
	return nom;
}

char * readFlags(int flags) {
	char * res = malloc(sizeof(char)*16);
	int i = 0;
	if((flags & 0x01) != 0){
		res[i] = 'W';
		i++;
	}
	if((flags & 0x02) != 0){
		res[i] = 'A';
		i++;
	}
	if((flags & 0x04) != 0){
		res[i] = 'X';
		i++;
	}
	if((flags & 0x10) != 0){
		res[i] = 'M';
		i++;
	}
	if((flags & 0x20) != 0){
		res[i] = 'S';
		i++;
	}
	if((flags & 0x40) != 0){
		res[i] = 'I';
		i++;
	}
	if((flags & 0x80) != 0){
		res[i] = 'L';
		i++;
	}
	if((flags & 0x100) != 0){
		res[i] = 'O';
		i++;
	}
	if((flags & 0x200) != 0){
		res[i] = 'G';
		i++;
	}
	if((flags & 0x400) != 0){
		res[i] = 'T';
		i++;
	}
	if((flags & 0x0ff00000) != 0){
		res[i] = 'K';
		i++;
	}
	if((flags & 0xf0000000) != 0){
		res[i] = 'P';
		i++;
	}
	if((flags & 0x40000000) != 0){
		res[i] = 'D';
		i++;
	}
	if((flags & 0x80000000) != 0){
		res[i] = 'E';
		i++;
	}
	return res;
}


void getEnTeteSection(sh * sheader, int * tab,int nbEnTete,int offsetsec,int e_shstrndx){int i = offsetsec;
	int j;
	int offset_Sect = 0 ;
	for(j=0;j<nbEnTete;j++){
		sheader[j].nom = malloc(sizeof(char)*50);
		sheader[j].nom_off = ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i+=4;
		sheader[j].type= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].flags= readFlags(((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24)));
		i += 4;
		sheader[j].adresse= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].off= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].size= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].link= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].info= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].addralign= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader[j].entsize= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;

		if (j==e_shstrndx){
			offset_Sect = sheader[j].off;
		}


	}
	for(int k = 0; k < nbEnTete; k++){
		sheader[k].nom = getnom(offset_Sect,sheader[k].nom_off,tab);
	}
}


void afficherSection(int * tab){
	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));
	printf("\n Il y a %d en-tetes de section, debutant à l'adresse de decalage 0x%x\n", nbEnTete, offsetsec);
	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);

	for(int k = 0; k < nbEnTete; k++){
		printf("nom_offset : %d\n", sheader[k].nom_off);
		afficherEnTeteSection(sheader[k].nom,sheader[k].type,sheader[k].flags,sheader[k].adresse,sheader[k].off,sheader[k].size,sheader[k].link,sheader[k].info,sheader[k].addralign,sheader[k].entsize);

	}

}

int getNumSection(char * para, sh * sheader, int nbEnTete){
	int res = atoi(para);
	if(res == 0){
		for(int i = 0; i < nbEnTete; i++){
			if(!strcmp(sheader[i].nom,para)){
				res = i;
				break;
			}
		}
	}
	return res;
}

void afficherDetailSection(int * tab, char * para){
	int debut_section;
	int i;
	int fin_section;
	int size;
	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));

	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	int section = getNumSection(para, sheader, nbEnTete);
	debut_section= sheader[section].off;
	size= sheader[section].size;
	i = debut_section;
	fin_section=size+debut_section;
	printf("-> %8x %8x",debut_section,size);

	printf("Vidange hexadecimal de la section \"%s\" : \n",sheader[section].nom);
	int tailleRes = (fin_section-i)*2+2;
	char * res = malloc(sizeof(char)*(tailleRes));
	while(i<fin_section){
		tab[i] = tab[i];
		char * tmp = malloc(sizeof(char)*2);
		sprintf(tmp,"%2X",tab[i]);
		res = strcat(res,tmp);
		//printf("%s",res);
		i++;
	}
	for(i = 0; i < tailleRes; i++){
		if(i%32 == 0){
			printf("\n");
		}else if(i%8 == 0){
			printf(" ");
		}
		if(res[i] == ' '){
			res[i] = '0';
		}
		printf("%c",res[i]);
	}
	printf("\n");
}

char * getSymboleType(int type){
	switch (type) {
		case 0:
					return("NOTYPE");
					break;
		case 1:
					return("OBJECT");
					break;
		case 2:
					return("FUNC");
					break;
		case 3:
					return("SECTION");
					break;
		case 4:
					return("FILE");
					break;
		case 13:
					return("LOPROC");
					break;
		case 15:
					return("HIPROC");
					break;
		default:
					return("NOTYPE");
	};
}

char * getSymboleLien(int lien){
	switch (lien) {
		case 0:
					return("LOCAL");
					break;
		case 1:
					return("GLOBAL");
					break;
		case 2:
					return("WEAK");
					break;
		case 13:
					return("LOPROC");
					break;
		case 15:
					return("HIPROC");
					break;
		default:
					return("lien non defini");
	};
}

void getContenueSection(symb * symboles, int * tab, int offsetNom, int debut_symtab, int size, int fin_symtab){
	int i = debut_symtab;
	while(i<fin_symtab){
		//printf("%d\n",((i - debut_symtab)/16));
		symboles[(i-debut_symtab)/16].idNom = ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		symboles[(i-debut_symtab)/16].nom = getnom(offsetNom,symboles[(i-debut_symtab)/16].idNom,tab);
		i += 4;
		symboles[(i-debut_symtab)/16].valeur = (tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24);
		i += 4;
		symboles[(i-debut_symtab)/16].tail = (tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24);
		i +=4;
		symboles[(i-debut_symtab)/16].type = tab[i] & 0x0F;
		symboles[(i-debut_symtab)/16].lien = (tab[i] & 0xF0)>>4;
		i +=2;
		symboles[(i-debut_symtab)/16].ndx = tab[i];
		i +=1;
		i +=1;
	}
}

void afficherSymbole(int * tab){
	int nb_entree;
	int debut_symtab;
	int fin_symtab;
	int strTabId;
	int offsetNom;


	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));

	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	int section;
	for(int j = 0; j < nbEnTete; j++){
		if(!strcmp(sheader[j].nom,".symtab")){
			section = j;
		}
		if(!strcmp(sheader[j].nom,".strtab")){
			strTabId = j;
		}
	}
	offsetNom = sheader[strTabId].off;
	printf("%d\n",section);
	debut_symtab=sheader[section].off;
	int size=sheader[section].size;
	fin_symtab=size+debut_symtab;

	symb symboles[size];
	getContenueSection(symboles, tab, offsetNom, debut_symtab, size, fin_symtab);
	for(int i = 0; i < (size/16); i++){
		printf("\n%d : \n",i);
		printf("\tnom : \t\t%s",symboles[i].nom);
		printf("\n\tvaleur : \t%x",symboles[i].valeur);
		printf("\n\ttail : \t\t%d",symboles[i].tail);
		printf("\n\ttype : \t\t%s",getSymboleType(symboles[i].type));
		printf("\n\tlien : \t\t%s",getSymboleLien(symboles[i].lien));
		printf("\n\tndx : \t\t%d",symboles[i].ndx);
		printf("\n\tvis : \t\tDEFAULT");
	}
	printf("\n");

	nb_entree = size/16;
	printf("Table des symboles \".symtab\" contient %d entrees\n",nb_entree);
}


void test(int * tab){
	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));

	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	for(int j = 0; j < nbEnTete; j++){
		if(strncmp(sheader[j].nom,".rel.",5) == 0){
			printf("nom : %s\n",sheader[j].nom);
			afficherDetailSection(tab,sheader[j].nom);
		}
	}
}

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
			case 't' :
				test(tab);
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
