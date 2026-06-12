/*
** EPITECH PROJECT, 2026
** hash_table.c
** File description:
** hash table creation and lookup operations
*/

#include "hash.h"

#include <stdlib.h>
#include <string.h>

static hash_table_t *hash_table_create(size_t nb_buckets)
{
    hash_table_t *table = malloc(sizeof(hash_table_t));

    if (table == NULL)
        return NULL;
    table->buckets = calloc(nb_buckets, sizeof(hash_node_t *));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->nb_buckets = nb_buckets;
    return table;
}

static bool insert_word(hash_table_t *table, const char *word,
    uint32_t word_len, uint32_t vec_index)
{
    size_t bucket = hash_word(word, word_len, table->nb_buckets);
    hash_node_t *node = hash_node_create(word, word_len, vec_index);

    if (node == NULL)
        return false;
    node->next = table->buckets[bucket];
    table->buckets[bucket] = node;
    return true;
}

static bool fill_table(hash_table_t *table, const cvec_t *cvec)
{
    const word_index_entry_t *entry = NULL;

    for (uint32_t i = 0; i < cvec->nb_words; ++i) {
        entry = &cvec->index_table[i];
        if (!insert_word(table, cvec->string_pool + entry->offset,
                entry->length, entry->vec_index))
            return false;
    }
    return true;
}

hash_table_t *hash_table_build(const cvec_t *cvec)
{
    hash_table_t *table = hash_table_create(cvec->nb_words + 1);

    if (table == NULL)
        return NULL;
    if (!fill_table(table, cvec)) {
        hash_table_destroy(table);
        return NULL;
    }
    return table;
}

static void free_bucket(hash_node_t *node)
{
    hash_node_t *next = NULL;

    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
}

void hash_table_destroy(hash_table_t *table)
{
    if (table == NULL)
        return;
    for (size_t i = 0; i < table->nb_buckets; ++i)
        free_bucket(table->buckets[i]);
    free(table->buckets);
    free(table);
}

const hash_node_t *hash_table_lookup(const hash_table_t *table,
    const char *word)
{
    size_t len = strlen(word);
    size_t bucket = hash_word(word, len, table->nb_buckets);
    const hash_node_t *node = table->buckets[bucket];

    while (node != NULL) {
        if (node->word_len == len
            && strncmp(node->word, word, len) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}
