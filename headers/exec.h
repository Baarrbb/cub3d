/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:09:02 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 14:13:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "cub3d.h"

int	release_key(int keycode, t_game *game);
int	press_key(int keycode, t_game *game);
int	key_event(t_game *game);

/***************************************************/
/*                      EXEC                       */
/***************************************************/
/**/
/*                    GAME_INIT_C                   */
void			game_init(t_game *game, t_parse *p);

/*                   MLX_PIXEL_C                 */
unsigned int	pixel_get(t_mlx *img, int x, int y);
void			my_mlx_pixel_put(t_mlx *img, int x, int y, int color);

/*                   RAYCASTING.C                 */
double			get_horiz_inter(t_game *game, double curr_ang, double s);
double			get_verti_inter(t_game *game, double curr_ang, double c);

/*                   GET_DISTANCE.C               */
int				eval_distance(t_game *game);

/*                   RENDER.C                     */
int				render(t_game *game);

/*                   HIT_WALL.C                    */
int				hit_wall(t_game *game, t_coor *move);

/*                   KEY_EVENT.C                   */
int				get_key_event(int keycode, t_game *game);

/*                   TRIGO_UTILS.C                 */
void			eval_move(t_game *game, t_coor *move, int dir);
void			eval_step(double curr_ang, double *step, int x);
void			check_max_trigo(double ang);

/*                   SANITIZE_C                    */
void			handle_error(const char *s, t_parse *parsing, int ex);
void			free_ptr(t_game *game);
int				win_exit(t_game *game);

#endif