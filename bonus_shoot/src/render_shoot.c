/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:28:58 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:31:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_shoot(t_game *game, int pos)
{
	int				y;
	int				i;
	unsigned int	color;
	int				k;

	k = -1;
	while (++k < game->var.slice)
	{
		i = -1;
		while (++i < game->var.slice)
		{
			y = (WIN_HEIGHT / 2) - (game->var.slice / 2) + i;
			color = pixel_get(&game->shoot[game->index_anim],
					k * (SHOOT_SIZE / game->var.slice),
					i * (SHOOT_SIZE / game->var.slice));
			if (game->var.cross_l && pos + k <= game->var.cross_l)
				continue ;
			if (game->var.cross_r && pos + k >= game->var.cross_r)
				return ;
			if (y <= WIN_HEIGHT && y >= 0 && color != 0xff000000)
				my_mlx_pixel_put(&game->img, k + pos, y, color);
		}
	}
}

void	get_right_shoot(t_game *game, double dist_view)
{
	int	i;
	int	flag;
	int	slice;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		flag = eval_distance(game, i, 1);
		slice = round(IMG_SIZE / game->distance * dist_view);
		if (i == WIN_WIDTH / 2)
		{
			game->var.slice = slice;
			game->var.flag = flag;
			game->var.dwin_x = i - (slice / 2);
			game->var.fwin_x = i + (slice / 2);
			game->var.hit_shoot = game->hit_wall;
			game->tir = 0;
		}
		game->ray_ang -= ((FOV / (double)WIN_WIDTH) * M_PI / 180.);
		check_max_trigo(game->ray_ang);
	}
}

void	get_left_shoot(t_game *game)
{
	int		i;

	game->ray_ang = game->play_ang + (game->fov_ang / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		eval_distance(game, i, 2);
		game->ray_ang -= ((FOV / (double)WIN_WIDTH) * M_PI / 180.);
		check_max_trigo(game->ray_ang);
	}
}
