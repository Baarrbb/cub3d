/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:34:32 by bsuc              #+#    #+#             */
/*   Updated: 2024/06/19 17:30:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	release_key(int keycode, t_game *game)
{
	if (game->render)
	{
		game->key_event.l_view = 0;
		game->key_event.r_view = 0;
		game->key_event.f_move = 0;
		game->key_event.r_move = 0;
		game->key_event.b_move = 0;
		game->key_event.l_move = 0;
	}
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

static void	press_key_bis(int keycode, t_game *game)
{
	if (keycode == XK_q)
		shoot(game);
	if (keycode == XK_space && game->light == 1)
		game->light = 0;
	else if (keycode == XK_space && game->light == 0)
		game->light = 1;
	if (keycode == XK_Control_L && game->fog == 1)
		game->fog = 0;
	else if (keycode == XK_Control_L && game->fog == 0)
		game->fog = 1;
	if (keycode == XK_e)
		open_door(game);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		win_exit(game);
	if (game->render)
		return (0);
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
	press_key_bis(keycode, game);
	return (0);
}

int	key_event(t_game *game)
{
	if (game->key_event.l_view)
	{
		game->play_ang += (M_PI * 2 / 720);
		check_max_trigo(&game->play_ang);
	}
	if (game->key_event.r_view)
	{
		game->play_ang -= (M_PI * 2 / 720);
		check_max_trigo(&game->play_ang);
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
