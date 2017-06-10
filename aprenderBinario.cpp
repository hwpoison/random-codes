#include <iostream>
#include <cmath>
#define BYTE 8
#define NIBBLE 4

void decAbin(int *binario, int numeroDecimal);//decimal a Binario
int binAdec(int arrayBinario[]);//binario a Decimal

using namespace std;
int main(int argc, char *argv[])
{
		
	while(1)
	{
		int decimal;
		cout << endl;
		cout << "Introducir un numero para convertir:";
		cin >> decimal;
		int binario[(int)pow(2, 8)];
		decAbin(binario, decimal);
		binAdec(binario);
	}
	return 0;
}

int binAdec(int arrayBinario[]){
	int multiplo = 1;//Multiplo inicial
	int sumaFinal = 0;//acum
	cout << endl;
	cout << "Muy bien, Ahora lo convertiremos a decimal." << endl;
	cout << "para ello comenzamos a multiplicar cada bit desde" << endl;
	cout << "la derecha a izquierda por un multiplo ascendente de 2." << endl;
	
	int i;for(i = BYTE;i != 0;i--){
		int multiplicacion = multiplo * arrayBinario[i-1];
		cout << multiplo << " * " << arrayBinario[i-1] << " = " << multiplicacion << endl;
		sumaFinal += multiplicacion;
		multiplo = multiplo*2;
	}
	cout << "Sumamos todos los resultados de las multiplicaciones y" << endl;
	cout << "obtenemos el numero en decimal que es :" << sumaFinal << endl;
	return sumaFinal;
}

void decAbin(int *binario, int numeroDecimal){
	if( numeroDecimal >= 256 )
	{
		cout << "1 byte soporta 8^8 combinaciones, es decir, solo 255 permutaciones!" << endl;
		cout << "por lo tanto se hace imposible con 1 byte representar" << endl;
		cout << "un resultado mayor ya que no alcanza a permutarlo." << endl;
	}
	else
	{
		cout << "====Convirtiendo " << numeroDecimal << " a Binario:" <<endl;
		cout << "Se divide el " << numeroDecimal << " 8 veces contando con el 0 ";
		cout << "para completar el byte entero." << endl;
	}
	//*binario = new int[1]; //se reserva 1 byte -> 8 bits
	int n = numeroDecimal;		 //Estado actual de la operacion
	
	int i;for(i=BYTE; i!= 0;i--){
		
		if(n%2)
		{					 //Si la division es par, es un 0, de lo contrario es 1
			cout << n<< " dividido por '2' es impar, corresponde a un 1." << endl;
			binario[i-1] = 1;
		}
		else
		{
			cout << n << " dividido por '2' es par, corresponde a un 0." << endl;
			binario[i-1] = 0;	
		}
		
		n = n/2;				 //Se re divide el numero para volver a ser comparado
	};	
	cout << endl;
	cout << "Ahora si analizamos los 'bits' obtenidos en la operacion" << endl;
	cout << "de abajo hacia arriba, obtendemos la candena '";

	int cnt;for(cnt = 0; cnt < BYTE; cnt++)
	{
		cout << binario[cnt];
	}
	
	cout << "'"<< endl;
	cout << "ese es  el numero en binario." <<endl;
	
}
