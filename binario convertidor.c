//by srbill 2018
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BITS_SIZE 16

char *aBinario(int decimal){
	char *bin = (char*)malloc(sizeof(char) * BITS_SIZE);
	int cnt;for(cnt=BITS_SIZE-1; cnt>=0;decimal=decimal/2)
		bin[cnt--] = decimal%2?'1':'0';
	return bin;
	
}
int aDecimal(char *binario){
	int32_t sum_general = 0, multiplos = 1;
	int8_t cnt;for(cnt=BITS_SIZE-1;cnt>=0;){
		sum_general+=multiplos*(binario[cnt--]=='0'?0:1);
		multiplos=multiplos*2;
	}
	return sum_general;
} 
int main(int argc, char **argv){
	uint64_t numero = 255;
	printf("A binario = %s\n",aBinario(numero));
	printf("De binario a decimal = %d\n",aDecimal(aBinario(numero)));
	printf("En hex = 0x%lx\n", numero);
	return 0;
}

