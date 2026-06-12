/*
** EPITECH PROJECT, 2026
** args.h
** File description:
** args manipulation
*/

#ifndef ARGS_H_
    #define ARGS_H_

    #include <stdbool.h>

typedef enum {
    ARGS_OK,
    ARGS_HELP,
    ARGS_ERR,
    ARGS_OSERR
} args_result_type_t;

typedef struct {
    char *input;
    char *output;
} args_ctx_t;

typedef struct {
    bool ok;
    args_result_type_t type;
    union {
        char *err_msg;
        args_ctx_t *args;
    } data;
} args_result_t;

args_result_t parse_args(int argc, char **argv);
void args_destroy(args_ctx_t *args);

#endif // !ARGS_H_
