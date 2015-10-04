
#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */

#include "stack.h"


int main(int argc, char *argv[]){

    stack_t * stack;
    int element;

    printf("Hello, world!\n");

    stack = stack_new(4);

    stack_push(stack, 1);
    stack_push(stack, 20);
    stack_push(stack, 300);
    stack_push(stack, 4000);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    element = stack_pop(stack);
    printf("Pop: %d\n", element);

    stack_delete(stack);

    return(EXIT_SUCCESS);
}
