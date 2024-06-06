/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:12:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:34:14 by marvin           ###   ########.fr       */
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

	x = (int)SHOOT_SIZE;
	y = (int)SHOOT_SIZE;
	dir = "./textures/shoot/";
	path = strjoin(ft_strdup(dir), name);
	t.img = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	if (!t.img)
	{
		free(name);
		free(ext);
		free_shoot(game, i);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		handle_error("Malloc problem ptr img shoot\n", game->parsing, 1);
	}
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.l_len, &t.endian);
	game->shoot[i] = t;
	free(path);
}

void	init_shoot(t_game *game)
{
	int		i;
	char	*final;
	char	*str;
	char	*ext;

	i = -1;
	ext = ft_strdup(".xpm");
	while (++i < NB_ANIM)
	{
		str = ft_itoa(i);
		final = strjoin(ft_strdup("shoot"), str);
		final = strjoin(final, ext);
		free(str);
		init_xpm(game, final, i, ext);
		free(final);
	}
	free(ext);
}

void	shoot(t_game *game)
{
	ft_memset(&(game->var), 0, sizeof(t_shoot));
	game->tir = 1;
	game->render = 1;
	game->var.cross_r = 0;
	game->var.cross_l = 0;
}
