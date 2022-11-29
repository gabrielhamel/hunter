/*
** EPITECH PROJECT, 2017
** SCRREN
** File description:
** SCREEN
*/

#include "display.h"

#include <stdio.h>

hit_value_t *create_hit(game_t *game, int score_value, sfVector2i *pos)
{
    char buff[9] = {0};
    hit_value_t *hit = malloc(sizeof(hit_value_t));

    hit->text = sfText_create();
    sfText_setFont(hit->text, game->font),
    sfText_setFillColor(hit->text, sfBlack);
    sprintf(buff, "%d", score_value);
    sfText_setString(hit->text, buff);
    sfText_setPosition(hit->text, (sfVector2f){pos->x - 15, pos->y - 30});
    return hit;
}

void append_hit(game_t *game, hit_value_t *hit)
{
    if (game->hit_scores == NULL) {
        game->hit_scores = malloc(sizeof(hit_value_t *) * 2);
        game->hit_scores[0] = hit;
        game->hit_scores[1] = NULL;
        return;
    }
    // Compute length
    size_t length = 0;
    for (; game->hit_scores[length]; length++);
    // Realloc array
    game->hit_scores = realloc(game->hit_scores, sizeof(hit_value_t *) * (length + 2));
    game->hit_scores[length] = hit;
    game->hit_scores[length + 1] = NULL;
}

void draw_hits_marker(game_t *game, sfRenderWindow *win)
{
    if (!game->hit_scores)
        return;
    for (size_t idx = 0; game->hit_scores[idx]; idx++) {
        sfRenderWindow_drawText(win, game->hit_scores[idx]->text, NULL);

        sfText_move(game->hit_scores[idx]->text, (sfVector2f){0, - 3});

    }
}