/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:57:24 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 16:47:47 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_game *game, t_coor *move, int key)
{
	if (key == XK_d)
	{
		move->x = -sin(game->play_ang) * PLAYER_SPEED;
		move->y = cos(game->play_ang) * PLAYER_SPEED;
		eval_move(game, move, 1);
	}
	if (key == XK_a)
	{
		move->x = sin(game->play_ang) * PLAYER_SPEED;
		move->y = -cos(game->play_ang) * PLAYER_SPEED;
		eval_move(game, move, 0);
	}
	if (key == XK_w)
	{
		move->x = cos(game->play_ang) * PLAYER_SPEED;
		move->y = -sin(game->play_ang) * PLAYER_SPEED;
	}
	if (key == XK_s)
	{
		move->x = -cos(game->play_ang) * PLAYER_SPEED;
		move->y = sin(game->play_ang) * PLAYER_SPEED;
	}
}

static void	coll_init(t_coll *collision, int *test, t_coor *move, t_game *game)
{
	collision->count = 0;
	collision->negatifx = 1;
	collision->negatify = 1;
	collision->startp.x = game->play_x - 2;
	collision->startp.y = game->play_y - 2;
	collision->endp.x = game->play_x + 2;
	collision->endp.y = game->play_y + 2;
	if ((int)fabs(move->x) > (int)fabs(move->y))
		*test = (int)fabs(move->x) - (int)fabs(move->y);
	else
		*test = (int)fabs(move->y) - (int)fabs(move->x);
	if (move->x > 0)
		collision->negatifx = -1;
	else
		collision->negatifx = 1;
	if (move->y > 0)
		collision->negatify = -1;
	else
		collision->negatify = 1;
}

static int	collision(t_coor move, t_game game)
{
	int		test;
	t_coll	collision;

	coll_init(&collision, &test, &move, &game);
	while ((int)move.x != 0 || (int)move.y != 0)
	{
		if (test == 0)
			equal_zero(&collision, &move);
		count_coll(&collision, &move, test);
		if (is_in_square(game, collision.startp, collision.endp) == 1)
			return (1);
	}
	return (0);
}

void	key_move(t_game *game, int keycode)
{
	t_coor	move;

	move.x = 0;
	move.y = 0;
	move_player(game, &move, keycode);
	if (collision(move, *game) == 0)
	{
		game->play_x += move.x;
		game->play_y += move.y;
	}
}
