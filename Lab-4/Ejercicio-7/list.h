#ifndef _LIST_L
#define _LIST_L
#include <assert.h>
#include <stdbool.h>	

typedef int list_elem;
typedef struct node* list;
/*Constructors*/

list empty(void);
/*
	Create empty list
*/

list addl(list_elem e, list l);
/*
	Adds element e to the beginning of list l
*/


/*Destroy*/
list destroy(list l);
/*
	frees memory ocuppied by the list
*/

/*Operations*/
bool is_empty(list l);
/*
	return True if l is empty
	
*/

list_elem head(list l);
/*
	PRE: not is_empty(l)
	Returns the first element of list l
*/

list tail(list l);
/*
	PRE: not is_empty(l)
	Deletes the first item in the list l 
*/

list addr(list l, list_elem e);
/*
	adds element e to the end of list l.
*/

list copy_list(list l);
/*
	Copies all elements of l1 to the new list l2
*/

unsigned int length(list l);
/*
	Returns the number of items in list l
*/

list concat(list l1, list l2);
/*
	Adds to the end of l all the elements of l0 in the same order
*/

list_elem index(list l, unsigned int n);
/*
 	PRE: length(l) > n
	Returns the n-th element of list l
*/

list take(list l, unsigned int n);
/*
	Leave in l only the first n elements, eliminating the rest
*/

list drop(list l, unsigned int n);
/*
	Removes the first n elements of l
*/	

#endif
