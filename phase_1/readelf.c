#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char c;
	int i = 0;
	int tab[7];
	FILE *ptr = malloc(sizeof(FILE));
	ptr = fopen("/home/s/salamanl/projet/elf_linker-1.0/Examples_loader/example1.o","r");
	if (ptr==NULL){
		printf("Erreur fopen");
	}
	while (!feof(ptr)){
		c = fgetc(ptr);
		if (c == '\0'){
			break;
		}
		tab[i] = c;
		i++;
	}
	printf("identification : 0x%x",tab[0]);
	for(i = 1; i <=3;i++){
		printf("%c",tab[i]);
	}
	printf("\nclass : ");
	switch (tab[4]) {
		case 0:
			printf("ClassNONE");
			break;
		case 1:
			printf("Class32");
			break;
		case 2:
			printf("Class64");
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

	return 0;
}
