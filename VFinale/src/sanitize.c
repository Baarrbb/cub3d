/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:09:56 by bsuc              #+#    #+#             */
/*   Updated: 2024/06/19 17:44:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_anim(t_game *game, int i, int j)
{
	int	k;

	k = -1;
	while (++k < i)
	{
		if (game->shoot[k].img)
			mlx_destroy_image(game->mlx, game->shoot[k].img);
	}
	k = -1;
	while (++k < j)
	{
		if (game->pistol[k].img)
			mlx_destroy_image(game->mlx, game->pistol[k].img);
	}
}

static void	free_doors(t_game *game)
{
	t_door	*tmp;

	if (game->doors)
	{
		while (game->doors)
		{
			tmp = game->doors->next;
			free(game->doors);
			game->doors = tmp;
		}
		game->doors = 0;
	}
	if (game->door.img)
		mlx_destroy_image(game->mlx, game->door.img);
}

static void	free_ptr(t_game *game)
{
	if (game->text[0].img)
		mlx_destroy_image(game->mlx, game->text[0].img);
	if (game->text[1].img)
		mlx_destroy_image(game->mlx, game->text[1].img);
	if (game->text[2].img)
		mlx_destroy_image(game->mlx, game->text[2].img);
	if (game->text[3].img)
		mlx_destroy_image(game->mlx, game->text[3].img);
}

void	handle_error(const char *s, t_parse *parsing, t_game *game, int ex)
{
	ft_putstr_fd(RED BOLD "[Error]\n" RESET, 2);
	if (s)
		ft_putstr_fd((char *)s, 2);
	if (parsing)
		free_parse(parsing);
	free_ptr(game);
	free_anim(game, NB_ANIM, 5);
	free_doors(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (ex)
		exit(EXIT_FAILURE);
}

int	win_exit(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_ptr(game);
	free_anim(game, NB_ANIM, 5);
	free_doors(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->parsing)
		free_parse(game->parsing);
	exit(EXIT_SUCCESS);
	return (0);
}
