/*
** EPITECH PROJECT, 2026
** vec2bin.h
** File description:
** vec2bin converter header
*/

#ifndef VEC2BIN_H_
    #define VEC2BIN_H_

    #include <stdbool.h>

    #define IS_OK(result) ((result).ok)
    #define IS_ERROR(result) (!(result).ok)
    #define GET_ERROR(result) ((result).data.err_msg)

#endif /* !VEC2BIN_H_ */
