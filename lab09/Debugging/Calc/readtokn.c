/*----- FILE READTOKN.C ----------------------------------------------*/
/*                                                                    */
/* A function to read input and tokenize it for a simple calculator   */
/*                                                                    */
/* NOV 2018                                                           */
/*                                                                    */
/* Ganked from                                                        */
/*   https://www.ibm.com/support/knowledgecenter/SSGTSD_13.1.0/com.ibm.debugtool.doc_13.1/ugdita/tgstce.html#tgstce */
/*                                                                    */
/* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609                */
/*                                                                    */
/*--------------------------------------------------------------------*/
#include <ctype.h>
#include <stdio.h>
#include "calc.h"

extern char *word ;
extern FILE *fin ;

	/*--------------------------------------------------------------------*/
	/* output: buf - null terminated token                                */
	/* return: token type                                                 */
	/* action: reads chars through nextchar() and tokenizes them          */
	/*--------------------------------------------------------------------*/
Token read_token( char *buff )
{
	char fmt[10] ;
	sprintf( fmt, "%%%ds", (WORD_SIZE-1) ) ; 
	if( fscanf( fin, fmt, buff ) == EOF )
		return T_STOP ;

  switch( buff[0] )
  {
    case '+' : return T_PLUS;
    case '-' : return T_MINUS;
    case '*' : return T_TIMES;
    case '/' : return T_DIVIDE;
    case '=' : return T_EQUALS;
  }

	if( isdigit( buff[0] ))
		return T_INTEGER ;
	
	return T_ERROR ;
}

