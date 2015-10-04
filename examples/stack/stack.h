
# ifndef STACK_H
# define STACK_H


/**
 * A stack represents a last-in-first-out (LIFO) collection of elements.
 *
 * Elements are stored as integers.
 *
 * When a stack is first created, it contains no elements.
 */
typedef struct stack_struct stack_t;


/**
 * Allocates an empty stack.
 *
 * @returns NULL if stack is too big to fit in memory
 */
extern stack_t * stack_new(size_t elements);

/**
 * Deallocates this stack.
 */
extern void stack_delete(stack_t * stack);

/**
 * Adds an element onto the top of this stack.
 */
extern void stack_push(stack_t * stack, int element);

/**
 * Removes the element at the top of this stack and returns that element as the value of this function.
 *
 * @returns -1 if stack is empty
 */
extern int stack_pop(stack_t * stack);


# endif
