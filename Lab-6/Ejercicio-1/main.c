/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
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

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    bool bl = true;
    unsigned int opt = 0u;
    int elem = 0;
    int n_ord; 
    abb_ordtype ord;
    while (bl) {
        // Muestro en pantalla la siguiete interfaz
        fprintf(stdout, "\nSelecciona una una operación a realizar. En caso contrario, salir del programa.\n");
        fprintf(stdout, "1)....... Mostrar el árbol por pantalla.\n");
        fprintf(stdout, "2)....... Agregar un elemento.\n");
        fprintf(stdout, "3)....... Eliminar un elemento.\n");
        fprintf(stdout, "4)....... Chequear existencia de elemento.\n");
        fprintf(stdout, "5)....... Mostrar la longitud del árbol.\n");
        fprintf(stdout, "6)....... Mostrar raiz, máximo y mínimo del árbol\n");
        fprintf(stdout, "7)....... Salir del programa.\n");
        // Pido al usuario que selección una opcción:
        fscanf(stdin, "%u", &opt);
        //opt = 1
        if (opt == 1u) {
            fprintf(stdout, "\nSelecciona una de las siguientes constantes que hacen referencia al tipo de recorrido ha utilizar para mostrar el árbol en pantalla. Para ello, introduce el número de referencia:\n(1)ABB_IN_ORDER\n(2)ABB_PRE_ORDER\n(3)ABB_POST_ORDER.\n");
            fscanf(stdin, "%d", &n_ord );
            while (n_ord != 1 && n_ord != 2 && n_ord != 3) {
                fprintf(stdout, "Error al elegir el recorrido. Debes volver a introducir la opción de recorrido que quieras. Asegurate que el número ingresado se 1, 2, o 3.\n");
                fscanf(stdin, "%d", &n_ord );    
            }

            if (n_ord == 1) {
                ord = ABB_IN_ORDER;
            } else if (n_ord == 2) {
                ord = ABB_PRE_ORDER;
            } else if  (n_ord == 3) {
                ord = ABB_POST_ORDER;
            }
            abb_dump(tree, ord);
        }        
        //opt = 2
        if (opt == 2u) {
            fprintf(stdout, "\nIntroduce el elemento a agregar en el árbol: ");
            fscanf(stdin, "%d", &elem);
            abb_add(tree, elem);
        }
        //opt = 3
        if (opt == 3u) {
            fprintf(stdout, "\nIntroduce el elemento a eliminar del árbol: ");
            fscanf(stdin, "%d", &elem);
            if (!abb_exists(tree, elem)) {
                fprintf(stdout, "\nEl elemento ingresado no existe en el árbol. Asegurate de ingresar un elemento que si pertenezca.\n");
                while (!abb_exists(tree, elem)) {
                    fprintf(stdout, "Introduce el elemento a eliminar del árbol: ");
                    fscanf(stdin, "%d", &elem);    
                }    
            }
            abb_remove(tree, elem);
            fprintf(stdout, "\nEl elemento fue eliminado con éxito,");     
        }
        //opt = 4
        if (opt == 4u) {
            fprintf(stdout, "\nIntroduce un elemento para verificar si pertenece al árbol: ");
            fscanf(stdin, "%d", &elem);
            if (abb_exists(tree, elem)) {
                fprintf(stdout, "\nEl elemento %d existe en el árbol.\n", elem);
            } else {
                fprintf(stdout, "\nEl elemento %d no existe en el árbol.\n", elem);
            }            
        }
        //opt = 5
        if (opt == 5u) {
            fprintf(stdout, "La longitud del árbol es de %u elementos.\n", abb_length(tree));
        }
        //opt = 6
        if (opt == 6u) {
            if (!abb_is_empty(tree)) {
                fprintf(stdout,"La raíz del árbol es: %d.\n El elemento mínimo del árbol es: %d.\n El elemento máximo del árbol es: %d.\n", abb_root(tree), abb_min(tree), abb_max(tree));
            } else {
                fprintf(stdout, "El árbol es vacío.\n");
            }
        }
        //opt = 7
        if (opt == 7u) {
            bl = false;
            fprintf(stdout, "El programa ha finalizado.\n");
        }
    }
    //Al finalizar el programa, libero la memoria
    tree = abb_destroy(tree);
    return (EXIT_SUCCESS);
}
