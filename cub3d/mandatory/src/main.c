/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:19:43 by bsuc              #+#    #+#             */
/*   Updated: 2024/06/20 16:50:40 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	loop_fun(t_game *game)
{
	render(game);
	key_event(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_parse	*pars;
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd(RED BOLD "Error\n" RESET "Wrong arguments\n", 2);
		ft_putstr_fd(BLUE "\nUsage : " RESET "./cub3D <filename>.cub\n", 2);
		return (1);
	}
	pars = parsing(av);
	if (parsing_map(pars))
		return (free_parse(pars), 1);
	pars->len_y = ft_strlen_matrice(pars->map);
	game_init(&game, pars);
	ft_memset(&(game.key_event), 0, sizeof(t_key));
	mlx_hook(game.win, KeyPress, KeyPressMask, press_key, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, release_key, &game);
	mlx_loop_hook(game.mlx, &loop_fun, &game);
	mlx_hook(game.win, DestroyNotify, 0, win_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
