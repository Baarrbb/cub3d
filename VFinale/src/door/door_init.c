/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:32:09 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/20 15:51:11 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

long	get_current_time(long times)
{
	struct timespec	time;

	if (clock_gettime(CLOCK_MONOTONIC, &time) == -1)
		write(2, "clock_gettime() error\n", 23);
	return (time.tv_sec * 1000 + time.tv_nsec / 1000000 - times);
}

void	init_door(t_game *game)
{
	t_mlx	t;
	int		x;
	int		y;

	game->minimap_size = WIN_HEIGHT / 6;
	if (game->minimap_size % 2 == 0)
		game->minimap_size++;
	game->start_timer = get_current_time(get_current_time(0));
	x = IMG_SIZE;
	y = IMG_SIZE;
	t.img = mlx_xpm_file_to_image(game->mlx, "textures/door.xpm", &x, &y);
	if (!t.img)
		handle_error("Malloc problem ptr img door\n", game->parsing, game, 1);
	t.addr = mlx_get_data_addr(t.img, &t.bpp, &t.l_len, &t.endian);
	game->door = t;
}

static void	tree_doors(t_door **doors, int y, int x)
{
	t_door	*door;
	t_door	*ptr;

	door = ft_calloc(1, sizeof(t_door));
	if (door == NULL)
		return ;
	door->startx = x;
	door->starty = y + 1;
	door->endx = x + 1;
	door->endy = y + 1;
	door->px = door->startx * (int)IMG_SIZE;
	door->py = door->starty * (int)IMG_SIZE + (int)(IMG_SIZE / 2);
	door->endpx = door->endx * (int)IMG_SIZE;
	door->endpy = door->endy * (int)IMG_SIZE + (int)(IMG_SIZE / 2);
	door->time = get_current_time(0);
	if (*doors == NULL)
	{
		*doors = door;
		return ;
	}
	ptr = (*doors);
	while (ptr != NULL && ptr->next)
		ptr = ptr->next;
	if (ptr != NULL)
		ptr->next = door;
}

void	govalo(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->parsing->map[y])
	{
		x = 0;
		while (game->parsing->map[y][x])
		{
			if (game->parsing->map[y][x] == 'D')
				tree_doors(&game->doors, y, x);
			x++;
		}
		y++;
	}
}
