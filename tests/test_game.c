/*
** EPITECH PROJECT, 2026
** test_game.c
** File description:
** tests for game logic and secret word selection
*/

#include <criterion/criterion.h>
#include <string.h>
#include "game.h"

/* Word of the day selection */

Test(game, same_date_gives_same_word)
{
    cr_assert(1 == 0, "word selection not implemented yet");
}

Test(game, different_date_gives_different_word)
{
    cr_assert(1 == 0, "word selection not implemented yet");
}

Test(game, selected_word_is_within_vocabulary)
{
    cr_assert(1 == 0, "word selection not implemented yet");
}

/* Guess processing */

Test(game, exact_match_is_victory)
{
    cr_assert(1 == 0, "guess processing not implemented yet");
}

Test(game, unknown_word_returns_error)
{
    cr_assert(1 == 0, "guess processing not implemented yet");
}

Test(game, duplicate_guess_detected)
{
    cr_assert(1 == 0, "guess processing not implemented yet");
}

Test(game, empty_guess_rejected)
{
    cr_assert(1 == 0, "guess processing not implemented yet");
}

/* Game state */

Test(game, init_returns_non_null)
{
    cr_assert(1 == 0, "game init not implemented yet");
}

Test(game, guess_count_increments)
{
    cr_assert(1 == 0, "game state not implemented yet");
}
