
#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <stddef.h> /* NULL */

#include "stack.h"


int main(int argc, char *argv[]){

    stack_t * stack;
    int element;

    printf("Hello, world!\n");

    stack = stack_new(4);
    if(stack == NULL){

        printf("Could not allocate a new stack\n");
        return(EXIT_FAILURE);
    }

    stack_push(stack, -1);
    stack_push(stack, 20);
    stack_push(stack, 300);
    stack_push(stack, 4000);

    /* this elements will be lost */
    stack_push(stack, 50000);
    stack_push(stack, 600000);
    stack_push(stack, 7000000);
    stack_push(stack, 80000000);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    /* what if we pushed -1? */
    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    stack_delete(stack);

    return(EXIT_SUCCESS);
}
