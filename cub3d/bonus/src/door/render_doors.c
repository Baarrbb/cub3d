/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:31:40 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/19 17:56:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	render_opening_doors(t_game *game, int slice, int pos, t_door *ptr)
{
	t_data	d;
	int		visible_width;

	ft_memset(&d, 0, sizeof(d));
	d.i = -1;
	while (++d.i < slice)
	{
		d.j = -1;
		d.y = (WIN_HEIGHT / 2) - (slice / 2) + d.i;
		visible_width = (int)IMG_SIZE - (ptr->endpx % (int)IMG_SIZE);
		d.offset = (int)game->hit_wall.x % (int)IMG_SIZE;
		if (d.offset + visible_width > (int)IMG_SIZE)
			visible_width = (int)IMG_SIZE - d.offset;
		while (++d.j < visible_width)
		{
			d.color = pixel_get(&(game->door), d.offset + d.j, \
			(int)(d.i * (IMG_SIZE / slice)));
			game->intensity = (game->distance - (int)IMG_SIZE) / game->distance;
			if (!game->fog)
				render_with_fog(game, pos, &d);
			else if (d.y <= WIN_HEIGHT && d.y >= 0)
				my_mlx_pixel_put(&game->img, pos, d.y, d.color);
		}
	}
}

static void	render_closed_door(t_game *game, int slice, int pos)
{
	t_mlx	door;
	t_data	d;

	ft_memset(&d, 0, sizeof(d));
	d.i = -1;
	door = game->door;
	while (++d.i < slice)
	{
		d.y = (WIN_HEIGHT / 2) - (slice / 2) + d.i;
		d.offset = (int)game->hit_wall.x % (int)IMG_SIZE;
		d.color = pixel_get(&door, d.offset, (int)(d.i * (IMG_SIZE / slice)));
		if (!game->fog)
			render_with_fog(game, pos, &d);
		else
		{
			if (d.y <= WIN_HEIGHT && d.y >= 0)
				my_mlx_pixel_put(&game->img, pos, d.y, d.color);
		}
	}
}

static void	render_door(t_game *game, int slice, int pos)
{
	t_door	*ptr;

	ptr = game->doors;
	while (ptr)
	{
		if (ptr->startx == (int)(game->hit_wall.x / (int)IMG_SIZE) \
		&& ptr->starty - 1 == (int)(game->hit_wall.y / (int)IMG_SIZE))
			break ;
		ptr = ptr->next;
	}
	if (ptr == NULL || (ptr->open == 2 || ptr->open == 0))
		render_closed_door(game, slice, pos);
	else
		render_opening_doors(game, slice, pos, ptr);
}

static double	get_horiz_inter_door(t_game *game, double curr_ang)
{
	t_coor	step;
	t_coor	pos_ray;
	int		test;

	test = -1;
	if (curr_ang > 0 && curr_ang < M_PI)
	{
		pos_ray.y = (int)(game->play_y / IMG_SIZE) * IMG_SIZE;
		test = 2;
	}
	else
		pos_ray.y = (int)(game->play_y / IMG_SIZE) * IMG_SIZE + IMG_SIZE;
	pos_ray.x = game->play_x + ((game->play_y - pos_ray.y) / tan(curr_ang));
	step.y = IMG_SIZE;
	if (curr_ang > 0 && curr_ang < M_PI)
		step.y *= -1;
	step.x = IMG_SIZE / tan(curr_ang);
	eval_step(curr_ang, &step.x, 1);
	if (find_door(game, step, &pos_ray, test) == -1)
		return (-1);
	return (get_distance(game, &pos_ray));
}

void	print_door(t_game *game, double curr_ang, int ray)
{
	double	h_inter_dist_door;
	int		slice;
	double	dist_view;

	dist_view = (WIN_WIDTH / 2.) / tan(game->fov_ang / 2.);
	h_inter_dist_door = get_horiz_inter_door(game, curr_ang);
	game->distance = h_inter_dist_door;
	if (game->v_inter < h_inter_dist_door)
		return ;
	get_hit_wall(game);
	game->distance *= cos(curr_ang - game->play_ang);
	slice = floor(IMG_SIZE / game->distance * dist_view);
	if (h_inter_dist_door != -1)
		render_door(game, slice, ray);
}
