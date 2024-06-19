/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:38:17 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/19 18:03:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	middle_door(t_game *game, int *x, int *y)
{
	if (game->ray_ang > 0 && game->ray_ang < M_PI)
	{
		*y += 1;
		*x += (int)(IMG_SIZE / 2) / tan(game->ray_ang);
		*y += -(int)(IMG_SIZE / 2) + (int)IMG_SIZE;
	}
	else
	{
		*y += (int)IMG_SIZE;
		*x += -(int)(IMG_SIZE / 2) / tan(game->ray_ang);
		*y += (int)(IMG_SIZE / 2) + (int)IMG_SIZE;
	}
}

static int	pos_door(t_game *game, int x, int y)
{
	t_door	*tmp;

	tmp = game->doors;
	middle_door(game, &x, &y);
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		if (game->ray_ang > 0 && game->ray_ang < M_PI)
		{
			if (x >= tmp->px && x <= tmp->endpx && y == tmp->py)
				return (1);
		}
		else
			if (x >= tmp->px && x <= tmp->endpx && y == tmp->py + (int)IMG_SIZE)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	check_door(t_game *game, t_coor inter, int inters)
{
	int	len;
	int	map_y;

	if (inters == 2)
		inter.y -= 1;
	map_y = (int)(inter.y / IMG_SIZE);
	if (inter.y < 0 || inter.x < 0)
		return (2);
	if ((inter.y / IMG_SIZE) > game->parsing->len_y)
		return (2);
	if (game->parsing->map[(int)(inter.y / IMG_SIZE)] != NULL)
		len = (int)ft_strlen(game->parsing->map[map_y]);
	else
		len = 0;
	if ((int)(inter.x / IMG_SIZE) < 0)
		return (2);
	if (game->parsing->map[map_y] && (int)(inter.x / IMG_SIZE) <= len)
	{
		if (game->parsing->map[map_y][(int)(inter.x / IMG_SIZE)] == '1')
			return (2);
		if (game->parsing->map[map_y][(int)(inter.x / IMG_SIZE)] == 'D' \
		&& pos_door(game, inter.x, inter.y) == 1)
			return (0);
	}
	return (1);
}

static void	add_distance(t_game *game, t_coor *pos_ray)
{
	if (game->ray_ang > 0 && game->ray_ang < M_PI)
	{
		pos_ray->x += (IMG_SIZE / 2) / tan(game->ray_ang);
		pos_ray->y += -(int)(IMG_SIZE / 2);
	}
	else
	{
		pos_ray->x += -(IMG_SIZE / 2) / tan(game->ray_ang);
		pos_ray->y += (int)(IMG_SIZE / 2);
	}
}

int	find_door(t_game *game, t_coor step, t_coor *pos_ray, int test)
{
	int	test2;

	test2 = check_door(game, *pos_ray, test);
	while (test2 == 1)
	{
		pos_ray->x += step.x;
		pos_ray->y += step.y;
		test2 = check_door(game, *pos_ray, test);
	}
	if (test2 == 2)
		return (-1);
	add_distance(game, pos_ray);
	return (0);
}
