/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};
    /*Defino dos punteros*/
    int *p_int = NULL;
    char *p_char = NULL;
    
    p_int = &x; /*p_int apunta a x*/
    *p_int = 9; /*x ahora vale 9*/

    p_int = &a[1]; /*ahora p_int apunta a a[1]*/
    *p_int = 42;  /*a[1] tiene el valor 42*/

    p_int = &m.age; /*p_int apunta a m*/
    *p_int = 100; /*m.age ahora vale 100*/

    p_char = &m.name_initial; /*p_char apunta a m*/ 
    *p_char = 'F'; /*m.name_initial ahora vale F*/
    
     
    /* Completar aquí:
       Al finalizar la ejecución las variables deben tener los siguientes valores
       x = 9
       m = (100, F)
       a[1] = 42

       Las restricciones son:
       - No usar las variables 'x', 'm' y 'a' en la parte izquierda de alguna asignación.
       - Se pueden agregar líneas de código, pero no modificar las que ya existen.
       - Se pueden declarar hasta 2 punteros.
       AYUDA: podes usar GDB para consultares valores de variables y la dirección de memoria donde estan alojadas.
    */

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);

    return EXIT_SUCCESS;
}

