/*
** EPITECH PROJECT, 2018
** I
** File description:
** I
*/

#include <stdio.h>
#include "display.h"
#include <unistd.h>
#include <fcntl.h>

void init_part(bird_t *bird)
{
	bird->pos.x = -53;
	bird->pos.y = rand() % 400 + 90;
	bird->vit.x = ((float)(rand() % 250 + 30))
	/ ((float)(rand() % 60 + 10));
	bird->vit.y = ((float)(rand() % 15 - 5)) /
	((float)(rand() % 30 - 10));
	bird->type = 0;
	bird->go = 0;
	bird->is_dead = 0;
	bird->anim = 0;
}

bird_t **init_bird(char **type_bird)
{
	bird_t **bird = malloc(sizeof(bird_t *) * (BIRDS_NB + 1));
	sfImage *img = NULL;
	sfIntRect size = {0, 0, 53, 40};
	sfIntRect size2 = {53, 0, 53, 40};
	int bird_type;

	for (int i = 0; i < BIRDS_NB; i++) {
		bird_type = rand() % 4;
		bird[i] = malloc(sizeof(bird_t));
		img = sfImage_createFromFile(type_bird[bird_type]);
		bird[i]->give_life = bird_type == 2 ? sfTrue : sfFalse;
		bird[i]->tex = malloc(sizeof(sfTexture *) * 2);
		bird[i]->tex[0] = sfTexture_createFromImage(img, &size);
		bird[i]->tex[1] = sfTexture_createFromImage(img, &size2);
		init_part(bird[i]);
		bird[i]->spr = malloc(sizeof(sfSprite *) * 2);
		bird[i]->spr[0] = sfSprite_create();
		bird[i]->spr[1] = sfSprite_create();
		sfSprite_setTexture(bird[i]->spr[0], bird[i]->tex[0], sfTrue);
		sfSprite_setTexture(bird[i]->spr[1], bird[i]->tex[1], sfTrue);
		sfImage_destroy(img);
	}
	bird[BIRDS_NB] = NULL;
	return (bird);
}

char **type_bird(void)
{
	char **type_bird = malloc(sizeof(char *) * 5);

	type_bird[0] = "res/blue.png";
	type_bird[1] = "res/green.png";
	type_bird[2] = "res/red.png";
	type_bird[3] = "res/grey.png";
	type_bird[4] = "res/dead/png";
	return (type_bird);
}

game_t *init_game(size_t highscore)
{
	game_t *game = malloc(sizeof(game_t));
	char buff[9] = {0};

	game->type_bird = type_bird();
	game->onclick = 0;
	game->t_aim = NULL;
	game->t_back = NULL;
	game->t_heart = NULL;
	game->font = sfFont_createFromFile("res/font.ttf");
	game->score = 0;
    game->hit_scores = NULL;
	game->score_text = sfText_create();
	sfText_setFont(game->score_text, game->font),
	sfText_setFillColor(game->score_text, sfYellow);
	sfText_setString(game->score_text, "00000000");
	sfText_setPosition(game->score_text, (sfVector2f){25, 10});
	game->highscore = highscore;
	game->highscore_text = sfText_create();
	sfText_setFont(game->highscore_text, game->font),
	sfText_setFillColor(game->highscore_text, sfYellow);
	sprintf(buff, "%08ld", game->highscore);
	sfText_setString(game->highscore_text, buff);
	sfText_setPosition(game->highscore_text, (sfVector2f){WIDTH - 185, 10});
	game->life = 3;
	game->bird = init_bird(game->type_bird);
	game->clock = sfClock_create();
	game->bounce = sfClock_create();
	game->add = sfClock_create();
	game->music = sfMusic_createFromFile("res/birds.wav");
	game->tir = sfMusic_createFromFile("res/tir.wav");
	game->s_back = load_sprite("res/back.png", game->t_back);
	game->aim = load_sprite("res/aim.png", game->t_aim);
	game->s_heart = load_sprite("res/heart.png", game->t_heart);
	sfMusic_setLoop(game->music, sfTrue);
	sfMusic_play(game->music);
	return (game);
}

size_t load_highscore(void)
{
	int fd = open(".score", O_RDONLY | O_CREAT, 0664);
	size_t score = 0;
	size_t size = read(fd, &score, sizeof(size_t));

	close(fd);
	return score;
}

void save_highscore(size_t highscore)
{
	int fd = open(".score", O_WRONLY | O_CREAT, 0664);
	size_t size = write(fd, &highscore, sizeof(size_t));
	close(fd);
}

void duck_hunt(void)
{
	sfVideoMode mode = {WIDTH, HEIGHT, 32};
	sfEvent event;
	int loop = 1;
	size_t highscore = load_highscore();
	game_t *game = NULL;
	sfRenderWindow *win = sfRenderWindow_create(mode, "My hunter",
	sfClose, 0);

	sfRenderWindow_pollEvent(win, &event);
	sfRenderWindow_setMouseCursorVisible(win, sfFalse);
	sfRenderWindow_setKeyRepeatEnabled(win, sfFalse);
	sfRenderWindow_setFramerateLimit(win, 60);
	sfRenderWindow_setVerticalSyncEnabled(win, sfTrue);
	while (loop) {
		game = init_game(highscore);
		if (my_pause(win, &event, game) != -1) {
			loop = boucle(win, &event, game);
			highscore = game->highscore;
		}
		else
			loop = 0;
		destroy_game(game);
	}
	sfRenderWindow_destroy(win);
	save_highscore(highscore);
}
