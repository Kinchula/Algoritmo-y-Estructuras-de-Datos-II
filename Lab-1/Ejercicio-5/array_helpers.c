#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*now, I include the project*/
#include "mybool.h"
unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    // Open the file for read  
    FILE *archive = NULL;
    archive = fopen(filepath, "r");
    //verify if the openning wase successful
    if (archive == NULL) {
        printf("Error opening the file \n");
        exit(EXIT_FAILURE);
    }
    
    //determine the file size
    unsigned int i, length;
    i = 0;
    fscanf(archive, "%u", &length);
    if (length < max_size) {
        while (i < length) {
            fscanf(archive, "%d", &array[i]);
            i++;
            
        }
    }
    
    //Close file
    fclose(archive);

    return length;
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

mybool array_is_sorted(int a[], unsigned int length) {
	mybool ord = true;
	for (unsigned int i = 1u; i < length; i++) {
		if (a[i] > a[i-1]) {
			ord	= ord && true;
		} else {
			ord = false;
		}
	}

	return ord;
}
