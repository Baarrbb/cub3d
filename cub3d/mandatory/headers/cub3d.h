/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:20:53 by bsuc              #+#    #+#             */
/*   Updated: 2024/06/20 16:51:02 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/headers/libft.h"
# include "../libft/headers/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <math.h>
# include <errno.h>

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

/*       GAME                          */
# define WIN_WIDTH 640
# define WIN_HEIGHT 400
# define FOV 60
# define IMG_SIZE 64.
# define PLAY_HEIGHT 32 // ??
# define PLAYER_SPEED 2
# define PLAYER_WIDTH 8

#endif