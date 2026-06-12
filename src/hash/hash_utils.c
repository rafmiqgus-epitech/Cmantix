/*
** EPITECH PROJECT, 2026
** hash_utils.c
** File description:
** hash function and collision handling
*/

#include "hash.h"

#include <stdlib.h>

size_t hash_word(const char *word, size_t len, size_t nb_buckets)
{
    size_t hash = 5381;

    for (size_t i = 0; i < len; ++i)
        hash = ((hash << 5) + hash) + (unsigned char)word[i];
    return hash % nb_buckets;
}

hash_node_t *hash_node_create(const char *word, uint32_t word_len,
    uint32_t vec_index)
{
    hash_node_t *node = malloc(sizeof(hash_node_t));

    if (node == NULL)
        return NULL;
    node->word = word;
    node->word_len = word_len;
    node->vec_index = vec_index;
    node->next = NULL;
    return node;
}
