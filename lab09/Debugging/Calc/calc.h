/*----- FILE CALC.H --------------------------------------------------*/
/*                                                                    */
/* Header file for CALC.C PUSHPOP.C READTOKN.C                        */
/* a simple calculator                                                */
/*                                                                    */
/* NOV 2018                                                           */
/*                                                                    */
/* Ganked from                                                        */
/*   https://www.ibm.com/support/knowledgecenter/SSGTSD_13.1.0/com.ibm.debugtool.doc_13.1/ugdita/tgstce.html#tgstce */
/*                                                                    */
/* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609                */
/*                                                                    */
/*--------------------------------------------------------------------*/

typedef enum toks {
  T_INTEGER,
  T_PLUS,
  T_TIMES,
  T_MINUS,
  T_DIVIDE,
  T_EQUALS,
  T_STOP,
	T_ERROR
} Token;

enum{ WORD_SIZE=100 } ;

/* Token read_token(char buf[]); */
Token read_token() ;

typedef struct int_link  {
  struct int_link * next;
  int i;
} IntLink;

typedef struct int_stack {
  IntLink * top;
} IntStack;

extern void  push(IntStack *, int);

extern int pop(IntStack *);

