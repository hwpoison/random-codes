#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//Contiene la funcion usleep()

//Dimensiones Letrero
#define T_ALTO 6
#define T_ANCHO 80
//Dimensiones Letra
#define L_ANCHO 10
//Otros
#define LED ' '//Caracter vacio por defecto
typedef struct cartel {
	char tablero[T_ALTO][T_ANCHO];
	int animando;//Estado de animacion
	int c_letras;//Cantidad de letras
	int e_letras;//Espacio entre letras
} panel;

void setear(char tablero[][T_ANCHO]);//Setea el tablero
void animar(panel *Letrero, float intervalo);//Anima el tablero en bucle
int agregarLetra(panel *Letrero, char *letra[L_ANCHO]);//Agrega una letra (no detecta hasta cuantas)
void ver(char tablero[][T_ANCHO]);//Visualiza el tablero sin borrar la pantalla
void desplazarArray(char array[]);//Desplaza el contenido del array hacia la derecha y
								  //lo ultimo aparece en el principio

int main(int argc, char *argv[]){

	
	char *letra1[10] = { //Las letras tienen que ser proporcionales al letrero en altura
		"H        H",
		"H        H",
		"hhhhhhhhhh",
		"H        H",
		"H        H",
		"H        H"
	};
	char *letra2[10] = {
		"OOOOOOOOOO",
		"O        O",
		"0        O",
		"O        0",
		"O        O",
		"OOOOOOOOOO"
	};
	char *letra3[10] = {
		"L         ",
		"L         ",
		"L         ",
		"L         ",
		"L         ",
		"LLLLLLLLLL",
	};
	char *letra4[10] = {
		"  AAAAAA  ",
		" A       A",
		"A        A",
		"AAAAAAAAAA",
		"A        A",
		"A        A"
	};
	char *letra5[10] = {
		"| |       ",
		"| |       ",
		"| |       ",
		"| |       ",
		"          ",
		" O        "
	};
	
	//Inicializacion
	panel Letrero;
	setear(Letrero.tablero);
	Letrero.c_letras = 0;
	Letrero.e_letras = 2;
	//Se agregan las letras
	agregarLetra(&Letrero, letra1);
	agregarLetra(&Letrero, letra2);
	agregarLetra(&Letrero, letra3);
	agregarLetra(&Letrero, letra4);
	agregarLetra(&Letrero, letra5);
	//Comienza la animacion
	animar(&Letrero, 0.1);
	return 0;
}

int agregarLetra(panel *Letrero, char *letra[L_ANCHO]){
	short x,y;
	short separacion;
	for(x=0; x<T_ALTO; x++){
		for(y=0; y<L_ANCHO; y++){
			separacion = Letrero->c_letras>0?y+((L_ANCHO+1)*Letrero->c_letras)+Letrero->e_letras:y;
			Letrero->tablero[x][separacion] = letra[x][y];
		}
	}
	Letrero->c_letras++;
	return 1;
}

void setear(char tablero[][T_ANCHO]){
	short x,y;
	for(x=0; x<T_ALTO;  x++){
		for(y=0; y<T_ANCHO-1; y++)
			tablero[x][y] = LED;
		tablero[x][y] = '\0';
	}
}

void desplazarArray(char array[]){
	char tmp0 = array[1];
	char tmp1;
	array[1] = array[0];
	short cnt;for(cnt=2; cnt<strlen(array); cnt++){
		tmp1  = array[cnt];
		array[cnt] = tmp0;
		tmp0 = tmp1;
	}
	array[0] = tmp0;
}

void animar(panel *Letrero, float intervalo){
	Letrero->animando = 1;
	short x;
	while(Letrero->animando){
		system("clear");
		for(x=0;x < T_ALTO; x++)
			desplazarArray(Letrero->tablero[x]);
		ver(Letrero->tablero);
		usleep(intervalo*100000);
	}
}

void ver(char tablero[][T_ANCHO]){
	short x;for(x=0; x<T_ALTO; x++)
		printf("%s\n", tablero[x]);
}
