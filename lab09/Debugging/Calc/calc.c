/*----- FILE CALC.C --------------------------------------------------*/
/*                                                                    */
/* A simple calculator that does operations on integers that          */
/* are pushed and popped on a stack                                   */
/*                                                                    */
/* NOV 2018                                                           */
/*                                                                    */
/* Ganked from                                                        */
/*   https://www.ibm.com/support/knowledgecenter/SSGTSD_13.1.0/com.ibm.debugtool.doc_13.1/ugdita/tgstce.html#tgstce */
/*                                                                    */
/* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609                */
/*                                                                    */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

IntStack stack = { 0 };
FILE *fin = NULL ;

int main( int argc, char **argv )
{
  Token tok;
	char word[WORD_SIZE] ;
  char buf_out[100];
  int num, num2;
	fin = stdin ;


  for(;;)
  {
    tok = read_token( word ) ;

    switch(tok)
    {
      case T_STOP:
        break;
      case T_INTEGER:
        num = atoi(word);
        push(&stack,num);     /*  CALC1  statement */
        break;
      case T_PLUS:
        push(&stack, pop(&stack)+pop(&stack) );
        break;
      case T_MINUS:
        num = pop(&stack);
        push(&stack, pop(&stack)-num); //switch order of num and pop(&stack)
        break;
      case T_TIMES:
        push(&stack, pop(&stack)*pop(&stack));
        break;
      case T_DIVIDE:
        num2 = pop(&stack);
        num = pop(&stack);
        push(&stack, num/num2);   /* CALC2  statement */
        break;
      case T_EQUALS:
        num = pop(&stack);
        sprintf(buf_out,"= %d ",num);
				fprintf( stdout, "%s\n", buf_out ) ;
        push(&stack,num);
        break;
    }
    if (tok==T_STOP)
      break;
  }
  return 0;
}

