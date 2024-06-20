/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuc <bsuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:20:20 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 15:48:43 by bsuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d_bonus.h"

/***************************************************/
/*                   PARSING                       */
/***************************************************/
/**/
/*                   PARSING.C                     */
t_parse			*parsing(char **argv);
int				trim_backslashn(t_file *init);

/*                   PARSING_UTILS.C               */
void			check_end_parse(t_parse *parsed, t_file *init, int index);
int				ft_inisize(t_file *lst);
t_parse			*initalizeparse(void);
int				skip_nb_and_spaces(int index, t_parse *parsed, t_file *init);
int				ft_strlen_matrice(char **map);

/*                   PARSING_UTILS2.C                */
int				file_len(t_file *file);
void			empty_init(t_file *init);
int				check_border(char **copy_map);
int				line_copy(t_data *d, int i, int j, char **map);
void			handle_error_pars(char *s);

/*                   PARSING_CHARS.C               */
void			fill_struct(t_parse *parsed, t_file *init);

/*                   PARSING_STRUCT.C                 */
void			get_cubfile(t_file **init, char *file);

/*                   PARSING_MAP.C                 */
int				parsing_map(t_parse *parsed);
int				check_correct_walls(char **map, int x, int y, int type);
char			**map_copy(char **map);

/*                   RIGHT_SIDE.C                  */
int				find_longest_line(char **map, int *i);
char			**copy_right_with_spaces(char **map, int i, int j);
int				handle_right(char **copy_map);

/*                   PARSING_MAP2.C                */
int				check_inside(t_parse *parsed, char **copy_map);

/*                   PARSING_SANITIZE.C            */
void			free_struct(t_file *init);
void			errorfunctionparse(t_parse *parsed, char *message);
void			free_map(char **map);
void			free_parse(t_parse *parsed);

#endif