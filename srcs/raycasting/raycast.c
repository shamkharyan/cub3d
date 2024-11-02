/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:03:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/02 23:00:56 by shamkharyan      ###   ########.fr       */
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

static void set_start_values(t_game *g)
{
    g->mlx_win = mlx_new_window(g->mlx, SCREEN_W, SCREEN_H, "cub3d");
    g->screen_buff.img = mlx_new_image(g->mlx, SCREEN_W, SCREEN_H);
    g->screen_buff.addr = mlx_get_data_addr(g->screen_buff.img,
        &g->screen_buff.bits_per_pixel, &g->screen_buff.line_length, &g->screen_buff.endian);
    g->ray.pos.x = g->player.x;
	g->ray.pos.y = g->player.y;
	g->ray.plane.x = 0;
	g->ray.plane.y = 0;
	g->ray.dir.x = 0;
	g->ray.dir.y = 0;
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
		g->ray.cameraX = 2 * x / (double) SCREEN_W - 1;
        g->ray.rayDir.x = g->ray.dir.x + g->ray.plane.x * g->ray.cameraX;
        g->ray.rayDir.y = g->ray.dir.y + g->ray.plane.y * g->ray.cameraX;
        g->ray.map.x = (int) g->ray.pos.x;
        g->ray.map.y = (int) g->ray.pos.y;

        g->ray.deltaDist.x = ternary(g->ray.rayDir.x == 0, 1e30, fabs(1 / g->ray.rayDir.x));
        g->ray.deltaDist.y = ternary(g->ray.rayDir.y == 0, 1e30, fabs(1 / g->ray.rayDir.y));
		g->ray.hit = 0;
        if (g->ray.rayDir.x < 0)
		{
        g->ray.step.x = -1;
        g->ray.sideDist.x = (g->ray.pos.x - g->ray.map.x) * g->ray.deltaDist.x;
        }
		else
		{
            g->ray.step.x = 1;
            g->ray.sideDist.x = (g->ray.map.x + 1.0 - g->ray.pos.x) * g->ray.deltaDist.x;
        }
        if (g->ray.rayDir.y < 0)
		{
            g->ray.step.y = -1;
            g->ray.sideDist.y = (g->ray.pos.y - g->ray.map.y) * g->ray.deltaDist.y;
        }
		else
		{
            g->ray.step.y = 1;
            g->ray.sideDist.y = (g->ray.map.y + 1.0 - g->ray.pos.y) * g->ray.deltaDist.y;
        }
        while (g->ray.hit == 0)
		{
            if (g->ray.sideDist.x < g->ray.sideDist.y)
		    {
                g->ray.sideDist.x += g->ray.deltaDist.x;
                g->ray.map.x += g->ray.step.x;
                g->ray.side = 0;
            }
			else
			{
                g->ray.sideDist.y += g->ray.deltaDist.y;
                g->ray.map.y += g->ray.step.y;
                g->ray.side = 1;
            }
        	if (g->map[g->ray.map.y][g->ray.map.x] == '1')
				g->ray.hit = 1;
        }
        if (g->ray.side == 0)
		    g->ray.perpWallDist = g->ray.sideDist.x - g->ray.deltaDist.x;
        else
			g->ray.perpWallDist = g->ray.sideDist.y - g->ray.deltaDist.y;
        g->ray.lineHeight = (int)(SCREEN_H / g->ray.perpWallDist);

        g->ray.drawStart = -g->ray.lineHeight / 2 + SCREEN_H / 2;
        if (g->ray.drawStart < 0)
		    g->ray.drawStart = 0;
        g->ray.drawEnd = g->ray.lineHeight / 2 + SCREEN_H / 2;
        if (g->ray.drawEnd >= SCREEN_H)
		g->ray.drawEnd = SCREEN_H - 1;
    
        //textures
        if (g->ray.side == 1)
            g->ray.texNum = ternary(g->ray.rayDir.y > 0, 1, 0);
        else
            g->ray.texNum = ternary(g->ray.rayDir.x > 0, 2, 3);
        if (g->ray.side == 0)
            g->ray.wallX = g->ray.pos.y + g->ray.perpWallDist * g->ray.rayDir.y;
        else
            g->ray.wallX = g->ray.pos.x + g->ray.perpWallDist * g->ray.rayDir.x;
        g->ray.wallX -= floor(g->ray.wallX);
        g->ray.tex.x = (int)(g->ray.wallX * (double)(g->walls[g->ray.texNum].width));
        if ((g->ray.side == 0 && g->ray.rayDir.x > 0) || (g->ray.side == 1 && g->ray.rayDir.y < 0))
            g->ray.tex.x = g->walls[g->ray.texNum].width - g->ray.tex.x - 1;

        y = g->ray.drawStart - 1;
        while (++y < g->ray.drawEnd)
        {
            g->ray.tex.y = (int)(((y - SCREEN_H / 2 + g->ray.lineHeight / 2) * g->walls[g->ray.texNum].height) / g->ray.lineHeight);
            g->ray.color = get_texture_color(&g->walls[g->ray.texNum], g->ray.tex.x, g->ray.tex.y);
            my_mlx_pixel_put(&g->screen_buff, x, y, g->ray.color);
        }
    }
    mlx_put_image_to_window(g->mlx, g->mlx_win, g->screen_buff.img, 0, 0);
    return (0);
}

void	start(t_game *g)
{
	set_start_values(g);
    set_directions(g);
    mlx_loop_hook(g->mlx, draw_scene, g);
    mlx_hook(g->mlx_win, 17, 0, exit_game, g);
    mlx_hook(g->mlx_win, 2, 1L << 0, movement, g);
    mlx_loop(g->mlx);
}