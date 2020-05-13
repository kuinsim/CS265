/*----- FILE PUSHPOP.C -----------------------------------------------*/
/*                                                                    */
/* A push and pop function for a stack of integers                    */
/*                                                                    */
/* NOV 2018                                                           */
/*                                                                    */
/* Ganked from                                                        */
/*   https://www.ibm.com/support/knowledgecenter/SSGTSD_13.1.0/com.ibm.debugtool.doc_13.1/ugdita/tgstce.html#tgstce */
/*                                                                    */
/* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609                */
/*                                                                    */
/*--------------------------------------------------------------------*/

#include <stdlib.h>
#include "calc.h"

	/*--------------------------------------------------------------------*/
	/* input:  stk - stack of integers                                    */
	/*         num - value to push on the stack                           */
	/* action: get a link to hold the pushed value, push link on stack    */
	/*                                                                    */
extern void push(IntStack * stk, int num)
{
  IntLink * ptr;
  ptr       = (IntLink *) malloc( sizeof(IntLink));  /*  PUSHPOP1   */
  ptr->i    = num;                /*  PUSHPOP2  statement */
  ptr->next = stk->top;
  stk->top  = ptr;

}

	/*--------------------------------------------------------------------*/
	/* return: int value popped from stack                                */
	/* action: pops top element from stack and gets return value from it  */
	/*--------------------------------------------------------------------*/
extern int pop(IntStack * stk)
{
  IntLink * ptr;
  int num;
  ptr      = stk->top;
  num      = ptr->i;
  stk->top = ptr->next;
  free(ptr);
  return num;
}
