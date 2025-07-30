#include <stdio.h>
#include <stdbool.h>
#include "string.h"

int main(void) {
	string str1 = string_create("Que no te demore el mundo, no. Poniendote el antifaz.\n");
	string_dump(str1, stdout);
	string str2 = string_create("Mata el miedo que guarda el animal. Limpia el cuerpo, pues dentro de el estás.\n");
	string_dump(str2, stdout);
	bool bl = string_eq(str1, str2);
	if (bl) {
		fprintf(stdout, "Las cadenas de caracteres no son iguales :( \n");
	} else {
		if (string_less(str1, str2)) {
			fprintf(stdout, "La primera cadena de caracteres es menor en orden alfabético con respecto a la segunda.\n");
		} else {
			fprintf(stdout, "La primera cadena de caracteres es mayor en orden alfabético.\n");
		}
	}
	return 0;
}
