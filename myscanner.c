#include <stdio.h>
#include "myscanner.h"

extern int yylineno;
extern int yylex();
extern char* yytext;

char* names[] = {NULL, "db_type", "db_name", "db_prefix", "db_port"};

int main(void)
{
	int ntoken, vtoken;
	
	ntoken = yylex();

	while(ntoken) //yylex returns 0 for eof
	{
		printf("%d\n", ntoken);
		if(yylex() !=COLON)
		{
			printf("Syntax error in line %d, expected a ':' but found %s\n", yylineno, yytext);
			return 1; // exit compilation
		}
		vtoken = yylex();
		switch(ntoken)
		{
			case TYPE:
			case NAME:
			case TABLE_PREFIX:
			 if(vtoken!=IDENTIFIER)
			 {
			 printf("Syntax error in line %d, expected an identifier but found %s\n", yylineno, yytext);
				return 1;
			 }
			 printf("DataType %s is set to %s\n", names[ntoken], yytext);
			 break;

			case PORT:
			 if(vtoken!=INTEGER)
			 {
				 printf("Syntax error in line %d, expected an integer but found %s\n", yylineno, yytext);
				return 1;
			 }
			printf("DataType %s is set to %s\n", names[ntoken],     yytext);
			break;

			default:
			printf("Syntax error in line %d\n", yylineno);
		}
		ntoken = yylex();
	} 

	return 0;
}
