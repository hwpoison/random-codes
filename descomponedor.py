def generar_nprimo():#Generador de numeros primos
    generar_nprimo.numero_+=1
    for i in range(2,generar_nprimo.numero_):
        if i >generar_nprimo.numero_-1:break
        if generar_nprimo.numero_%i == 0:
            generar_nprimo.numero_+=1
            generar_nprimo()
            break
    yield generar_nprimo.numero_
def factorizar(numero_factorizar):#Factoriza un numero
    numero_primo = generar_nprimo().__next__()
    acu_mul_pr = 0#Acumulador de numeros primos que se van aplicando
    string_resultado = ""
    while True:
        if numero_factorizar%numero_primo == 0:
            print(int(numero_factorizar)," | ",numero_primo)
            string_resultado+=" %s"%numero_primo
            numero_factorizar = numero_factorizar/numero_primo
            if acu_mul_pr == 0:
                acu_mul_pr = numero_primo
            else:
                acu_mul_pr = acu_mul_pr * numero_primo
        elif numero_factorizar%numero_primo == numero_factorizar:
            print(int(numero_factorizar/numero_factorizar))
            print("_________\n")
            string_resultado = string_resultado.lstrip().replace(" "," x ")
            print(string_resultado , "= " , acu_mul_pr)
            break
        else:
            numero_primo = generar_nprimo().__next__()
if __name__ == "__main__":
 while True:
    try:
        generar_nprimo.numero_ = 1#Inicializador el generador a 1
        numero_factorizar = int(input("Numero a factorizar:"))
        factorizar(numero_factorizar)
        input("\nPresionar una tecla para factorizar otro numero..")
    except(ValueError):
        print("Por favor insertar un numero.")

