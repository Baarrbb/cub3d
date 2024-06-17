/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 15:52:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../libft/headers/libft.h"
# include "../libft/headers/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <math.h>
# include <errno.h>
# include <time.h>

# include "struct.h"
# include "parsing.h"
# include "exec.h"

/*       ERROR                          */
# define BOLD "\x1b[1m"
# define RED "\x1b[31m"
# define RESET "\x1b[0m"

/*       PARSING                        */
# define UP 1
# define DOWN 3
# define LEFT 2
# define RIGHT 4
# define NORTH 5
# define SOUTH 6
# define EAST 7
# define WEST 8

/*       GAME                          */
# define WIN_WIDTH 640
# define WIN_HEIGHT 400
# define FOV 60.
# define PLAYER_WIDTH 8
# define IMG_SIZE 64.
# define SHOOT_SIZE 130.
# define PISTOL_W 99
# define PISTOL_H 88
# define MINIMAP_BLOCK 9.


# define PLAYER_SPEED 3
# define FOG 1
# define TORCHE 100

uint32_t	whiten_color(uint32_t color, uint8_t increase);
uint32_t	lighten_color(uint32_t color, uint8_t increase);
void		cursor(t_game *game);
void		pistol(t_game *game);
void		minimap(char **map, t_game *game);
char		**map_copy(char **map);

void		init_pistol(t_game *game);
void		render_pistol(t_game *game);
void		pistol_anim(t_game *game);

#endif