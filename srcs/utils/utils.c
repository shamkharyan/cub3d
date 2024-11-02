/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:06:57 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/02 16:08:50 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_msg(const char *err)
{
	int x;
	x = write(2, "Error: ", 7);
	x = write(2, err, ft_strlen(err));
	x += 0;
}

void	game_init(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		g->img[i] = NULL;
		g->data_path[i] = NULL;
	}
	g->data_path[4] = NULL;
	g->data_path[5] = NULL;
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
