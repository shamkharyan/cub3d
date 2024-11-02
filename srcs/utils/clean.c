/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:29:00 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/02 16:10:47 by shamkharyan      ###   ########.fr       */
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
		free(g->data_path[i]);
		g->data_path[i] = NULL;
	}
}

void	clean_mlx(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (g->img[i] != NULL)
		{
			mlx_destroy_image(g->mlx, g->img[i]);
			g->img[i] = NULL;
		}
	}
	if (g->screen_buff.img != NULL)
	{
		mlx_destroy_image(g->mlx, g->screen_buff.img);
		g->screen_buff.img = NULL;
		g->screen_buff.addr = NULL;
	}
}


