/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:17:27 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 17:18:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static unsigned int	darken_color(unsigned int color, double fog)
{
	t_color	c1;
	t_color	c2;
	t_color	c3;

	c1.t = (color >> 24) & 0xFF;
	c1.r = (color >> 16) & 0xFF;
	c1.g = (color >> 8) & 0xFF;
	c1.b = color & 0xFF;
	c3.t = (0 >> 24) & 0xFF;
	c3.r = (0 >> 16) & 0xFF;
	c3.g = (0 >> 8) & 0xFF;
	c3.b = 0 & 0xFF;
	c2.t = (unsigned int)(c1.t * (1.0 - fog) + c3.t * fog);
	c2.r = (unsigned int)(c1.r * (1.0 - fog) + c3.r * fog);
	c2.g = (unsigned int)(c1.g * (1.0 - fog) + c3.g * fog);
	c2.b = (unsigned int)(c1.b * (1.0 - fog) + c3.b * fog);
	return (c2.t << 24 | c2.r << 16 | c2.g << 8 | c2.b);
}

void	render_with_fog(t_game *game, int pos, t_data *d)
{
	game->intensity = fmax((game->distance
				- (int)IMG_SIZE) / game->distance, 0.1);
	if (game->intensity == 0.1)
		d->color = darken_color(d->color, game->intensity);
	else if (game->light && ((pos - (WIN_WIDTH / 2))
			* (pos - (WIN_WIDTH / 2)))
		+ ((d->y - (WIN_HEIGHT / 2)) * (d->y - (WIN_HEIGHT / 2)))
		< TORCHE * TORCHE)
	{
		if (game->intensity - 0.5 > 0)
			d->color = darken_color(d->color, game->intensity - 0.5);
	}
	else
		d->color = darken_color(d->color, game->intensity);
	if (d->y <= WIN_HEIGHT && d->y >= 0)
		my_mlx_pixel_put(&game->img, pos, d->y, d->color);
}

void	render_floor_with_fog(t_game *game, int pos, t_data *d)
{
	game->intensity = fmax((game->distance
				- (int)IMG_SIZE) / game->distance, 0.1);
	if (game->light && ((pos - (WIN_WIDTH / 2)) * (pos - (WIN_WIDTH / 2)))
		+ ((d->y - (WIN_HEIGHT / 2)) * (d->y - (WIN_HEIGHT / 2)))
		< TORCHE * TORCHE)
	{
		if (game->intensity - 0.25 > 0)
			d->color = darken_color(d->color, game->intensity - 0.25);
		else
			d->color = game->floor;
	}
	else
		d->color = darken_color(d->color, 0.88);
	if (d->y <= WIN_HEIGHT && d->y >= 0)
		my_mlx_pixel_put(&game->img, pos, d->y, d->color);
}
