/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistol_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:51:17 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 15:40:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_xpm(t_game *game, char *name, int i, char *ext)
{
	char	*dir;
	char	*path;
	t_mlx	t;
	int		x;
	int		y;

	x = (int)IMG_SIZE;
	y = (int)IMG_SIZE;
	dir = "./textures/pistol/";
	path = strjoin(ft_strdup(dir), name);
	t.img = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	if (!t.img)
	{
		free(name);
		free(ext);
		free(path);
		handle_error("Malloc problem ptr img pistol\n", game->parsing, game, 1);
	}
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.l_len, &t.endian);
	game->pistol[i] = t;
	free(path);
}

void	init_pistol(t_game *game)
{
	int		i;
	char	*final;
	char	*str;
	char	*ext;

	i = -1;
	ext = ft_strdup(".xpm");
	while (++i < 5)
	{
		str = ft_itoa(i);
		final = strjoin(ft_strdup("pistol"), str);
		final = strjoin(final, ext);
		free(str);
		init_xpm(game, final, i, ext);
		free(final);
	}
	free(ext);
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
				my_mlx_pixel_put(&game->img, (WIN_WIDTH / 2) + i - 200 / 2,
					(WIN_HEIGHT - 200) + j, color);
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
