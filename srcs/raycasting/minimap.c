/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:09:15 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/11/20 23:26:38 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_rectangle(t_game *g, t_icoord c, int width, int height, int color)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            my_mlx_pixel_put(&g->screen_buff, c.x + j, c.y + i, color);
    }
}

static void draw_circle(t_game *g, t_icoord c, int radius, int color)
{
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++)
            if (i * i + j * j <= radius * radius)
                my_mlx_pixel_put(&g->screen_buff, c.x + j, c.y + i, color);
}

static void draw_line(t_game *g, t_icoord c1, t_icoord c2, int color)
{
    int dx = abs(c2.x - c1.x), dy = abs(c2.y - c1.y);
    int sx = c1.x < c2.x ? 1 : -1;
    int sy = c1.y < c2.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        my_mlx_pixel_put(&g->screen_buff, c1.x, c1.y, color);
        if (c1.x == c2.x && c1.y == c2.y) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; c1.x += sx; }
        if (e2 < dy) { err += dx; c1.y += sy; }
    }
}

void draw_minimap(t_game *g) {
    int x, y;
    int scale = 10;

    int map_width = g->map_width;
    int map_height = g->map_height;

    int minimap_size = 200;

    int map_x_offset = 10;
    int map_y_offset = 10;

    for (y = map_y_offset - 1; y < map_y_offset + minimap_size + 1; y++) {
        for (x = map_x_offset - 1; x < map_x_offset + minimap_size + 1; x++) {
            if (x < map_x_offset || x >= map_x_offset + minimap_size || y < map_y_offset || y >= map_y_offset + minimap_size)
                my_mlx_pixel_put(&g->screen_buff, x, y, 0x000000);
        }
    }

    for (y = 0; y < map_height; y++) {
        for (x = 0; x < map_width; x++) {
            int rect_x = map_x_offset + (x - (int)g->ray.pos.x) * scale + minimap_size / 2;
            int rect_y = map_y_offset + (y - (int)g->ray.pos.y) * scale + minimap_size / 2;

            if (rect_x >= map_x_offset && rect_x < map_x_offset + minimap_size &&
                rect_y >= map_y_offset && rect_y < map_y_offset + minimap_size) {
                if (g->map[y][x] == '1') {
                    draw_rectangle(g, (t_icoord){rect_x, rect_y}, scale, scale, 0xFFFFFF);
                } else if (g->map[y][x] == '0') {  
                    draw_rectangle(g, (t_icoord){rect_x, rect_y}, scale, scale, 0x000000);
                }
            }
        }
    }

    int player_x = map_x_offset + (g->ray.pos.x - (int)g->ray.pos.x) * scale + minimap_size / 2;
    int player_y = map_y_offset + (g->ray.pos.y - (int)g->ray.pos.y) * scale + minimap_size / 2;
    if (player_x >= map_x_offset && player_x < map_x_offset + minimap_size &&
        player_y >= map_y_offset && player_y < map_y_offset + minimap_size) {
        draw_circle(g, (t_icoord){player_x, player_y}, scale / 4, 0xFF0000); 
    }

    int line_length = scale;
    int dir_x = player_x + cos(atan2(g->ray.dir.y, g->ray.dir.x)) * line_length;
    int dir_y = player_y + sin(atan2(g->ray.dir.y, g->ray.dir.x)) * line_length;
    if (dir_x >= map_x_offset && dir_x < map_x_offset + minimap_size &&
        dir_y >= map_y_offset && dir_y < map_y_offset + minimap_size) {
        draw_line(g, (t_icoord){player_x, player_y}, (t_icoord){dir_x, dir_y}, 0x00FF00);
    }
}
