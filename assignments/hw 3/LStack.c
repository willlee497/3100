/* NOTE: To test this program, you must create a copy of list.c and list.h that you've implemented in 1.1 */

#include "LStack.h"

void initStack(Stack * s)
{
  initList(&s->list);
  /* TODO: Fill this in. One line of code. */
}

void pushStack(Stack* stack, int number)
{
  /* TODO: Fill this in. One line of code. */
  pushBackList(&stack->list, number);
}

int popStack(Stack* stack)
{
  /* TODO: Fill this in. One line of code. */
  popBackList(&stack->list, number);
}

void freeStack(Stack* stack)
{
  /* TODO: Fill this in. One line of code. */
  freeList(&stack->list);
}  

void printStack(Stack* stack)
{
  printList(&stack->list);
  /* TODO: Fill this in. One line of code. */
}

int isEmpty(Stack* stack)
{
  return stack->list->head == NULL;
  /* TODO: Fill this in. One line of code. */
}
