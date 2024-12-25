/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:09:15 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/12/25 16:04:21 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_game *g)
{
	t_vector2i	start1;
	t_vector2i	start2;
	t_vector2i	size1;
	t_vector2i	size2;

	start1 = g->minimap.offset;
	size1.x = g->minimap.size.x + 2 * g->minimap.border_width;
	size1.y = g->minimap.size.y + 2 * g->minimap.border_width;
	start2.x = start1.x + g->minimap.border_width;
	start2.y = start1.y + g->minimap.border_width;
	size2 = g->minimap.size;
	draw_rectangle(g, start1, size1, g->minimap.border_color);
	draw_rectangle(g, start2, size2, g->minimap.void_color);
}

static void	draw_minimap_rect(t_game *g, int x, int y)
{
	t_vector2i	rect_pos;
	t_vector2i	rect_size;

	rect_size.x = g->minimap.scale;
	rect_size.y = g->minimap.scale;
	rect_pos.x = g->minimap.offset.x
		+ (x - g->ray.pos.x) * g->minimap.scale + g->minimap.size.x / 2;
	rect_pos.y = g->minimap.offset.y
		+ (y - g->ray.pos.y) * g->minimap.scale + g->minimap.size.y / 2;
	if (rect_pos.x >= g->minimap.offset.x && rect_pos.y >= g->minimap.offset.y
		&& rect_pos.x < g->minimap.offset.x + g->minimap.size.x
		- 2 * g->minimap.border_width
		&& rect_pos.y < g->minimap.offset.y + g->minimap.size.y
		- 2 * g->minimap.border_width)
	{
		if (g->map[y][x] == '1')
			draw_rectangle(g, rect_pos, rect_size, g->minimap.wall_color);
		else if (g->map[y][x] == '0')
			draw_rectangle(g, rect_pos, rect_size, g->minimap.ground_color);
	}
}

static void	draw_player(t_game *g)
{
	t_vector2i	player_pos;

	player_pos.x = g->minimap.offset.x
		+ g->minimap.size.x / 2.0 - g->minimap.scale / 2.0;
	player_pos.y = g->minimap.offset.y
		+ g->minimap.size.y / 2.0 - g->minimap.scale / 2.0;
	draw_circle(g, player_pos, g->minimap.scale / 2, g->minimap.player_color);
}

void	draw_minimap(t_game *g)
{
	int			x;
	int			y;

	draw_background(g);
	y = -1;
	while (++y < g->map_height)
	{
		x = -1;
		while (++x < g->map_width)
			draw_minimap_rect(g, x, y);
	}
	draw_player(g);
}
