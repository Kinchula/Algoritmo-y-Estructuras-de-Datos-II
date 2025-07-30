#ifndef _ARRAY_HELPERS_
#define _ARRAY_HELPERS

#include "mybool.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath); 
/*
        All elements are read from the file 'filepath'.
        The file must exist on disk, and its format is of the form:

                <array_size>
                <element_1>,<element_2>,...;<element_100000>.

        The first line contains the size of the array and the next line contains the elements of the array, separated by comma and one or more blanks between each one.

        Each element of the file, except for its size, is copied into the array 'a'.The size of 'a' must be less than or equal to max_size.
        At the end, return length.
*/

void array_dump(int a[], unsigned int length);
/*
        Writes the contents of the array 'a' to STDOUT
        El arreglo 'a' debe tener necesariamente longitud 'length'
*/

mybool array_is_sorted(int a[], unsigned int length);
/*
        Given an array a[] and its size length it must return true
        if and only if the elements of the array a[] are sorted in ascending order, i.e.

                             a[0] <= a[1] <= ... <= a[length - 1]
*/

#endif
