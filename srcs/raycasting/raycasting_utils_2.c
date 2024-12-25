/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:00:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 18:37:42 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *g)
{
	g->player.pos.x = g->start_pos.x + 0.5;
	g->player.pos.y = g->start_pos.y + 0.5;
	if (g->map[g->start_pos.y][g->start_pos.x] == 'N')
	{
		g->player.dir.y = -1;
		g->player.plane.x = 0.66;
	}
	else if (g->map[g->start_pos.y][g->start_pos.x] == 'S')
	{
		g->player.dir.y = 1;
		g->player.plane.x = -0.66;
	}
	else if (g->map[g->start_pos.y][g->start_pos.x] == 'E')
	{
		g->player.dir.x = 1;
		g->player.plane.y = 0.66;
	}
	else if (g->map[g->start_pos.y][g->start_pos.x] == 'W')
	{
		g->player.dir.x = -1;
		g->player.plane.y = -0.66;
	}
	g->map[g->start_pos.y][g->start_pos.x] = '0';
}

void	init_game(t_game *g)
{
	g->mlx_win = mlx_new_window(g->mlx, SCREEN_W, SCREEN_H, "cub3d");
	g->screen_buff.img = mlx_new_image(g->mlx, SCREEN_W, SCREEN_H);
	g->screen_buff.addr = mlx_get_data_addr(g->screen_buff.img,
			&g->screen_buff.bits_per_pixel,
			&g->screen_buff.line_length, &g->screen_buff.endian);
	g->prev_mouse_x = SCREEN_W / 2;
	init_player(g);
}

void	setup_dda_x(t_game *g)
{
	g->ray.delta_dist.x = ternary(g->ray.ray_dir.x == 0,
			1e30, fabs(1 / g->ray.ray_dir.x));
	if (g->ray.ray_dir.x < 0)
	{
		g->ray.step.x = -1;
		g->ray.side_dist.x = (g->player.pos.x - g->ray.map.x)
			* g->ray.delta_dist.x;
	}
	else
	{
		g->ray.step.x = 1;
		g->ray.side_dist.x = (g->ray.map.x + 1.0 - g->player.pos.x)
			* g->ray.delta_dist.x;
	}
}

void	setup_dda_y(t_game *g)
{
	g->ray.delta_dist.y = ternary(g->ray.ray_dir.y == 0,
			1e30, fabs(1 / g->ray.ray_dir.y));
	if (g->ray.ray_dir.y < 0)
	{
		g->ray.step.y = -1;
		g->ray.side_dist.y = (g->player.pos.y - g->ray.map.y)
			* g->ray.delta_dist.y;
	}
	else
	{
		g->ray.step.y = 1;
		g->ray.side_dist.y = (g->ray.map.y + 1.0 - g->player.pos.y)
			* g->ray.delta_dist.y;
	}
}

void	clean_scene(t_game *g)
{
	if (g->screen_buff.img != NULL)
		mlx_destroy_image(g->mlx, g->screen_buff.img);
	g->screen_buff.img = mlx_new_image(g->mlx, SCREEN_W, SCREEN_H);
	g->screen_buff.addr = mlx_get_data_addr(g->screen_buff.img,
			&g->screen_buff.bits_per_pixel,
			&g->screen_buff.line_length, &g->screen_buff.endian);
}
