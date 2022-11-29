/*
** EPITECH PROJECT, 2017
** SCRREN
** File description:
** SCREEN
*/

#include "display.h"

void refresh_struct(game_t *game, sfRenderWindow *win)
{
	sfRenderWindow_drawSprite(win, game->s_back, NULL);
	draw_bird(game->bird, win, game->clock);
	sfRenderWindow_drawSprite(win, game->aim, NULL);
	draw_hearts(game, win);
	draw_hits_marker(game, win);
	sfRenderWindow_drawText(win, game->score_text, NULL);
	sfRenderWindow_drawText(win, game->highscore_text, NULL);
}

void update(game_t *game)
{
	add_bird(game->bird, game->add);
	apply_speed(game->bird, game->bounce);
	sfSprite_setPosition(game->aim, game->cursf);
}

int my_pause(sfRenderWindow *win, sfEvent *event, game_t *game)
{
	sfText *text = sfText_create();

	sfText_setFont(text, game->font);
	sfText_setString(text, "Click to begin");
	sfText_setFillColor(text, sfRed);
	sfText_setCharacterSize(text, 90);

	sfFloatRect text_bounds = sfText_getLocalBounds(text);

	sfText_setPosition(text, (sfVector2f){WIDTH / 2 - text_bounds.width / 2,
										  HEIGHT / 2 - text_bounds.height / 2});
	while (sfRenderWindow_isOpen(win) && game->life > 0) {
		while (sfRenderWindow_pollEvent(win, event)) {
			if (sfKeyboard_isKeyPressed(sfKeyEscape) || event->type == sfEvtClosed)
				return -1;
			if (sfKeyboard_isKeyPressed(sfKeySpace))
				return 0;
			if (sfMouse_isButtonPressed(sfMouseLeft))
				return 0;
		}
		sfRenderWindow_clear(win, sfBlack);
		sfRenderWindow_drawSprite(win, game->s_back, NULL);
		sfRenderWindow_drawText(win, game->score_text, NULL);
		sfRenderWindow_drawText(win, game->highscore_text, NULL);
		sfRenderWindow_drawText(win, text, NULL);
		sfRenderWindow_display(win);
	}
	return -1;
}

int game_over_screen(sfRenderWindow *win, sfEvent *event, game_t *game)
{
	sfText *text = sfText_create();

	sfText_setFont(text, game->font);
	sfText_setString(text, "Game over");
	sfText_setFillColor(text, sfRed);
	sfText_setCharacterSize(text, 90);

	sfFloatRect text_bounds = sfText_getLocalBounds(text);

	sfText_setPosition(text, (sfVector2f){WIDTH / 2 - text_bounds.width / 2,
										  HEIGHT / 2 - text_bounds.height / 2});

	while (sfRenderWindow_isOpen(win)) {
		while (sfRenderWindow_pollEvent(win, event)) {
			if (sfKeyboard_isKeyPressed(sfKeyEscape) || event->type == sfEvtClosed) {
				sfRenderWindow_close(win);
				return -1;
			}
			if (sfKeyboard_isKeyPressed(sfKeySpace))
				return 0;
			if (sfMouse_isButtonPressed(sfMouseLeft))
				return 0;
		}
		sfRenderWindow_clear(win, sfBlack);
		sfRenderWindow_drawSprite(win, game->s_back, NULL);
		sfRenderWindow_drawText(win, game->score_text, NULL);
		sfRenderWindow_drawText(win, game->highscore_text, NULL);
		sfRenderWindow_drawText(win, text, NULL);
		sfRenderWindow_display(win);
	}
	return -1;
}

int boucle(sfRenderWindow *win, sfEvent *event, game_t *game)
{
	while (sfRenderWindow_isOpen(win) && game->life > 0) {
		while (sfRenderWindow_pollEvent(win, event)) {
			if (sfKeyboard_isKeyPressed(sfKeyEscape) || event->type == sfEvtClosed)
				sfRenderWindow_close(win);
			if (!game->onclick && sfMouse_isButtonPressed(sfMouseLeft)) {
				sfMusic_stop(game->tir);
				sfMusic_play(game->tir);
				game->life += kill_bird(game->bird, game->cursi, game);
				game->life = min(game->life, 3);
				game->onclick = 1;
			}
			else if (event->type == sfEvtMouseButtonReleased)
				game->onclick = 0;
			game->cursi = sfMouse_getPositionRenderWindow(win);
			game->cursf.x = game->cursi.x - 15;
			game->cursf.y = game->cursi.y - 15;
		}
		update(game);
		sfRenderWindow_clear(win, sfBlack);
		refresh_struct(game, win);
		sfRenderWindow_display(win);
	}
	if (game->life <= 0) {
		game_over_screen(win, event, game);
		return 1;
	}
	return 0;
}
