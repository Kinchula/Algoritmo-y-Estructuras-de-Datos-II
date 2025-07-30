#include "strfuncs.h"

size_t string_length(const char *str) {
	if (str == NULL) {
		return 0;
	}
	size_t cont = 0u;
	while (str[cont] != '\0') {
		++cont;
	}
	return cont;
}

char *string_filter(const char *str, char c) {
	unsigned int n = 0u;
	char *filtered = NULL;
	for (unsigned int i=0u; i<string_length(str); ++i) {
		/*Compruebo que el caracter de la cadena apuntada por str sea distinto a c*/
		if (str[i] != c) {
			/*
			Cambio el tamaño del bloqe de memoria apuntado por filtered
			a bytes de tamaño
			*/
			filtered = realloc(filtered, n+1); //Cambio el tamaño del bloqe de memoria apuntado por filtered.
			filtered[n] = str[i]; //Almaceno el caracter en memoria dinámica
			++n;
		}
	}
	return filtered;
}

bool string_is_symmetric(const char *str) {
	// Obtengo el tamaño de la cadena
	size_t n = string_length(str);
	// Comparar caracteres desde el principio y el final de la cadena
	for (size_t i = 0; i < n/2; ++i) {
		if (str[i] != str[n - i -1]) {
			return false; // No es simétrico
		}
	}
	return true; // Es simétrico
}
