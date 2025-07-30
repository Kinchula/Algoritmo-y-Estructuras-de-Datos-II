#ifndef helpers_func
#define helpers_func

unsigned int data_from_file(const char *path,
						   unsigned int indexes[],
						   char letters[],
						   unsigned int max_size);

void array_sort(unsigned int indexes[],
			    	   char letters[], 
			    	   char sorted[], 
			           unsigned int max_size);

#endif
