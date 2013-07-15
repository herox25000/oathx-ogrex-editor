#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "tailor.h"

char nomIn[256],nomOut[256];
int method;

void main()
{
	int inOld,in,outOld,out;
	int op;

	inOld=dup(0);
	outOld=dup(1);
	
	printf( "fichier a zipper/dezipper : " );
	scanf( "%s", nomIn );

	printf( "operation (1:zip,2:dezip) : ");
	scanf( "%d", &op );

	in=open( nomIn, _O_BINARY | _O_RDONLY );
	if (in==-1)
	{ 
		printf("impossible ouvrir in\n"); 
		return; 
	}
	
	if (op==1) 
		sprintf(nomOut,"zip.out");
	else
		sprintf(nomOut,"paquet.paq");
	out=open( nomOut, _O_BINARY | _O_RDWR | _O_CREAT );
	if (out==-1)
	{ 
		printf("impossible ouvrir out\n"); 
		return; 
	}

	dup2(in,0);
	dup2(out,1);

	switch (op)
	{
	case 1:
		zip( in, out );
		break;
	case 2:
		method = get_method(in);
		if (method < 0) 
			do_exit(-1); /* error message already emitted */
		unzip(in, out );
		break;
	}

	close(in);
	close(out);

	dup2(inOld,0);
	dup2(outOld,0);
}