/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:08:53 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 16:48:14 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data
{
	char	**copy_map;
	int		index;
	int		index_j;
}	t_data;

typedef struct s_file
{
	char			*line;
	struct s_file	*next;
}	t_file;

typedef struct s_parse
{
	char	**map;

	char	*north;
	char	*south;
	char	*east;
	char	*west;

	t_file	*init;

	int		f_red;
	int		f_green;
	int		f_blue;

	int		c_red;
	int		c_green;
	int		c_blue;

	int		player_position;

	int		len_y;
}	t_parse;

typedef struct s_coor
{
	double	x;
	double	y;
}	t_coor;

typedef struct s_coll
{
	int		count;
	int		negatifx;
	int		negatify;
	t_coor	startp;
	t_coor	endp;
}	t_coll;

typedef struct s_mlx
{
	void	*img;
	void	*addr;

	int		bpp;
	int		l_len;
	int		endian;
}	t_mlx;

typedef struct s_key
{
	int	l_view;
	int	r_view;
	int	l_move;
	int	r_move;
	int	f_move;
	int	b_move;
}	t_key;

typedef struct s_game
{
	t_parse	*parsing;

	void	*mlx;
	void	*win;

	t_mlx	text[4];
	t_mlx	img;

	int		floor;
	int		ceiling;

	t_coor	hit_wall;

	double	play_x;
	double	play_y;
	double	play_ang;
	double	fov_ang;
	double	ray_ang;
	double	distance;

	t_key	key_event;
}	t_game;

#endif