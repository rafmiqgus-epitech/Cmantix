/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** vec2bin entry point
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sysexits.h>

#include "args.h"
#include "parse_vec.h"
#include "write_cvec.h"
#include "vec2bin.h"

static void print_help(void)
{
    printf("Usage: vec2bin <input.vec> <output.cvec>\n");
    printf("\n");
    printf("Converts FastText .vec text files to .cvec binary format.\n");
    printf("\n");
    printf("Arguments:\n");
    printf("  input.vec     Input file in FastText text format\n");
    printf("  output.cvec   Output file in CVEC binary format\n");
    printf("\n");
    printf("Options:\n");
    printf("  -h            Display this help message\n");
}

static int handle_args_error(const args_result_t *args_res)
{
    fprintf(stderr, "Error: %s", GET_ERROR(*args_res));
    if (args_res->type == ARGS_OSERR)
        return errno;
    return EX_USAGE;
}

static int convert_content(cvec_content_t *content, const char *output)
{
    write_result_t write_res = write_cvec(content, output);

    cvec_content_destroy(content);
    if (IS_ERROR(write_res)) {
        fprintf(stderr, "Error: %s", write_res.err_msg);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int run_conversion(args_ctx_t *args)
{
    parse_result_t parse_res = parse_vec(args->input);

    if (IS_ERROR(parse_res)) {
        fprintf(stderr, "Error: %s", GET_ERROR(parse_res));
        return EXIT_FAILURE;
    }
    return convert_content(parse_res.data.content, args->output);
}

int main(int argc, char **argv)
{
    args_result_t args_res = parse_args(argc, argv);
    int status = 0;

    if (IS_ERROR(args_res))
        return handle_args_error(&args_res);
    if (args_res.type == ARGS_HELP) {
        print_help();
        return EXIT_SUCCESS;
    }
    status = run_conversion(args_res.data.args);
    args_destroy(args_res.data.args);
    return status;
}
