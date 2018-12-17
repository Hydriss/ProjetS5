#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char c;
	char str[100];
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
		sprintf(str,"%x",c);
		printf("%x ",c);
	}
	printf("%s",str);
	fclose(ptr);
}
