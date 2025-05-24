#ifndef CUT_LIST_H
#define CUT_LIST_H

#include <stdbool.h>

#include "piece_values.h"
#include "vec.h"

typedef struct {
    PieceLengthValue pv;
    int count;
} PieceGroup;

typedef struct {
    Vec groups;
    PieceLength remainder;
    int total_value;
} CutList;

CutList *new_cutlist(Vec length_and_values, PieceLength length);
CutList *cutlist_copy(CutList *cl);
void cutlist_free(CutList *cl);

bool cutlist_can_add_piece(CutList *cl, PieceLengthValue pv);
CutList *cutlist_add_piece(CutList *cl, PieceLengthValue pv);

void cutlist_print(CutList *cl);

CutList *choose_best_cuts(CutList *starting_cutlist, Vec pv);
CutList *optimal_cutlist_for(Vec pv, PieceLength total_length);

#endif
