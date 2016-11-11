X = 2
NUMERO = int(input(">"))
while True:
    if X <= NUMERO:
        if NUMERO%X == 0:
            FACTOR = X
            NUMERO = NUMERO/X
            print(NUMERO,X)
        else:
            X = X+1
    else:#FIN
        break
