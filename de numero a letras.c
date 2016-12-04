#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void print(char *s);
int dnumero(int *);
int rebajar(int,int);
int main( void ) {
	const int max_num = 9;
	char *n_banco = "GUILLE BANK";
	char *n_persona = "Guillermo Gimenez";
	float monto_in = 1897.12;
	int c,len = 0;
	char monto[max_num],*m1;
	m1 = &monto[0];
	printf("===Bienvenido al Banco Central=====\n");
	printf(">Sesion generadora de cheques electronicos==\n");
	printf("Insertar monto total del cheque:");
	scanf("%f",&monto_in);
	sprintf(monto,"%1.2f",(monto_in));
	for(;*m1!='\0';m1++,len++);
	printf("_____________________________________________________________\n\n");
	printf("Banco emisor:%s\n",n_banco);
	printf("Paguese a:%s \t\t",n_persona);
	if(len <= max_num){
		for(c = 0;c < (max_num-len);c++){
			printf("%c",'*');
		}
		printf("$%1.2f\n",atof(monto));
	}else{
		printf("Numero no valido.\n");
	}
	printf("La cantidad de:");
	int numerador  = (int)monto_in;
	int denominador = (int)((monto_in-numerador)*100);
	dnumero(&numerador);printf(" pesos con ");
	dnumero(&denominador);printf("centavos");
	
	printf("\n_____________________________________________________________\n\n");
	printf("\n\n\n");
	return 0;
}
int rebajar(int n,int veces){
	int res = n/10;
	int c;
	for(c = 1;c < veces;c++){
		res = res/10;
	}
	if(res){
		return res;
	}else{
		return n;
	}
}
int snumero(int *numero){//describe numero del 1 al 999
	char *numeros0[20] = {
		"cero",
		"uno",
		"dos",
		"tres",
		"cuatro",
		"cinco",
		"seis",
		"siete",
		"ocho",
		"nueve",
		"diez",
		"once",
		"doce",
		"trece","catorce","quince",
		"dieciseis","diecisiete","diesiocho","diecinueve"
	};
	char *numeros20[10] ={
		" "," ","veinte","treinta","cuarenta","cincuenta",
		"sesenta","setenta","ochenta","noventa",
	};
	char *ciento[10] ={
		"cien","cientos","dosciento","tresciento","cuatrocientos","quinientos",
		"seiscientos","setecientos","ochocientos","novecientos"
	};
	int cambio = 0;
	while(*numero != 0){
		if(*numero == 0){
				return 0;
		}else if(*numero <= 19){
			if(cambio){
				printf("y %s ",numeros0[*numero]);
			}else{
				printf("%s ",numeros0[*numero]);
			}
			*numero = 0;
		}else if(*numero >= 20 && *numero <=99){
			printf("%s ",numeros20[*numero/10]);
			*numero = *numero - (*numero/10)*10;
		}else if(*numero >= 100){
			int rebaje = rebajar(*numero,2);
			if(*numero == 100){
				printf("%s ",ciento[0]);
			}else{
				printf("%s ",ciento[rebaje]);
			}
			*numero = *numero - rebaje*100;
		};
		cambio++;
	};
	if(*numero == 0 && cambio == 0){
	
	};
	return 0;		
}
int dnumero(int *numero){
	int snumero(int *);
	int numero_buff = *numero;
	int ext,c = 0;
	int numeros[4] = {1000000000,1000000,1000,100};
	char *sufijos_plural[3] = {	
							"billones",
							"millones",
							"mil"
	};
	char *sufijos_singular[3] = {
							"Millon",
							"Millon",
							"Mil"
	};
	for(c = 0;c<10;c++){
		if(numero_buff <= 999){
			snumero(&numero_buff);
			break;
		}else if(numero_buff >= numeros[c]){
			ext = numero_buff/numeros[c];
			numero_buff = numero_buff-(ext*numeros[c]);
			if(ext != 1){
				snumero(&ext);
				printf("%s ",sufijos_plural[c]);
	
			}else if(*numero == numeros[c] && *numero != 1000){
				
				printf("%s ",sufijos_singular[c]);
				snumero(&ext);
			}else{
				printf("%s ",sufijos_singular[c]);
				snumero(&numero_buff);
			}
		}
	}
	getchar();
	return 0;
}
void print(char *s){
	printf("%s\n",s);
	
}



