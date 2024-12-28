/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:04:57 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/12/27 18:19:55 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *g, int direction)
{
	t_vector2f	move_dir;

	if (direction == NO)
	{
		move_dir.x = g->player.dir.x * MOVE_SPEED;
		move_dir.y = g->player.dir.y * MOVE_SPEED;
	}
	if (direction == SO)
	{
		move_dir.x = -g->player.dir.x * MOVE_SPEED;
		move_dir.y = -g->player.dir.y * MOVE_SPEED;
	}
	else if (direction == WE)
	{
		move_dir.x = -g->player.dir.y * MOVE_SPEED;
		move_dir.y = g->player.dir.x * MOVE_SPEED;
	}
	else if (direction == EA)
	{
		move_dir.x = g->player.dir.y * MOVE_SPEED;
		move_dir.y = -g->player.dir.x * MOVE_SPEED;
	}
	set_new_pos(g, move_dir);
}

void	rotate(t_game *g, int direction, double ag)
{
	double	old_dir_x;
	double	old_plane_x;

	if (direction == EA)
	{
		old_dir_x = g->player.dir.x;
		g->player.dir.x = g->player.dir.x * cos(-ag)
			- g->player.dir.y * sin(-ag);
		g->player.dir.y = old_dir_x * sin(-ag) + g->player.dir.y * cos(-ag);
		old_plane_x = g->player.plane.x;
		g->player.plane.x = g->player.plane.x * cos(-ag)
			- g->player.plane.y * sin(-ag);
		g->player.plane.y = old_plane_x * sin(-ag)
			+ g->player.plane.y * cos(-ag);
	}
	else if (direction == WE)
	{
		old_dir_x = g->player.dir.x;
		g->player.dir.x = g->player.dir.x * cos(ag) - g->player.dir.y * sin(ag);
		g->player.dir.y = old_dir_x * sin(ag) + g->player.dir.y * cos(ag);
		old_plane_x = g->player.plane.x;
		g->player.plane.x = g->player.plane.x * cos(ag)
			- g->player.plane.y * sin(ag);
		g->player.plane.y = old_plane_x * sin(ag) + g->player.plane.y * cos(ag);
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
	rot_speed = (double)(abs(x - g->prev_mouse_x) * MOUSE_ROT_SPEED);
	if (x > g->prev_mouse_x)
		rotate(g, WE, rot_speed);
	else
		rotate(g, EA, rot_speed);
	g->prev_mouse_x = x;
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
	else if (keycode == KEY_Q)
		rotate(g, EA, ROT_SPEED);
	else if (keycode == KEY_E)
		rotate(g, WE, ROT_SPEED);
	else if (keycode == KEY_ESC)
		exit_game(g);
	clean_scene(g);
	draw_scene(g);
	return (0);
}
