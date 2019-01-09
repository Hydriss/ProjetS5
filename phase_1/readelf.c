#include "readelf.h"


int lireFichier(int * tab, FILE * ptr, int * taille){
	char c;
	unsigned int i = 0;
	while (!feof(ptr)){
		c = fgetc(ptr);
		if(i >= *taille){
			*taille *= 2;
			tab = realloc(tab, sizeof(int)*(*taille));
			if(tab == NULL){
				printf("erreur de reallocation");
				return 1;
			}
		}
		//printf("%d : %x\n ",i,c);
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
	printf("%16s  ",nom);
	switch (type) {
		case  0 :
			printf("NULL          ");
			break;
		case  1 :
			printf("PROGBITS      ");
			break;
		case  2:
			printf("SYMTAB        ");
			break;
		case  3 :
			printf("STRTAB        ");
			break;
		case  4 :
			printf("RELA          ");
			break;
		case  5 :
			printf("HASH          ");
			break;
		case  6 :
			printf("DYNAMIC       ");
			break;
		case  7 :
			printf("NOTE          ");
			break;
		case  8 :
			printf("NOBITS        ");
			break;
		case  9:
			printf("REL           ");
			break;
		case  10 :
			printf("SHLIB         ");
			break;
		case  11 :
			printf("DYNSYM        ");
			break;
		case  0x70000000 :
			printf("LOPROC        ");
			break;
		case   0x7fffffff  :
			printf("HIPROC        ");
			break;
		case  0x80000000:
			printf("LOUSER        ");
			break;
		case  0xffffffff :
			printf("HIUSER        ");
			break;
		case 0x70000003:
			printf("ARM_ATTRIBUTES");
			break;
		default :
			printf("type inconnu  ");
	}
	printf("   %3s ",flags);
	printf("%8x %8x %4x %4d %4d      %4d      %4d\n",adresse,off,size,link,info,addralign,entsize);
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
	free(nom);
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
	free(res);
}


void getEnTeteSection(sh * sheader, int * tab,int nbEnTete,int offsetsec,int e_shstrndx){
	int i = offsetsec;
	int j;
	int offset_Sect = 0;
	for(j=0;j<nbEnTete;j++){
		sheader[j].offset_debutligne = i;
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
			printf("%d\n",offset_Sect );
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
	printf("e_shstrndx : %d\n",e_shstrndx );
	printf("\n Il y a %d en-tetes de section, debutant à l'adresse de decalage 0x%x\n", nbEnTete, offsetsec);
	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);

	printf("NUM\t        NOM  TYPE           FLAGS  ADRESSE   OFFSET SIZE LINK INFO ADDRALIGN   ENTSIZE\n");
	for(int k = 0; k < nbEnTete; k++){
		//printf("\nnom_offset : %d\n", sheader[k].nom_off);
		printf("[%d]",k );
		afficherEnTeteSection(sheader[k].nom,sheader[k].type,sheader[k].flags,sheader[k].adresse,sheader[k].off,sheader[k].size,sheader[k].link,sheader[k].info,sheader[k].addralign,sheader[k].entsize);
		free(sheader[k].nom);
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

void DetailSection(int * tab, char * para, int * debut, int * fin) {
	int debut_section;
	int size;
	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));

	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	int section = getNumSection(para, sheader, nbEnTete);
	debut_section= sheader[section].off;
	size= sheader[section].size;
	*debut = debut_section;
	*fin = size+debut_section;
}

// uint16_t lisHalf(int *tab, int pos) {
// 	return ((int) tab[pos])
// }
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
	char * resAff = malloc(sizeof(char)*(tailleRes));
	char * tmpChar = malloc(sizeof(char)*2);
	while(i<fin_section){
		tab[i] = tab[i];
		char * tmp = malloc(sizeof(char)*2);
		sprintf(tmp,"%02X",tab[i]);
		tmpChar[(i - debut_section)] = tab[i];
		resAff = strcat(resAff,tmp);
		//printf("%s",res);
		i++;
	}
	for(i = 0; i < tailleRes; i++){
		if(i%32 == 0){
			if(i > 0){
				printf("  ");
				for(int k = 0; k < 16; k++){
					char c = tmpChar[(i-1)/32*16 + k];
					printf("%c",(c >= 0x33 && c < 0x7f)? c : '.');
				}
			}
			printf("\n");
		}else if(i%8 == 0){
			printf(" ");
		}
		if(resAff[i] == ' '){
			resAff[i] = '0';
		}
		printf("%c",resAff[i]);
	}
	if(i%32 > 0){
		for(int k = 0;k <((32 - i%32) + 5-((i%32)/8));k++){
			printf(" ");
		}
		printf("  ");
		for(int k = 0; k < (i%32)/2; k++){
			printf("%c",tmpChar[(i-1)/32*16 + k]);
		}
	}
	printf("\n");
	//free(resAff);
	//free(tmpChar);
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
	debut_symtab=sheader[section].off;
	int size=sheader[section].size;
	fin_symtab=size+debut_symtab;

	symb symboles[size];
	nb_entree = size/16;
	printf("\nTable des symboles \".symtab\" contient %d entrees\n\n",nb_entree);
	getContenueSection(symboles, tab, offsetNom, debut_symtab, size, fin_symtab);
	printf(" NUM              NOM   VALEUR TAIL             TYPE             LIEN  NDX     VIS \n");
	for(int i = 0; i < (size/16); i++){
		printf("[%2d] ",i);
		printf("%16s ",symboles[i].nom);
		printf("%8x ",symboles[i].valeur);
		printf("%4d ",symboles[i].tail);
		printf("%16s ",getSymboleType(symboles[i].type));
		printf("%16s ",getSymboleLien(symboles[i].lien));
		printf("%4d ",symboles[i].ndx);
		printf("DEFAULT \n");

	}
	printf("\n");
}


