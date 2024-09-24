/* NOTE: To test this program, you must create a copy of vector.c and vector.h that you've implemented in 1.2 */

#include "VStack.h"

void initStack(Stack * s)
{
  /* TODO: Fill this in. One line of code. */
  initVector(&s->vector);
}

void pushStack(Stack* stack, int number)
{
  /* TODO: Fill this in. One line of code. */
  pushFrontVector(&stack->vector, number);
}

int popStack(Stack* stack)
{
  return popBackVector(&stack->vector);
  /* TODO: Fill this in. One line of code. */

}

void freeStack(Stack* stack)
{
  freeVector(&stack->vector);
  /* TODO: Fill this in. One line of code. */
}

void printStack(Stack* stack)
{
  printVector(&stack->vector);
  /* TODO: Fill this in. One line of code. */
}

int isEmpty(Stack* stack)
{
  return stack->vector.size == 0;
  /* TODO: Fill this in. One line of code. */
}
