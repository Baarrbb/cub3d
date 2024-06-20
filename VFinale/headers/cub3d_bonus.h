/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:57:47 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 16:23:33 by bsuc             ###   ########.fr       */
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
# define BLUE "\x1b[36m"
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

/*       COLORS                        */
# define ROSE 0xff11b2
# define BLEU 0xf1034A6
# define BLANC 0x000000
# define NOIR 0xffffff
# define MARRON 0x582900
# define JAUNE 0xFFE600

/*       GAME                          */
# define FOV 60.
# define PLAYER_WIDTH 1
# define IMG_SIZE 64.
# define SHOOT_SIZE 130.
# define PISTOL_W 99
# define PISTOL_H 88
# define MINIMAP_BLOCK 9.

# define WIN_WIDTH 640
# define WIN_HEIGHT 400
# define PLAYER_SPEED 4
# define TORCHE 100

#endif