#ifndef PIECE_VALUES_H
#define PIECE_VALUES_H

#include <stdbool.h>

#include "vec.h"

typedef int PieceLength;
typedef int PieceValue;

typedef struct pv {
    PieceLength length;
    PieceValue value;
} PieceLengthValue;

// Returns NULL if there is an error in the input
// Returns them sorted by value then length (both descending)
int compare_piece_values( PieceLengthValue* a, PieceLengthValue *b );
Vec read_piece_values_from_file(const char *filename);
Vec read_piece_values_from_stdin();
void print_piece_values( Vec ptr );
bool pvs_equal( PieceLengthValue *pv1, PieceLengthValue *pv2 );

#endif
