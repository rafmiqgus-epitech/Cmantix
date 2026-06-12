/*
** EPITECH PROJECT, 2026
** parse_vec.h
** File description:
** .vec file reading
*/

#ifndef PARSE_VEC_H_
    #define PARSE_VEC_H_

    #include <stdbool.h>

    #include "cvec_content.h"

    #define STR(x) #x
    #define XSTR(x) STR(x)
    #define ERR_MSG_BUF_SIZE 64

typedef enum {
    PARSE_OK,
    PARSE_ERR,
    PARSE_OSERR
} parse_result_type_t;

typedef struct {
    bool ok;
    parse_result_type_t type;
    union {
        char *err_msg;
        cvec_content_t *content;
    } data;
} parse_result_t;

parse_result_t parse_vec(const char *input_file);

#endif // !PARSE_VEC_H_
