/*
** EPITECH PROJECT, 2017
** Hunt
** File description:
** Hunt
*/

#include "display.h"

sfSprite *load_sprite(char *name, sfTexture *tex)
{
	sfSprite *spr = sfSprite_create();

	tex = sfTexture_createFromFile(name, NULL);
	sfSprite_setTexture(spr, tex, sfTrue);
	return (spr);
}

void add_bird(bird_t **bird, sfClock *clock)
{
	sfTime tmp = sfClock_getElapsedTime(clock);

	if (sfTime_asMilliseconds(tmp) > 1000) {
		bird[rand() % BIRDS_NB]->go = 1;
		sfClock_restart(clock);
	}
}

void draw_bird(bird_t **bird, sfRenderWindow *win, sfClock *clock)
{
	sfTime tmp = sfClock_getElapsedTime(clock);
	char clk = 0;

	for (int i = 0; bird[i] != NULL; i++) {
		if (bird[i]->go) {
			(sfTime_asMilliseconds(tmp) > 470) ?
			bird[i]->anim = (bird[i]->anim + 1) % 2 : 0;
			(sfTime_asMilliseconds(tmp) > 470) ? clk = 1: 0;
			(!bird[i]->anim) ? sfRenderWindow_drawSprite(
			win, bird[i]->spr[0], NULL)
			: sfRenderWindow_drawSprite(win, bird[i]->spr[1], NULL);
		}
	}
	if (clk)
		sfClock_restart(clock);
}

void draw_hearts(game_t *game, sfRenderWindow *win)
{
	for (int i = 0; i < game->life; i++) {
		sfSprite_setPosition(game->s_heart, (sfVector2f){60 * i + 25, HEIGHT - 75});
		sfRenderWindow_drawSprite(win, game->s_heart, NULL);
	}
}

void destroy_bird(bird_t **bird)
{
	for (int i = 0; bird[i] != NULL; i++) {
		sfSprite_destroy(bird[i]->spr[0]);
		sfSprite_destroy(bird[i]->spr[1]);
		sfTexture_destroy(bird[i]->tex[0]);
		sfTexture_destroy(bird[i]->tex[1]);
		free(bird[i]->tex);
		free(bird[i]->spr);
		free(bird[i]);
	}
	free(bird);
}

void apply_texture(bird_t *bird, sfIntRect *img)
{
	if (bird->vit.x >= 0) {
		(*img).left = 53;
		(*img).width = -53;
		(*img).height = 40;
	}
	else {
		(*img).left = 0;
		(*img).width = 53;
		(*img).height = 40;
	}
	sfSprite_setTextureRect(bird->spr[0], *img);
	sfSprite_setTextureRect(bird->spr[1], *img);
	bird->pos.x += bird->vit.x;
	bird->pos.y += bird->vit.y;
	sfSprite_setPosition(bird->spr[0], bird->pos);
	sfSprite_setPosition(bird->spr[1], bird->pos);
}
