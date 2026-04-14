/*
** EPITECH PROJECT, 2026
** test_score.c
** File description:
** tests for temperature score conversion
*/

#include <criterion/criterion.h>
#include "similarity.h"

/* Score range: 0 to 1000 */

Test(score, identical_word_gives_1000)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}

Test(score, completely_dissimilar_gives_zero)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}

Test(score, mid_similarity_gives_mid_score)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}

/* Boundary tests */

Test(score, similarity_of_one_maps_to_1000)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}

Test(score, similarity_of_zero_maps_to_low_score)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}

Test(score, negative_similarity_maps_to_zero)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}

/* Monotonicity: higher similarity → higher score */

Test(score, higher_similarity_gives_higher_score)
{
    cr_assert(1 == 0, "score conversion not implemented yet");
}
