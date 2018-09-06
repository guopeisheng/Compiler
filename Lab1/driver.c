#include <stdio.h>
extern FILE *yyin;
int yyparse( );
int errCnt;
int lineNo;

int main (int argc, char** argv) {
if (argc == 2) {
	if (!strcmp("-h", argv[1])) {
		printf(" The command line syntax should be\n");
		printf(" demo [-h] [filename]\n");
		printf(" where items in square brackets ( [ and ] ) are optional.\n");
    return 0;
	} 
  else {
		yyin=fopen(argv[1], "r");
	}
} else {
	yyin = stdin;
}

yyparse();

if (errCnt == 0) {
    fprintf(stderr,"Parser succeeds.\n");
  }
  else { /* first, complain */
    fprintf(stderr,"\nParser fails with %d error messages.\nExecution halts.\n",
	    errCnt);
  }
}