/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:17:27 by marvin            #+#    #+#             */
/*   Updated: 2024/06/06 21:33:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	darken_color(unsigned int color, double fog)
{
	t_color	c1;
	t_color	c2;
	t_color	c3;

	c1.t = (color >> 24) & 0xFF;
	c1.r = (color >> 16) & 0xFF;
	c1.g = (color >> 8) & 0xFF;
	c1.b = color & 0xFF;
	c3.t = (0 >> 24) & 0xFF;
	c3.r = (0 >> 16) & 0xFF;
	c3.g = (0 >> 8) & 0xFF;
	c3.b = 0 & 0xFF;
	c2.t = (unsigned int)(c1.t * (1.0 - fog) + c3.t * fog);
	c2.r = (unsigned int)(c1.r * (1.0 - fog) + c3.r * fog);
	c2.g = (unsigned int)(c1.g * (1.0 - fog) + c3.g * fog);
	c2.b = (unsigned int)(c1.b * (1.0 - fog) + c3.b * fog);
	return (c2.t << 24 | c2.r << 16 | c2.g << 8 | c2.b);
}

/*
uint32_t whiten_color(uint32_t color, uint8_t increase)
{
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = r + increase > 255 ? 255 : r + increase;
    g = g + increase > 255 ? 255 : g + increase;
    b = b + increase > 255 ? 255 : b + increase;

    return (r << 16) | (g << 8) | b;
}

uint32_t lighten_color(uint32_t color, uint8_t increase)
{
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = fmin(r + increase, 255);
    g = fmin(g + increase, 255);
    b = fmin(b + increase, 255);

    return (r << 16) | (g << 8) | b;
}
*/