int getRelocationTable(int * tab,reloc_section ** preloc_sec,int ** tailleSymbReloc){
	int offsetSymb;
	int info;
	int symbo;
	int type;
	int strTabId;
	int section;
	int debut_symtab;
	int fin_symtab;
	int existe = 0;

	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));

	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	for(int j = 0; j < nbEnTete; j++){
		if(!strcmp(sheader[j].nom,".symtab")){
			section = j;
		} else if(!strcmp(sheader[j].nom,".strtab")){
			strTabId = j;
		}
	}

	debut_symtab=sheader[section].off;
	int size=sheader[section].size;
	int offsetNom = sheader[strTabId].off;
	fin_symtab=size+debut_symtab;

	symb symboles[size];
	getContenueSection(symboles, tab, offsetNom, debut_symtab, size, fin_symtab);
	int nb_RelocSec;

	for(int j = 0; j < nbEnTete; j++){
		if(strncmp(sheader[j].nom,".rel.",5) == 0){
			nb_RelocSec++;
		}
	}
	int z = 0;
	reloc_section * reloc_sec = malloc(sizeof(reloc_section)*nb_RelocSec);
	int * tabSymb = malloc(sizeof(int)*nb_RelocSec);
	*tailleSymbReloc = tabSymb;
	*preloc_sec = reloc_sec;
	for (int x = 0 ; x<nb_RelocSec; x++){
		reloc_sec[x].nom = malloc(sizeof(char)*10);
	}
	for(int j = 0; j < nbEnTete; j++){
		if(strncmp(sheader[j].nom,".rel.",5) == 0){
			existe = 1;
			reloc_sec[z].nom = sheader[j].nom;
			int debut;
			int fin;
			DetailSection(tab,sheader[j].nom,&debut,&fin);
			int nbSymb = (fin-debut)/8;
			tabSymb[z] = nbSymb;
			for(int i = 0; i < nbSymb;i++){
				int decalage = debut + i*8;
				offsetSymb = (tab[decalage] << 0) + (tab[decalage+1] << 8) + (tab[decalage+2] << 16) + (tab[decalage+3] << 24);
				info = (tab[decalage+4] << 0) + (tab[decalage+5] << 8) + (tab[decalage+6] << 16) + (tab[decalage+7] << 24);
				symbo = info >> 8;
				type = (unsigned char)info;
				reloc_sec[z].vals[i].symbNom = malloc(sizeof(char)*100);
				reloc_sec[z].vals[i].offsetSymb = offsetSymb;
				reloc_sec[z].vals[i].info = info;
				reloc_sec[z].vals[i].type = type;
				reloc_sec[z].vals[i].symbNom = symboles[symbo].nom;
			}
			z++;
		}
	}
	if(!existe){
		return 0;
	}
	return nb_RelocSec;
}


