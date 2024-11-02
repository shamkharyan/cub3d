/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:04:57 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/11/02 18:20:32 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *g, int direction)
{
	if (direction == NO)
	{
		if (g->map[(int) (g->ray.pos.y + g->ray.dir.y * MOVE_SPEED)][(int) g->ray.pos.x] == '0')
			g->ray.pos.x += g->ray.dir.x * MOVE_SPEED;
		if (g->map[(int) g->ray.pos.y][(int) (g->ray.pos.x + g->ray.dir.x * MOVE_SPEED)] == '0')
			g->ray.pos.y += g->ray.dir.y * MOVE_SPEED;
	}
	else if (direction == SO)
	{
		if (g->map[(int) (g->ray.pos.y - g->ray.dir.y * MOVE_SPEED)][(int) g->ray.pos.x] == '0')
			g->ray.pos.x -= g->ray.dir.x * MOVE_SPEED;
		if (g->map[(int) g->ray.pos.y][(int) (g->ray.pos.x - g->ray.dir.x * MOVE_SPEED)] == '0')
			g->ray.pos.y -= g->ray.dir.y * MOVE_SPEED;
	}
}

void	rotate(t_game *g, int direction)
{
	double oldDirX;
	double oldPlaneX;

	if (direction == EA)
	{
		oldDirX = g->ray.dir.x;
		g->ray.dir.x = g->ray.dir.x * cos(-ROT_SPEED) - g->ray.dir.y * sin(-ROT_SPEED);
    	g->ray.dir.y = oldDirX * sin(-ROT_SPEED) + g->ray.dir.y * cos(-ROT_SPEED);
    	oldPlaneX = g->ray.plane.x;
    	g->ray.plane.x = g->ray.plane.x * cos(-ROT_SPEED) - g->ray.plane.y * sin(-ROT_SPEED);
    	g->ray.plane.y = oldPlaneX * sin(-ROT_SPEED) + g->ray.plane.y * cos(-ROT_SPEED);
	}
	else if (direction == WE)
	{
		oldDirX = g->ray.dir.x;
		g->ray.dir.x = g->ray.dir.x * cos(ROT_SPEED) - g->ray.dir.y * sin(ROT_SPEED);
    	g->ray.dir.y = oldDirX * sin(ROT_SPEED) + g->ray.dir.y * cos(ROT_SPEED);
    	oldPlaneX = g->ray.plane.x;
    	g->ray.plane.x = g->ray.plane.x * cos(ROT_SPEED) - g->ray.plane.y * sin(ROT_SPEED);
    	g->ray.plane.y = oldPlaneX * sin(ROT_SPEED) + g->ray.plane.y * cos(ROT_SPEED);
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

int	movement(int keycode, t_game *g)
{
	if (keycode == KEY_W)
		move(g, NO);
	else if (keycode == KEY_S)
		move(g, SO);
	else if (keycode == KEY_A)
		rotate(g, EA);
	else if (keycode == KEY_D)
		rotate(g, WE);
	else if (keycode == KEY_ESC)
		exit_game(g);
	else
		printf("%d\n", keycode);
	clean_scene(g);
	draw_scene(g);
	return (0);
}
