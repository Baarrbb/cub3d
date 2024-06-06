/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:45:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/06 22:56:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_color(t_game *game, int flag, int i, int slice)
{
	int	offset;
	int	color;

	if (flag == 0 || flag == 1)
		offset = (int)game->hit_wall.x % (int)IMG_SIZE;
	else
		offset = (int)game->hit_wall.y % (int)IMG_SIZE;
	color = pixel_get(&game->text[flag], offset, i * (IMG_SIZE / slice));
	return (color);
}

static void	render_wall(t_game *game, int slice, int pos, int flag)
{
	int				y;
	int				i;
	unsigned int	color;

	i = -1;
	while (++i < slice)
	{
		y = (WIN_HEIGHT / 2) - (slice / 2) + i;
		color = get_color(game, flag, i, slice);
		if (FOG)
		{
			game->intensity = fmax((game->distance
						- (int)IMG_SIZE) / game->distance, 0.1);
			if (game->intensity == 0.1)
				color = darken_color(color, game->intensity);
			else if (((pos - (WIN_WIDTH / 2)) * (pos - (WIN_WIDTH / 2)))
				+ ((y - (WIN_HEIGHT / 2)) * (y - (WIN_HEIGHT / 2)))
				< TORCHE * TORCHE)
			{
				if (game->intensity - 0.5 > 0)
					color = darken_color(color, game->intensity - 0.5);
				else
					color = get_color(game, flag, i, slice);
			}
			else
				color = darken_color(color, game->intensity);
			if (y <= WIN_HEIGHT && y >= 0)
				my_mlx_pixel_put(&game->img, pos, y, color);
		}
		else
		{
			if (y <= WIN_HEIGHT && y >= 0)
				my_mlx_pixel_put(&game->img, pos, y, color);
		}
	}
}

static void	render_floor(t_game *game, int slice, int pos)
{
	int				y;
	unsigned int	color;

	y = 0;
	while (y < (WIN_HEIGHT / 2) - (slice / 2))
	{
		color = game->ceiling;
		game->intensity = fmax((game->distance
					- (int)IMG_SIZE) / game->distance, 0.1);
		if (((pos - (WIN_WIDTH / 2)) * (pos - (WIN_WIDTH / 2)))
			+ ((y - (WIN_HEIGHT / 2)) * (y - (WIN_HEIGHT / 2)))
			< TORCHE * TORCHE)
		{
			if (game->intensity - 0.25 > 0)
				color = darken_color(color, game->intensity - 0.25);
			else
				color = game->floor;
		}
		else
			color = darken_color(color, 0.88);
		if (FOG)
			my_mlx_pixel_put(&game->img, pos, y, color);
		else
			my_mlx_pixel_put(&game->img, pos, y, game->ceiling);
		y++;
	}
	y = (WIN_HEIGHT / 2) + (slice / 2);
	while (y < WIN_HEIGHT)
	{
		color = game->floor;
		game->intensity = fmax((game->distance
					- (int)IMG_SIZE) / game->distance, 0.1);
		if (((pos - (WIN_WIDTH / 2)) * (pos - (WIN_WIDTH / 2)))
			+ ((y - (WIN_HEIGHT / 2)) * (y - (WIN_HEIGHT / 2)))
			< TORCHE * TORCHE)
		{
			if (game->intensity - 0.25 > 0)
				color = darken_color(color, game->intensity - 0.25);
			else
				color = game->floor;
		}
		else
			color = darken_color(color, 0.88);
		if (FOG)
			my_mlx_pixel_put(&game->img, pos, y, color);
		else
			my_mlx_pixel_put(&game->img, pos, y, game->floor);
		y++;
	}
}

static void	render_all(t_game *game)
{
	int		ray;
	int		slice;
	int		flag;
	double	dist_view;

	dist_view = (WIN_WIDTH / 2.) / tan(game->fov_ang / 2.);
	if (game->tir)
	{
		get_right_shoot(game, dist_view);
		get_left_shoot(game);
	}
	game->ray_ang = game->play_ang + (game->fov_ang / 2);
	ray = -1;
	while (++ray < WIN_WIDTH)
	{
		flag = eval_distance(game, ray, 0);
		slice = round(IMG_SIZE / game->distance * dist_view);
		render_wall(game, slice, ray, flag);
		render_floor(game, slice, ray);
		if (game->render && ray == game->var.fwin_x)
			render_shoot(game, game->var.dwin_x);
		game->ray_ang -= ((FOV / (double)WIN_WIDTH) * M_PI / 180.);
		check_max_trigo(game->ray_ang);
	}
}

int	render(t_game *game)
{
	game->ray_ang = game->play_ang + (game->fov_ang / 2);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.l_len, &game->img.endian);
	render_all(game);
	minimap(game->parsing->map_copy, game);
	if (game->p)
		pistol_anim(game);
	else
		render_pistol(game);
	cursor(game);
	if (game->render)
		game->index_anim++;
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	if (game->render || game->p)
		usleep(10000);
	if (game->render && game->index_anim == NB_ANIM - 1)
	{
		game->render = 0;
		game->index_anim = 0;
	}
	return (0);
}
