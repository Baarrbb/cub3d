/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:27:00 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/19 23:01:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cursor(t_game *game)
{
	int	i;
	int	j;

	i = -5;
	while (i <= 5)
	{
		j = -5;
		while (j <= 5)
		{
			if ((j > -2 && j < 2) || (i > -2 && i < 2))
			{
				if (!(j > -2 && j < 2 && i > -2 && i < 2))
				{
					my_mlx_pixel_put(&game->img, \
					(WIN_WIDTH / 2) + i, (WIN_HEIGHT / 2) + j, ROSE);
				}
			}
			j++;
		}
		i++;
	}
}

void	render_pistol(t_game *game)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			color = pixel_get(&game->pistol[0], i * (IMG_SIZE / 200),
					j * (IMG_SIZE / 200));
			if (color != 0xff000000)
			{
				my_mlx_pixel_put(&game->img, (WIN_WIDTH / 2) + i
					- 200 / 2, (WIN_HEIGHT - 200) + j,
					color);
			}
			j++;
		}
		i++;
	}
}

void	pistol_anim(t_game *game)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			color = pixel_get(&game->pistol[game->p_index],
					i * (IMG_SIZE / 200), j * (IMG_SIZE / 200));
			if (color != 0xff000000)
			{
				my_mlx_pixel_put(&game->img, (WIN_WIDTH / 2) + i - 200 / 2,
					(WIN_HEIGHT - 200) + j, color);
			}
			j++;
		}
		i++;
	}
	game->p_index++;
	if (game->p_index == 5)
		game->p = 0;
}
