/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** main entry file
*/

#include "cvec.h"
#include "hash.h"
#include "similarity.h"

#include <stdio.h>
#include <stdlib.h>

static const float *resolve_vector(const cvec_t *cvec,
    const hash_table_t *table, const char *word)
{
    const hash_node_t *node = hash_table_lookup(table, word);

    if (node == NULL) {
        fprintf(stderr, "word not found: %s\n", word);
        return NULL;
    }
    return cvec_vector_at(cvec, node->vec_index);
}

static int compare_words(const cvec_t *cvec, const hash_table_t *table,
    char **words)
{
    const float *vec_a = resolve_vector(cvec, table, words[0]);
    const float *vec_b = resolve_vector(cvec, table, words[1]);
    float similarity = 0.0f;

    if (vec_a == NULL || vec_b == NULL)
        return EXIT_FAILURE;
    similarity = cosine_similarity(vec_a, vec_b, cvec->dimensions);
    printf("%s <-> %s : similarity=%.4f score=%d\n", words[0], words[1],
        similarity, similarity_to_score(similarity));
    return EXIT_SUCCESS;
}

static int run_demo(const char *path, char **words)
{
    cvec_t *cvec = cvec_load(path);
    hash_table_t *table = NULL;
    int status = EXIT_FAILURE;

    if (cvec == NULL) {
        fprintf(stderr, "failed to load %s\n", path);
        return EXIT_FAILURE;
    }
    table = hash_table_build(cvec);
    if (table != NULL)
        status = compare_words(cvec, table, words);
    hash_table_destroy(table);
    cvec_destroy(cvec);
    return status;
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file.cvec> <word1> <word2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    return run_demo(argv[1], &argv[2]);
}
