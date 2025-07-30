#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"

/* Realizo una serie de pruebas para ver como se comportar algunas funciones en casos extremos. */

int main(void) {
	stack p = stack_empty();
	/* 
		¿Funciona bien stack_pop() para pilas de tamaño 1? 
	*/
	stack_elem e = 23;
	stack_push(p, e);
	printf("El primer elemento de la pila es: %d. \n", stack_top(p));
	/*
		Si la pila queda vacía, ¿puedo volver a insertar elementos?
	*/
	p = stack_pop(p);
	if (stack_is_empty(p)) {
		printf("La pila esta vacía.\n");
	} else {
		printf("La pila no esta vacía.\n");
	}
	p = stack_push(p, 12); // Hago la prueba de incertar un elemento a la Stack vacía  
	printf("EL nuevo elemento superior de la pila es: %d.\n", stack_top(p));
	
	/*
		Compruebo si la función stack_to_array() devuelve NULL para una pila vacía.
		Además, compruebo si devuelve los elementos en el orden correcto.
	*/
	// Agrego elementos a la pila
	p = stack_push(p, 2);
	p = stack_push(p, 4);
	p = stack_push(p, 6);
	p = stack_push(p, 8);
	int *arr = NULL;
	arr = stack_to_array(p); // Cargo los elementos de la pila en el nuevo arreglo
	for (unsigned int i=0u; i<stack_size(p); ++i) {
		// Imprimo en pantallas los elementos para verificar si su orden es correcto
		printf("El elemento %u del arreglo es = %d.\n", i, arr[i]);
	} 
	return 0;
}	
