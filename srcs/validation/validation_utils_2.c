/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:28:54 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 20:58:56 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_msg(const char *err)
{
	write(2, "Error: ", 7);
	write(2, err, ft_strlen(err));
}

void	setup_game(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		g->walls[i].img = NULL;
		g->walls[i].addr = NULL;
		g->walls[i].width = TEXTURE_W;
		g->walls[i].height = TEXTURE_H;
		g->map_data[i] = NULL;
	}
	g->map_data[4] = NULL;
	g->map_data[5] = NULL;
	g->mlx = NULL;
	g->mlx_win = NULL;
	g->map = NULL;
	g->screen_buff.img = NULL;
	g->screen_buff.addr = NULL;
	g->tex_height = TEXTURE_H;
	g->tex_width = TEXTURE_W;
	g->map_height = 0;
	g->map_width = 0;
}

void	clean_map(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->map_height)
	{
		free(g->map[i]);
		g->map[i] = NULL;
	}
	free(g->map);
	g->map = NULL;
}

void	clean_data(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		free(g->map_data[i]);
		g->map_data[i] = NULL;
	}
}

void	clean_mlx(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (g->walls[i].img != NULL)
		{
			mlx_destroy_image(g->mlx, g->walls[i].img);
			g->walls[i].img = NULL;
			g->walls[i].addr = NULL;
		}
	}
	if (g->screen_buff.img != NULL)
	{
		mlx_destroy_image(g->mlx, g->screen_buff.img);
		g->screen_buff.img = NULL;
		g->screen_buff.addr = NULL;
	}
}
