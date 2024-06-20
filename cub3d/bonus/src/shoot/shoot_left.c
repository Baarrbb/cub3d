/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:42:27 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:42:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_left_shoot(t_game *game, t_coor pos, int ray)
{
	if (game->var.flag == 0 || game->var.flag == 1)
	{
		if (cos(game->ray_ang) > 0 && pos.x > game->hit_mat.x
			&& pos.x + 1 != game->hit_mat.x && pos.x - 1 != game->hit_mat.x)
			game->var.cross_l = ray;
		else if (cos(game->ray_ang) < 0 && pos.x < game->hit_mat.x
			&& pos.x + 1 != game->hit_mat.x && pos.x - 1 != game->hit_mat.x)
			game->var.cross_l = ray;
	}
	else
	{
		if (sin(game->ray_ang) > 0 && pos.y < game->hit_mat.y
			&& pos.y + 1 != game->hit_mat.y && pos.y - 1 != game->hit_mat.y)
			game->var.cross_l = ray;
		else if (sin(game->ray_ang) < 0 && pos.y > game->hit_mat.y
			&& pos.y + 1 != game->hit_mat.y && pos.y - 1 != game->hit_mat.y)
			game->var.cross_l = ray;
	}
}

static void	check_left_ns(t_game *game, t_coor pos, t_coor diff, int ray)
{
	if (game->var.flag == 0)
	{
		pos.y = (int)((game->var.hit_shoot.y - diff.y - 1) / IMG_SIZE);
		if (pos.y < game->hit_mat.y && pos.y + 1 != game->hit_mat.y
			&& pos.y - 1 != game->hit_mat.y)
			game->var.cross_l = ray;
		check_left_shoot(game, pos, ray);
	}
	else if (game->var.flag == 1)
	{
		pos.y += 1;
		if (pos.y > game->hit_mat.y && pos.y + 1 != game->hit_mat.y
			&& pos.y - 1 != game->hit_mat.y)
			game->var.cross_l = ray;
		check_left_shoot(game, pos, ray);
	}
}

static void	check_left_ew(t_game *game, t_coor pos, t_coor diff, int ray)
{
	if (game->var.flag == 2)
	{
		pos.x += 1;
		if (pos.x > game->hit_mat.x && pos.x + 1 != game->hit_mat.x
			&& pos.x - 1 != game->hit_mat.x)
			game->var.cross_l = ray;
		check_left_shoot(game, pos, ray);
	}
	else if (game->var.flag == 3)
	{
		pos.x = (int)((game->var.hit_shoot.x - diff.x - 1) / IMG_SIZE);
		if (pos.x < game->hit_mat.x && pos.x + 1 != game->hit_mat.x
			&& pos.x - 1 != game->hit_mat.x)
			game->var.cross_l = ray;
		check_left_shoot(game, pos, ray);
	}
}

void	eval_left_shoot(t_game *game, int ray)
{
	t_coor	pos;
	t_coor	diff;

	diff.x = (game->var.dec.x * game->var.size);
	diff.y = (game->var.dec.y * game->var.size);
	while (diff.x > IMG_SIZE)
		diff.x /= 2;
	while (diff.x < -IMG_SIZE)
		diff.x /= 2;
	while (diff.y > IMG_SIZE)
		diff.y /= 2;
	while (diff.y < -IMG_SIZE)
		diff.y /= 2;
	pos.x = (int)((game->var.hit_shoot.x - diff.x) / IMG_SIZE);
	pos.y = (int)((game->var.hit_shoot.y - diff.y) / IMG_SIZE);
	check_left_ns(game, pos, diff, ray);
	check_left_ew(game, pos, diff, ray);
	game->var.size--;
}
