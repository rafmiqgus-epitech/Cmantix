/*
** EPITECH PROJECT, 2026
** cvec_free.c
** File description:
** free cvec data structures
*/

#include "cvec.h"

#include <stdlib.h>

void cvec_destroy(cvec_t *cvec)
{
    if (cvec == NULL)
        return;
    free(cvec->index_table);
    free(cvec->string_pool);
    free(cvec->vectors);
    free(cvec);
}

const float *cvec_vector_at(const cvec_t *cvec, uint32_t vec_index)
{
    if (vec_index >= cvec->nb_words)
        return NULL;
    return cvec->vectors + (size_t)vec_index * cvec->dimensions;
}
