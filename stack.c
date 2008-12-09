#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "cube.h"

/*
 * See stack.h for more info on this stuff
 */


/*
 * This should also consider a newly initialized stack, hopefully done with
 * calloc.  We can tell when stack->rightindex is null
 *
 * Copies the cube string given by cube_to_append
 *
 * Returns 1 on success, 0 on failure
 */
int stack_push(stacktype *stack, const char *cube_to_append, int turn, int distance)
{
    qdata *newq;
    if (stack->rightblock == NULL){
        /* initialize */
        stack->rightblock = malloc(sizeof(block));
        stack->rightblock->leftlink = NULL;
        stack->length = 0;
        stack->rightindex = -1;
    }
    else if (stack->rightindex == BLOCKLEN-1) {
        /* Needs a new block */
        block *newblock = malloc(sizeof(block));
        newblock->leftlink = stack->rightblock;
        stack->rightblock = newblock;
        stack->rightindex = -1;
    }
    stack->length++;
    stack->rightindex++;
    /* Now copy data in */
    newq = &(stack->rightblock->data[stack->rightindex]);
    memcpy(newq->cube_data, cube_to_append, CUBELEN);
    newq->turn = turn;
    newq->distance = distance;
    return 1;
}

/*
 * Returns 1 on success, 0 on failure
 */
int stack_pop(stacktype *stack)
{
    /* Just erase the last element */
    stack->length--;
    if (stack->rightindex == 0) {
        /* Freeing an entire block */
        block *oldblock = stack->rightblock;
        stack->rightblock = oldblock->leftlink;
        free(oldblock); /* goodbye */
        stack->rightindex = BLOCKLEN-1;
    } else {
        stack->rightindex--;
    }
    return 1;
}

int stack_peek_cube(stacktype *stack, cube_type *targetcube)
{
    memcpy(targetcube, stack->rightblock->data[stack->rightindex].cube_data, CUBELEN);
    return 1;
}
int stack_peek_turn(stacktype *stack)
{
    return stack->rightblock->data[stack->rightindex].turn;
}
    
int stack_peek_distance(stacktype *stack)
{
    return stack->rightblock->data[stack->rightindex].distance;
}
