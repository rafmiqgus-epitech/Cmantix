/*
** EPITECH PROJECT, 2026
** write_cvec.c
** File description:
** write cvec binary format output
*/

#include "write_cvec.h"
#include "cvec.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

static write_result_t write_ok(void)
{
    return (write_result_t){ .ok = true, .type = WRITE_OK, .err_msg = NULL };
}

static write_result_t write_err(write_result_type_t type, char *err_msg)
{
    return (write_result_t){ .ok = false, .type = type, .err_msg = err_msg };
}

static bool write_header(const cvec_content_t *content, FILE *out)
{
    cvec_header_t header = {
        .magic = CVEC_MAGIC_NUMBER,
        .version = CVEC_VERSION,
        .nb_words = content->nb_words,
        .dimensions = content->dimensions
    };

    return fwrite(&header, sizeof(header), 1, out) == 1;
}

static bool write_index_table(const cvec_content_t *content, FILE *out)
{
    size_t nb_words = content->nb_words;

    return fwrite(content->index_table, sizeof(word_index_entry_t),
        nb_words, out) == nb_words;
}

static bool write_string_pool(const cvec_content_t *content, FILE *out)
{
    size_t size = content->string_pool.size;

    return fwrite(content->string_pool.pool, sizeof(char), size, out) == size;
}

static bool write_vectors(const cvec_content_t *content, FILE *out)
{
    size_t count = (size_t)content->nb_words * content->dimensions;

    return fwrite(content->vectors, sizeof(float), count, out) == count;
}

static bool write_sections(const cvec_content_t *content, FILE *out)
{
    return write_header(content, out)
        && write_index_table(content, out)
        && write_string_pool(content, out)
        && write_vectors(content, out);
}

write_result_t write_cvec(const cvec_content_t *content,
    const char *output_file)
{
    FILE *out = fopen(output_file, "wb");
    bool ok = false;

    if (out == NULL)
        return write_err(WRITE_OSERR, strerror(errno));
    ok = write_sections(content, out);
    fclose(out);
    if (!ok)
        return write_err(WRITE_ERR, "failed to write .cvec file\n");
    return write_ok();
}
