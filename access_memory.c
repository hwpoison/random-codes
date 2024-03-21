#include <stdio.h>
#include <stdlib.h>
/*
 Program to interact with process space memory, you can write a memory address in hex and acces to his content in runtime.
*/

int main(){
    // demo vars
    int number_1 = 100;
    char string[] =  "Hello World!";
    double pi = 3.314;
    char *hidden = "I'm hidden hehe";
    // Demo vars and his memory address
    printf("%ld\n", sizeof(double));
    printf("%p | int number_1  = %d\n", &number_1, number_1 );
    printf("%p | char string[] = %s\n", &string, string);
    printf("%p | double pi     = %f\n", &pi, pi);
  
    unsigned long long int mem_address; 
    char *ptr;
    
    // read input address
    char input_address[64];
    while(1){
        printf("> Memory adress:");
        scanf("%s", &input_address);
        mem_address = strtoull(input_address, NULL, 16);

        // assign to pointer
        ptr = (char  *)mem_address;

        // retrieve pointer value
        printf("Memory address: %p  \n", (void*)ptr);
        printf("---> hex    : 0x%X  \n", *ptr);
        printf("---> str    :   %s  \n", ptr);
        printf("---> int    :   %d  \n", *ptr);
    };

}

