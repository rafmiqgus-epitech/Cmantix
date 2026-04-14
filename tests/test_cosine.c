/*
** EPITECH PROJECT, 2026
** test_cosine.c
** File description:
** tests for cosine similarity computation
*/

#include <criterion/criterion.h>
#include <math.h>
#include "similarity.h"

/* Identity and basic properties */

Test(cosine, identical_vectors_similarity_is_one)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

Test(cosine, opposite_vectors_similarity_is_negative_one)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

Test(cosine, orthogonal_vectors_similarity_is_zero)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

/* Symmetry property: sim(a,b) == sim(b,a) */

Test(cosine, similarity_is_symmetric)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

/* Scale invariance: sim(a,b) == sim(2a,b) */

Test(cosine, similarity_is_scale_invariant)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

/* Edge cases */

Test(cosine, zero_vector_returns_zero)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

Test(cosine, single_dimension_vectors)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

Test(cosine, null_vectors_returns_zero)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}

/* Precision */

Test(cosine, result_within_minus_one_to_one)
{
    cr_assert(1 == 0, "cosine similarity not implemented yet");
}
