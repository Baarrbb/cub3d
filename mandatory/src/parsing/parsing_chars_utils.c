/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_chars_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ersees <ersees@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:37:54 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/22 21:38:31 by ersees           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_utils(t_parse *parsed, t_file *init, int *index)
{
	parsed->c_red = ft_atoi(&init->line[*index]);
	*index = skip_nb_and_spaces(*index, parsed, init);
	if (parsed->c_red > 255 || parsed->c_red < 0)
		errorfunctionparse(parsed, "Wrong red code\n");
	parsed->c_green = ft_atoi(&init->line[*index]);
	if (parsed->c_green > 255 || parsed->c_green < 0)
		errorfunctionparse(parsed, "Wrong green code\n");
	*index = skip_nb_and_spaces(*index, parsed, init);
	parsed->c_blue = ft_atoi(&init->line[*index]);
	if (parsed->c_blue > 255 || parsed->c_blue < 0)
		errorfunctionparse(parsed, "Wrong blue code\n");
}

int	fill_util(t_parse *parsed, t_file *init, int *index)
{
	parsed->f_red = ft_atoi(&init->line[*index]);
	*index = skip_nb_and_spaces(*index, parsed, init);
	if (parsed->f_red > 255 || parsed->f_red < 0)
		errorfunctionparse(parsed, "Wrong red code\n");
	parsed->f_green = ft_atoi(&init->line[*index]);
	if (parsed->f_green > 255 || parsed->f_green < 0)
		errorfunctionparse(parsed, "Wrong green code\n");
	*index = skip_nb_and_spaces(*index, parsed, init);
	parsed->f_blue = ft_atoi(&init->line[*index]);
	if (parsed->f_blue > 255 || parsed->f_blue < 0)
		errorfunctionparse(parsed, "Wrong blue code\n");
}