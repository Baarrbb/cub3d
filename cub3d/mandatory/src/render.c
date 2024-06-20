/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:45:31 by marvin            #+#    #+#             */
/*   Updated: 2024/03/18 16:31:25 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (y <= WIN_HEIGHT && y >= 0)
			my_mlx_pixel_put(&game->img, pos, y, color);
	}
}

static void	render_floor(t_game *game, int slice, int pos)
{
	int	y;

	y = 0;
	while (y < (WIN_HEIGHT / 2) - (slice / 2))
	{
		my_mlx_pixel_put(&game->img, pos, y, game->ceiling);
		y++;
	}
	y = (WIN_HEIGHT / 2) + (slice / 2);
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->img, pos, y, game->floor);
		y++;
	}
}

int	render(t_game *game)
{
	int		ray;
	int		slice;
	int		flag;
	double	dist_view;

	dist_view = (WIN_WIDTH / 2.) / tan(game->fov_ang / 2.);
	game->ray_ang = game->play_ang + (game->fov_ang / 2);
	ray = -1;
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.l_len, &game->img.endian);
	while (++ray < WIN_WIDTH)
	{
		flag = eval_distance(game);
		slice = round(IMG_SIZE / game->distance * dist_view);
		render_wall(game, slice, ray, flag);
		render_floor(game, slice, ray);
		game->ray_ang -= (((double)FOV / (double)WIN_WIDTH) * M_PI / 180.);
		check_max_trigo(game->ray_ang);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
