
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

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, -1);
    }

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 20);
    }

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 300);
    }

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 4000);
    }

    /* these elements will be lost */
    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 50000);
    }

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 600000);
    }

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 7000000);
    }

    if( stack_is_full(stack) ){

        printf("Stack is full\n");
    }else{

        stack_push(stack, 80000000);
    }

    if( stack_is_empty(stack) ){

        printf("Stack is empty\n");
    }else{

        element = stack_pop(stack);
        printf("Pop: %d\n", element);
    }

    if( stack_is_empty(stack) ){

        printf("Stack is empty\n");
    }else{

        element = stack_pop(stack);
        printf("Pop: %d\n", element);
    }

    if( stack_is_empty(stack) ){

        printf("Stack is empty\n");
    }else{

        element = stack_pop(stack);
        printf("Pop: %d\n", element);
    }

    if( stack_is_empty(stack) ){

        printf("Stack is empty\n");
    }else{

        element = stack_pop(stack);
        printf("Pop: %d\n", element);
    }

	/* the stack will be empty here */
    if( stack_is_empty(stack) ){

        printf("Stack is empty\n");
    }else{

        element = stack_pop(stack);
        printf("Pop: %d\n", element);
    }

    stack_delete(stack);

    return(EXIT_SUCCESS);
}
