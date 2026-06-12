/*
** EPITECH PROJECT, 2026
** cvec_content.h
** File description:
** in-memory cvec content structure and lifecycle
*/

#ifndef CVEC_CONTENT_H_
    #define CVEC_CONTENT_H_

    #include <stdint.h>
    #include <stdbool.h>

    #include "cvec.h"

    #define MAX_WORD_LEN 256
    #define DEFAULT_STRING_POOL_SIZE 524288

typedef struct {
    char *pool;
    uint32_t size;
    uint32_t cap;
} string_pool_t;

typedef struct {
    uint32_t nb_words;
    uint32_t dimensions;
    word_index_entry_t *index_table;
    string_pool_t string_pool;
    float *vectors;
} cvec_content_t;

cvec_content_t *cvec_content_build(uint32_t nb_words, uint32_t dimensions);
void cvec_content_destroy(cvec_content_t *content);

#endif /* !CVEC_CONTENT_H_ */
