#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
	stack_elem peak;
	unsigned int height;
	struct _s_stack *next;
};

 
stack stack_empty() {
	return NULL;
}

stack stack_push(stack s, stack_elem e) {
	stack p = malloc(sizeof(struct _s_stack));
	p->peak = e;
	p->next = s;
	p->height = stack_size(s)+1;
	return p;
}

stack stack_pop(stack s) {
	stack p = s;
	stack q = p->next;
	free(p);
	return q;
}

unsigned int stack_size(stack s) {
	if (s==NULL) {
		return 0;
	}
	return s->height;
}

stack_elem stack_top(stack s) {
	assert(!stack_is_empty(s));
	return s->peak;
}

bool stack_is_empty(stack s) {
	return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
	stack_elem *arr = calloc(stack_size(s), sizeof(struct _s_stack));
	stack p = s;
	for (unsigned int i=stack_size(s); i>0u ; ++i) {
		arr[i-1] = p->peak;
		p = p->next;
	}
	return arr;
}

stack stack_destroy(stack s) {
	stack p = s;
	while (p!=NULL) {
		p = stack_pop(p);
	}
	return p;
}

