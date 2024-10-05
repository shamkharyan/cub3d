/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:03:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/05 16:17:07 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_data *data, t_game *g)
{
	t_coord curr;
	int	i;
	int	j;

	i = -1;
	while (++i < g->map_height)
	{
		j = -1;
		while (++j < g->map_width)
		{
			curr.y = i * IMG_HEIGHT + 1;
			curr.x = j * IMG_WIDTH + 1;
			if (g->map[i][j] == '1')
				draw_square(data, curr, IMG_WIDTH - 1, 0x00FFFFFF);
			else
				draw_square(data, curr, IMG_WIDTH - 1, 0x00888888);
		}
	}
}

void	draw_player(t_data *data, t_game *g)
{
	(void) g;
	draw_square(data, g->player, 5, 0x0000FF);
}

int	player_movement(int keycode, t_game *g)
{
	draw_square(g->img_data, g->player, 5, 0x00888888);
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
		--g->player.y;
	else if (keycode == KEY_S)
		++g->player.y;
	else if (keycode == KEY_A)
		--g->player.x;
	else if (keycode == KEY_D)
		++g->player.x;
	draw_map(g->img_data, g);
	draw_player(g->img_data, g);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->img_data->img, 0, 0);
	return (0);
}

void	start(t_game *g)
{
	t_coord c1;
	t_coord c2;

	c1.x = 20;
	c1.y = 20;
	c2.x = 50;
	c2.y = 30;

	g->mlx_win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	g->img_data->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->img_data->addr = mlx_get_data_addr(g->img_data->img, &g->img_data->bits_per_pixel, &g->img_data->line_length,
								&g->img_data->endian);
	draw_map(g->img_data, g);
	draw_player(g->img_data, g);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->img_data->img, 0, 0);
	mlx_key_hook(g->mlx_win, player_movement, g);
	mlx_loop(g->mlx);
}


