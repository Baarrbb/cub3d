/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:22:26 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/19 17:47:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	animation_choosing(t_game *game, t_door *ptr)
{
	char	**map;

	map = game->parsing->map;
	if (map[ptr->starty - 1][ptr->startx] == 'D' && ptr->open == 0)
		ptr->open = 1;
	else if (map[ptr->starty - 1][ptr->startx] == 'D' && ptr->open == 1)
		ptr->open = 3;
	else if (map[ptr->starty - 1][ptr->startx] == 'D' && ptr->open == 3)
		ptr->open = 1;
	if (map[ptr->starty - 1][ptr->startx] == 'd' && ptr->open == 2)
	{
		map[ptr->starty - 1][ptr->startx] = 'D';
		ptr->open = 3;
	}
}

void	open_door(t_game *game)
{
	t_door	*ptr;
	int		xdist;
	int		ydist;

	ptr = game->doors;
	while (ptr)
	{
		xdist = (int)fabs(game->play_x / (int)IMG_SIZE - ptr->startx);
		ydist = (int)fabs(game->play_y / (int)IMG_SIZE - ptr->starty + 1);
		if (xdist + ydist < 2 && xdist + ydist > 0)
			animation_choosing(game, ptr);
		ptr = ptr->next;
	}
}

static void	opening_doors(t_game *game, t_door *ptr)
{
	int	play_y;
	int	play_x;

	if (ptr->open == 3 && ptr->endpx < ptr->endx * (int)IMG_SIZE)
		ptr->endpx += 4;
	else if (ptr->open == 3 && ptr->endpx == ptr->endx * (int)IMG_SIZE)
		ptr->open = 0;
	if (ptr->open == 2 && get_current_time(ptr->time) > 5000)
	{
		play_y = (game->play_y / (int)IMG_SIZE);
		play_x = (game->play_x / (int)IMG_SIZE);
		if (game->parsing->map[play_y][play_x] == 'd')
			ptr->time = get_current_time(game->start_timer) + 2000;
		else
		{
			game->parsing->map[ptr->starty - 1][ptr->startx] = 'D';
			ptr->open = 3;
		}
	}
}

void	doors_state(t_game *game)
{
	t_door	*ptr;

	ptr = game->doors;
	while (ptr)
	{
		if (ptr->open == 1 && ptr->endpx != ptr->px)
			ptr->endpx -= 4;
		if (ptr->endpx == ptr->px && ptr->open == 1)
		{
			ptr->time = get_current_time(game->start_timer);
			game->parsing->map[ptr->starty - 1][ptr->startx] = 'd';
			ptr->open = 2;
		}
		opening_doors(game, ptr);
		ptr = ptr->next;
	}
}
