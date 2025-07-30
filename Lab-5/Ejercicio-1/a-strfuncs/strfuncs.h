#ifndef STRFUNCS_H_
#define STRFUNCS_H_	
#include <stdlib.h>
#include <stdbool.h>

size_t string_length(const char *str);
/*
*	Calcula la longitud de la cadena de caracteres apuntada por str
*/

char *string_filter(const char *str, char c);
/*
*	Devuelve una nueva cadena en memoria dinámica que se obtiene tomando 
*	los caracteres de str que son distintos del caracter c:
*/

bool string_is_symmetric(const char *str);
/*
	Devuelve TRUE si la cadena apuntada por str es simétrica en cuanto que el primer caracter coincide con el
	último, el segundo con el penúltimo, etc. 
	Por Ejemplo:
				"aba", "abcba", "a", "".
*/
#endif
