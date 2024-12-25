/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:40:34 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 18:56:24 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_textures *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	get_tex_color(t_textures *texture, t_vector2i tex_pos)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (tex_pos.y * texture->line_length
			+ tex_pos.x * (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
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

void	set_new_pos(t_game *g, t_vector2f move_dir)
{
	t_vector2i	new_pos;

	new_pos.x = (int)(g->player.pos.x + move_dir.x);
	new_pos.y = (int)(g->player.pos.y + move_dir.y);
	if ((int)new_pos.y >= 0 && (int)new_pos.y < g->map_height
		&& g->map[(int)new_pos.y][(int)(g->player.pos.x)] == '0')
		g->player.pos.y += move_dir.y;
	if ((int)new_pos.x >= 0 && (int)new_pos.x < g->map_width
		&& g->map[(int)(g->player.pos.y)][(int)new_pos.x] == '0')
		g->player.pos.x += move_dir.x;
}
