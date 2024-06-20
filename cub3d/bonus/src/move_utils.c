/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:35:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 22:16:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	data_collision(t_coll *collision, t_coor *move, int x)
{
	if (x)
	{
		collision->startp.x -= collision->negatifx;
		collision->endp.x -= collision->negatifx;
		move->x += collision->negatifx;
	}
	else
	{
		collision->startp.y -= collision->negatify;
		collision->endp.y -= collision->negatify;
		move->y += collision->negatify;
	}
}

void	equal_zero(t_coll *collision, t_coor *move)
{
	if (collision->count == 0)
	{
		data_collision(collision, move, 1);
		collision->count++;
	}
	if (collision->count == 1)
	{
		data_collision(collision, move, 0);
		collision->count = 0;
	}
}

void	count_coll(t_coll *collision, t_coor *move, int test)
{
	if (collision->count < test)
	{
		if ((int)fabs(move->x) > (int)fabs(move->y))
			data_collision(collision, move, 1);
		else
			data_collision(collision, move, 0);
		collision->count++;
	}
	else if (test != 0 && collision->count >= test)
	{
		if ((int)fabs(move->x) > (int)fabs(move->y))
			data_collision(collision, move, 0);
		else
			data_collision(collision, move, 1);
		collision->count = 0;
	}
}

static void	eval_step_move(int d, int *step)
{
	if (d > 0)
		*step = 1;
	else
		*step = -1;
}

int	is_in_square(t_game game, t_coor startp, t_coor endp)
{
	int	step_size;
	int	step_x;
	int	step_y;
	int	i;
	int	map_x;

	i = -1;
	if (fabs(endp.x - startp.x) > fabs(endp.y - startp.y))
		step_size = fabs(endp.x - startp.x);
	else
		step_size = fabs(endp.y - startp.y);
	eval_step_move(endp.x - startp.x, &step_x);
	eval_step_move(endp.y - startp.y, &step_y);
	while (++i <= step_size)
	{
		map_x = (int)startp.x / (int)IMG_SIZE;
		if (game.parsing->map[(int)startp.y / (int)IMG_SIZE][map_x] == '1' \
		|| game.parsing->map[(int)startp.y / (int)IMG_SIZE][map_x] == 'D')
			return (1);
		startp.x += step_x;
		startp.y += step_y;
	}
	return (0);
}
