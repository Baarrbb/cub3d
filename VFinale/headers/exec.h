/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:20:23 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 22:15:39 by marvin           ###   ########.fr       */
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

/*                    KEY_EVENT.C                   */
int				press_key(int keycode, t_game *game);
int				release_key(int keycode, t_game *game);
int				key_event(t_game *game);

/*                    MOVE.C                        */
void			key_move(t_game *game, int keycode);

/*                    MOVE_UTILS_C                  */
void			equal_zero(t_coll *collision, t_coor *move);
void			count_coll(t_coll *collision, t_coor *move, int test);
int				is_in_square(t_game game, t_coor startp, t_coor endp);

/*                   RENDER.C                     */
int				render(t_game *game);

/*                   GET_DISTANCE.C               */
int				eval_distance(t_game *game, int ray, int yes);
void			get_hit_wall(t_game *game);

/*                   RAYCASTING.C                 */
double			get_horiz_inter(t_game *game, double curr_ang, double s);
double			get_verti_inter(t_game *game, double curr_ang, double c);
double			get_distance(t_game *game, t_coor *inter);

/*                   MLX_PIXEL_C                 */
unsigned int	pixel_get(t_mlx *img, int x, int y);
void			my_mlx_pixel_put(t_mlx *img, int x, int y, int color);

/*                   TRIGO_UTILS.C                 */
void			eval_move(t_game *game, t_coor *move, int dir);
void			eval_step(double curr_ang, double *step, int x);
void			check_max_trigo(double *ang);

/*                   SANITIZE_C                    */
void			handle_error(const char *s, t_parse *parsing,
					t_game *game, int ex);
int				win_exit(t_game *game);

/*                   MINIMAP_C                      */
void			minimap(char **map, t_game *game);

/*                   FOG_C                          */
void			render_with_fog(t_game *game, int pos, t_data *d);
void			render_floor_with_fog(t_game *game, int pos, t_data *d);

/***************************************************/
/*                      SHOOT/                     */
/***************************************************/
/**/
/*                   PISTOL_INIT_C                 */
void			init_pistol(t_game *game);

/*                   PISTOL.C                      */
void			cursor(t_game *game);
void			render_pistol(t_game *game);
void			pistol_anim(t_game *game);

/*                    SHOOT_INIT.C                 */
void			init_shoot(t_game *game);

/*                   SHOOT.C                       */
void			render_shoot(t_game *game, int pos);
void			get_right_shoot(t_game *game, double dist_view);
void			get_left_shoot(t_game *game);
void			shoot(t_game *game);

/*                   SHOOT_RIGHT.C                */
void			eval_right_shoot(t_game *game, t_coor last_wall, int ray);

/*                   SHOOT_LEFT.C                 */
void			eval_left_shoot(t_game *game, int ray);

/***************************************************/
/*                      DOOR/                      */
/***************************************************/
/**/
/*                   DOOR_INIT_C                   */
long			get_current_time(long times);
void			init_door(t_game *game);
void			govalo(t_game *game);

/*                   DOOR_ANIMATIONS_C             */
void			open_door(t_game *game);
void			doors_state(t_game *game);

/*                  RENDER_DOORS_UTILS_C           */
int				find_door(t_game *game, t_coor step, t_coor *pos_ray, int test);

/*                   PRINT_DOORS_C                 */
void			print_door(t_game *game, double curr_ang, int ray);

#endif