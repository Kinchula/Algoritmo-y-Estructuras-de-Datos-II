#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x < 0) {
        y = -x;
    } else {
        y = x;
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;
    /*Determino el valor absoluto de a*/
    absolute(a, res);
    /*Muestro en pantalla el valor absoluto de a*/
    printf("EL valor absoluto de %d es: %d.\n", a, res);
    return EXIT_SUCCESS;
}

/*
El valor que muestra en pantalla es 0, por lo que no coincide con el programa del
lenguaje teórico.
El parámetro y se establece dentro de la función absolute(), y como nunca se utiliza
luego en el código, en la linea 4 me salta un error, ya que estoy estableciendo un valor
para un parámetro que nunca se usa.
*/
