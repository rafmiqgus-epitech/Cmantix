/*
** EPITECH PROJECT, 2026
** test_hash.c
** File description:
** tests for hash table word lookup
*/

#include <criterion/criterion.h>
#include <string.h>
#include "hash.h"

/* Hash function tests */

Test(hash, same_input_same_output)
{
    cr_assert(1 == 0, "hash function not implemented yet");
}

Test(hash, different_inputs_different_outputs)
{
    cr_assert(1 == 0, "hash function not implemented yet");
}

Test(hash, empty_string_does_not_crash)
{
    cr_assert(1 == 0, "hash function not implemented yet");
}

/* Hash table creation */

Test(hash, create_table_returns_non_null)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

Test(hash, create_table_zero_size_returns_null)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

/* Lookup tests */

Test(hash, lookup_existing_word_found)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

Test(hash, lookup_missing_word_returns_null)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

Test(hash, lookup_null_word_returns_null)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

Test(hash, insert_and_retrieve_many_words)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

/* Collision handling */

Test(hash, collision_both_words_retrievable)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}

/* Cleanup */

Test(hash, free_table_null_does_not_crash)
{
    cr_assert(1 == 0, "hash table not implemented yet");
}
