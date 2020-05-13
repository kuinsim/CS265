/* Suin Kim */
/* CS265-005 */
/* Lab 8 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "csv.h"


static char fieldsep[] = "," ; /* field separator chars */

	/***** Prototypes for local helper functions ******/
static char *advquoted( char* ) ;
static int split( csv_t* ) ;

	/* reset: set variables back to starting values */
static void reset( csv_t* S )
{
	free( S->line );	 /* free(NULL) permitted by ANSI C */
	free( S->sline ) ;
	free( S->field ) ;
	S->line = NULL ;
	S->sline = NULL ;
	S->field = NULL ;
	S->maxline = S->maxfield = S->nfield = 0 ;
}

csv_t* csv_init( FILE *f )
{
	csv_t *rv = (csv_t*) malloc( sizeof( csv_t )) ;
	rv->fin = f ;
	reset( rv ) ;

	return( rv ) ;
}


void kill( csv_t* s )
{
	reset( s ) ;
	free( s ) ;
}

/* TODO
 *  Copy all the functions (but for main) from csvgetline2 here.  Not the prototypes.  You already have them in
 *  csv.h.  Functions that access global CSV data need to be modified, take a pointer to a CSV struct as the first
 *  argument, and any references need to be modified
 */

	/* endofline: check for and consume \r, \n, \r\n, or EOF */
static int endofline( FILE *fin, int c )
{
	int eol ;

	eol = ( c=='\r' || c=='\n' ) ;
	if( c=='\r' ) {
		c = getc( fin ) ;
		if( c!='\n' && c != EOF )
			ungetc( c, fin ) ;	/* read too far; put c back */
	}
	return eol ;
}

	/* csvgetline:  get one line, grow as needed */
	/* sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
char* csvgetline( csv_t* S )
{	
	int i, c ;
	char *newl, *news ;

	if( S->line==NULL ) {			/* allocate on first call */
		S->maxline = S->maxfield = 1 ;
		S->line = (char*) malloc( S->maxline ) ;
		S->sline = (char*) malloc( S->maxline ) ;
		S->field = (char**) malloc( S->maxfield*sizeof( S->field[0] )) ;
		if( S->line==NULL || S->sline==NULL || S->field==NULL) {
			reset( S ) ;
			return NULL ;		/* out of memory */
		}
	}

	for( i=0; (c=getc( S->fin ))!=EOF && ! endofline(S->fin,c); i++ ) {
		if( i>=S->maxline-1 ) {	  /* grow line */
			S->maxline *= 2;		    /* double current size */
			newl = (char*) realloc( S->line, S->maxline ) ;
			if( newl==NULL ) {
				reset( S ) ;
				return NULL ;
			}
			S->line = newl ;
			news = (char*) realloc( S->sline, S->maxline ) ;
			if( news==NULL ) {
				reset( S ) ;
				return NULL ;
			}
			S->sline = news ;
		}
		S->line[i] = c ;
	}  /* for i */

	S->line[i] = '\0' ;
	if( split( S )==NOMEM ) {
		reset( S ) ;
		return NULL;			/* out of memory */
	}
	return (c==EOF && i==0) ? NULL : S->line ;
}

/* split: split line into fields */
int split( csv_t* S )
{
	char *p, **newf ;
	char *sepp; /* pointer to temporary separator character */
	int sepc;   /* temporary separator character */

	S->nfield = 0 ;
	if( S->line[0]=='\0' )
		return 0 ;
	strcpy( S->sline, S->line ) ;
	p = S->sline ;

	do {
		if( S->nfield>=S->maxfield ) {
			S->maxfield *= 2;			/* double current size */
			newf = (char**) realloc( S->field, 
							S->maxfield * sizeof( S->field[0] )) ;
			if( newf==NULL )
				return NOMEM ;
			S->field = newf ;
		}
		if( *p=='"' )
			sepp = advquoted( ++p ) ;	/* skip initial quote */
		else
			sepp = p + strcspn( p, fieldsep ) ;
		sepc = sepp[0] ;
		sepp[0] = '\0' ;			/* terminate field */
		S->field[S->nfield++] = p ;
		p = sepp + 1 ;
	} while( sepc==',' ) ;

	return S->nfield ;
}

/* advquoted: quoted field; return pointer to next separator */
char *advquoted( char* p )
{
	int i, j ;

	for( i=j=0; p[j]!='\0'; ++i, ++j ) {
		if( p[j]=='"' && p[++j]!='"' ) {
				/* copy up to next separator or \0 */
			int k = strcspn( p+j, fieldsep ) ;
			memmove( p+i, p+j, k ) ;
			i += k ;
			j += k ;
			break ;
		}
		p[i] = p[j] ;
	}
	p[i] = '\0' ;
	return p + j ;
}

/* csvfield:  return pointer to n-th field */
char* csvfield( csv_t* S, int n )
{
	if( n<0 || n>=S->nfield )
		return NULL ;
	return S->field[n] ;
}

/* csvnfield:  return number of fields */ 
int csvnfield( csv_t* S )
{
	return S->nfield ;
}

