/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:09:56 by bsuc              #+#    #+#             */
/*   Updated: 2024/06/05 15:32:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_anim(t_game *game)
{
	int	i;

	i = -1;
	while (++i < NB_ANIM)
	{
		if (game->shoot[i].img)
			mlx_destroy_image(game->mlx, game->shoot[i].img);
	}
}

void	free_ptr(t_game *game)
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

void	handle_error(const char *s, t_parse *parsing, int ex)
{
	ft_putstr_fd(RED BOLD "[Error]\n" RESET, 2);
	if (s)
		ft_putstr_fd((char *)s, 2);
	if (parsing)
		free_parse(parsing);
	if (ex)
		exit(EXIT_FAILURE);
}

int	win_exit(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_ptr(game);
	free_anim(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->parsing)
		free_parse(game->parsing);
	exit(EXIT_SUCCESS);
	return (0);
}

void	free_shoot(t_game *game, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (game->shoot[j].img)
			mlx_destroy_image(game->mlx, game->shoot[j].img);
	}
}
