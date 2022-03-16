#include <stdlib.h>
#include "stack.h"

stack_t * 
create_stack (int capacity) 
{
	stack_t * stack = (stack_t *) malloc(sizeof(stack_t)) ;
	stack->capacity = capacity ;
	stack->top = 0 ;
	stack->buffer = (int *) calloc(capacity, sizeof(int)) ;
	return stack ; 
}

void
delete_stack (stack_t * stack) 
{
	free(stack->buffer) ;
	free(stack) ;
}

int 
push (stack_t * stack, int elem)
{
	if (is_full(stack))
		return 1 ;
	
	stack->buffer[stack->top] = elem ;
	stack->top += 1 ;
	return 0 ;
}

int
pop (stack_t * stack, int * elem)
{
	if (is_empty(stack)) 
		return 1 ;
	
	*elem = stack->buffer[stack->top - 1] ;
	stack->top -= 1 ;
	return 0;
}

int 
is_empty (stack_t * stack) 
{
	return (stack->top == 0) ;
}

int 
is_full (stack_t * stack) 
{
	return (stack->top == stack->capacity) ;
}

int
get_size (stack_t * stack) 
{
	return stack->top ;
}

int
get_element (stack_t * stack, int index, int * elem)
{
	if (stack->top <= index) 
		return 1 ;

	*elem = stack->buffer[index] ;
	return 0 ;
}
