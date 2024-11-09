/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:06:57 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/09 16:04:36 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_msg(const char *err)
{
	write(2, "Error: ", 7);
	write(2, err, ft_strlen(err));
}

void	game_init(t_game *g)
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
	g->img_height = TEXTURE_H;
	g->img_width = TEXTURE_W;
	g->map_height = 0;
	g->map_width = 0;
}

double	ternary(int condition, double t, double f)
{
	if (condition)
		return (t);
	return (f);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

