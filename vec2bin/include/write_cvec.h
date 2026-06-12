/*
** EPITECH PROJECT, 2026
** write_cvec.h
** File description:
** serialize in-memory cvec content to a .cvec binary file
*/

#ifndef WRITE_CVEC_H_
    #define WRITE_CVEC_H_

    #include <stdbool.h>

    #include "cvec_content.h"

typedef enum {
    WRITE_OK,
    WRITE_ERR,
    WRITE_OSERR
} write_result_type_t;

typedef struct {
    bool ok;
    write_result_type_t type;
    char *err_msg;
} write_result_t;

write_result_t write_cvec(const cvec_content_t *content,
    const char *output_file);

#endif /* !WRITE_CVEC_H_ */
