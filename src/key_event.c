/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:34:32 by bsuc              #+#    #+#             */
/*   Updated: 2024/06/05 14:07:01 by marvin           ###   ########.fr       */
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

static void	key_move(t_game *game, int keycode)
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

// int	get_key_event(int keycode, t_game *game)
// {
// 	if (keycode == XK_Escape)
// 		win_exit(game);
// 	if (keycode == XK_Left)
// 	{
// 		game->play_ang += (M_PI * 2 / 180);
// 		check_max_trigo(game->play_ang);
// 	}
// 	if (keycode == XK_Right)
// 	{
// 		game->play_ang -= (M_PI * 2 / 180);
// 		check_max_trigo(game->play_ang);
// 	}
// 	if (keycode == XK_w || keycode == XK_d || keycode == XK_s
// 		|| keycode == XK_a)
// 		key_move(game, keycode);
// 	return (0);
// }

int	release_key(int keycode, t_game *game)
{
	// if (game->render)
	// {
	// 	game->key_event.l_view = 0;
	// 	game->key_event.r_view = 0;
	// 	game->key_event.f_move = 0;
	// 	game->key_event.r_move = 0;
	// 	game->key_event.b_move = 0;
	// 	game->key_event.l_move = 0;
	// }
	if (keycode == XK_Left)
		game->key_event.l_view = 0;
	if (keycode == XK_Right)
		game->key_event.r_view = 0;
	if (keycode == XK_w)
		game->key_event.f_move = 0;
	if (keycode == XK_d)
		game->key_event.r_move = 0;
	if (keycode == XK_s)
		game->key_event.b_move = 0;
	if (keycode == XK_a)
		game->key_event.l_move = 0;
	return (0);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		win_exit(game);
	// if (game->render)
	// 	return (0);
	if (keycode == XK_Left)
		game->key_event.l_view = 1;
	if (keycode == XK_Right)
		game->key_event.r_view = 1;
	if (keycode == XK_w)
		game->key_event.f_move = 1;
	if (keycode == XK_d)
		game->key_event.r_move = 1;
	if (keycode == XK_s)
		game->key_event.b_move = 1;
	if (keycode == XK_a)
		game->key_event.l_move = 1;
	// if (keycode == XK_q)
	// 	shoot(game);
	return (0);
}

int	key_event(t_game *game)
{
	if (game->key_event.l_view)
	{
		game->play_ang += (M_PI * 2 / 720);
		check_max_trigo(game->play_ang);
	}
	if (game->key_event.r_view)
	{
		game->play_ang -= (M_PI * 2 / 720);
		check_max_trigo(game->play_ang);
	}
	if (game->key_event.f_move)
		key_move(game, XK_w);
	if (game->key_event.b_move)
		key_move(game, XK_s);
	if (game->key_event.l_move)
		key_move(game, XK_a);
	if (game->key_event.r_move)
		key_move(game, XK_d);
	return (0);
}
