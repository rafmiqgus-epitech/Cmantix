/*
** EPITECH PROJECT, 2026
** parse_vec.c
** File description:
** parse FastText .vec text files
*/

#include "parse_vec.h"
#include "cvec.h"
#include "vec2bin.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

static parse_result_t parse_ok(parse_result_type_t type,
    cvec_content_t *content)
{
    parse_result_t res = (parse_result_t){
        .ok = true,
        .type = type,
        .data.content = content
    };

    return res;
}

static parse_result_t parse_err(parse_result_type_t type,
    char *err_msg)
{
    parse_result_t res = (parse_result_t){
        .ok = false,
        .type = type,
        .data.err_msg = err_msg
    };

    return res;
}

static bool read_word_dimensions(cvec_content_t *content,
    FILE *vec_file, uint32_t i)
{
    uint32_t dimensions = content->dimensions;

    for (uint32_t j = 0; j < dimensions; ++j) {
        if (fscanf(vec_file, "%f",
                &content->vectors[i * dimensions + j]) != 1)
            return false;
    }
    return true;
}

static bool string_pool_word_append(char word_buf[MAX_WORD_LEN + 1],
    size_t word_len, string_pool_t *string_pool)
{
    char *new_pool = NULL;
    size_t new_cap = 0;

    if ((string_pool->size + word_len) >= string_pool->cap) {
        new_cap = string_pool->cap * 2;
        new_pool = realloc(string_pool->pool, new_cap);
        if (new_pool == NULL)
            return false;
        string_pool->pool = new_pool;
        string_pool->cap = new_cap;
    }
    memcpy(string_pool->pool + string_pool->size, word_buf, word_len);
    string_pool->size += word_len;
    return true;
}

static bool read_one_word(cvec_content_t *content, FILE *vec_file, uint32_t i)
{
    char word_buf[MAX_WORD_LEN + 1];
    word_index_entry_t *entry = &content->index_table[i];
    size_t word_len = 0;

    if (fscanf(vec_file, "%" XSTR(MAX_WORD_LEN) "s", word_buf) != 1)
        return false;
    if (!read_word_dimensions(content, vec_file, i))
        return false;
    word_len = strlen(word_buf);
    entry->offset = content->string_pool.size;
    entry->length = word_len;
    entry->vec_index = i;
    return string_pool_word_append(word_buf, word_len, &content->string_pool);
}

static parse_result_t read_words(cvec_content_t *content, FILE *vec_file)
{
    if (content == NULL || vec_file == NULL)
        return parse_err(PARSE_OSERR, "something went wrong...\n");
    for (uint32_t i = 0; i < content->nb_words; ++i) {
        if (!read_one_word(content, vec_file, i))
            return parse_err(PARSE_ERR, "invalid word format\n");
    }
    return parse_ok(PARSE_OK, content);
}

static parse_result_t read_header(FILE *vec_file, uint32_t *nb_words,
    uint32_t *dimensions)
{
    struct stat st;

    if (fstat(fileno(vec_file), &st) == -1)
        return parse_err(PARSE_OSERR, strerror(errno));
    if (!S_ISREG(st.st_mode))
        return parse_err(PARSE_ERR, "input file is not regular file.\n");
    if (fscanf(vec_file, "%u %u", nb_words, dimensions) != 2)
        return parse_err(PARSE_ERR, "invalid .vec header\n");
    if (*nb_words == 0 || *dimensions == 0)
        return parse_err(PARSE_ERR,
            "invalid word count or dimensions in .vec header.\n");
    return parse_ok(PARSE_OK, NULL);
}

static parse_result_t get_vec_data(FILE *vec_file)
{
    uint32_t nb_words = 0;
    uint32_t dimensions = 0;
    parse_result_t header_status = read_header(vec_file, &nb_words,
        &dimensions);
    parse_result_t words_status = {0};
    cvec_content_t *content = NULL;

    if (IS_ERROR(header_status))
        return header_status;
    content = cvec_content_build(nb_words, dimensions);
    if (content == NULL)
        return parse_err(PARSE_OSERR, "failed to allocate memory.\n");
    words_status = read_words(content, vec_file);
    if (IS_ERROR(words_status))
        cvec_content_destroy(content);
    return words_status;
}

parse_result_t parse_vec(const char *input_file)
{
    parse_result_t status = {0};
    FILE *vec_file = fopen(input_file, "r");

    if (vec_file == NULL)
        return parse_err(PARSE_OSERR, strerror(errno));
    status = get_vec_data(vec_file);
    fclose(vec_file);
    return status;
}
