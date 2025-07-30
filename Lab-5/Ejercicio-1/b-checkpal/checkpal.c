#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    char *res = fgets(user_input, MAX_LENGTH, stdin); // Remplzao scanf()

    if (res == NULL) {
        printf("Error al leer los caracteres. \n");
        return EXIT_FAILURE;    
    }
    
    filtered = string_filter(user_input, ignore_chars[0]); // Pido memoria para filtered
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        char *aux = filtered;
        filtered = string_filter(filtered, ignore_chars[i]);
        free(aux);
    }
    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n",
             filtered, string_is_symmetric(filtered) ? "Es": "NO es");
    free(filtered);
    return EXIT_SUCCESS;
}

