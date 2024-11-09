/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:29:00 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/09 16:04:45 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


