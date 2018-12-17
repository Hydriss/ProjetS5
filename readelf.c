#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int i,j;
	char strH[120];
	char c;
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
		printf("0x%x ",c);
	}
	/*char l[120];
	if(fgets(l,120,ptr)!= NULL){
			/*set strH with nulls
	    memset(strH,0,sizeof(strH));

	    /*converting str character into Hex and adding into strH
	    for(i=0,j=0;i<strlen(l);i++,j+=2)
	    {
	        sprintf((char*)strH+j,"%02X",l[i]);
	    }
	    strH[j]='\0'; /*adding NULL in the end
		printf("ELF Header \n");
	    printf("Magic : %s\n",strH);
		printf("%s \n",l);
	}*/
	fclose(ptr);
}
