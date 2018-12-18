#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char * nom;
	int type;
	int flags;
	int adresse;
	int off;
	int size;
	int link;
	int info;
	int addralign;
	int entsize;
}sh;

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
		printf("%d : %x \n",i,c);
		tab[i] = c;
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

void afficherEnTeteSection(char *nom,int type,int flags,int adresse,int off,int size,int link,int info,int addralign,int entsize){
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
		default :
			printf("type inconnu" );
	}
	printf("\n\t-flags : ");
	switch (flags) {
		case 0x1:
			printf("WRITE");
			break;
		case 0x2:
			printf("ALLOC");
			break;
		case 0x4:
			printf("EXECINSTR");
			break;
		case 0x10:
			printf("MERGE");
			break;
		case 0x20:
			printf("STRINGS");
			break;
		case 0x40:
			printf("INFO_LINK");
			break;
		case 0x80:
			printf("LINK_ORDER");
			break;
		case 0x100:
			printf("OS_NONCONFORMING");
			break;
		case 0x200:
			printf("GROUP");
			break;
		case 0x400:
			printf("TLS");
			break;
		case 0x0ff00000:
			printf("MASKOS");
			break;
		case 0xf0000000:
			printf("MASKPROC");
			break;
		case 0x40000000:
			printf("ORDERED");
			break;
		case 0x80000000:
			printf("EXCLUDE");
			break;
		default:
			printf("?????");
	}
	printf("\n");
	printf("\t-adresse: %x\n\t-off: %x\n\t-size: %x\n\t-link: %d\n\t-info: %d\n\t-addralign: %d\n\t-entsize: %d\n",adresse,off,size,link,info,addralign,entsize);
}

char ** getnom(sh *sheader,int offset,int taille,int * tab,int nbEnTete){
	char ** noms;
	int nbLettre[nbEnTete];
	int numMot = 0;
	for(int i = 0; i < nbEnTete;i++){
		nbLettre[i] = 0;
	}
 	for(int i=0; i<taille;i++){
		if (tab[offset+i]==0){
			numMot++;
		} else {
			nbLettre[numMot]++;
		}
	}
	noms = malloc(sizeof(char*)*nbEnTete);
	for(int i = 0; i < nbEnTete; i++){
		noms[i] = malloc(sizeof(char)*nbLettre[i]);
	}

	numMot = 0;
	int numLettre = 0;
	for(int i=0; i<taille;i++){
		if (tab[offset+i]==0){
			numMot++;
			numLettre=0;
		} else {
			noms[numMot][numLettre] = tab[offset+i];
			numLettre++;
		}
	}
	return noms;
}

void afficherSection(int * tab){
	int nbEnTete = ((tab[48] << 0) + (tab[49] << 8));
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);
	int e_shstrndx = ((tab[50] << 0) + (tab[51] << 8));
	//printf("\n%d",offsetsec);
	printf("\n Il y a %d en-tetes de section, debutant à l'adresse de decalage 0x%x\n", nbEnTete, offsetsec);

	int i = offsetsec;
	int j;
	/*int nom = ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
	printf("Nom : %x \n",nom);
	int type;
	int flags;
	int adresse;
	int off;
	int size;
	int link;
	int info;
	int addralign;
	int entsize;*/

	sh sheader;
	i +=4;
	for(j=0;j<nbEnTete;j++){
		sheader.type= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		//printf("i : %d %x %x %x %x\n",i,tab[i],tab[i+1],tab[i+2],tab[i+3]);
		i += 4;
		sheader.flags= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.adresse= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.off= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.size= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.link= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.info= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.addralign= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		sheader.entsize= ((tab[i] << 0) + (tab[i+1] << 8) + (tab[i+2] << 16) + (tab[i+3] << 24));
		i += 4;
		i += 4;

		if (j==e_shstrndx){
			/*sheader.off = (sheader.off << 24);
			sheader.off = (sheader.off >> 24);//>> 24);*/
			sheader.off -= 0xffffff00;
			char ** noms = getnom(&sheader,sheader.off,sheader.size,tab,nbEnTete);
			for(int k = 0; k < nbEnTete; k++){
				printf("%s\n", noms[k]);
			}
		}

		//printf("%d : \n\t -nom: %d\n\t -type: %x\n\t -flags: %x\n\t -adresse: %x\n\t -off: %x\n\t -size: %x\n\t -link: %x\n\t -info: %x\n\t -addralign: %x\n\t -entsize: %x\n",j,nom,type,flags,adresse,off,size,link,info,addralign,entsize);
		printf("%d:\n",j);

		afficherEnTeteSection(sheader.nom,sheader.type,sheader.flags,sheader.adresse,sheader.off,sheader.size,sheader.link,sheader.info,sheader.addralign,sheader.entsize);


	}

}
void afficherDetailSection(int * tab, int section){
	/*int nom;
	int j;
	int debut_section;
	int i;
	int fin_section;
	int offsetsec = (tab[32] << 0) + (tab[33] << 8) + (tab[34] << 16) + (tab[35] << 24);

	j = offsetsec;
	nom = ((tab[j] << 0) + (tab[j+1] << 8) + (tab[j+2] << 16) + (tab[j+3] << 24));
	i = debut_section;

	printf("Vidange hexadecimal de la section \"%d\" : \n",nom );*/



}

int main(int argc, char * argv[]){
	int taille = 2000;
	int * tab;
	int section;
	if(argc < 3){
		printf("il manque un nom de fichier");
	}
	char * file = NULL;

	if(argv[1][0] == '-' && argv[1][1] != 'x'){
		file = argv[2];
	}
	else{
		file = argv[3];
		section = atoi(argv[2]);
		printf("\n--------------%d\n",section);
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
				afficherDetailSection(tab,section);
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
