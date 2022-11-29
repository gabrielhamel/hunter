/*
** EPITECH PROJECT, 2017
** Display
** File description:
** Functions
*/

#ifndef DISPLAY_H
#define DISPLAY_H
#define WIDTH 1050
#define HEIGHT 863
#define BIRDS_NB 50

#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bird_s {
	sfVector2f pos;
	sfVector2f vit;
	char type;
	sfSprite **spr;
	char anim;
	char is_dead;
	sfTexture **tex;
	char go;
	sfBool give_life;
} bird_t;

typedef struct {
    sfText *text;
} hit_value_t;

typedef struct game_t {
	char **type_bird;
	char onclick;
	int life;
	bird_t **bird;
	sfClock *clock;
	sfClock *bounce;
	sfClock *add;
	sfMusic *music;
	sfMusic *tir;
	sfTexture *t_back;
	sfTexture *t_aim;
	sfTexture *t_heart;
	sfSprite *s_back;
	sfSprite *aim;
	sfSprite *s_heart;
	sfVector2f cursf;
	sfVector2i cursi;
	sfFont *font;
	sfText *score_text;
	sfText *highscore_text;
	size_t score;
	size_t highscore;
    hit_value_t **hit_scores;
} game_t;

void duck_hunt(void);
int boucle(sfRenderWindow *win, sfEvent *event, game_t *game);
void destroy_bird(bird_t **bird);
void draw_bird(bird_t **bird, sfRenderWindow *win, sfClock *clock);
void add_bird(bird_t **bird, sfClock *clock);
sfSprite *load_sprite(char *name, sfTexture *tex);
void apply_texture(bird_t *bird, sfIntRect *img);
void swap_texture(bird_t *bird, sfIntRect *size,
sfIntRect *size2, sfImage *img);
void apply_speed(bird_t **bird, sfClock *clock);
void test_collision(bird_t *bird);
void init_part(bird_t *bird);
bird_t **init_bird(char **type_bird);
game_t *init_game(size_t highscore);
void duck_hunt(void);
void destroy_game(game_t *game);
void draw_hearts(game_t *game, sfRenderWindow *win);
int kill_bird(bird_t **bird, sfVector2i pos, game_t *game);
int my_pause(sfRenderWindow *win, sfEvent *event, game_t *game);
int game_over_screen(sfRenderWindow *win, sfEvent *event, game_t *game);
hit_value_t *create_hit(game_t *game, int score_value, sfVector2i *pos);
void append_hit(game_t *game, hit_value_t *hit);
int min(int a, int b);
int max(int a, int b);
void draw_hits_marker(game_t *game, sfRenderWindow *win);

#endif
