/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:57:24 by marvin            #+#    #+#             */
/*   Updated: 2024/06/07 13:19:00 by marvin           ###   ########.fr       */
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
		move->x = cos(game->play_ang) * (PLAYER_SPEED);
		move->y = -sin(game->play_ang) * (PLAYER_SPEED);
	}
	if (key == XK_s)
	{
		move->x = -cos(game->play_ang) * (PLAYER_SPEED);
		move->y = sin(game->play_ang) * (PLAYER_SPEED);
	}
}

void	smoothing(int smoothing, int delay, int x, int y, t_game *game)
{
	for (int i = 0; i < smoothing; i++)
	{
		game->play_x += x / smoothing;
		game->play_y += y / smoothing;
		// usleep(delay / smoothing); // Utilisez usleep pour le délai
	}
	game->play_x += x % smoothing;
	game->play_y += y % smoothing;
	// usleep(delay % smoothing);
}

int is_in_square(t_game game, t_coor startp, t_coor endp) {
	int dx;
	int dy;
	int stepSize;
	int stepX;
	int stepY;
	int	i;
	
	dx = endp.x - startp.x;
	i = -1;
	dy = endp.y - startp.y;
	stepSize = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	stepX = dx > 0 ? 1 : -1;
	stepY = dy > 0 ? 1 : -1;
	while (++i <= stepSize)
	{
		if (game.parsing->map[(int)startp.y / 64][(int)startp.x / 64] == '1')
			return (1);
		startp.x += stepX;
		startp.y += stepY;
	}
	return (0);
}

int	testthings(t_coor move, t_coor startp, t_coor endp, t_game game)
{
	int	test = 0;
	int	count = 0;
	int negatifx = 1;
	int	negatify = 1;

	if ((int)fabs(move.x) > (int)fabs(move.y))
		test = (int)fabs(move.x) - (int)fabs(move.y);
	else
		test = (int)fabs(move.y) - (int)fabs(move.x);
	if (move.x > 0)
		negatifx = -1;
	else 
		negatifx = 1;
	if (move.y > 0)
		negatify = -1;
	else 
		negatify = 1;
	while ((int)move.x != 0 || (int)move.y != 0)
	{
		if (test == 0 && count == 0)
		{
			startp.x -= negatifx;
			endp.x -= negatifx;
			move.x += negatifx;
			count++;
		}
		if (test == 0 && count == 1)
		{
			startp.y -= negatify;
			endp.y -= negatify;
			move.y += negatify;
			count = 0;
		}
		if (count < test && (int)fabs(move.x) > (int)fabs(move.y))
		{
			startp.x -= negatifx;
			endp.x -= negatifx;
			move.x += negatifx;
			count++;
		}
		else if ((count < test && (int)fabs(move.x) <= (int)fabs(move.y)))
		{
			startp.y -= negatify;
			endp.y -= negatify;
			move.y += negatify;
			count++;
		}
		else if (test != 0 && (count >= test && (int)fabs(move.x) > (int)fabs(move.y)))
		{
			startp.y -= negatify;
			endp.y -= negatify;
			move.y += negatify;
			count = 0;
		}
		else if (test != 0 && (count >= test && (int)fabs(move.x) <= (int)fabs(move.y)))
		{
			startp.x -= negatifx;
			endp.x -= negatifx;
			move.x += negatifx;
			count = 0;
		}
		if (is_in_square(game, startp, endp) == 1)
			return (1);
	}
	return (0);
}

void	key_move(t_game *game, int keycode)
{
	t_coor	move;
	t_coor	startp;
	t_coor	endp;

	move.x = 0;
	move.y = 0;
	startp.x = game->play_x - 2;
	startp.y = game->play_y - 2;
	endp.x = game->play_x + 2;
	endp.y = game->play_y + 2;
	move_player(game, &move, keycode);
	if (testthings(move, startp, endp, *game) == 0)
	{
		game->play_x += move.x;
		game->play_y += move.y;
		// smoothing(10, 10000, move.x, move.y, game);
	}
}






// static int	collision(t_game *game, int x, int y)
// {
// 	if (game->parsing->map[y][x] == '1')
// 		return (1);
// 	return (0);
// }
// static int	check_wall(t_game *game, t_coor *move)
// {
// 	int	debx;
// 	int	deby;
// 	int	finx;
// 	int	finy;
// 	debx = (int)game->play_x - PLAYER_WIDTH + (int)move->x;
// 	finx = (int)game->play_x + PLAYER_WIDTH + (int)move->x;
// 	while (debx < finx)
// 	{
// 		deby = (int)game->play_y - PLAYER_WIDTH + (int)move->y;
// 		finy = (int)game->play_y + PLAYER_WIDTH + (int)move->y;
// 		while (deby < finy)
// 		{
// 			if (collision(game, debx / IMG_SIZE, deby / IMG_SIZE))
// 				return (1);
// 			debx++;
// 			deby++;
// 		}
// 	}
// 	return (0);
// }
// void	key_move(t_game *game, int keycode)
// {
// 	t_coor	move;
// 	move.x = 0;
// 	move.y = 0;
// 	move_player(game, &move, keycode);
// 	if (!check_wall(game, &move))
// 	{
// 		game->play_x += move.x;
// 		game->play_y += move.y;
// 	}
// }
