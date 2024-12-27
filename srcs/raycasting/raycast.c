/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:03:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/27 15:52:53 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_perp_wall_dist(t_game *g)
{
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
}

static void	setup_textures(t_game *g)
{
	if (g->ray.side == 1)
		g->ray.tex_ind = ternary(g->ray.ray_dir.y > 0, SO, NO);
	else
		g->ray.tex_ind = ternary(g->ray.ray_dir.x > 0, WE, EA);
	if (g->ray.side == 0)
		g->ray.wall_x = g->player.pos.y
			+ g->ray.perp_wall_dist * g->ray.ray_dir.y;
	else
		g->ray.wall_x = g->player.pos.x
			+ g->ray.perp_wall_dist * g->ray.ray_dir.x;
	g->ray.wall_x -= floor(g->ray.wall_x);
	g->ray.tex_pos.x = g->ray.wall_x * g->walls[g->ray.tex_ind].width;
	if ((g->ray.side == 0 && g->ray.ray_dir.x > 0)
		|| (g->ray.side == 1 && g->ray.ray_dir.y < 0))
		g->ray.tex_pos.x = g->walls[g->ray.tex_ind].width
			- g->ray.tex_pos.x - 1;
}

static void	draw_vline(t_game *g, int x)
{
	int			line_height;
	int			y;
	t_vector2i	draw_pos;

	line_height = (int)(SCREEN_H / g->ray.perp_wall_dist);
	draw_pos.x = -line_height / 2 + SCREEN_H / 2;
	if (draw_pos.x < 0)
		draw_pos.x = 0;
	draw_pos.y = line_height / 2 + SCREEN_H / 2;
	if (draw_pos.y >= SCREEN_H)
		draw_pos.y = SCREEN_H - 1;
	y = -1;
	while (++y < draw_pos.x)
		my_mlx_pixel_put(&g->screen_buff, x, y, g->colors[0]);
	y = draw_pos.x - 1;
	while (++y < draw_pos.y)
	{
		g->ray.tex_pos.y = (int)(((y - SCREEN_H / 2 + line_height / 2)
					* g->walls[g->ray.tex_ind].height) / line_height);
		g->ray.color = get_tex_color(&g->walls[g->ray.tex_ind], g->ray.tex_pos);
		my_mlx_pixel_put(&g->screen_buff, x, y, g->ray.color);
	}
	y = draw_pos.y;
	while (++y < SCREEN_H)
		my_mlx_pixel_put(&g->screen_buff, x, y, g->colors[1]);
}

int	draw_scene(t_game *g)
{
	int			x;
	double		camera_x;

	x = -1;
	while (++x < SCREEN_W)
	{
		camera_x = 2 * x / (double) SCREEN_W - 1;
		g->ray.ray_dir.x = g->player.dir.x + g->player.plane.x * camera_x;
		g->ray.ray_dir.y = g->player.dir.y + g->player.plane.y * camera_x;
		g->ray.map.x = (int) g->player.pos.x;
		g->ray.map.y = (int) g->player.pos.y;
		g->ray.hit = 0;
		setup_dda_x(g);
		setup_dda_y(g);
		calculate_perp_wall_dist(g);
		setup_textures(g);
		draw_vline(g, x);
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
