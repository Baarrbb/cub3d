/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:25:56 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:43:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	get_hit_wall(t_game *game)
{
	t_coor	step;
	double	s;

	s = sin(game->ray_ang);
	step.x = game->distance * cos(game->ray_ang);
	step.y = game->distance * s;
	if (s > 0 && step.y > 0)
		step.y *= -1;
	if (s < 0 && step.y < 0)
		step.y *= -1;
	game->hit_wall.x = game->play_x + step.x;
	game->hit_wall.y = game->play_y + step.y;
	game->hit_mat.x = (int)(round(game->hit_wall.x) / (int)IMG_SIZE);
	game->hit_mat.y = (int)(round(game->hit_wall.y) / (int)IMG_SIZE);
}

static int	eval_text(t_game *game, t_coor *dist, double c, double s)
{
	int	flag;

	if (dist->y <= dist->x)
	{
		if (c > 0)
			flag = 2;
		else
			flag = 3;
		game->distance = dist->y;
	}
	else
	{
		if (s > 0)
			flag = 0;
		else
			flag = 1;
		game->distance = dist->x;
	}
	return (flag);
}

int	eval_distance(t_game *game, int ray, int yes)
{
	t_coor	trigo;
	t_coor	dist;
	t_coor	last_wall;
	int		flag;

	trigo.x = cos(game->ray_ang);
	trigo.y = sin(game->ray_ang);
	dist.x = get_horiz_inter(game, game->ray_ang, trigo.y);
	dist.y = get_verti_inter(game, game->ray_ang, trigo.x);
	flag = eval_text(game, &dist, trigo.x, trigo.y);
	last_wall.y = game->hit_wall.y;
	last_wall.x = game->hit_wall.x;
	get_hit_wall(game);
	if (yes == 1 && ray > (WIN_WIDTH / 2)
		&& ray <= (WIN_WIDTH / 2) + game->var.slice && !game->var.cross_r)
		eval_right_shoot(game, last_wall, ray);
	if (yes == 2 && ray >= game->var.dwin_x && ray <= (WIN_WIDTH / 2))
		eval_left_shoot(game, ray);
	game->distance *= cos(game->ray_ang - game->play_ang);
	return (flag);
}
