/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:20:23 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:43:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "cub3d_bonus.h"

/***************************************************/
/*                      EXEC                       */
/***************************************************/
/**/
/*                    GAME_INIT_C                   */
void			game_init(t_game *game, t_parse *p);

/*                    SHOOT.C                       */
void			init_shoot(t_game *game);
void			shoot(t_game *game);

/*                    KEY_EVENT.C                   */
int				press_key(int keycode, t_game *game);
int				release_key(int keycode, t_game *game);
int				key_event(t_game *game);

/*                    MOVE.C                        */
void			key_move(t_game *game, int keycode);

/*                   RENDER.C                     */
int				render(t_game *game);

/*                   RENDER_SHOOT.C               */
void			get_right_shoot(t_game *game, double dist_view);
void			get_left_shoot(t_game *game);
void			render_shoot(t_game *game, int pos);

/*                   GET_DISTANCE.C               */
int				eval_distance(t_game *game, int ray, int yes);

/*                   RAYCASTING.C                 */
double			get_horiz_inter(t_game *game, double curr_ang, double s);
double			get_verti_inter(t_game *game, double curr_ang, double c);

/*                   SHOOT_RIGHT.C                */
void			eval_right_shoot(t_game *game, t_coor last_wall, int ray);

/*                   SHOOT_LEFT.C                 */
void			eval_left_shoot(t_game *game, int ray);

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
void			free_shoot(t_game *game, int i);

#endif