/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:03:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 16:15:06 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void set_directions(t_game *g)
{
    if (g->map[g->player.y][g->player.x] == 'N')
    {
        g->ray.dir.y = -1;
        g->ray.plane.x = 0.66;
    }
    else if (g->map[g->player.y][g->player.x] == 'S')
    {
        g->ray.dir.y = 1;
        g->ray.plane.x = -0.66;
    }
    else if (g->map[g->player.y][g->player.x] == 'E')
    {
        g->ray.dir.x = 1;
        g->ray.plane.y = 0.66;
    }
    else if (g->map[g->player.y][g->player.x] == 'W')
    {
        g->ray.dir.x = -1;
        g->ray.plane.y = -0.66;
    }
    g->map[g->player.y][g->player.x] = '0';
}

static void init_game(t_game *g)
{
    g->mlx_win = mlx_new_window(g->mlx, SCREEN_W, SCREEN_H, "cub3d");
    g->screen_buff.img = mlx_new_image(g->mlx, SCREEN_W, SCREEN_H);
    g->screen_buff.addr = mlx_get_data_addr(g->screen_buff.img,
        &g->screen_buff.bits_per_pixel, &g->screen_buff.line_length, &g->screen_buff.endian);
    g->ray.pos.x = g->player.x + 0.5;
	g->ray.pos.y = g->player.y + 0.5;
	g->ray.plane.x = 0;
	g->ray.plane.y = 0;
	g->ray.dir.x = 0;
	g->ray.dir.y = 0;
	g->ray.prev_mouse_x = SCREEN_W / 2;
	set_directions(g);
}

void	clean_scene(t_game *g)
{
	if (g->screen_buff.img != NULL)
		mlx_destroy_image(g->mlx, g->screen_buff.img);
	g->screen_buff.img = mlx_new_image(g->mlx, SCREEN_W, SCREEN_H);
    g->screen_buff.addr = mlx_get_data_addr(g->screen_buff.img,
        &g->screen_buff.bits_per_pixel, &g->screen_buff.line_length, &g->screen_buff.endian);
}

int    draw_scene(t_game *g)
{
    int x;
    int y;

    x = -1;
    while (++x < SCREEN_W)
	{
		g->ray.camera_x = 2 * x / (double) SCREEN_W - 1;
        g->ray.ray_dir.x = g->ray.dir.x + g->ray.plane.x * g->ray.camera_x;
        g->ray.ray_dir.y = g->ray.dir.y + g->ray.plane.y * g->ray.camera_x;
        g->ray.map.x = (int) g->ray.pos.x;
        g->ray.map.y = (int) g->ray.pos.y;

        g->ray.delta_dist.x = ternary(g->ray.ray_dir.x == 0, 1e30, fabs(1 / g->ray.ray_dir.x));
        g->ray.delta_dist.y = ternary(g->ray.ray_dir.y == 0, 1e30, fabs(1 / g->ray.ray_dir.y));
		g->ray.hit = 0;
        if (g->ray.ray_dir.x < 0)
		{
        	g->ray.step.x = -1;
        	g->ray.side_dist.x = (g->ray.pos.x - g->ray.map.x) * g->ray.delta_dist.x;
        }
		else
		{
            g->ray.step.x = 1;
            g->ray.side_dist.x = (g->ray.map.x + 1.0 - g->ray.pos.x) * g->ray.delta_dist.x;
        }
        if (g->ray.ray_dir.y < 0)
		{
            g->ray.step.y = -1;
            g->ray.side_dist.y = (g->ray.pos.y - g->ray.map.y) * g->ray.delta_dist.y;
        }
		else
		{
            g->ray.step.y = 1;
            g->ray.side_dist.y = (g->ray.map.y + 1.0 - g->ray.pos.y) * g->ray.delta_dist.y;
        }
        while (g->ray.hit == 0)
		{
            if (g->ray.side_dist.x < g->ray.side_dist.y)
		    {
                g->ray.side_dist.x += g->ray.delta_dist.x;
                g->ray.map.x += g->ray.step.x;
                g->ray.side = 0;
            }
			else
			{
                g->ray.side_dist.y += g->ray.delta_dist.y;
                g->ray.map.y += g->ray.step.y;
                g->ray.side = 1;
            }
        	if (g->map[g->ray.map.y][g->ray.map.x] == '1')
				g->ray.hit = 1;
        }
        if (g->ray.side == 0)
		    g->ray.perp_wall_dist = g->ray.side_dist.x - g->ray.delta_dist.x;
        else
			g->ray.perp_wall_dist = g->ray.side_dist.y - g->ray.delta_dist.y;
        g->ray.line_height = (int)(SCREEN_H / g->ray.perp_wall_dist);

        g->ray.draw_start = -g->ray.line_height / 2 + SCREEN_H / 2;
        if (g->ray.draw_start < 0)
		    g->ray.draw_start = 0;
        g->ray.draw_end = g->ray.line_height / 2 + SCREEN_H / 2;
        if (g->ray.draw_end >= SCREEN_H)
		g->ray.draw_end = SCREEN_H - 1;

        //textures
        if (g->ray.side == 1)
            g->ray.tex_num = ternary(g->ray.ray_dir.y > 0, 1, 0);
        else
            g->ray.tex_num = ternary(g->ray.ray_dir.x > 0, 2, 3);
        if (g->ray.side == 0)
            g->ray.wall_x = g->ray.pos.y + g->ray.perp_wall_dist * g->ray.ray_dir.y;
        else
            g->ray.wall_x = g->ray.pos.x + g->ray.perp_wall_dist * g->ray.ray_dir.x;
        g->ray.wall_x -= floor(g->ray.wall_x);
        g->ray.tex.x = (int)(g->ray.wall_x * (double)(g->walls[g->ray.tex_num].width));
        if ((g->ray.side == 0 && g->ray.ray_dir.x > 0) || (g->ray.side == 1 && g->ray.ray_dir.y < 0))
            g->ray.tex.x = g->walls[g->ray.tex_num].width - g->ray.tex.x - 1;

        y = -1;
        while (++y < g->ray.draw_start)
            my_mlx_pixel_put(&g->screen_buff, x, y, g->colors[0]);

        y = g->ray.draw_start - 1;
        while (++y < g->ray.draw_end)
        {
            g->ray.tex.y = (int)(((y - SCREEN_H / 2 + g->ray.line_height / 2) * g->walls[g->ray.tex_num].height) / g->ray.line_height);
            g->ray.color = get_texture_color(&g->walls[g->ray.tex_num], g->ray.tex.x, g->ray.tex.y);
            my_mlx_pixel_put(&g->screen_buff, x, y, g->ray.color);
        }

        y = g->ray.draw_end;
        while (++y < SCREEN_H)
            my_mlx_pixel_put(&g->screen_buff, x, y, g->colors[1]);
    }
    draw_minimap(g);
    mlx_put_image_to_window(g->mlx, g->mlx_win, g->screen_buff.img, 0, 0);
    return (0);
}

void	start(t_game *g)
{
	init_game(g);
	init_minimap(g);
	mlx_hook(g->mlx_win, 6, 0, mouse_rotate, g);
    mlx_loop_hook(g->mlx, draw_scene, g);
    mlx_hook(g->mlx_win, 17, 0, exit_game, g);
    mlx_hook(g->mlx_win, 2, 1L << 0, movement, g);
    mlx_loop(g->mlx);
}
