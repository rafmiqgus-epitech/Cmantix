/*
** EPITECH PROJECT, 2026
** cvec_header.c
** File description:
** read and validate cvec file header
*/

#include "cvec.h"

#include <stdio.h>

static bool is_valid_header(const cvec_header_t *header)
{
    if (header->magic != CVEC_MAGIC_NUMBER)
        return false;
    if (header->version != CVEC_VERSION)
        return false;
    if (header->nb_words == 0 || header->dimensions == 0)
        return false;
    return true;
}

bool cvec_read_header(FILE *file, cvec_t *cvec)
{
    cvec_header_t header = {0};

    if (fread(&header, sizeof(header), 1, file) != 1)
        return false;
    if (!is_valid_header(&header))
        return false;
    cvec->nb_words = header.nb_words;
    cvec->dimensions = header.dimensions;
    return true;
}
