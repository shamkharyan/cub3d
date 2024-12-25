/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:51:43 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 15:52:38 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_game *g, t_vector2i start, t_vector2i size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size.y)
	{
		j = -1;
		while (++j < size.x)
			my_mlx_pixel_put(&g->screen_buff, start.x + j, start.y + i, color);
	}
}

void	draw_circle(t_game *g, t_vector2i start, int radius, int color)
{
	int	i;
	int	j;

	i = -radius - 1;
	while (++i <= radius)
	{
		j = -radius - 1;
		while (++j <= radius)
			if (i * i + j * j <= radius * radius)
				my_mlx_pixel_put(
					&g->screen_buff, start.x + j, start.y + i, color);
	}
}

void	init_minimap(t_game *g)
{
	g->minimap.size.x = 200;
	g->minimap.size.y = 200;
	g->minimap.scale = 10;
	g->minimap.border_width = 5;
	g->minimap.offset.x = 15;
	g->minimap.offset.y = 15;
	g->minimap.wall_color = create_trgb(0, 0x88, 0x88, 0x88);
	g->minimap.void_color = create_trgb(0, 0, 0, 0);
	g->minimap.player_color = create_trgb(0, 0xFF, 0, 0);
	g->minimap.ground_color = create_trgb(0, 0xFF, 0xFF, 0xFF);
	g->minimap.border_color = create_trgb(0, 0xFF, 0, 0);
}
