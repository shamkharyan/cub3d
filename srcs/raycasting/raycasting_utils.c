/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:40:34 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 14:25:15 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_textures *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void	draw_vline(t_textures *data, int x, t_vector2i y12, int color)
{
	int y;

	y = y12.x - 1;
	while (++y <= y12.y)
		my_mlx_pixel_put(data, x, y, color);
}

int get_texture_color(t_textures *texture, int x, int y)
{
    char	*pixel;
    int		color;

    pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    color = *(unsigned int *)pixel;

    return color;
}

double	ternary(int condition, double t, double f)
{
	if (condition)
		return (t);
	return (f);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
