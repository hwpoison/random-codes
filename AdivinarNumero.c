#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANT_NUMEROS 21
#define ANCHO 3
#define ALTURA CANT_NUMEROS/ANCHO
//Code by SrBill1990
//replica del truco de cartas llamado "21"
//////////////////////////////

void mostrarNumeros(int numeros[])
{
	int i;
	for(i=0; i < CANT_NUMEROS; i++){
		printf("%d    ", numeros[i]);
		if((i+1)%ANCHO == 0)
			printf("\n");
	}
	printf("\n");
}

void conteoAnimado(int numeros[], int pos){
	char msjNo[6][10] = {"Mm nop", "No creo ", "Este no", "Ni cerca","Mm na","Nou"};
	int sec = 0;
	int cnt = pos-5;
	time_t timet;
	struct tm *times = localtime(&timet);
	while(1){	
		timet = time(0);
		times=localtime(&timet);
		if(times->tm_sec != sec){
			sec = times->tm_sec;
			if(cnt == pos){
			   printf("\nEs este %d!! :D", numeros[cnt++]);
			   break;
			}else{
			   printf("\n%s %d",msjNo[rand()%5], numeros[cnt++]);
			}
		}
	}
}
void reacomodarNumeros(int columna, int numeros[], int numTmp[]){
	 //Se centra la columna elegida por el usuario
	int i, c , count , tmp = 0;
	for(i=0; i<ALTURA; i++){
		tmp = numeros[(ANCHO/2)+(ANCHO*i)];
		numeros[(ANCHO/2)+(ANCHO*i)] = numeros[(columna-1)+(ANCHO*i)];
		numeros[(columna-1)+(ANCHO*i)] = tmp;
	}
							
	//Se baraja de izq a der horizontalmente por fila
	count = 0;
	for(c=0;c<ANCHO;c++){
		for(i=0; i<ALTURA; i++)
			numTmp[count++] = numeros[c+(ANCHO*i)];
	}
	for(i=0; i<CANT_NUMEROS;i++)
		numeros[i] = numTmp[i];
}

void jugar(){
	printf("Hola! Piensa un numero y dime en que columna esta. (1,2 o 3) Intentare leerte la mente!!\n");
	int columna, i, rondaActual = 0;
	int numeros[CANT_NUMEROS] = {0};
	int numTmp[CANT_NUMEROS];
	//Se centra la columna elegida
	for(i=0; i < CANT_NUMEROS; i++)
		numeros[i] = i+1;
	//Comienza el juego
	while(rondaActual <= 2){
		mostrarNumeros(numeros);
		rondaActual++>0? printf("En que columna esta ahora?:") : printf("En que columna esta?:");
		scanf("%d", &columna);
		reacomodarNumeros(columna, numeros, numTmp);
	};
	//Se lanza el numero "adivinado"
	printf("A ver cual sera..\n");
	if(CANT_NUMEROS%2==0){
		conteoAnimado(numeros,CANT_NUMEROS/2+1);
		printf("\n\nEl numero que elegiste es el %d ! :*)\n", numeros[(CANT_NUMEROS/2)+1]);
	}else{
		conteoAnimado(numeros,CANT_NUMEROS/2);
		printf("\n\nEl numero que elegiste es el %d ! :*)\n", numeros[(CANT_NUMEROS/2)]);
	}
}

void borrarPantalla(){
	if(__WIN32)
		system("cls");
	else
		system("clear");
};

int main(int argc, char **argv)
{
	srand(time(NULL));
	if(CANT_NUMEROS%ANCHO != 0){
		printf("ERROR:La cantidad de numeros debe ser divisible por el ancho!");
		exit(1);
	}
	char decision;
	while(1){
		jugar();
		printf("\nJugar de nuevo? s/n:");
		scanf(" %c", &decision);
		if(decision != 's')
			exit(1);
		borrarPantalla();
	};
	return 0;
}
