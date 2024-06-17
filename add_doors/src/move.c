/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:24:16 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:24:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		move->x = cos(game->play_ang) * (PLAYER_SPEED);
		move->y = -sin(game->play_ang) * (PLAYER_SPEED);
	}
	if (key == XK_s)
	{
		move->x = -cos(game->play_ang) * (PLAYER_SPEED);
		move->y = sin(game->play_ang) * (PLAYER_SPEED);
	}
}

static int	collision(t_game *game, int x, int y)
{
	if (game->parsing->map[y][x] == '1')
		return (1);
	return (0);
}

static int	check_wall(t_game *game, t_coor *move)
{
	int	debx;
	int	deby;
	int	finx;
	int	finy;

	debx = (int)game->play_x - PLAYER_WIDTH + (int)move->x;
	finx = (int)game->play_x + PLAYER_WIDTH + (int)move->x;
	while (debx < finx)
	{
		deby = (int)game->play_y - PLAYER_WIDTH + (int)move->y;
		finy = (int)game->play_y + PLAYER_WIDTH + (int)move->y;
		while (deby < finy)
		{
			if (collision(game, debx / IMG_SIZE, deby / IMG_SIZE))
				return (1);
			debx++;
			deby++;
		}
	}
	return (0);
}

void	key_move(t_game *game, int keycode)
{
	t_coor	move;

	move.x = 0;
	move.y = 0;
	move_player(game, &move, keycode);
	if (!check_wall(game, &move))
	{
		game->play_x += move.x;
		game->play_y += move.y;
	}
}