void afficherRelocationTable(int * tab){
	reloc_section * reloc_Table = NULL;
	int tailleRelocTable=0;
	int * tailleSymbReloc = NULL;
	tailleRelocTable = getRelocationTable(tab,&reloc_Table,&tailleSymbReloc);

	if (tailleRelocTable == 0){
		printf("Il n'y a pas de relocalisation dans ce fichier.\n");
		exit(EXIT_SUCCESS);
	}

	for (int i = 0; i<tailleRelocTable;i++){
		printf("nom : %s\n",reloc_Table[i].nom);
		printf("\tNUMERO OFFSET     INFO          SYMBOLE     TYPE\n");
		for(int x = 0; x < tailleSymbReloc[i];x++){
			printf("\t[%d]  ",x);
			printf("%8x ",reloc_Table[i].vals[x].offsetSymb);
			printf("%8x ",reloc_Table[i].vals[x].info);
			printf("%16s ", reloc_Table[i].vals[x].symbNom);
			switch (reloc_Table[i].vals[x].type) {
				case 2:
					printf("  R_ARM_ABS32\n");
					break;
				case 5:
					printf("  R_ARM_ABS16\n");
					break;
				case 8:
					printf("  R_ARM_ABS8\n");
					break;
				case 0x1c  :
					printf("  R_ARM_CALL\n");
					break;
				case 0x1d:
					printf("  R_ARM_JUMP24\n");
					break;
				default :
					printf("  type inconnu\n");
			}
		}
		printf("\n");
		}
}




/*	int offsetSymb;
	int info;
	int symbo;
	int type;
	int strTabId;
	int section;
	int debut_symtab;
	int fin_symtab;
	int existe = 0;

	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));

	sh sheader[nbEnTete];
	getEnTeteSection(sheader,tab,nbEnTete,offsetsec,e_shstrndx);
	for(int j = 0; j < nbEnTete; j++){
		if(!strcmp(sheader[j].nom,".symtab")){
			section = j;
		} else if(!strcmp(sheader[j].nom,".strtab")){
			strTabId = j;
		}
	}

	debut_symtab=sheader[section].off;
	int size=sheader[section].size;
	int offsetNom = sheader[strTabId].off;
	fin_symtab=size+debut_symtab;

	symb symboles[size];
	getContenueSection(symboles, tab, offsetNom, debut_symtab, size, fin_symtab);

	for(int j = 0; j < nbEnTete; j++){
		if(strncmp(sheader[j].nom,".rel.",5) == 0){
			existe = 1;
			printf("nom : %s\n",sheader[j].nom);
			int debut;
			int fin;
			DetailSection(tab,sheader[j].nom,&debut,&fin);
			int nbSymb = (fin-debut)/8;
			printf("\tNUMERO OFFSET     INFO          SYMBOLE     TYPE\n");
			for(int i = 0; i < nbSymb;i++){
				printf("\t[%d]  ",i);
				int decalage = debut + i*8;
				offsetSymb = (tab[decalage] << 0) + (tab[decalage+1] << 8) + (tab[decalage+2] << 16) + (tab[decalage+3] << 24);
				info = (tab[decalage+4] << 0) + (tab[decalage+5] << 8) + (tab[decalage+6] << 16) + (tab[decalage+7] << 24);
				symbo = info >> 8;
				type = (unsigned char)info;
				printf("%8x ",offsetSymb);
				printf("%8x ",info);
				printf("%16s ", symboles[symbo].nom);
				//printf("%8x\n",type);
				switch (type) {
					case 2:
						printf("  R_ARM_ABS32\n");
						break;
					case 5:
						printf("  R_ARM_ABS16\n");
						break;
					case 8:
						printf("  R_ARM_ABS8\n");
						break;
					case 0x1c  :
						printf("  R_ARM_CALL\n");
						break;
					case 0x1d:
						printf("  R_ARM_JUMP24\n");
						break;
					default :
						printf("  type inconnu\n");
				}
			}
			printf("\n");
		}
	}
	if(!existe){
		printf("il n'y a pas de relocalisation dans ce fichier\n");
	}
	*/
