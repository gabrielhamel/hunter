/*
** EPITECH PROJECT, 2017
** CSFML
** File description:
** Initiation
*/

#include <stdio.h>
#include <math.h>
#include "display.h"

static sfImage *img;

int min(int a, int b)
{
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int max(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


int kill_bird(bird_t **bird, sfVector2i pos, game_t *game)
{
	sfIntRect size = {0, 0, 53, 40};
	sfIntRect size2 = {53, 0, 53, 40};
	int ret = -1;
	char tab[9] = {0};
	int combo = 0;
    int combo_value = game->score;

	for (int i = 0; bird[i] != NULL; i++) {
		if (pos.x >= bird[i]->pos.x && pos.x <=
		bird[i]->pos.x + 53 && pos.y >= bird[i]->pos.y
		&& pos.y <= bird[i]->pos.y + 53) {
			if (bird[i]->give_life == sfTrue)
				game->life++;
			swap_texture(bird[i], &size, &size2, img);
			ret = 0;
            int bird_value = max(1, pow((fabsf(bird[i]->vit.x) + fabsf(bird[i]->vit.y)), 2));
			game->score += bird_value;
			sprintf(tab, "%08ld", game->score);
			sfText_setString(game->score_text, tab);
			combo += 1;
		}
	}
	if (combo > 1) {
		game->score += (combo - 1) * 100;
		sprintf(tab, "%08ld", game->score);
		sfText_setString(game->score_text, tab);
	}
    if (combo >= 1) {
        hit_value_t *hit = create_hit(game, game->score - combo_value, &pos);
        append_hit(game, hit);
    }
	if (game->score > game->highscore) {
		game->highscore = game->score;
		sprintf(tab, "%08ld", game->highscore);
		sfText_setString(game->highscore_text, tab);
	}
	return (ret);
}

int main(void)
{
	srand(time(NULL));
	img = sfImage_createFromFile("res/dead.png");
	duck_hunt();
	sfImage_destroy(img);
	return (0);
}
