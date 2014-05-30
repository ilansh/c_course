#include <stdio.h>
#include "ErrorHandle.h"

void reportError(BoardErrors boardError)
{
	switch (boardError) {
		case MEM_OUT:
			fprintf(stderr, "ERROR: Out Of Memory\n");
			return;
		case OUT_OF_BOUND:
			fprintf(stderr, "ERROR: Out Of Board Bounds\n");
			return;
		case SQUARE_FULL:
			fprintf(stderr, "ERROR: Can not mark the square - square already full.\n");
			return;
		case WRONG_TURN:
			fprintf(stderr, "ERROR: Can not change the square - it's not your turn\n");
			return;
		case BAD_VAL:
			fprintf(stderr, "ERROR: Wrong input parameter for \'val\'\n");
			return;
		case ILLEGAL_CANCELLATION:
			fprintf(stderr, "ERROR: Can not cancel the move - request is illegal\n");
			return;
		default:
			fprintf(stderr, "ERROR: General error.\n");
			return;
	}
}
