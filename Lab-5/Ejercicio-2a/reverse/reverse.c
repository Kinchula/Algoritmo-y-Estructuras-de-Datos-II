/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "../stack.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    printf("Original: ");
    array_dump(array, length);

    /*Creo un pila vacía*/
    stack p = stack_empty();

    /*Itero el arreglo de izq a der, insertando uno por uno los elementos en la pila*/
    for (unsigned int i=0u; i<length; ++i) {
         p = stack_push(p, array[i]);
    }

    /*Extraer cada uno de los elementos de la pila, usando stack_top() para obtenerlos y
    stack_pop() para removerlos.*/
    int* new_array = (int*)malloc(length * sizeof(int)); // Creo el nuevo arreglo y reservo la memoria necesaria
  
    if (new_array == NULL) {
        // Si el arreglo es nulo, muestro un error en patalla, destruyo la pila y termino el programa
        fprintf(stderr, "Error al reservar memoria.");
        p = stack_destroy(p);
        return EXIT_FAILURE;
    }

    for (unsigned int i=0u; i<length; ++i) {
        // Cargo los elementos de la pila en el nuevo arreglo
        new_array[i] = stack_top(p);
        p = stack_pop(p);
    }
  
    p = stack_destroy(p); // Libero memoria que se reservo para la pila
    // Compurebo que el arreglo haya sido cargado correctamente
    if (new_array==NULL) {
        fprintf(stderr, "Error al cargar el arreglo");
        return EXIT_FAILURE;
    }
    printf("Reversed: ");
    array_dump(new_array, length);
    return (EXIT_SUCCESS);
}
