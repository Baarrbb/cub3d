/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:09:02 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:06:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "cub3d.h"

/***************************************************/
/*                      EXEC                       */
/***************************************************/
/**/
/*                    GAME_INIT_C                   */
void			game_init(t_game *game, t_parse *p);

/*                   KEY_EVENT.C                   */
int				press_key(int keycode, t_game *game);
int				release_key(int keycode, t_game *game);
int				key_event(t_game *game);

/*                   MOVE.C                        */
void			key_move(t_game *game, int keycode);

/*                   RENDER.C                     */
int				render(t_game *game);

/*                   GET_DISTANCE.C               */
int				eval_distance(t_game *game);

/*                   RAYCASTING.C                 */
double			get_horiz_inter(t_game *game, double curr_ang, double s);
double			get_verti_inter(t_game *game, double curr_ang, double c);

/*                   MLX_PIXEL_C                 */
unsigned int	pixel_get(t_mlx *img, int x, int y);
void			my_mlx_pixel_put(t_mlx *img, int x, int y, int color);

/*                   TRIGO_UTILS.C                 */
void			eval_move(t_game *game, t_coor *move, int dir);
void			eval_step(double curr_ang, double *step, int x);
void			check_max_trigo(double ang);

/*                   SANITIZE_C                    */
void			handle_error(const char *s, t_parse *parsing, int ex);
void			free_ptr(t_game *game);
int				win_exit(t_game *game);

#endif