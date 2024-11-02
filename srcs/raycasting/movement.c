/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:04:57 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/11/02 16:49:35 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *g)
{
	if (g->map[(int) (g->ray.pos.y + g->ray.dir.y * MOVE_SPEED)][(int) g->ray.pos.x] == '0')
		g->ray.pos.x += g->ray.dir.x * MOVE_SPEED;
    if (g->map[(int) g->ray.pos.y][(int) (g->ray.pos.x + g->ray.dir.x * MOVE_SPEED)] == '0')
		g->ray.pos.y += g->ray.dir.y * MOVE_SPEED;
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
		move(g);
	else if (keycode == KEY_S)
		printf("DOWN\n");
	else if (keycode == KEY_A)
		printf("LEFT\n");
	else if (keycode == KEY_D)
		printf("RIGHT\n");
	else if (keycode == KEY_ESC)
		exit_game(g);
	else
		printf("%d\n", keycode);
	return (0);
}
