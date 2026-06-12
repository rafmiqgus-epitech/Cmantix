/*
** EPITECH PROJECT, 2026
** hash.h
** File description:
** hash table for word to vector lookup
*/

#ifndef HASH_H_
    #define HASH_H_

    #include <stdint.h>
    #include <stddef.h>

    #include "cvec.h"

typedef struct hash_node_s {
    const char *word;
    uint32_t word_len;
    uint32_t vec_index;
    struct hash_node_s *next;
} hash_node_t;

typedef struct {
    hash_node_t **buckets;
    size_t nb_buckets;
} hash_table_t;

hash_table_t *hash_table_build(const cvec_t *cvec);
void hash_table_destroy(hash_table_t *table);
const hash_node_t *hash_table_lookup(const hash_table_t *table,
    const char *word);
size_t hash_word(const char *word, size_t len, size_t nb_buckets);
hash_node_t *hash_node_create(const char *word, uint32_t word_len,
    uint32_t vec_index);

#endif /* !HASH_H_ */
