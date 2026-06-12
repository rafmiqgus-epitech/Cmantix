/*
** EPITECH PROJECT, 2026
** score.c
** File description:
** convert cosine similarity to temperature score
*/

#include "similarity.h"

int similarity_to_score(float similarity)
{
    int score = (int)(similarity * SCORE_MAX);

    if (score < SCORE_MIN)
        return SCORE_MIN;
    if (score > SCORE_MAX)
        return SCORE_MAX;
    return score;
}
