#include <stdio.h>
//IO
#define LCT 10
#define WRT 11
//C/A
#define CHR 20
#define ALM 21
//Aritmetica
#define SUM 30
#define RES 31 
#define DIV 32
#define MUL 33
//Transferencia de Control
#define JMP 40
#define JMN 41
#define JMC 42
#define END 43
//personales
#define CLN 55 //libera memoria
#define MAP 56
#define DLT 57 //elimina variable
#define VAC 58 //vacia acumulador
//Memoria
#define MEMORY_LONG 10

void print_sys(const char *,int init, int end,int len);
void map_memory(const int *,int len);
void clean_memory(int *,int len);
void load_in(int *program, int *memory, int len_program);
int main(){
	static int memoria_[MEMORY_LONG];
	static int ram_[MEMORY_LONG];
	int ram_test;
	for(ram_test = 0;ram_test < MEMORY_LONG;ram_test++){
		ram_[ram_test] = -999999;
	}
	const char msg_char[7][50] = {
		"Iniciando sistema..",
		"Creando memoria..",
		"Bienvenido a Simpletron..",
		"A la espera de instrucciones..",
		"Carga de programa finalizada..",
		"Iniciando ejecucion de instrucciones..",
		"=================",
	};
	print_sys(*msg_char,0,3,50); 
	int long_soft = 7;
	int programa[7] = {//test programa
		5800,//vaciar acumulador
		1004,//0 RECIBE VARIABLE EN 04
		2004,//1 carga  ala memoria
		4105,//2 si es negativo finaliza
		4000,//salta al comienzo
		1005,//recibe numero
		4300,//4 termina
	};
	//CARGA EL PROGRAMA
	load_in(programa,memoria_,long_soft);
	//Inicio de ejecucion
	print_sys(*msg_char,4,6,50); 
	signed int acumulador = +0000;
	int mip_c = 0;
	while(mip_c!=-99999 && mip_c < long_soft) {
		int mip_in = memoria_[mip_c] / 100;
		int mip_op = memoria_[mip_c] % 100;
		printf("%d<<<\n",memoria_[mip_c]);
		if(mip_op > MEMORY_LONG ){
			printf("VIOLACION DE MEMORIA!.\n");
			printf("Programa terminado incorrectamente.\n");
			break;
		}
		printf("== %d ==\n",mip_c);
		mip_c++;
		switch(mip_in) {
			//IO 
			case LCT:
				printf("Instruccion LECTURA\n");
				printf("$");
				scanf("%d",&ram_[mip_op]);
				break;
			case WRT:
				printf("Instruccion ESCRITURA\n");
				printf(">%d\n",ram_[mip_op]);
				break;
			//Carga
			case CHR:
				printf("Instruccion CARGA %d\n",ram_[mip_op]);
				acumulador += ram_[mip_op];
				break;
			case ALM:	
				printf("Instruccion ALMACENA/sobrescribe\n");
				ram_[mip_op] = acumulador;
				break;
			//aritmetica
			case SUM:
				printf("Instruccion SUMA\n");
				acumulador +=ram_[mip_op];
				break;
			case RES:
				printf("Instruccion RESTA\n");
				acumulador -=ram_[mip_op];
				break;
			case DIV:
				printf("Instruccion DIVIDE\n");
				acumulador = acumulador / ram_[mip_op];
				break;
			case MUL:
				printf("Instruccion MULTIPLICA\n");
				acumulador = acumulador * ram_[mip_op];
				break;
			//Transf. Control
			case JMP:
				printf("Instruccion SALTA\n");
				mip_c = mip_op;
				break;
			case JMN:
				if(acumulador <0){
					printf("ES NEGATIVO\n");
					mip_c = mip_op;
				}
				break;
			case JMC:
				printf("Instruccion SALTACERO\n");
				if(acumulador == 0){
				}
				break;
			case END:
				printf("**Fin de la operacion**\n");
				mip_c = -99999;
				break;
			case CLN:
				clean_memory(ram_, MEMORY_LONG);
				printf("MEMORY CLEARED..\n");
				break;
			case MAP:
				map_memory(ram_,MEMORY_LONG);
				break;
			case DLT:
				ram_[mip_op] = -999999;
				break;
			case VAC:
				acumulador = 00000;
				break;
			case -99999:
				printf("ALTO\n");
				break;
			default:
				printf("ERROR:BAD INSTRUCCION?.\n");
				break;
		}
		
	}
	
	return 0;
}



void map_memory(const int *mem, int len) {
	int c;
	int free = 0;
	printf("________\n");
	printf("MEMORY:\n");
	for(c = 0;c < len;c++){
		if(mem[c] == -999999){
			free++;
		}
		printf(" %p  :%d >  %d\n",&mem[c],c,mem[c]);
	}
	printf("USADO:%d LIBRE:%d\n",len-free,free);
	printf("________\n");
	
}
void clean_memory(int *mem, int len){
	int c;
	for(c = 0;c < len;c++){
		mem[c] = 0;
	}
}
void load_in(int *program, int *memory,int len_program){
	int c;
	for(c = 0;c < len_program;c++){
		memory[c] = program[c];
	}
}
void print_sys(const char *mm,int init, int end, int len){
	int a = 0;
	int b = len*(init);
	int c = init;
	for(c = init;c < end+1;c++){
		for(a = b;*(mm+a)!= '\0' ;a++){
			printf("%c",*(mm+a));
		}
		b+=len;
		printf("\n");
	}
}


