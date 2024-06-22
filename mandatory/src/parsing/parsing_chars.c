/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ersees <ersees@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:37:42 by ytouihar          #+#    #+#             */
/*   Updated: 2024/06/22 21:40:25 by ersees           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map(t_parse *parsed, t_file *init)
{
	int		i;
	char	**map;

	i = file_len(init);
	map = malloc(sizeof(char *) * (i + 1));
	if (map == NULL)
		errorfunctionparse(parsed, "Error malloc");
	map[i] = 0;
	i = 0;
	while (init)
	{
		map[i] = ft_strdup(init->line);
		if (map[i] == NULL)
		{
			free_map(map);
			errorfunctionparse(parsed, "Error malloc");
		}
		init = init->next;
		i++;
	}
	parsed->map = map;
}

/*static int	fill_ceiling(t_parse *parsed, t_file *init, char direction)
{
	int	index;

	index = 0;
	while (init->line && init->line[index] == ' ')
		index++;
	index++;
	if (init->line[index - 1] == direction)
	{
		while (init->line[index] && init->line[index] == ' ')
			index++;
		parsed->c_red = ft_atoi(&init->line[index]);
		index = skip_nb_and_spaces(index, parsed, init);
		if (parsed->c_red > 255 || parsed->c_red < 0)
			errorfunctionparse(parsed, "Wrong red code\n");
		parsed->c_green = ft_atoi(&init->line[index]);
		if (parsed->c_green > 255 || parsed->c_green < 0)
			errorfunctionparse(parsed, "Wrong green code\n");
		index = skip_nb_and_spaces(index, parsed, init);
		parsed->c_blue = ft_atoi(&init->line[index]);
		if (parsed->c_blue > 255 || parsed->c_blue < 0)
			errorfunctionparse(parsed, "Wrong blue code\n");
		check_end_parse(parsed, init, index);
		return (1);
	}
	return (0);
}*/

static int	fill_ceiling(t_parse *parsed, t_file *init, char platform, int *done)
{
	int	index;

	index = 0;
	while (init->line && init->line[index] == ' ')
		index++;
	index++;
	if (init->line[index - 1] == platform)
	{
		if (*done == 0)
			*done = 1;
		else
			errorfunctionparse(parsed, "There is already a ceiling.\n");
		while (init->line && init->line[index] == ' ')
			index++;
		if (init->line[index] < '0' && init->line[index] > '9')
			errorfunctionparse(parsed, "Wrong red code\n");
		parsed->f_red = ft_atoi(&init->line[index]);
		fill_utils(parsed, init, &index);
		check_end_parse(parsed, init, index);
		return (1);
	}
	return (0);
}

static int	fill_floor(t_parse *parsed, t_file *init, char platform, int *done)
{
	int	index;

	index = 0;
	while (init->line && init->line[index] == ' ')
		index++;
	index++;
	if (init->line[index - 1] == platform)
	{
		if (*done == 0)
			*done = 1;
		else
			errorfunctionparse(parsed, "There is already a floor.\n");
		while (init->line && init->line[index] == ' ')
			index++;
		if (init->line[index] < '0' && init->line[index] > '9')
			errorfunctionparse(parsed, "Wrong red code\n");
		parsed->f_red = ft_atoi(&init->line[index]);
		fill_util(parsed, init, &index);
		check_end_parse(parsed, init, index);
		return (1);
	}
	return (0);
}

static int	parse_direction(t_parse *parsed, t_file *init, char *dir, char **t)
{
	int	index;
	int	len;

	index = 0;
	len = 0;
	while (init->line && init->line[index] == ' ')
		index++;
	if (ft_strncmp(&init->line[index], dir, ft_strlen(dir)) == 0)
	{
		index += 2;
		while (init->line[index] == ' ')
			index++;
		if (*t != NULL)
			errorfunctionparse(parsed, "This dir already exists\n");
		while (init->line[index])
		{
			index++;
			len++;
		}
		*t = ft_substr(init->line, index - len, len - 1);
		if (*t == NULL)
			errorfunctionparse(parsed, "Substr error malloc\n");
		return (1);
	}
	return (0);
}

void	fill_struct(t_parse *parsed, t_file *init)
{
	int	check;
	int	count;
	int	donec;
	int	donef;

	count = 0;
	donec = 0;
	donef = 0;
	parsed->init = init;
	while (init && count < 6)
	{
		check = 0;
		check += parse_direction(parsed, init, "NO", &parsed->north);
		check += parse_direction(parsed, init, "EA", &parsed->east);
		check += parse_direction(parsed, init, "SO", &parsed->south);
		check += parse_direction(parsed, init, "WE", &parsed->west);
		check += fill_floor(parsed, init, 'F', &donef);
		check += fill_ceiling(parsed, init, 'C', &donec);
		if (check <= 0)
			errorfunctionparse(parsed, "Lacks something\n");
		count++;
		init = init->next;
	}
	fill_map(parsed, init);
}
