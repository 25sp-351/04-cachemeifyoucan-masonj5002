#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "piece_values.h"
#include "cut_list.h"
#include "vec.h"

void usage(char *program_name);

int main(int argc, char *argv[]) {
    int rod_length = 0;

    if (argc != 2 || !strcmp(argv[1], "-h"))
        usage(argv[0]);

    int arg_len;
    if (1 != sscanf(argv[1], "%d%n", &rod_length, &arg_len) ||
        arg_len != strlen(argv[1]) || rod_length < 1)
        usage(argv[0]);

    Vec value_list = read_piece_values();

    if (value_list == NULL) {
        fprintf(stderr,"Error in value list.\n");
        return 1;
    }

    //print_piece_values(value_list);

    CutList *cl = optimal_cutlist_for(value_list, rod_length);

    cutlist_print(cl);

    cutlist_free(cl);

    return 0;
}

noreturn void usage(char *program_name) {
    fprintf(stderr,
            "Usage:\n"
            "%s [-h] length\n"
            "length = integer > 0\n",
            program_name);
    exit(1);
}
