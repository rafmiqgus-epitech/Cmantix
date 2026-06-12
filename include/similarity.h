/*
** EPITECH PROJECT, 2026
** similarity.h
** File description:
** cosine similarity and temperature score computation
*/

#ifndef SIMILARITY_H_
    #define SIMILARITY_H_

    #include <stdint.h>

    #define SCORE_MIN 0
    #define SCORE_MAX 1000

float cosine_similarity(const float *a, const float *b, uint32_t dim);
int similarity_to_score(float similarity);

#endif /* !SIMILARITY_H_ */
