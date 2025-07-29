#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stdin(int array[], unsigned int max_size) {    
	// Request for the size of the array
    unsigned int i;
    printf("Ingrese el tamaño del arreglo: \n");
	scanf("%u", &max_size);
	// Prompt the user to enter the items  
	i = 0; 
    while (i < max_size) {
			printf("Ingrese un valor para el elemento %d del arregle:\n", i);
            scanf("%d", &array[i]);
            i++;      
    }

    return max_size;
}

void array_dump(int a[], unsigned int length) {
    unsigned int i;
    i = 0;
    //Show array in the screen
    printf("[");
    if (length>0) {
        while (i<length-1) {
            printf("%d, ", a[i]);
            i++;
        }
        printf("%d]\n", a[length-1]);
    } else {
        printf("[]");
    }
}


int main() {

    // Create an array of MAX_SIZE elements
	int array[MAX_SIZE];

    unsigned int length;

    length = array_from_stdin(array, MAX_SIZE);

    // Dumping the array
    array_dump(array,length);
        
    return EXIT_SUCCESS;
}
