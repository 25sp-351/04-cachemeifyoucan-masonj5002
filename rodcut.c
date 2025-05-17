#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "cut_list.h"
#include "piece_values.h"
#include "vec.h"

void usage(char *program_name);

int main(int argc, char *argv[]) {
    if (argc != 2 || !strcmp(argv[1], "-h"))
        usage(argv[0]);

    Vec value_list = read_piece_values_from_file(argv[1]);
    if (value_list == NULL) {
        fprintf(stderr, "Error reading value list from file: %s\n", argv[1]);
        return 1;
    }

    Vec rod_lengths = new_vec(sizeof(int));
    int rod_length;
    while (scanf("%d", &rod_length) == 1) {
        if (rod_length < 1) {
            fprintf(stderr, "Invalid rod length: %d\n", rod_length);
            continue;
        }
        vec_add(rod_lengths, &rod_length);
    }

    int *lengths = vec_items(rod_lengths);
    for (size_t i = 0; i < vec_length(rod_lengths); i++) {
        CutList *cl = optimal_cutlist_for(value_list, lengths[i]);
        printf("Rod length: %d\n", lengths[i]);
        cutlist_print(cl);
        printf("\n");
        cutlist_free(cl);
    }

    vec_free(rod_lengths);
    vec_free(value_list);
    return 0;
}

noreturn void usage(char *program_name) {
    fprintf(stderr,
            "Usage:\n"
            "%s [-h] value_file.txt\n"
            "Provide rod lengths via standard input, one per line.\n",
            program_name);
    exit(1);
}
