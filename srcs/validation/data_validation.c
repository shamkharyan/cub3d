/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:54:18 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/02 21:24:45 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_commas(char *color)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (color[++i] != '\0')
		if (color[i] == ',')
			++count;
	return (count == 2);
}

static int	check_rgb(char *color)
{
	int	rgb;

	if (ft_strlen(color) > 3)
		return (0);
	rgb = ft_atoi(color);
	if (rgb >= 0 && rgb <= 255)
		return (1);
	return (0);
}

static int	check_colors(t_game *g)
{
	char	**tokens[2];
	int		i;
	int		j;

	if (!check_commas(g->data_path[F]) || !check_commas(g->data_path[C]))
		return (0);
	tokens[F - 4] = ft_split(g->data_path[F], ',');
	tokens[C - 4] = ft_split(g->data_path[C], ',');
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
			if (!check_rgb(tokens[i][j]))
				return (0);
	}
	g->colors[C - 4].r = ft_atoi(tokens[F - 4][0]);
	g->colors[C - 4].g = ft_atoi(tokens[F - 4][1]);
	g->colors[C - 4].b = ft_atoi(tokens[F - 4][2]);
	g->colors[F - 4].r = ft_atoi(tokens[F - 4][0]);
	g->colors[C - 4].g = ft_atoi(tokens[F - 4][1]);
	g->colors[C - 4].b = ft_atoi(tokens[F - 4][2]);
	free_split(tokens[0]);
	free_split(tokens[1]);
	return (1);
}

static int	check_xpm(t_game *g)
{
	int	i;
	
	g->mlx = mlx_init();
	g->walls[NO].img = xpm2img(g, g->data_path[NO]);
	if (g->walls[NO].img == NULL)
		return (0);
	g->walls[SO].img = xpm2img(g, g->data_path[SO]);
	if (g->walls[SO].img == NULL)
		return (0);
	g->walls[EA].img = xpm2img(g, g->data_path[EA]);
	if (g->walls[EA].img == NULL)
		return (0);
	g->walls[WE].img = xpm2img(g, g->data_path[WE]);
	if (g->walls[WE].img == NULL)
		return (0);
	i = -1;
	while (++i < 4)
		g->walls[i].addr = mlx_get_data_addr(g->walls[i].img, &g->walls[i].bits_per_pixel,
			&g->walls[i].line_length, &g->walls[i].endian);
	return (1);
}

int	check_data(t_game *g)
{
	if (!check_colors(g))
		return (err_msg("Wrong color format.\n"), 0);
	if (!check_xpm(g))
		return (err_msg("Can't parse images.\n"), 0);
	return (1);
}
