#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "helpers_func.h"

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {

	unsigned int index_elem ,length=0;
	char letter;
	FILE *file = NULL;
	file = fopen(path, "r");
	/*Comprubo que la apertura del archivo haya sido exitosa*/
	if (file == NULL) {
		fprintf(stderr, "File does not exist.\n");
		fclose(file);
		assert(EXIT_FAILURE);
	}
	
	while(!feof(file) && length < max_size) {
		int err = fscanf(file, "%u -> *%c*\n", &index_elem , &letter);
		if(err == EOF || index_elem>=max_size) {
			fprintf(stderr, "File does not exist or is invalid.\n");
			fclose(file);
			assert(EXIT_FAILURE);		
		}
		indexes[length] = index_elem;
		letters[length] = letter;
		length++; 			
	}
	return length;
}

void array_sort(unsigned int indexes[], char letters[], char sorted[], unsigned int max_size) {

		for(unsigned int i=0u; i < max_size; i++) {
			unsigned int index = indexes[i];
			sorted[indexes[index]] = letters[i];	
		}
}

