/*
** EPITECH PROJECT, 2026
** cvec_content.c
** File description:
** lifecycle of the in-memory cvec content (build and destroy)
*/

#include "cvec_content.h"
#include "cvec.h"

#include <stdlib.h>

static bool allocate_buffers(cvec_content_t *content)
{
    content->index_table = calloc(content->nb_words,
        sizeof(word_index_entry_t));
    content->vectors = calloc(content->nb_words * content->dimensions,
        sizeof(float));
    content->string_pool.pool = calloc(DEFAULT_STRING_POOL_SIZE,
        sizeof(char));
    if (content->index_table == NULL || content->vectors == NULL
        || content->string_pool.pool == NULL)
        return false;
    content->string_pool.cap = DEFAULT_STRING_POOL_SIZE;
    return true;
}

cvec_content_t *cvec_content_build(uint32_t nb_words, uint32_t dimensions)
{
    cvec_content_t *content = calloc(1, sizeof(cvec_content_t));

    if (content == NULL)
        return NULL;
    content->nb_words = nb_words;
    content->dimensions = dimensions;
    if (!allocate_buffers(content)) {
        cvec_content_destroy(content);
        return NULL;
    }
    return content;
}

void cvec_content_destroy(cvec_content_t *content)
{
    if (content == NULL)
        return;
    free(content->index_table);
    free(content->vectors);
    free(content->string_pool.pool);
    free(content);
}
