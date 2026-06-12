/*
** EPITECH PROJECT, 2026
** args.c
** File description:
** args manipulation
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "args.h"

static args_result_t args_ok(args_result_type_t type, args_ctx_t *args)
{
    args_result_t res = (args_result_t){
        .ok = true,
        .type = type,
        .data.args = args
    };

    return res;
}

static args_result_t args_err(args_result_type_t type, char *err_msg)
{
    args_result_t res = (args_result_t){
        .ok = false,
        .type = type,
        .data.err_msg = err_msg
    };

    return res;
}

static void free_input_output(char *input, char *output)
{
    free(input);
    free(output);
}

void args_destroy(args_ctx_t *args)
{
    if (args == NULL)
        return;
    free_input_output(args->input, args->output);
    free(args);
}

static args_ctx_t *args_build(char *input, char *output)
{
    args_ctx_t *args = NULL;

    if (input == NULL || output == NULL)
        return NULL;
    args = malloc(sizeof(args_ctx_t));
    if (args == NULL) {
        free_input_output(input, output);
        return NULL;
    }
    args->input = input;
    args->output = output;
    return args;
}

args_result_t parse_args(int argc, char **argv)
{
    char *input;
    char *output;
    args_ctx_t *args = NULL;

    if (argc <= 0 || argv == NULL)
        return args_err(ARGS_ERR, "Usage: vec2bin <input.vec> <output.cvec>\n");
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        return (args_result_t){ .ok = true, .type = ARGS_HELP };
    if (argc != 3)
        return args_err(ARGS_ERR, "Usage: vec2bin <input.vec> <output.cvec>\n");
    input = strdup(argv[1]);
    output = strdup(argv[2]);
    if (input == NULL || output == NULL) {
        free_input_output(input, output);
        return args_err(ARGS_OSERR, "error allocating memory for file path\n");
    }
    args = args_build(input, output);
    if (args == NULL)
        return args_err(ARGS_OSERR, "error allocating memory.\n");
    return args_ok(ARGS_OK, args);
}
