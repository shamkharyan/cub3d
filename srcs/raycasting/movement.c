/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:04:57 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/11/09 18:23:53 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *g, int direction)
{
	t_dcoord	move_dir;

	if (direction == NO)
	{
		move_dir.x = g->ray.dir.x * MOVE_SPEED;
		move_dir.y = g->ray.dir.y * MOVE_SPEED;
	}
	if (direction == SO)
	{
		move_dir.x = -g->ray.dir.x * MOVE_SPEED;
		move_dir.y = -g->ray.dir.y * MOVE_SPEED;
	}
	else if (direction == WE)
	{
		move_dir.x = -g->ray.dir.y * MOVE_SPEED;
		move_dir.y = g->ray.dir.x * MOVE_SPEED;
	}
	else if (direction == EA)
	{
		move_dir.x = g->ray.dir.y * MOVE_SPEED;
		move_dir.y = -g->ray.dir.x * MOVE_SPEED;
	}
	if ((int)(g->ray.pos.y + move_dir.y) >= 0 &&
		(int)(g->ray.pos.y + move_dir.y) < g->map_height &&
		g->map[(int)(g->ray.pos.y + move_dir.y)][(int)(g->ray.pos.x)] == '0')
		g->ray.pos.y += move_dir.y;
	if ((int)(g->ray.pos.x + move_dir.x) >= 0 &&
		(int)(g->ray.pos.x + move_dir.x) < g->map_width &&
		g->map[(int)(g->ray.pos.y)][(int)(g->ray.pos.x + move_dir.x)] == '0')
		g->ray.pos.x += move_dir.x;
}

void	rotate(t_game *g, int direction, double ag)
{
	double	old_dir_x;
	double	old_plane_x;

	if (direction == EA)
	{
		old_dir_x = g->ray.dir.x;
		g->ray.dir.x = g->ray.dir.x * cos(-ag) - g->ray.dir.y * sin(-ag);
		g->ray.dir.y = old_dir_x * sin(-ag) + g->ray.dir.y * cos(-ag);
		old_plane_x = g->ray.plane.x;
		g->ray.plane.x = g->ray.plane.x * cos(-ag) - g->ray.plane.y * sin(-ag);
		g->ray.plane.y = old_plane_x * sin(-ag) + g->ray.plane.y * cos(-ag);
	}
	else if (direction == WE)
	{
		old_dir_x = g->ray.dir.x;
		g->ray.dir.x = g->ray.dir.x * cos(ag) - g->ray.dir.y * sin(ag);
		g->ray.dir.y = old_dir_x * sin(ag) + g->ray.dir.y * cos(ag);
		old_plane_x = g->ray.plane.x;
		g->ray.plane.x = g->ray.plane.x * cos(ag) - g->ray.plane.y * sin(ag);
		g->ray.plane.y = old_plane_x * sin(ag) + g->ray.plane.y * cos(ag);
	}
}

int	exit_game(t_game *g)
{
	clean_data(g);
	clean_map(g);
	clean_mlx(g);
	exit(EXIT_SUCCESS);
	return (0);
}

int	mouse_rotate(int x, int y, t_game *g)
{
	double	rot_speed;

	(void) y;
	rot_speed = (double)(abs(x - g->ray.prev_mouse_x) * MOUSE_ROT_SPEED);
	if (x > g->ray.prev_mouse_x)
		rotate(g, WE, rot_speed);
	else
		rotate(g, EA, rot_speed);
	g->ray.prev_mouse_x = x;
	return (0);
}

int	movement(int keycode, t_game *g)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move(g, NO);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move(g, SO);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move(g, EA);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move(g, WE);
	else if (keycode == KEY_ESC)
		exit_game(g);
	clean_scene(g);
	draw_scene(g);
	return (0);
}
