/*
** EPITECH PROJECT, 2017
** MY_HUNTER
** File description:
** MY
*/

#include "display.h"

void swap_texture(bird_t *bird, sfIntRect *size, sfIntRect *size2, sfImage *img)
{
	sfTexture_destroy(bird->tex[0]);
	sfTexture_destroy(bird->tex[1]);
	bird->tex[0] = sfTexture_createFromImage(
	img, size);
	bird->tex[1] = sfTexture_createFromImage(
	img, size2);
	sfSprite_setTexture(bird->spr[0],
	bird->tex[0], sfTrue);
	sfSprite_setTexture(bird->spr[1],
	bird->tex[1], sfTrue);
	bird->is_dead = 1;
}

void test_collision(bird_t *bird)
{
	if (bird->pos.x + bird->vit.x + 53 >= WIDTH)
		bird->vit.x *= -1;
	if (bird->pos.y + bird->vit.y <= 0)
		bird->vit.y *= -1;
	if (bird->pos.y + bird->vit.y > 540
	&& bird->is_dead == 0) {
		bird->vit.y *= -1;
	}
	else if (bird->is_dead)
		bird->vit.y = 7;
}

void apply_speed(bird_t **bird, sfClock *clock)
{
	sfIntRect img = {0, 0, 53, 40};
	sfTime tmp = sfClock_getElapsedTime(clock);
	char clk = 0;

	for (int i = 0; bird[i]; i++) {
		if (bird[i]->go) {
			if (sfTime_asMilliseconds(tmp) > rand() % 1300 + 700) {
				bird[i]->vit.y = rand() % 3 - 1;
				clk = 1;
			}
			test_collision(bird[i]);
			apply_texture(bird[i], &img);
		}
	}
	if (clk)
		sfClock_restart(clock);
}

void destroy_game(game_t *game)
{
	free(game->type_bird);
	sfClock_destroy(game->clock);
	sfClock_destroy(game->bounce);
	sfClock_destroy(game->add);
	sfMusic_destroy(game->music);
	sfMusic_destroy(game->tir);
	destroy_bird(game->bird);
	sfTexture_destroy((void *)sfSprite_getTexture(game->s_back));
	sfTexture_destroy((void *)sfSprite_getTexture(game->aim));
	sfTexture_destroy((void *)sfSprite_getTexture(game->s_heart));
	sfSprite_destroy(game->s_back);
	sfSprite_destroy(game->aim);
	sfSprite_destroy(game->s_heart);
	sfTexture_destroy(game->t_aim);
	sfTexture_destroy(game->t_back);
	sfTexture_destroy(game->t_heart);
	sfText_destroy(game->score_text);
	sfText_destroy(game->highscore_text);
	sfFont_destroy(game->font);
	free(game);
}
