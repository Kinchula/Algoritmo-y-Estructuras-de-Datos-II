#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x < 0) {
        *y = -x;
    } else {
        *y = x;
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;
    /*Determino el valor absoluto de a*/
    absolute(a, &res);
    printf("EL valor absoluto de %d es: %d.\n", a, res);
    /*Muestro en pantalla el valor absoluto de a*/
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*  El apuntador *y en la función absolute() es un parametro in, ya que es uno de los argumentos de entrada
    de dicha función, y esta es de tipo void, lo que implica que no exita nigún valor de salida, ya que no retorna nada.  
    En C existen tres posibles tipos de parámetros: in, out y in/out.
*/
