#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "cut_list.h"
#include "piece_values.h"
#include "vec.h"

void usage(char *program_name);

Vec read_piece_values_from_file(const char *filename);

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

Vec read_piece_values_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    Vec val_list = new_vec(sizeof(PieceLengthValue));
    PieceLengthValue item;

    while (fscanf(fp, "%d, %d\n", &item.length, &item.value) == 2) {
        if (item.length < 1 || item.value < 1) {
            vec_free(val_list);
            fclose(fp);
            return NULL;
        }

        PieceLengthValue *items = vec_items(val_list);
        bool duplicate          = false;
        for (size_t i = 0; i < vec_length(val_list); i++) {
            if (items[i].length == item.length) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            vec_free(val_list);
            fclose(fp);
            return NULL;
        }

        vec_add(val_list, &item);
    }

    fclose(fp);

    if (vec_length(val_list) == 0) {
        vec_free(val_list);
        return NULL;
    }

    qsort(vec_items(val_list), vec_length(val_list), sizeof(PieceLengthValue),
          (int (*)(const void *, const void *))compare_piece_values);

    return val_list;
}

noreturn void usage(char *program_name) {
    fprintf(stderr,
            "Usage:\n"
            "%s [-h] value_file.txt\n"
            "Provide rod lengths via standard input, one per line.\n",
            program_name);
    exit(1);
}
