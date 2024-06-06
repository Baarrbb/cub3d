/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:40:08 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:41:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_right_shoot(t_game *game, t_coor pos, int ray, int ns)
{
	if (ns)
	{
		if (cos(game->ray_ang) > 0 && pos.x > game->hit_mat.x
			&& pos.x + 1 != game->hit_mat.x && pos.x - 1 != game->hit_mat.x)
			game->var.cross_r = ray;
		else if (cos(game->ray_ang) < 0 && pos.x < game->hit_mat.x
			&& pos.x + 1 != game->hit_mat.x && pos.x - 1 != game->hit_mat.x)
			game->var.cross_r = ray;
		game->var.pos_check.x += game->var.dec.x;
	}
	else
	{
		if (sin(game->ray_ang) > 0 && pos.y < game->hit_mat.y
			&& pos.y + 1 != game->hit_mat.y && pos.y - 1 != game->hit_mat.y)
			game->var.cross_r = ray;
		else if (sin(game->ray_ang) < 0 && pos.y > game->hit_mat.y
			&& pos.y + 1 != game->hit_mat.y && pos.y - 1 != game->hit_mat.y)
			game->var.cross_r = ray;
		game->var.pos_check.y += game->var.dec.y;
	}
}

static void	check_right_ns(t_game *game, t_coor pos, int ray, t_coor diff)
{
	if (game->var.flag == 0)
	{
		pos.y = (int)((diff.y - 1) / IMG_SIZE);
		if (pos.y < game->hit_mat.y && pos.y + 1 != game->hit_mat.y
			&& pos.y - 1 != game->hit_mat.y)
			game->var.cross_r = ray;
		check_right_shoot(game, pos, ray, 1);
	}
	else if (game->var.flag == 1)
	{
		pos.y += 1;
		if (pos.y > game->hit_mat.y && pos.y + 1 != game->hit_mat.y
			&& pos.y - 1 != game->hit_mat.y)
			game->var.cross_r = ray;
		check_right_shoot(game, pos, ray, 1);
	}
}

static void	check_right_ew(t_game *game, t_coor pos, int ray, t_coor diff)
{
	if (game->var.flag == 2)
	{
		pos.x += 1;
		if (pos.x > game->hit_mat.x && pos.x + 1 != game->hit_mat.x
			&& pos.x - 1 != game->hit_mat.x)
			game->var.cross_r = ray;
		check_right_shoot(game, pos, ray, 0);
	}
	else if (game->var.flag == 3)
	{
		pos.x = (int)((diff.x - 1) / IMG_SIZE);
		if (pos.x < game->hit_mat.x && pos.x + 1 != game->hit_mat.x
			&& pos.x - 1 != game->hit_mat.x)
			game->var.cross_r = ray;
		check_right_shoot(game, pos, ray, 0);
	}
}

void	eval_right_shoot(t_game *game, t_coor last_wall, int ray)
{
	t_coor	pos;
	t_coor	diff;

	game->var.size++;
	if (ray == (WIN_WIDTH / 2) + 1)
	{
		game->var.pos_check.y = (game->hit_wall.y - last_wall.y);
		game->var.pos_check.x = (game->hit_wall.x - last_wall.x);
		game->var.dec.y = (game->hit_wall.y - last_wall.y);
		game->var.dec.x = (game->hit_wall.x - last_wall.x);
	}
	diff.x = round(game->var.hit_shoot.x + game->var.pos_check.x);
	diff.y = round(game->var.hit_shoot.y + game->var.pos_check.y);
	pos.x = (int)(diff.x / IMG_SIZE);
	pos.y = (int)(diff.y / IMG_SIZE);
	check_right_ns(game, pos, ray, diff);
	check_right_ew(game, pos, ray, diff);
}
