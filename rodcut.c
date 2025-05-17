#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "cache.h"
#include "cut_list.h"
#include "piece_values.h"
#include "vec.h"

static Vec global_pv;
ValueType cutlist_value_provider(KeyType key);
void usage(char *program_name);

#include "cache.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || !strcmp(argv[1], "-h"))
        usage(argv[0]);

    Vec value_list = read_piece_values_from_file(argv[1]);
    if (value_list == NULL) {
        fprintf(stderr, "Error reading value list from file: %s\n", argv[1]);
        return 1;
    }

    global_pv = value_list;

    // Loading dynamic cache module
    const char *libname = NULL;
    if (strstr(argv[0], "rr")) {
        libname = "./random_replacement.so";
    } else if (strstr(argv[0], "lru")) {
        libname = "./least_recently_used.so";
    } else {
        fprintf(stderr,
                "Unknown caching policy. Use rodcut_rr or rodcut_lru.\n");
        return 1;
    }

    Cache *cache = load_cache_module(libname);

    if (!cache) {
        fprintf(stderr, "Failed to load cache module\n");
        return 1;
    }

    // register caching provider
    ProviderFunction cached_func =
        cache->set_provider_func(cutlist_value_provider);

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
        int value = cached_func(lengths[i]);
        printf("Rod length:   %d\n", lengths[i]);
        printf("Value:     %5d\n\n", value);
    }

    cache->cache_cleanup();
    free(cache);

    vec_free(rod_lengths);
    vec_free(value_list);
    return 0;
}

ValueType cutlist_value_provider(KeyType key) {
    CutList *result = optimal_cutlist_for(global_pv, key);
    cutlist_print(result);  // prints for uncached values
    int value = result->total_value;
    cutlist_free(result);
    return value;
}

noreturn void usage(char *program_name) {
    fprintf(stderr,
            "Usage:\n"
            "%s [-h] value_file.txt\n"
            "Provide rod lengths via standard input, one per line.\n",
            program_name);
    exit(1);
}
