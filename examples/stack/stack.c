
# include <stdlib.h> /* malloc, free */
# include <string.h> /* memcpy */

# include "stack.h"


struct stack_struct{

    int * top;
};

stack_t * stack_new(size_t elements){

    stack_t * stack;

    stack = malloc( sizeof(stack_t) + sizeof(int) * elements);

    if(stack != NULL){

        stack->top = (void *)(stack + 1);
    }

    return(stack);
}

void stack_delete(stack_t * stack){

    free(stack);
}

void stack_push(stack_t * stack, int element){

    memcpy(stack->top, &element, sizeof(element));

    stack->top++;
}

int stack_pop(stack_t * stack){

    int element;

    stack->top--;

    memcpy(&element, stack->top, sizeof(element));

    return(element);
}
