/*
** EPITECH PROJECT, 2026
** cvec.h
** File description:
** cvec binary format loading and structures
*/

#ifndef CVEC_H_
    #define CVEC_H_

    #define CVEC_MAGIC_NUMBER 0x43455643
    #define CVEC_VERSION 1

    #include <stdint.h>
    #include <stdbool.h>
    #include <stdio.h>

typedef struct __attribute__((packed)) {
    uint32_t magic;
    uint32_t version;
    uint32_t nb_words;
    uint32_t dimensions;
} cvec_header_t;

typedef struct __attribute__((packed)) {
    uint32_t offset;
    uint32_t length;
    uint32_t vec_index;
} word_index_entry_t;

typedef struct {
    uint32_t nb_words;
    uint32_t dimensions;
    word_index_entry_t *index_table;
    char *string_pool;
    float *vectors;
} cvec_t;

bool cvec_read_header(FILE *file, cvec_t *cvec);
cvec_t *cvec_load(const char *path);
void cvec_destroy(cvec_t *cvec);
const float *cvec_vector_at(const cvec_t *cvec, uint32_t vec_index);

#endif /* !CVEC_H_ */
