/*
** EPITECH PROJECT, 2026
** cvec_load.c
** File description:
** load and parse cvec binary files
*/

#include "cvec.h"

#include <stdlib.h>

static uint32_t compute_pool_size(const cvec_t *cvec)
{
    uint32_t total = 0;

    for (uint32_t i = 0; i < cvec->nb_words; ++i)
        total += cvec->index_table[i].length;
    return total;
}

static bool read_index_table(FILE *file, cvec_t *cvec)
{
    size_t count = cvec->nb_words;

    cvec->index_table = calloc(count, sizeof(word_index_entry_t));
    if (cvec->index_table == NULL)
        return false;
    return fread(cvec->index_table, sizeof(word_index_entry_t), count,
        file) == count;
}

static bool read_string_pool(FILE *file, cvec_t *cvec)
{
    size_t pool_size = compute_pool_size(cvec);

    cvec->string_pool = calloc(pool_size + 1, sizeof(char));
    if (cvec->string_pool == NULL)
        return false;
    return fread(cvec->string_pool, sizeof(char), pool_size, file)
        == pool_size;
}

static bool read_vectors(FILE *file, cvec_t *cvec)
{
    size_t count = (size_t)cvec->nb_words * cvec->dimensions;

    cvec->vectors = calloc(count, sizeof(float));
    if (cvec->vectors == NULL)
        return false;
    return fread(cvec->vectors, sizeof(float), count, file) == count;
}

static bool load_sections(FILE *file, cvec_t *cvec)
{
    if (!cvec_read_header(file, cvec))
        return false;
    if (!read_index_table(file, cvec))
        return false;
    if (!read_string_pool(file, cvec))
        return false;
    return read_vectors(file, cvec);
}

cvec_t *cvec_load(const char *path)
{
    FILE *file = fopen(path, "rb");
    cvec_t *cvec = calloc(1, sizeof(cvec_t));
    bool ok = false;

    if (file == NULL) {
        free(cvec);
        return NULL;
    }
    if (cvec == NULL) {
        fclose(file);
        return NULL;
    }
    ok = load_sections(file, cvec);
    fclose(file);
    if (!ok) {
        cvec_destroy(cvec);
        return NULL;
    }
    return cvec;
}
