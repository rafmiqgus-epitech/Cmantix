/*
** EPITECH PROJECT, 2026
** cosine.c
** File description:
** cosine similarity computation between word vectors
*/

#include "similarity.h"

#include <math.h>

static double dot_product(const float *a, const float *b, uint32_t dim)
{
    double sum = 0.0;

    for (uint32_t i = 0; i < dim; ++i)
        sum += (double)a[i] * (double)b[i];
    return sum;
}

static double vector_norm(const float *vec, uint32_t dim)
{
    double sum = 0.0;

    for (uint32_t i = 0; i < dim; ++i)
        sum += (double)vec[i] * (double)vec[i];
    return sqrt(sum);
}

float cosine_similarity(const float *a, const float *b, uint32_t dim)
{
    double norm_a = vector_norm(a, dim);
    double norm_b = vector_norm(b, dim);

    if (norm_a == 0.0 || norm_b == 0.0)
        return 0.0f;
    return (float)(dot_product(a, b, dim) / (norm_a * norm_b));
}
