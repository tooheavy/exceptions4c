
# include <stdlib.h> /* malloc, free */
# include <string.h> /* memcpy */

# include "stack.h"


struct stack_struct{

    int * top;
    int * ceiling;
    int * bottom;
};

stack_t * stack_new(size_t elements){

    stack_t * stack;

    stack = malloc( sizeof(stack_t) + sizeof(int) * elements);

    // Check if could not allocate stack
    if(stack == NULL){

        return(NULL);
    }

    stack->bottom  = (void *)(stack + 1);
    stack->top     = stack->bottom;
    stack->ceiling = stack->bottom + elements;

    return(stack);
}

void stack_delete(stack_t * stack){

    free(stack);
}

void stack_push(stack_t * stack, int element){

    // Check if null stack
    if(stack == NULL){

        return;
    }

    // Check if full stack
    if(stack->top >= stack->ceiling){

        return;
    }

    memcpy(stack->top, &element, sizeof(element));

    stack->top++;
}

int stack_pop(stack_t * stack){

    int element;

    // Check if null stack
    if(stack == NULL){

        return(-1);
    }

    // Check if empty stack
    if(stack->top <= stack->bottom){

        return(-1);
    }

    stack->top--;

    memcpy(&element, stack->top, sizeof(element));

    return(element);
}
